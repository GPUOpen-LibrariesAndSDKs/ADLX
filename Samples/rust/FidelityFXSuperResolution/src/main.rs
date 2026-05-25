//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to query AMD FidelityFX Super Resolution (FSR) with ADLX. This
//! is the Rust counterpart of `Samples/C/3DGraphics/FidelityFXSuperResolution`.
//!
//! FSR is exposed by `IADLX3DSettingsServices3`
//! (`QueryInterface("IADLX3DSettingsServices3")`).

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

        // FSR lives on IADLX3DSettingsServices3.
        let iid = iid::wide("IADLX3DSettingsServices3");
        let mut svc3_ptr: *mut c_void = std::ptr::null_mut();
        if !adlx_succeeded((svc_vtbl.QueryInterface)(svc, iid.as_ptr(), &mut svc3_ptr))
            || svc3_ptr.is_null()
        {
            (svc_vtbl.Release)(svc);
            wait_and_exit("IADLX3DSettingsServices3 (FSR) not available");
            return;
        }
        let svc3 = svc3_ptr as *mut IADLX3DSettingsServices3;
        let svc3_vtbl = &*(*svc3).pVtbl;

        // Use the first GPU.
        let mut gpus: *mut IADLXGPUList = std::ptr::null_mut();
        if adlx_succeeded((sys_vtbl.GetGPUs)(sys, &mut gpus)) {
            let list_vtbl = &*(*gpus).pVtbl;
            let mut gpu: *mut IADLXGPU = std::ptr::null_mut();
            if adlx_succeeded((list_vtbl.At_GPUList)(gpus, (list_vtbl.Begin)(gpus), &mut gpu)) {
                let mut fsr: *mut IADLX3DFidelityFXSuperResolution = std::ptr::null_mut();
                if adlx_succeeded((svc3_vtbl.GetFidelityFXSuperResolution)(svc3, gpu, &mut fsr)) {
                    let f = &*(*fsr).pVtbl;
                    println!("\n  === FidelityFX Super Resolution ===");
                    let mut supported: adlx_bool = 0;
                    if adlx_succeeded((f.IsSupported)(fsr, &mut supported)) {
                        println!("\tIs supported: {}", supported != 0);
                    }
                    let mut enabled: adlx_bool = 0;
                    if adlx_succeeded((f.IsEnabled)(fsr, &mut enabled)) {
                        println!("\tIs enabled: {}", enabled != 0);
                    }
                    (f.Release)(fsr);
                } else {
                    println!("Failed to get FSR interface");
                }
                ((&*(*gpu).pVtbl).Release)(gpu);
            }
            (list_vtbl.Release)(gpus);
        }

        (svc3_vtbl.Release)(svc3);
        (svc_vtbl.Release)(svc);
    }

    drop(helper);
    println!("Destroy ADLX finished");
    pause();
}
