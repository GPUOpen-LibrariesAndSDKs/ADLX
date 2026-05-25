//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to query AMD SmartShift Max with ADLX. This is the Rust
//! counterpart of `Samples/C/PowerTuning/SmartShiftMax`.
//!
//! Power tuning is reached through `IADLXSystem1`, obtained by calling
//! `QueryInterface("IADLXSystem1")` on the base system interface.

use std::os::raw::c_void;

use amd_adlx::*;

fn bias_mode_str(mode: i32) -> &'static str {
    match mode {
        SSM_BIAS_AUTO => "Auto",
        SSM_BIAS_MANUAL => "Manual",
        _ => "Unknown",
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

        // Power tuning lives on IADLXSystem1; query it from the base system.
        let iid = iid::wide("IADLXSystem1");
        let mut sys1_ptr: *mut c_void = std::ptr::null_mut();
        if !adlx_succeeded((sys_vtbl.QueryInterface)(sys, iid.as_ptr(), &mut sys1_ptr))
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

            let mut ssm: *mut IADLXSmartShiftMax = std::ptr::null_mut();
            if adlx_succeeded((power_vtbl.GetSmartShiftMax)(power, &mut ssm)) {
                let s = &*(*ssm).pVtbl;
                println!("\n  === SmartShift Max ===");

                let mut supported: adlx_bool = 0;
                if adlx_succeeded((s.IsSupported)(ssm, &mut supported)) {
                    println!("\tIs supported: {}", supported != 0);
                }
                let mut mode: i32 = 0;
                if adlx_succeeded((s.GetBiasMode)(ssm, &mut mode)) {
                    println!("\tBias mode: {}", bias_mode_str(mode));
                }
                let mut range = ADLX_IntRange { minValue: 0, maxValue: 0, step: 0 };
                if adlx_succeeded((s.GetBiasRange)(ssm, &mut range)) {
                    println!("\tBias range: {} .. {}", range.minValue, range.maxValue);
                }
                let mut bias: adlx_int = 0;
                if adlx_succeeded((s.GetBias)(ssm, &mut bias)) {
                    println!("\tCurrent bias: {}", bias);
                }

                (s.Release)(ssm);
            } else {
                println!("Failed to get SmartShift Max interface");
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
