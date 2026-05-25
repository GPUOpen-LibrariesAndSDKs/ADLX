//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to query GPU automatic tuning with ADLX. This is the Rust
//! counterpart of `Samples/C/GPUTuning/GPUAutoTuning` (read-only view).
//!
//! Reached through the GPU tuning services: check support, `GetAutoTuning`
//! (returns an `IADLXInterface`), then `QueryInterface("IADLXGPUAutoTuning")`.

use std::os::raw::c_void;

use amd_adlx::*;

/// Prints the auto-tuning support and current state.
///
/// # Safety
/// `tuning` must be a valid `IADLXGPUAutoTuning` interface pointer.
unsafe fn show_auto_tuning(tuning: *mut IADLXGPUAutoTuning) {
    let v = &*(*tuning).pVtbl;
    println!("\n  === GPU automatic tuning ===");

    let supports: &[(&str, unsafe extern "system" fn(
        *mut IADLXGPUAutoTuning,
        *mut adlx_bool,
    ) -> ADLX_RESULT)] = &[
        ("Undervolt GPU", v.IsSupportedUndervoltGPU),
        ("Overclock GPU", v.IsSupportedOverclockGPU),
        ("Overclock VRAM", v.IsSupportedOverclockVRAM),
    ];
    for (label, getter) in supports {
        let mut s: adlx_bool = 0;
        if adlx_succeeded(getter(tuning, &mut s)) {
            println!("\t{} supported: {}", label, s != 0);
        }
    }

    let currents: &[(&str, unsafe extern "system" fn(
        *mut IADLXGPUAutoTuning,
        *mut adlx_bool,
    ) -> ADLX_RESULT)] = &[
        ("Undervolt GPU", v.IsCurrentUndervoltGPU),
        ("Overclock GPU", v.IsCurrentOverclockGPU),
        ("Overclock VRAM", v.IsCurrentOverclockVRAM),
    ];
    for (label, getter) in currents {
        let mut s: adlx_bool = 0;
        if adlx_succeeded(getter(tuning, &mut s)) && s != 0 {
            println!("\tCurrent: {}", label);
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
                let ok = adlx_succeeded((svc_vtbl.IsSupportedAutoTuning)(
                    tuning_svc,
                    gpu,
                    &mut supported,
                ));
                if ok && supported != 0 {
                    let mut ifc: *mut IADLXInterface = std::ptr::null_mut();
                    if adlx_succeeded((svc_vtbl.GetAutoTuning)(tuning_svc, gpu, &mut ifc))
                        && !ifc.is_null()
                    {
                        let ifc_vtbl = &*(*ifc).pVtbl;
                        let iid = iid::wide("IADLXGPUAutoTuning");
                        let mut tuning_ptr: *mut c_void = std::ptr::null_mut();
                        if adlx_succeeded((ifc_vtbl.QueryInterface)(ifc, iid.as_ptr(), &mut tuning_ptr))
                            && !tuning_ptr.is_null()
                        {
                            let tuning = tuning_ptr as *mut IADLXGPUAutoTuning;
                            show_auto_tuning(tuning);
                            ((&*(*tuning).pVtbl).Release)(tuning);
                        }
                        (ifc_vtbl.Release)(ifc);
                    }
                } else {
                    println!("This GPU does not support automatic tuning");
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
