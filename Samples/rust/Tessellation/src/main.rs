//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to query tessellation settings with ADLX. This is the Rust
//! counterpart of `Samples/C/3DGraphics/Tessellation`.
//!
//! The mode and level are ADLX enums; their integer values are printed here (see
//! ADLXDefines.h for the value meanings).

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

        let mut gpus: *mut IADLXGPUList = std::ptr::null_mut();
        if adlx_succeeded((sys_vtbl.GetGPUs)(sys, &mut gpus)) {
            let list_vtbl = &*(*gpus).pVtbl;
            let mut gpu: *mut IADLXGPU = std::ptr::null_mut();
            if adlx_succeeded((list_vtbl.At_GPUList)(gpus, (list_vtbl.Begin)(gpus), &mut gpu)) {
                let mut feature: *mut IADLX3DTessellation = std::ptr::null_mut();
                if adlx_succeeded((svc_vtbl.GetTessellation)(svc, gpu, &mut feature)) {
                    let f = &*(*feature).pVtbl;
                    println!("\n  === Tessellation ===");
                    let mut supported: adlx_bool = 0;
                    if adlx_succeeded((f.IsSupported)(feature, &mut supported)) {
                        println!("\tIs supported: {}", supported != 0);
                    }
                    let mut mode: i32 = 0;
                    if adlx_succeeded((f.GetMode)(feature, &mut mode)) {
                        println!("\tCurrent mode (enum value): {}", mode);
                    }
                    let mut level: i32 = 0;
                    if adlx_succeeded((f.GetLevel)(feature, &mut level)) {
                        println!("\tCurrent level (enum value): {}", level);
                    }
                    (f.Release)(feature);
                } else {
                    println!("Failed to get Tessellation interface");
                }
                ((&*(*gpu).pVtbl).Release)(gpu);
            }
            (list_vtbl.Release)(gpus);
        }

        (svc_vtbl.Release)(svc);
    }

    drop(helper);
    println!("Destroy ADLX finished");
    pause();
}
