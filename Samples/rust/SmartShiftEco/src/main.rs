//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to query AMD SmartShift Eco with ADLX. This is the Rust
//! counterpart of `Samples/C/PowerTuning/SmartShiftEco`.
//!
//! SmartShift Eco is exposed by `IADLXPowerTuningServices1`, reached via
//! `IADLXSystem1` -> power tuning services -> `QueryInterface("IADLXPowerTuningServices1")`.

use std::os::raw::c_void;

use amd_adlx::*;

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

        // Power tuning lives on IADLXSystem1.
        let iid_sys1 = iid::wide("IADLXSystem1");
        let mut sys1_ptr: *mut c_void = std::ptr::null_mut();
        if !adlx_succeeded((sys_vtbl.QueryInterface)(sys, iid_sys1.as_ptr(), &mut sys1_ptr))
            || sys1_ptr.is_null()
        {
            wait_and_exit("IADLXSystem1 (power tuning) not available");
            return;
        }
        let sys1 = sys1_ptr as *mut IADLXSystem1;
        let sys1_vtbl = &*(*sys1).pVtbl;

        let mut power: *mut IADLXPowerTuningServices = std::ptr::null_mut();
        if adlx_succeeded((sys1_vtbl.GetPowerTuningServices)(sys1, &mut power)) {
            let power_vtbl = &*(*power).pVtbl;

            // SmartShift Eco is on IADLXPowerTuningServices1.
            let iid = iid::wide("IADLXPowerTuningServices1");
            let mut power1_ptr: *mut c_void = std::ptr::null_mut();
            if adlx_succeeded((power_vtbl.QueryInterface)(power, iid.as_ptr(), &mut power1_ptr))
                && !power1_ptr.is_null()
            {
                let power1 = power1_ptr as *mut IADLXPowerTuningServices1;
                let power1_vtbl = &*(*power1).pVtbl;

                let mut eco: *mut IADLXSmartShiftEco = std::ptr::null_mut();
                if adlx_succeeded((power1_vtbl.GetSmartShiftEco)(power1, &mut eco)) {
                    let s = &*(*eco).pVtbl;
                    println!("\n  === SmartShift Eco ===");
                    let mut supported: adlx_bool = 0;
                    if adlx_succeeded((s.IsSupported)(eco, &mut supported)) {
                        println!("\tIs supported: {}", supported != 0);
                    }
                    let mut enabled: adlx_bool = 0;
                    if adlx_succeeded((s.IsEnabled)(eco, &mut enabled)) {
                        println!("\tIs enabled: {}", enabled != 0);
                    }
                    let mut inactive: adlx_bool = 0;
                    if adlx_succeeded((s.IsInactive)(eco, &mut inactive)) {
                        println!("\tIs inactive: {}", inactive != 0);
                        if inactive != 0 {
                            let mut reason: i32 = 0;
                            if adlx_succeeded((s.GetInactiveReason)(eco, &mut reason)) {
                                println!("\tInactive reason (enum value): {}", reason);
                            }
                        }
                    }
                    (s.Release)(eco);
                } else {
                    println!("Failed to get SmartShift Eco interface");
                }

                (power1_vtbl.Release)(power1);
            } else {
                println!("IADLXPowerTuningServices1 (SmartShift Eco) not available");
            }

            (power_vtbl.Release)(power);
        } else {
            println!("Failed to get power tuning services");
        }

        (sys1_vtbl.Release)(sys1);
    }

    drop(helper);
    println!("Destroy ADLX finished");
    pause();
}
