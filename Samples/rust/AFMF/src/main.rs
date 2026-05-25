//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to query AMD Fluid Motion Frames (AFMF) with ADLX. This is the
//! Rust counterpart of `Samples/C/3DGraphics/AFMF`.
//!
//! AFMF is a system-wide feature exposed by `IADLX3DSettingsServices1`, obtained by
//! calling `QueryInterface("IADLX3DSettingsServices1")` on the base 3D settings
//! services.

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

        let mut svc: *mut IADLX3DSettingsServices = std::ptr::null_mut();
        if !adlx_succeeded((sys_vtbl.Get3DSettingsServices)(sys, &mut svc)) {
            wait_and_exit("Failed to get 3DSettings services");
            return;
        }
        let svc_vtbl = &*(*svc).pVtbl;

        // AFMF lives on IADLX3DSettingsServices1.
        let iid = iid::wide("IADLX3DSettingsServices1");
        let mut svc1_ptr: *mut c_void = std::ptr::null_mut();
        if adlx_succeeded((svc_vtbl.QueryInterface)(svc, iid.as_ptr(), &mut svc1_ptr))
            && !svc1_ptr.is_null()
        {
            let svc1 = svc1_ptr as *mut IADLX3DSettingsServices1;
            let svc1_vtbl = &*(*svc1).pVtbl;

            let mut afmf: *mut IADLX3DAMDFluidMotionFrames = std::ptr::null_mut();
            if adlx_succeeded((svc1_vtbl.GetAMDFluidMotionFrames)(svc1, &mut afmf)) {
                let f = &*(*afmf).pVtbl;
                println!("\n  === AMD Fluid Motion Frames ===");
                let mut supported: adlx_bool = 0;
                if adlx_succeeded((f.IsSupported)(afmf, &mut supported)) {
                    println!("\tIs supported: {}", supported != 0);
                }
                let mut enabled: adlx_bool = 0;
                if adlx_succeeded((f.IsEnabled)(afmf, &mut enabled)) {
                    println!("\tIs enabled: {}", enabled != 0);
                }
                (f.Release)(afmf);
            } else {
                println!("Failed to get AFMF interface");
            }

            (svc1_vtbl.Release)(svc1);
        } else {
            println!("IADLX3DSettingsServices1 (AFMF) not available");
        }

        (svc_vtbl.Release)(svc);
    }

    drop(helper);
    println!("Destroy ADLX finished");
    pause();
}
