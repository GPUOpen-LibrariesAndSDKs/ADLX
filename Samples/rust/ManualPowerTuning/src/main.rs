//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to read GPU manual power tuning with ADLX. This is the Rust
//! counterpart of `Samples/C/GPUTuning/ManualPowerTuning` (read-only view).
//!
//! Reached through the GPU tuning services: check support, `GetManualPowerTuning`
//! (returns an `IADLXInterface`), then `QueryInterface("IADLXManualPowerTuning")`.

use std::os::raw::c_void;

use amd_adlx::*;

/// Prints the power and TDC limit ranges and current values.
///
/// # Safety
/// `tuning` must be a valid `IADLXManualPowerTuning` interface pointer.
unsafe fn show_power_tuning(tuning: *mut IADLXManualPowerTuning) {
    let v = &*(*tuning).pVtbl;
    println!("\n  === Manual power tuning ===");

    let mut range = ADLX_IntRange { minValue: 0, maxValue: 0, step: 0 };
    if adlx_succeeded((v.GetPowerLimitRange)(tuning, &mut range)) {
        println!("\tPower limit range: {} .. {} %", range.minValue, range.maxValue);
    }
    let mut value: adlx_int = 0;
    if adlx_succeeded((v.GetPowerLimit)(tuning, &mut value)) {
        println!("\tPower limit: {} %", value);
    }

    let mut supported: adlx_bool = 0;
    if adlx_succeeded((v.IsSupportedTDCLimit)(tuning, &mut supported)) {
        println!("\tTDC limit supported: {}", supported != 0);
        if supported != 0 {
            let mut trange = ADLX_IntRange { minValue: 0, maxValue: 0, step: 0 };
            if adlx_succeeded((v.GetTDCLimitRange)(tuning, &mut trange)) {
                println!("\tTDC limit range: {} .. {} %", trange.minValue, trange.maxValue);
            }
            let mut tval: adlx_int = 0;
            if adlx_succeeded((v.GetTDCLimit)(tuning, &mut tval)) {
                println!("\tTDC limit: {} %", tval);
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

        let mut tuning_svc: *mut IADLXGPUTuningServices = std::ptr::null_mut();
        if !adlx_succeeded((sys_vtbl.GetGPUTuningServices)(sys, &mut tuning_svc)) {
            wait_and_exit("Get GPU tuning services failed");
            return;
        }
        let svc_vtbl = &*(*tuning_svc).pVtbl;

        let mut gpus: *mut IADLXGPUList = std::ptr::null_mut();
        if adlx_succeeded((sys_vtbl.GetGPUs)(sys, &mut gpus)) {
            let list_vtbl = &*(*gpus).pVtbl;
            let mut gpu: *mut IADLXGPU = std::ptr::null_mut();
            if adlx_succeeded((list_vtbl.At_GPUList)(gpus, (list_vtbl.Begin)(gpus), &mut gpu)) {
                let mut supported: adlx_bool = 0;
                let ok = adlx_succeeded((svc_vtbl.IsSupportedManualPowerTuning)(
                    tuning_svc,
                    gpu,
                    &mut supported,
                ));
                if ok && supported != 0 {
                    let mut ifc: *mut IADLXInterface = std::ptr::null_mut();
                    if adlx_succeeded((svc_vtbl.GetManualPowerTuning)(tuning_svc, gpu, &mut ifc))
                        && !ifc.is_null()
                    {
                        let ifc_vtbl = &*(*ifc).pVtbl;
                        let iid = iid::wide("IADLXManualPowerTuning");
                        let mut tuning_ptr: *mut c_void = std::ptr::null_mut();
                        if adlx_succeeded((ifc_vtbl.QueryInterface)(ifc, iid.as_ptr(), &mut tuning_ptr))
                            && !tuning_ptr.is_null()
                        {
                            let tuning = tuning_ptr as *mut IADLXManualPowerTuning;
                            show_power_tuning(tuning);
                            ((&*(*tuning).pVtbl).Release)(tuning);
                        }
                        (ifc_vtbl.Release)(ifc);
                    }
                } else {
                    println!("This GPU does not support manual power tuning");
                }

                ((&*(*gpu).pVtbl).Release)(gpu);
            }
            (list_vtbl.Release)(gpus);
        }

        (svc_vtbl.Release)(tuning_svc);
    }

    drop(helper);
    println!("Destroy ADLX finished");
    pause();
}
