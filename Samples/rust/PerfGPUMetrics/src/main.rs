//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to read GPU performance metrics with ADLX. This is the Rust
//! counterpart of `Samples/C/PerformanceMonitoring/PerfGPUMetrics`.
//!
//! It prints the supported GPU metric ranges and the current GPU metric values for
//! the first GPU. Each metric is guarded by its support query, matching the C sample.

use amd_adlx::*;

/// Prints the supported metric ranges for a GPU.
///
/// # Safety
/// `support` must be a valid `IADLXGPUMetricsSupport` interface pointer.
unsafe fn show_gpu_metrics_range(support: *mut IADLXGPUMetricsSupport) {
    let v = &*(*support).pVtbl;
    println!("\n  === GPU metrics range ===");

    let mut min = 0;
    let mut max = 0;

    let ranges: &[(&str, unsafe extern "system" fn(
        *mut IADLXGPUMetricsSupport,
        *mut adlx_int,
        *mut adlx_int,
    ) -> ADLX_RESULT, &str)] = &[
        ("GPU usage", v.GetGPUUsageRange, "%"),
        ("GPU clock speed", v.GetGPUClockSpeedRange, "MHz"),
        ("GPU VRAM clock speed", v.GetGPUVRAMClockSpeedRange, "MHz"),
        ("GPU temperature", v.GetGPUTemperatureRange, "\u{00B0}C"),
        ("GPU hotspot temperature", v.GetGPUHotspotTemperatureRange, "\u{00B0}C"),
        ("GPU power", v.GetGPUPowerRange, "W"),
        ("GPU fan speed", v.GetGPUFanSpeedRange, "RPM"),
        ("GPU VRAM", v.GetGPUVRAMRange, "MB"),
        ("GPU voltage", v.GetGPUVoltageRange, "mV"),
        ("GPU total board power", v.GetGPUTotalBoardPowerRange, "W"),
        ("GPU intake temperature", v.GetGPUIntakeTemperatureRange, "\u{00B0}C"),
    ];

    for (label, getter, unit) in ranges {
        let res = getter(support, &mut min, &mut max);
        if adlx_succeeded(res) {
            println!("\tThe {} range between {}{} and {}{}", label, min, unit, max, unit);
        } else {
            println!("\t{} range not supported", label);
        }
    }
}

/// Prints the current metric values for a GPU, each guarded by its support query.
///
/// # Safety
/// `support` and `metrics` must be valid interface pointers for the same GPU.
unsafe fn show_current_gpu_metrics(
    support: *mut IADLXGPUMetricsSupport,
    metrics: *mut IADLXGPUMetrics,
) {
    let s = &*(*support).pVtbl;
    let m = &*(*metrics).pVtbl;
    println!("\n  === Current GPU metrics ===");

    // TimeStamp is always available.
    let mut timestamp: adlx_int64 = 0;
    if adlx_succeeded((m.TimeStamp)(metrics, &mut timestamp)) {
        println!("\tThe GPU time stamp is: {} ms", timestamp);
    }

    let mut supported: adlx_bool = 0;

    if adlx_succeeded((s.IsSupportedGPUUsage)(support, &mut supported)) && supported != 0 {
        let mut data: adlx_double = 0.0;
        if adlx_succeeded((m.GPUUsage)(metrics, &mut data)) {
            println!("\tThe GPU usage is: {:.0}%", data);
        }
    }

    if adlx_succeeded((s.IsSupportedGPUClockSpeed)(support, &mut supported)) && supported != 0 {
        let mut data: adlx_int = 0;
        if adlx_succeeded((m.GPUClockSpeed)(metrics, &mut data)) {
            println!("\tThe GPU clock speed is: {} MHz", data);
        }
    }

    if adlx_succeeded((s.IsSupportedGPUVRAMClockSpeed)(support, &mut supported)) && supported != 0 {
        let mut data: adlx_int = 0;
        if adlx_succeeded((m.GPUVRAMClockSpeed)(metrics, &mut data)) {
            println!("\tThe GPU VRAM clock speed is: {} MHz", data);
        }
    }

    if adlx_succeeded((s.IsSupportedGPUTemperature)(support, &mut supported)) && supported != 0 {
        let mut data: adlx_double = 0.0;
        if adlx_succeeded((m.GPUTemperature)(metrics, &mut data)) {
            println!("\tThe GPU temperature is: {:.1}\u{00B0}C", data);
        }
    }

    if adlx_succeeded((s.IsSupportedGPUHotspotTemperature)(support, &mut supported)) && supported != 0
    {
        let mut data: adlx_double = 0.0;
        if adlx_succeeded((m.GPUHotspotTemperature)(metrics, &mut data)) {
            println!("\tThe GPU hotspot temperature is: {:.1}\u{00B0}C", data);
        }
    }

    if adlx_succeeded((s.IsSupportedGPUPower)(support, &mut supported)) && supported != 0 {
        let mut data: adlx_double = 0.0;
        if adlx_succeeded((m.GPUPower)(metrics, &mut data)) {
            println!("\tThe GPU power is: {:.3} W", data);
        }
    }

    if adlx_succeeded((s.IsSupportedGPUTotalBoardPower)(support, &mut supported)) && supported != 0 {
        let mut data: adlx_double = 0.0;
        if adlx_succeeded((m.GPUTotalBoardPower)(metrics, &mut data)) {
            println!("\tThe GPU total board power is: {:.3} W", data);
        }
    }

    if adlx_succeeded((s.IsSupportedGPUFanSpeed)(support, &mut supported)) && supported != 0 {
        let mut data: adlx_int = 0;
        if adlx_succeeded((m.GPUFanSpeed)(metrics, &mut data)) {
            println!("\tThe GPU fan speed is: {} RPM", data);
        }
    }

    if adlx_succeeded((s.IsSupportedGPUVRAM)(support, &mut supported)) && supported != 0 {
        let mut data: adlx_int = 0;
        if adlx_succeeded((m.GPUVRAM)(metrics, &mut data)) {
            println!("\tThe GPU VRAM is: {} MB", data);
        }
    }

    if adlx_succeeded((s.IsSupportedGPUVoltage)(support, &mut supported)) && supported != 0 {
        let mut data: adlx_int = 0;
        if adlx_succeeded((m.GPUVoltage)(metrics, &mut data)) {
            println!("\tThe GPU voltage is: {} mV", data);
        }
    }

    if adlx_succeeded((s.IsSupportedGPUIntakeTemperature)(support, &mut supported)) && supported != 0
    {
        let mut data: adlx_double = 0.0;
        if adlx_succeeded((m.GPUIntakeTemperature)(metrics, &mut data)) {
            println!("\tThe GPU intake temperature is: {:.1}\u{00B0}C", data);
        }
    }
}

fn wait_and_exit(msg: &str) {
    if !msg.is_empty() {
        println!("{}", msg);
    }
    pause();
}

fn pause() {
    use std::io::{Read, Write};
    print!("Press Enter to continue . . . ");
    let _ = std::io::stdout().flush();
    let _ = std::io::stdin().read(&mut [0u8]);
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

        // Get the GPU list and use the first GPU.
        let mut gpus: *mut IADLXGPUList = std::ptr::null_mut();
        if adlx_succeeded((sys_vtbl.GetGPUs)(sys, &mut gpus)) {
            let list_vtbl = &*(*gpus).pVtbl;
            let mut gpu: *mut IADLXGPU = std::ptr::null_mut();
            if adlx_succeeded((list_vtbl.At_GPUList)(gpus, (list_vtbl.Begin)(gpus), &mut gpu)) {
                // Get supported metrics for this GPU and print the ranges.
                let mut support: *mut IADLXGPUMetricsSupport = std::ptr::null_mut();
                if adlx_succeeded((perf_vtbl.GetSupportedGPUMetrics)(perf, gpu, &mut support)) {
                    show_gpu_metrics_range(support);

                    // Get the current metrics and print the values.
                    let mut metrics: *mut IADLXGPUMetrics = std::ptr::null_mut();
                    if adlx_succeeded((perf_vtbl.GetCurrentGPUMetrics)(perf, gpu, &mut metrics)) {
                        show_current_gpu_metrics(support, metrics);
                        ((&*(*metrics).pVtbl).Release)(metrics);
                    }

                    ((&*(*support).pVtbl).Release)(support);
                }

                ((&*(*gpu).pVtbl).Release)(gpu);
            }
            (list_vtbl.Release)(gpus);
        }

        (perf_vtbl.Release)(perf);
    }

    // ADLX is terminated and the library is unloaded when `helper` is dropped.
    drop(helper);
    println!("Destroy ADLX finished");

    pause();
}
