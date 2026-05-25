//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to access AMD SmartAccess Memory (SAM) with ADLX. This is the
//! Rust counterpart of `Samples/C/GPUTuning/SmartAccessMemory`.
//!
//! SAM is exposed through `IADLXGPUTuningServices1`, obtained by calling
//! `QueryInterface("IADLXGPUTuningServices1")` on the base GPU tuning services.

use std::os::raw::c_void;

use amd_adlx::*;

/// Prints the SAM support and enabled state for a GPU.
///
/// # Safety
/// `sam` must be a valid `IADLXSmartAccessMemory` interface pointer.
unsafe fn show_sam_state(sam: *mut IADLXSmartAccessMemory) -> Option<bool> {
    let v = &*(*sam).pVtbl;

    let mut supported: adlx_bool = 0;
    if adlx_succeeded((v.IsSupported)(sam, &mut supported)) {
        println!("\tIs supported: {}", supported != 0);
        if supported == 0 {
            return None;
        }
    }

    let mut enabled: adlx_bool = 0;
    if adlx_succeeded((v.IsEnabled)(sam, &mut enabled)) {
        println!("\tIs enabled: {}", enabled != 0);
        return Some(enabled != 0);
    }
    None
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
        let mut tuning: *mut IADLXGPUTuningServices = std::ptr::null_mut();
        if !adlx_succeeded((sys_vtbl.GetGPUTuningServices)(sys, &mut tuning)) {
            wait_and_exit("Failed to get GPU tuning services");
            return;
        }
        let tuning_vtbl = &*(*tuning).pVtbl;

        // Query the newer IADLXGPUTuningServices1 interface that exposes SAM.
        let iid = iid::wide("IADLXGPUTuningServices1");
        let mut tuning1_ptr: *mut c_void = std::ptr::null_mut();
        let res = (tuning_vtbl.QueryInterface)(tuning, iid.as_ptr(), &mut tuning1_ptr);
        if adlx_succeeded(res) && !tuning1_ptr.is_null() {
            let tuning1 = tuning1_ptr as *mut IADLXGPUTuningServices1;
            let tuning1_vtbl = &*(*tuning1).pVtbl;

            // Get the GPU list and use the first GPU.
            let mut gpus: *mut IADLXGPUList = std::ptr::null_mut();
            if adlx_succeeded((sys_vtbl.GetGPUs)(sys, &mut gpus)) {
                let list_vtbl = &*(*gpus).pVtbl;
                let mut gpu: *mut IADLXGPU = std::ptr::null_mut();
                if adlx_succeeded((list_vtbl.At_GPUList)(gpus, (list_vtbl.Begin)(gpus), &mut gpu)) {
                    // Get the SmartAccess Memory interface for this GPU.
                    let mut sam: *mut IADLXSmartAccessMemory = std::ptr::null_mut();
                    if adlx_succeeded((tuning1_vtbl.GetSmartAccessMemory)(tuning1, gpu, &mut sam)) {
                        let sam_vtbl = &*(*sam).pVtbl;

                        println!("\n  === SmartAccess Memory: original state ===");
                        let original = show_sam_state(sam);

                        // Toggle the state, then restore it. Enabling SAM may take
                        // some time and can require a system restart to complete.
                        if let Some(was_enabled) = original {
                            let toggled: adlx_bool = if was_enabled { 0 } else { 1 };
                            println!("\n  === Setting enabled = {} ===", toggled != 0);
                            let res = (sam_vtbl.SetEnabled)(sam, toggled);
                            println!("\tSetEnabled result: {} (0 means success)", res);
                            show_sam_state(sam);

                            println!("\n  === Restoring original state ===");
                            let _ = (sam_vtbl.SetEnabled)(sam, was_enabled as adlx_bool);
                            show_sam_state(sam);
                        }

                        (sam_vtbl.Release)(sam);
                    } else {
                        println!("Failed to get SmartAccess Memory interface");
                    }

                    ((&*(*gpu).pVtbl).Release)(gpu);
                }
                (list_vtbl.Release)(gpus);
            }

            (tuning1_vtbl.Release)(tuning1);
        } else {
            println!("IADLXGPUTuningServices1 (SmartAccess Memory) not available");
        }

        (tuning_vtbl.Release)(tuning);
    }

    // ADLX is terminated and the library is unloaded when `helper` is dropped.
    drop(helper);
    println!("Destroy ADLX finished");

    pause();
}
