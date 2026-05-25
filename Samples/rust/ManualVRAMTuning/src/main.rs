//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to read GPU manual VRAM tuning with ADLX. This is the Rust
//! counterpart of `Samples/C/GPUTuning/ManualVRAMTuning` (read-only view).
//!
//! Reached through the GPU tuning services: check support, `GetManualVRAMTuning`
//! (returns an `IADLXInterface`), then `QueryInterface("IADLXManualVRAMTuning2")`.

use std::os::raw::c_void;

use amd_adlx::*;

/// Prints the memory-timing support and the max VRAM frequency range/value.
///
/// # Safety
/// `tuning` must be a valid `IADLXManualVRAMTuning2` interface pointer.
unsafe fn show_vram_tuning(tuning: *mut IADLXManualVRAMTuning2) {
    let v = &*(*tuning).pVtbl;
    println!("\n  === Manual VRAM tuning ===");

    let mut supported: adlx_bool = 0;
    if adlx_succeeded((v.IsSupportedMemoryTiming)(tuning, &mut supported)) {
        println!("\tMemory timing supported: {}", supported != 0);
        if supported != 0 {
            let mut desc: i32 = 0;
            if adlx_succeeded((v.GetMemoryTimingDescription)(tuning, &mut desc)) {
                println!("\tCurrent memory timing (enum value): {}", desc);
            }
        }
    }

    let mut range = ADLX_IntRange { minValue: 0, maxValue: 0, step: 0 };
    if adlx_succeeded((v.GetMaxVRAMFrequencyRange)(tuning, &mut range)) {
        println!("\tMax VRAM frequency range: {} .. {} MHz", range.minValue, range.maxValue);
    }
    let mut freq: adlx_int = 0;
    if adlx_succeeded((v.GetMaxVRAMFrequency)(tuning, &mut freq)) {
        println!("\tMax VRAM frequency: {} MHz", freq);
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
                let ok = adlx_succeeded((svc_vtbl.IsSupportedManualVRAMTuning)(
                    tuning_svc,
                    gpu,
                    &mut supported,
                ));
                if ok && supported != 0 {
                    let mut ifc: *mut IADLXInterface = std::ptr::null_mut();
                    if adlx_succeeded((svc_vtbl.GetManualVRAMTuning)(tuning_svc, gpu, &mut ifc))
                        && !ifc.is_null()
                    {
                        let ifc_vtbl = &*(*ifc).pVtbl;
                        let iid = iid::wide("IADLXManualVRAMTuning2");
                        let mut tuning_ptr: *mut c_void = std::ptr::null_mut();
                        if adlx_succeeded((ifc_vtbl.QueryInterface)(ifc, iid.as_ptr(), &mut tuning_ptr))
                            && !tuning_ptr.is_null()
                        {
                            let tuning = tuning_ptr as *mut IADLXManualVRAMTuning2;
                            show_vram_tuning(tuning);
                            ((&*(*tuning).pVtbl).Release)(tuning);
                        } else {
                            println!("This GPU uses a VRAM tuning interface not shown here");
                        }
                        (ifc_vtbl.Release)(ifc);
                    }
                } else {
                    println!("This GPU does not support manual VRAM tuning");
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
