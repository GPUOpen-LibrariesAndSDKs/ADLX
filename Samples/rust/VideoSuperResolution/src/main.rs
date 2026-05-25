//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to query AMD Video Super Resolution with ADLX. This is the Rust
//! counterpart of `Samples/C/MultiMedia/VideoSuperResolution`.
//!
//! Multimedia services are reached through `IADLXSystem2`
//! (`QueryInterface("IADLXSystem2")`).

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

        let iid = iid::wide("IADLXSystem2");
        let mut sys2_ptr: *mut c_void = std::ptr::null_mut();
        if !adlx_succeeded((sys_vtbl.QueryInterface)(sys, iid.as_ptr(), &mut sys2_ptr))
            || sys2_ptr.is_null()
        {
            wait_and_exit("IADLXSystem2 (multimedia) not available");
            return;
        }
        let sys2 = sys2_ptr as *mut IADLXSystem2;
        let sys2_vtbl = &*(*sys2).pVtbl;

        let mut mm: *mut IADLXMultimediaServices = std::ptr::null_mut();
        if adlx_succeeded((sys2_vtbl.GetMultimediaServices)(sys2, &mut mm)) {
            let mm_vtbl = &*(*mm).pVtbl;

            let mut gpus: *mut IADLXGPUList = std::ptr::null_mut();
            if adlx_succeeded((sys_vtbl.GetGPUs)(sys, &mut gpus)) {
                let list_vtbl = &*(*gpus).pVtbl;
                let mut gpu: *mut IADLXGPU = std::ptr::null_mut();
                if adlx_succeeded((list_vtbl.At_GPUList)(gpus, (list_vtbl.Begin)(gpus), &mut gpu)) {
                    let mut vsr: *mut IADLXVideoSuperResolution = std::ptr::null_mut();
                    if adlx_succeeded((mm_vtbl.GetVideoSuperResolution)(mm, gpu, &mut vsr)) {
                        let v = &*(*vsr).pVtbl;
                        println!("\n  === Video Super Resolution ===");
                        let mut supported: adlx_bool = 0;
                        if adlx_succeeded((v.IsSupported)(vsr, &mut supported)) {
                            println!("\tIs supported: {}", supported != 0);
                        }
                        let mut enabled: adlx_bool = 0;
                        if adlx_succeeded((v.IsEnabled)(vsr, &mut enabled)) {
                            println!("\tIs enabled: {}", enabled != 0);
                        }
                        (v.Release)(vsr);
                    } else {
                        println!("Failed to get Video Super Resolution interface");
                    }
                    ((&*(*gpu).pVtbl).Release)(gpu);
                }
                (list_vtbl.Release)(gpus);
            }

            (mm_vtbl.Release)(mm);
        } else {
            println!("Failed to get multimedia services");
        }

        (sys2_vtbl.Release)(sys2);
    }

    drop(helper);
    println!("Destroy ADLX finished");
    pause();
}
