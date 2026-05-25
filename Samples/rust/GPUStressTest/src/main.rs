//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to check GPU stress-test support with ADLX.
//! This is the Rust counterpart of `Samples/C/Generic/GPUStressTest`.
//!
//! The C sample can also start a GPU stress test (which loads the GPU) and receive
//! a completion notification. This port performs only the read-only support query
//! (`IADLXGPU3::IsSupportedStressTest`) so it is safe to run unattended; the
//! `StartStressTest` method is bound in `amd-adlx` for callers that want it.

use amd_adlx::*;

/// Checks and prints GPU stress-test support for every GPU in the list.
///
/// # Safety
/// `gpus` must be a valid `IADLXGPUList` interface pointer.
unsafe fn is_gpu_stress_test_supported(gpus: *mut IADLXGPUList) {
    let list_vtbl = &*(*gpus).pVtbl;
    let iid_gpu3 = iid::wide("IADLXGPU3");

    let mut it = (list_vtbl.Begin)(gpus);
    let end = (list_vtbl.End)(gpus);
    while it != end {
        let mut gpu: *mut IADLXGPU = std::ptr::null_mut();
        if adlx_succeeded((list_vtbl.At_GPUList)(gpus, it, &mut gpu)) && !gpu.is_null() {
            let gpu_vtbl = &*(*gpu).pVtbl;

            // Query the IADLXGPU3 interface, which exposes the stress-test methods.
            let mut gpu3: *mut IADLXGPU3 = std::ptr::null_mut();
            let res = (gpu_vtbl.QueryInterface)(
                gpu,
                iid_gpu3.as_ptr(),
                &mut gpu3 as *mut _ as *mut *mut std::os::raw::c_void,
            );
            if adlx_succeeded(res) && !gpu3.is_null() {
                let gpu3_vtbl = &*(*gpu3).pVtbl;
                let mut supported: adlx_bool = 0;
                let res = (gpu3_vtbl.IsSupportedStressTest)(gpu3, &mut supported);
                if adlx_succeeded(res) {
                    println!(
                        "GPU stress test is {} on GPU {}, result: {}",
                        if supported != 0 {
                            "supported"
                        } else {
                            "not supported"
                        },
                        it,
                        res
                    );
                } else {
                    println!(
                        "Failed to check if GPU stress test is supported, result: {}",
                        res
                    );
                }
                (gpu3_vtbl.Release)(gpu3);
            } else {
                println!("Failed to query IADLXGPU3 interface: {}", res);
            }

            (gpu_vtbl.Release)(gpu);
        }

        it += 1;
    }
}

fn wait_and_exit(msg: &str) {
    if !msg.is_empty() {
        println!("{}", msg);
    }
    pause();
}

fn pause() {
    use std::io::{Read, Write};
    print!("Press Enter to continue . . . ");
    let _ = std::io::stdout().flush();
    let _ = std::io::stdin().read(&mut [0u8]);
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

        // Get the GPU list.
        let mut gpus: *mut IADLXGPUList = std::ptr::null_mut();
        if adlx_succeeded((sys_vtbl.GetGPUs)(sys, &mut gpus)) && !gpus.is_null() {
            is_gpu_stress_test_supported(gpus);

            // Release the GPU list interface.
            let list_vtbl = &*(*gpus).pVtbl;
            (list_vtbl.Release)(gpus);
        } else {
            println!("Failed to get the GPU list");
        }
    }

    // ADLX is terminated and the library is unloaded when `helper` is dropped.
    drop(helper);
    println!("Destroy ADLX finished");

    // Pause to see the printout.
    pause();
}
