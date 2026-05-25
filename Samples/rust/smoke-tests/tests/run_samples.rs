//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Smoke tests for the ADLX Rust samples.
//!
//! Every sample is a small console program that initializes ADLX, prints some
//! information, and then waits for the user to press Enter before exiting. These
//! tests build all sample binaries and run each one with an empty (closed) standard
//! input so the `pause()` prompts return immediately, then assert that each process
//! exits successfully.
//!
//! The samples are written to fail gracefully when the ADLX runtime is unavailable
//! (they print a message and return `0`), so these tests pass on machines without an
//! AMD GPU as well as on machines with one. They verify that no sample panics,
//! aborts, or hangs.
//!
//! To guarantee *every* sample is covered, the set of binaries under test is taken
//! directly from Cargo (via `cargo build --message-format=json`) rather than by
//! scanning the target directory, and it is cross-checked against the sample crates
//! declared in the workspace `members` list. A sample that fails to build, is
//! missing from the workspace, or produces no binary makes the test fail loudly.

#![cfg(windows)]

use std::collections::BTreeSet;
use std::path::{Path, PathBuf};
use std::process::{Command, Stdio};
use std::thread;
use std::time::{Duration, Instant};

/// Per-sample time budget. Samples do a small amount of work and then exit once
/// stdin reaches EOF, so this is a generous safety net against a hang.
const SAMPLE_TIMEOUT: Duration = Duration::from_secs(30);

/// Workspace members that are libraries, not samples, and therefore produce no
/// binary to smoke test.
const NON_SAMPLE_MEMBERS: &[&str] = &["amd-adlx", "smoke-tests"];

/// Returns the Cargo workspace root (the parent of this crate's directory).
fn workspace_root() -> PathBuf {
    Path::new(env!("CARGO_MANIFEST_DIR"))
        .parent()
        .expect("smoke-tests crate must live inside the workspace")
        .to_path_buf()
}

/// Builds every sample binary in the workspace and returns the exact executables
/// Cargo produced, parsed from its JSON build messages.
///
/// Using Cargo's own artifact messages (rather than scanning `target/<profile>`)
/// means the test sees precisely the binaries for the current sample crates: no
/// stale executables from renamed or deleted samples, and nothing missed.
fn build_sample_binaries(root: &Path) -> Vec<PathBuf> {
    let mut cmd = Command::new(env!("CARGO"));
    cmd.current_dir(root)
        .arg("build")
        .arg("--bins")
        .arg("--message-format=json")
        .stderr(Stdio::inherit());
    if !cfg!(debug_assertions) {
        cmd.arg("--release");
    }

    let output = cmd.output().expect("failed to invoke `cargo build --bins`");
    assert!(
        output.status.success(),
        "`cargo build --bins` failed (see stderr above)"
    );

    let stdout = String::from_utf8_lossy(&output.stdout);
    let mut bins: Vec<PathBuf> = stdout
        .lines()
        .filter_map(extract_executable)
        .map(PathBuf::from)
        .collect();
    bins.sort();
    bins.dedup();
    bins
}

/// Extracts the `"executable"` path from a single Cargo JSON message line, if the
/// message describes a built binary (the field is `null` for libraries).
///
/// This is a deliberately tiny, dependency-free JSON field reader: it finds the
/// `"executable":` key and decodes the following JSON string (handling `\\` and
/// `\"` escapes, which appear in Windows paths).
fn extract_executable(line: &str) -> Option<String> {
    const KEY: &str = "\"executable\":";
    let after = line.find(KEY)? + KEY.len();
    let rest = line[after..].trim_start();

    // Libraries and other non-binary artifacts report `"executable":null`.
    let mut chars = rest.strip_prefix('"')?.chars();
    let mut path = String::new();
    while let Some(c) = chars.next() {
        match c {
            '\\' => path.push(chars.next()?),
            '"' => return Some(path),
            other => path.push(other),
        }
    }
    None
}

/// Parses the sample crate names from the workspace `members` array in the root
/// `Cargo.toml`, excluding the non-sample library crates. Each sample crate sets its
/// binary name to the sample name, which matches its member directory, so these are
/// also the expected binary file stems.
fn expected_sample_names(root: &Path) -> BTreeSet<String> {
    let manifest =
        std::fs::read_to_string(root.join("Cargo.toml")).expect("read workspace Cargo.toml");

    let members_key = manifest
        .find("members")
        .expect("workspace Cargo.toml has a `members` key");
    let open = manifest[members_key..]
        .find('[')
        .map(|i| members_key + i)
        .expect("`members` is an array");
    let close = manifest[open..]
        .find(']')
        .map(|i| open + i)
        .expect("`members` array is closed");

    manifest[open + 1..close]
        .split(',')
        .map(|entry| entry.trim().trim_matches('"').trim())
        .filter(|entry| !entry.is_empty())
        .filter(|entry| !NON_SAMPLE_MEMBERS.contains(entry))
        // The binary name equals the last path component of the member entry.
        .map(|entry| entry.rsplit('/').next().unwrap_or(entry).to_string())
        .collect()
}

/// Runs a single executable with closed stdin and its output suppressed, killing it
/// if it exceeds [`SAMPLE_TIMEOUT`].
fn run_with_timeout(path: &Path) -> Result<std::process::ExitStatus, String> {
    let mut child = Command::new(path)
        .stdin(Stdio::null())
        .stdout(Stdio::null())
        .stderr(Stdio::null())
        .spawn()
        .map_err(|e| format!("spawn failed: {e}"))?;

    let start = Instant::now();
    loop {
        match child.try_wait() {
            Ok(Some(status)) => return Ok(status),
            Ok(None) => {
                if start.elapsed() > SAMPLE_TIMEOUT {
                    let _ = child.kill();
                    let _ = child.wait();
                    return Err(format!("timed out after {:?}", SAMPLE_TIMEOUT));
                }
                thread::sleep(Duration::from_millis(50));
            }
            Err(e) => return Err(format!("wait failed: {e}")),
        }
    }
}

#[test]
fn all_samples_build_and_exit_cleanly() {
    let root = workspace_root();

    let bins = build_sample_binaries(&root);
    assert!(!bins.is_empty(), "cargo produced no sample binaries");

    // Every sample declared in the workspace must have produced a binary. This is
    // what makes the test cover *all* samples: adding a sample crate to `members`
    // without it building here is a failure, not a silent skip.
    let expected = expected_sample_names(&root);
    let built: BTreeSet<String> = bins
        .iter()
        .map(|b| b.file_stem().unwrap_or_default().to_string_lossy().to_string())
        .collect();

    let missing: Vec<&String> = expected.difference(&built).collect();
    assert!(
        missing.is_empty(),
        "{} sample(s) declared in the workspace produced no binary: {:?}",
        missing.len(),
        missing
    );

    eprintln!(
        "smoke-testing {} sample binaries ({} expected from workspace members)",
        bins.len(),
        expected.len()
    );

    let mut failures = Vec::new();
    for bin in &bins {
        let name = bin
            .file_stem()
            .unwrap_or_default()
            .to_string_lossy()
            .to_string();
        match run_with_timeout(bin) {
            Ok(status) if status.success() => eprintln!("ok: {name}"),
            Ok(status) => failures.push(format!("{name}: exited with {status}")),
            Err(e) => failures.push(format!("{name}: {e}")),
        }
    }

    assert!(
        failures.is_empty(),
        "{} sample(s) failed:\n{}",
        failures.len(),
        failures.join("\n")
    );
}
