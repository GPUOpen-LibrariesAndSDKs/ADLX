# amd-adlx

Raw Rust FFI bindings for the [AMD ADLX](https://github.com/GPUOpen-LibrariesAndSDKs/ADLX)
C interface, plus a lightweight loader that initializes the ADLX runtime.

ADLX (AMD Device Library eXtra) is the modern API for configuring and monitoring
AMD Radeon GPUs and displays on Windows. This crate exposes its COM-like, vtable-based
C ABI to Rust and provides an `AdlxHelper` type that loads `amdadlx64.dll` /
`amdadlx32.dll` (installed with the AMD graphics driver) and hands out the
`IADLXSystem` interface.

## Status

This is a `-sys` style crate: it provides **raw, unsafe bindings**. Method calls go
through interface vtables, exactly like the ADLX C samples. A safe, idiomatic wrapper
is intentionally out of scope so the crate stays a thin, faithful mapping of the SDK.

The bindings currently cover the interfaces used by the ADLX Rust samples
(system, displays, GPUs, performance monitoring, logging, and 3D settings) and are
extended as more samples are ported.

## Platform

Windows only. The ADLX runtime is loaded dynamically at run time, so no import
library or SDK headers are needed to build against this crate. An AMD GPU with a
compatible driver is required at run time.

Build for the same architecture as the installed driver
(`x86_64-pc-windows-msvc` for the 64-bit driver).

## Example

```rust,no_run
use amd_adlx::*;

fn main() {
    // Load and initialize ADLX (terminated automatically on drop).
    let helper = AdlxHelper::new().expect("ADLX init failed");

    unsafe {
        let sys = helper.system_services();
        let sys_vtbl = &*(*sys).pVtbl;

        let mut services: *mut IADLXDisplayServices = std::ptr::null_mut();
        if adlx_succeeded((sys_vtbl.GetDisplaysServices)(sys, &mut services)) {
            let ds = &*(*services).pVtbl;
            let mut count: adlx_uint = 0;
            let _ = (ds.GetNumberOfDisplays)(services, &mut count);
            println!("Displays: {count}");
            (ds.Release)(services);
        }
    }
}
```

## Safety

All interface methods are `unsafe`. Callers must uphold the ADLX object lifetime and
reference-counting rules (`Acquire` / `Release`) and must not use interface pointers
after `AdlxHelper` is dropped (which terminates ADLX and unloads the library).

## License

Licensed under the MIT License, matching the public AMD ADLX SDK.
