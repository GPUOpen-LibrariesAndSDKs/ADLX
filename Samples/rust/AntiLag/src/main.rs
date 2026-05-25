//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to access AMD Radeon Anti-Lag options with ADLX. This is the
//! Rust counterpart of `Samples/C/3DGraphics/AntiLag`.
//!
//! It reads the Anti-Lag support and enabled state for the first GPU, toggles the
//! state, then restores the original value.

use amd_adlx::*;

/// Prints the Anti-Lag support and enabled state.
///
/// # Safety
/// `anti_lag` must be a valid `IADLX3DAntiLag` interface pointer.
unsafe fn show_anti_lag_state(anti_lag: *mut IADLX3DAntiLag) -> Option<bool> {
    let v = &*(*anti_lag).pVtbl;

    let mut supported: adlx_bool = 0;
    if adlx_succeeded((v.IsSupported)(anti_lag, &mut supported)) {
        println!("\tIs supported: {}", supported != 0);
        if supported == 0 {
            return None;
        }
    }

    let mut enabled: adlx_bool = 0;
    if adlx_succeeded((v.IsEnabled)(anti_lag, &mut enabled)) {
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

        // Get the 3D settings services.
        let mut svc: *mut IADLX3DSettingsServices = std::ptr::null_mut();
        if !adlx_succeeded((sys_vtbl.Get3DSettingsServices)(sys, &mut svc)) {
            wait_and_exit("Failed to get 3DSettings services");
            return;
        }
        let svc_vtbl = &*(*svc).pVtbl;

        // Get the GPU list and use the first GPU.
        let mut gpus: *mut IADLXGPUList = std::ptr::null_mut();
        if adlx_succeeded((sys_vtbl.GetGPUs)(sys, &mut gpus)) {
            let list_vtbl = &*(*gpus).pVtbl;
            let mut gpu: *mut IADLXGPU = std::ptr::null_mut();
            if adlx_succeeded((list_vtbl.At_GPUList)(gpus, (list_vtbl.Begin)(gpus), &mut gpu)) {
                // Get the Anti-Lag interface for this GPU.
                let mut anti_lag: *mut IADLX3DAntiLag = std::ptr::null_mut();
                if adlx_succeeded((svc_vtbl.GetAntiLag)(svc, gpu, &mut anti_lag)) {
                    let al_vtbl = &*(*anti_lag).pVtbl;

                    println!("\n  === Anti-Lag: original state ===");
                    let original = show_anti_lag_state(anti_lag);

                    // Toggle the state, then restore it.
                    if let Some(was_enabled) = original {
                        let toggled: adlx_bool = if was_enabled { 0 } else { 1 };
                        println!("\n  === Setting enabled = {} ===", toggled != 0);
                        let res = (al_vtbl.SetEnabled)(anti_lag, toggled);
                        println!("\tSetEnabled result: {} (0 means success)", res);
                        show_anti_lag_state(anti_lag);

                        println!("\n  === Restoring original state ===");
                        let _ = (al_vtbl.SetEnabled)(anti_lag, was_enabled as adlx_bool);
                        show_anti_lag_state(anti_lag);
                    }

                    (al_vtbl.Release)(anti_lag);
                } else {
                    println!("Failed to get Anti-Lag interface");
                }

                ((&*(*gpu).pVtbl).Release)(gpu);
            }
            (list_vtbl.Release)(gpus);
        }

        (svc_vtbl.Release)(svc);
    }

    // ADLX is terminated and the library is unloaded when `helper` is dropped.
    drop(helper);
    println!("Destroy ADLX finished");

    pause();
}
