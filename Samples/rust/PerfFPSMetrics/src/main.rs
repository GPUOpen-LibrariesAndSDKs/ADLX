//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to read the FPS performance metric with ADLX. This is the Rust
//! counterpart of `Samples/C/PerformanceMonitoring/PerfFPSMetrics`.
//!
//! FPS is reported for the foreground 3D application; it is typically 0 when no
//! accelerated application is running.

use amd_adlx::*;

/// Prints the current FPS metric.
///
/// # Safety
/// `fps` must be a valid `IADLXFPS` interface pointer.
unsafe fn show_current_fps(fps: *mut IADLXFPS) {
    let v = &*(*fps).pVtbl;
    println!("\n  === Current FPS metric ===");

    let mut timestamp: adlx_int64 = 0;
    if adlx_succeeded((v.TimeStamp)(fps, &mut timestamp)) {
        println!("\tThe FPS time stamp is: {} ms", timestamp);
    }

    let mut data: adlx_int = 0;
    let res = (v.FPS)(fps, &mut data);
    if adlx_succeeded(res) {
        println!("\tThe current FPS is: {}", data);
    } else if res == ADLX_NOT_SUPPORTED {
        println!("\tFPS not supported (no accelerated application running)");
    }
}

fn pause() {
    use std::io::{Read, Write};
    print!("Press Enter to continue . . . ");
    let _ = std::io::stdout().flush();
    let _ = std::io::stdin().read(&mut [0u8]);
}

fn wait_and_exit(msg: &str) {
    if !msg.is_empty() {
        println!("{}", msg);
    }
    pause();
}

fn main() {
    // Initialize ADLX.
    let helper = match AdlxHelper::new() {
        Ok(helper) => helper,
        Err(_) => {
            wait_and_exit("ADLX initialization failed");
            return;
        }
    };

    unsafe {
        let sys = helper.system_services();
        let sys_vtbl = &*(*sys).pVtbl;

        // Get the performance monitoring services.
        let mut perf: *mut IADLXPerformanceMonitoringServices = std::ptr::null_mut();
        if !adlx_succeeded((sys_vtbl.GetPerformanceMonitoringServices)(sys, &mut perf)) {
            wait_and_exit("Get performance monitoring services failed");
            return;
        }
        let perf_vtbl = &*(*perf).pVtbl;

        // Get the current FPS metric.
        let mut fps: *mut IADLXFPS = std::ptr::null_mut();
        if adlx_succeeded((perf_vtbl.GetCurrentFPS)(perf, &mut fps)) {
            show_current_fps(fps);
            ((&*(*fps).pVtbl).Release)(fps);
        } else {
            println!("Get current FPS failed");
        }

        (perf_vtbl.Release)(perf);
    }

    // ADLX is terminated and the library is unloaded when `helper` is dropped.
    drop(helper);
    println!("Destroy ADLX finished");

    pause();
}
