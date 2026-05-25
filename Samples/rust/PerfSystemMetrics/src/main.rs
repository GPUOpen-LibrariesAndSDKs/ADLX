//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to read system performance metrics with ADLX. This is the Rust
//! counterpart of `Samples/C/PerformanceMonitoring/PerfSystemMetrics`.
//!
//! It prints the supported system metric ranges and the current system metric
//! values (CPU usage, system RAM, SmartShift), each guarded by its support query.

use amd_adlx::*;

/// Prints the supported system metric ranges.
///
/// # Safety
/// `support` must be a valid `IADLXSystemMetricsSupport` interface pointer.
unsafe fn show_system_metrics_range(support: *mut IADLXSystemMetricsSupport) {
    let v = &*(*support).pVtbl;
    println!("\n  === System metrics range ===");

    let mut min = 0;
    let mut max = 0;

    let ranges: &[(&str, unsafe extern "system" fn(
        *mut IADLXSystemMetricsSupport,
        *mut adlx_int,
        *mut adlx_int,
    ) -> ADLX_RESULT, &str)] = &[
        ("CPU usage", v.GetCPUUsageRange, "%"),
        ("System RAM", v.GetSystemRAMRange, "MB"),
        ("SmartShift", v.GetSmartShiftRange, ""),
    ];

    for (label, getter, unit) in ranges {
        if adlx_succeeded(getter(support, &mut min, &mut max)) {
            println!("\tThe {} range between {}{} and {}{}", label, min, unit, max, unit);
        } else {
            println!("\t{} range not supported", label);
        }
    }
}

/// Prints the current system metric values, each guarded by its support query.
///
/// # Safety
/// `support` and `metrics` must be valid interface pointers.
unsafe fn show_current_system_metrics(
    support: *mut IADLXSystemMetricsSupport,
    metrics: *mut IADLXSystemMetrics,
) {
    let s = &*(*support).pVtbl;
    let m = &*(*metrics).pVtbl;
    println!("\n  === Current system metrics ===");

    let mut timestamp: adlx_int64 = 0;
    if adlx_succeeded((m.TimeStamp)(metrics, &mut timestamp)) {
        println!("\tThe system time stamp is: {} ms", timestamp);
    }

    let mut supported: adlx_bool = 0;

    if adlx_succeeded((s.IsSupportedCPUUsage)(support, &mut supported)) && supported != 0 {
        let mut data: adlx_double = 0.0;
        if adlx_succeeded((m.CPUUsage)(metrics, &mut data)) {
            println!("\tThe CPU usage is: {:.1}%", data);
        }
    }

    if adlx_succeeded((s.IsSupportedSystemRAM)(support, &mut supported)) && supported != 0 {
        let mut data: adlx_int = 0;
        if adlx_succeeded((m.SystemRAM)(metrics, &mut data)) {
            println!("\tThe system RAM is: {} MB", data);
        }
    }

    if adlx_succeeded((s.IsSupportedSmartShift)(support, &mut supported)) && supported != 0 {
        let mut data: adlx_int = 0;
        if adlx_succeeded((m.SmartShift)(metrics, &mut data)) {
            println!("\tThe SmartShift is: {}", data);
        }
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

        // Get supported system metrics and print the ranges.
        let mut support: *mut IADLXSystemMetricsSupport = std::ptr::null_mut();
        if adlx_succeeded((perf_vtbl.GetSupportedSystemMetrics)(perf, &mut support)) {
            show_system_metrics_range(support);

            // Get the current system metrics and print the values.
            let mut metrics: *mut IADLXSystemMetrics = std::ptr::null_mut();
            if adlx_succeeded((perf_vtbl.GetCurrentSystemMetrics)(perf, &mut metrics)) {
                show_current_system_metrics(support, metrics);
                ((&*(*metrics).pVtbl).Release)(metrics);
            }

            ((&*(*support).pVtbl).Release)(support);
        }

        (perf_vtbl.Release)(perf);
    }

    // ADLX is terminated and the library is unloaded when `helper` is dropped.
    drop(helper);
    println!("Destroy ADLX finished");

    pause();
}
