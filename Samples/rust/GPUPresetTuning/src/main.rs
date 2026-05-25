//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to query GPU preset tuning with ADLX. This is the Rust
//! counterpart of `Samples/C/GPUTuning/GPUPresetTuning` (read-only view).
//!
//! Reached through the GPU tuning services: check support, `GetPresetTuning`
//! (returns an `IADLXInterface`), then `QueryInterface("IADLXGPUPresetTuning")`.

use std::os::raw::c_void;

use amd_adlx::*;

/// Prints preset support and the currently active preset.
///
/// # Safety
/// `tuning` must be a valid `IADLXGPUPresetTuning` interface pointer.
unsafe fn show_preset_tuning(tuning: *mut IADLXGPUPresetTuning) {
    let v = &*(*tuning).pVtbl;
    println!("\n  === GPU preset tuning ===");

    let supports: &[(&str, unsafe extern "system" fn(
        *mut IADLXGPUPresetTuning,
        *mut adlx_bool,
    ) -> ADLX_RESULT)] = &[
        ("Power saver", v.IsSupportedPowerSaver),
        ("Quiet", v.IsSupportedQuiet),
        ("Balanced", v.IsSupportedBalanced),
        ("Turbo", v.IsSupportedTurbo),
        ("Rage", v.IsSupportedRage),
    ];
    for (label, getter) in supports {
        let mut s: adlx_bool = 0;
        if adlx_succeeded(getter(tuning, &mut s)) {
            println!("\t{} supported: {}", label, s != 0);
        }
    }

    let currents: &[(&str, unsafe extern "system" fn(
        *mut IADLXGPUPresetTuning,
        *mut adlx_bool,
    ) -> ADLX_RESULT)] = &[
        ("Power saver", v.IsCurrentPowerSaver),
        ("Quiet", v.IsCurrentQuiet),
        ("Balanced", v.IsCurrentBalanced),
        ("Turbo", v.IsCurrentTurbo),
        ("Rage", v.IsCurrentRage),
    ];
    for (label, getter) in currents {
        let mut s: adlx_bool = 0;
        if adlx_succeeded(getter(tuning, &mut s)) && s != 0 {
            println!("\tCurrent preset: {}", label);
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
                let ok = adlx_succeeded((svc_vtbl.IsSupportedPresetTuning)(
                    tuning_svc,
                    gpu,
                    &mut supported,
                ));
                if ok && supported != 0 {
                    let mut ifc: *mut IADLXInterface = std::ptr::null_mut();
                    if adlx_succeeded((svc_vtbl.GetPresetTuning)(tuning_svc, gpu, &mut ifc))
                        && !ifc.is_null()
                    {
                        let ifc_vtbl = &*(*ifc).pVtbl;
                        let iid = iid::wide("IADLXGPUPresetTuning");
                        let mut tuning_ptr: *mut c_void = std::ptr::null_mut();
                        if adlx_succeeded((ifc_vtbl.QueryInterface)(ifc, iid.as_ptr(), &mut tuning_ptr))
                            && !tuning_ptr.is_null()
                        {
                            let tuning = tuning_ptr as *mut IADLXGPUPresetTuning;
                            show_preset_tuning(tuning);
                            ((&*(*tuning).pVtbl).Release)(tuning);
                        }
                        (ifc_vtbl.Release)(ifc);
                    }
                } else {
                    println!("This GPU does not support preset tuning");
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
