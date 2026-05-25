//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to read GPU manual fan tuning settings with ADLX. This is the
//! Rust counterpart of `Samples/C/GPUTuning/ManualFanTuning` (read-only view).
//!
//! Manual fan tuning is reached through the GPU tuning services: check support,
//! `GetManualFanTuning` (returns an `IADLXInterface`), then
//! `QueryInterface("IADLXManualFanTuning")`. This sample only reads ranges and
//! current values; it does not modify the fan curve.

use std::os::raw::c_void;

use amd_adlx::*;

/// Prints the fan tuning ranges and current settings.
///
/// # Safety
/// `tuning` must be a valid `IADLXManualFanTuning` interface pointer.
unsafe fn show_fan_tuning(tuning: *mut IADLXManualFanTuning) {
    let v = &*(*tuning).pVtbl;

    println!("\n  === Fan tuning ranges ===");
    let mut speed = ADLX_IntRange { minValue: 0, maxValue: 0, step: 0 };
    let mut temp = ADLX_IntRange { minValue: 0, maxValue: 0, step: 0 };
    if adlx_succeeded((v.GetFanTuningRanges)(tuning, &mut speed, &mut temp)) {
        println!("\tFan speed range: {}% .. {}%", speed.minValue, speed.maxValue);
        println!(
            "\tTemperature range: {}\u{00B0}C .. {}\u{00B0}C",
            temp.minValue, temp.maxValue
        );
    }

    println!("\n  === Current fan settings ===");
    let mut supported: adlx_bool = 0;

    // Zero RPM.
    if adlx_succeeded((v.IsSupportedZeroRPM)(tuning, &mut supported)) {
        println!("\tZero RPM supported: {}", supported != 0);
        if supported != 0 {
            let mut is_set: adlx_bool = 0;
            if adlx_succeeded((v.GetZeroRPMState)(tuning, &mut is_set)) {
                println!("\tZero RPM enabled: {}", is_set != 0);
            }
        }
    }

    // Minimum acoustic limit.
    if adlx_succeeded((v.IsSupportedMinAcousticLimit)(tuning, &mut supported)) {
        println!("\tMin acoustic limit supported: {}", supported != 0);
        if supported != 0 {
            let mut range = ADLX_IntRange { minValue: 0, maxValue: 0, step: 0 };
            if adlx_succeeded((v.GetMinAcousticLimitRange)(tuning, &mut range)) {
                println!(
                    "\tMin acoustic limit range: {} .. {} MHz",
                    range.minValue, range.maxValue
                );
            }
            let mut value: adlx_int = 0;
            if adlx_succeeded((v.GetMinAcousticLimit)(tuning, &mut value)) {
                println!("\tMin acoustic limit: {} MHz", value);
            }
        }
    }

    // Minimum fan speed.
    if adlx_succeeded((v.IsSupportedMinFanSpeed)(tuning, &mut supported)) {
        println!("\tMin fan speed supported: {}", supported != 0);
        if supported != 0 {
            let mut range = ADLX_IntRange { minValue: 0, maxValue: 0, step: 0 };
            if adlx_succeeded((v.GetMinFanSpeedRange)(tuning, &mut range)) {
                println!("\tMin fan speed range: {}% .. {}%", range.minValue, range.maxValue);
            }
            let mut value: adlx_int = 0;
            if adlx_succeeded((v.GetMinFanSpeed)(tuning, &mut value)) {
                println!("\tMin fan speed: {}%", value);
            }
        }
    }

    // Target fan speed.
    if adlx_succeeded((v.IsSupportedTargetFanSpeed)(tuning, &mut supported)) {
        println!("\tTarget fan speed supported: {}", supported != 0);
        if supported != 0 {
            let mut range = ADLX_IntRange { minValue: 0, maxValue: 0, step: 0 };
            if adlx_succeeded((v.GetTargetFanSpeedRange)(tuning, &mut range)) {
                println!(
                    "\tTarget fan speed range: {}% .. {}%",
                    range.minValue, range.maxValue
                );
            }
            let mut value: adlx_int = 0;
            if adlx_succeeded((v.GetTargetFanSpeed)(tuning, &mut value)) {
                println!("\tTarget fan speed: {}%", value);
            }
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

        // Get the GPU tuning services.
        let mut tuning_svc: *mut IADLXGPUTuningServices = std::ptr::null_mut();
        if !adlx_succeeded((sys_vtbl.GetGPUTuningServices)(sys, &mut tuning_svc)) {
            wait_and_exit("Get GPU tuning services failed");
            return;
        }
        let svc_vtbl = &*(*tuning_svc).pVtbl;

        // Get the GPU list and use the first GPU.
        let mut gpus: *mut IADLXGPUList = std::ptr::null_mut();
        if adlx_succeeded((sys_vtbl.GetGPUs)(sys, &mut gpus)) {
            let list_vtbl = &*(*gpus).pVtbl;
            let mut gpu: *mut IADLXGPU = std::ptr::null_mut();
            if adlx_succeeded((list_vtbl.At_GPUList)(gpus, (list_vtbl.Begin)(gpus), &mut gpu)) {
                // Check manual fan tuning support.
                let mut supported: adlx_bool = 0;
                let ok = adlx_succeeded((svc_vtbl.IsSupportedManualFanTuning)(
                    tuning_svc,
                    gpu,
                    &mut supported,
                ));
                if ok && supported != 0 {
                    // Get the manual fan tuning IADLXInterface, then QueryInterface.
                    let mut ifc: *mut IADLXInterface = std::ptr::null_mut();
                    if adlx_succeeded((svc_vtbl.GetManualFanTuning)(tuning_svc, gpu, &mut ifc))
                        && !ifc.is_null()
                    {
                        let ifc_vtbl = &*(*ifc).pVtbl;
                        let iid = iid::wide("IADLXManualFanTuning");
                        let mut tuning_ptr: *mut c_void = std::ptr::null_mut();
                        if adlx_succeeded((ifc_vtbl.QueryInterface)(ifc, iid.as_ptr(), &mut tuning_ptr))
                            && !tuning_ptr.is_null()
                        {
                            let tuning = tuning_ptr as *mut IADLXManualFanTuning;
                            show_fan_tuning(tuning);
                            ((&*(*tuning).pVtbl).Release)(tuning);
                        }
                        (ifc_vtbl.Release)(ifc);
                    }
                } else {
                    println!("This GPU does not support manual fan tuning");
                }

                ((&*(*gpu).pVtbl).Release)(gpu);
            }
            (list_vtbl.Release)(gpus);
        }

        (svc_vtbl.Release)(tuning_svc);
    }

    // ADLX is terminated and the library is unloaded when `helper` is dropped.
    drop(helper);
    println!("Destroy ADLX finished");

    pause();
}
