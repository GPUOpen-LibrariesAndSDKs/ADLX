//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to query AMD Radeon Super Resolution (RSR) with ADLX. This is the
//! Rust counterpart of `Samples/C/3DGraphics/RSR`.
//!
//! RSR is a system-wide feature, so it is obtained from the 3D settings services
//! directly (no GPU argument).

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

        let mut svc: *mut IADLX3DSettingsServices = std::ptr::null_mut();
        if !adlx_succeeded((sys_vtbl.Get3DSettingsServices)(sys, &mut svc)) {
            wait_and_exit("Failed to get 3DSettings services");
            return;
        }
        let svc_vtbl = &*(*svc).pVtbl;

        let mut feature: *mut IADLX3DRadeonSuperResolution = std::ptr::null_mut();
        if adlx_succeeded((svc_vtbl.GetRadeonSuperResolution)(svc, &mut feature)) {
            let f = &*(*feature).pVtbl;
            println!("\n  === Radeon Super Resolution ===");
            let mut supported: adlx_bool = 0;
            if adlx_succeeded((f.IsSupported)(feature, &mut supported)) {
                println!("\tIs supported: {}", supported != 0);
            }
            let mut enabled: adlx_bool = 0;
            if adlx_succeeded((f.IsEnabled)(feature, &mut enabled)) {
                println!("\tIs enabled: {}", enabled != 0);
            }
            let mut range = ADLX_IntRange { minValue: 0, maxValue: 0, step: 0 };
            if adlx_succeeded((f.GetSharpnessRange)(feature, &mut range)) {
                println!("\tSharpness range: {} .. {}", range.minValue, range.maxValue);
            }
            let mut sharpness: adlx_int = 0;
            if adlx_succeeded((f.GetSharpness)(feature, &mut sharpness)) {
                println!("\tCurrent sharpness: {}", sharpness);
            }
            (f.Release)(feature);
        } else {
            println!("Failed to get RSR interface");
        }

        (svc_vtbl.Release)(svc);
    }

    drop(helper);
    println!("Destroy ADLX finished");
    pause();
}
