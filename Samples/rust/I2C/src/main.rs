//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to access the ADLX I2C interface for a GPU. This is the Rust
//! counterpart of `Samples/C/I2C/I2C`.
//!
//! The I2C interface is obtained from `IADLXSystem::GetI2C(gpu)`. This sample reads
//! the I2C interface version; it does not perform any bus transactions.

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

        // Use the first GPU.
        let mut gpus: *mut IADLXGPUList = std::ptr::null_mut();
        if adlx_succeeded((sys_vtbl.GetGPUs)(sys, &mut gpus)) {
            let list_vtbl = &*(*gpus).pVtbl;
            let mut gpu: *mut IADLXGPU = std::ptr::null_mut();
            if adlx_succeeded((list_vtbl.At_GPUList)(gpus, (list_vtbl.Begin)(gpus), &mut gpu)) {
                let mut i2c: *mut IADLXI2C = std::ptr::null_mut();
                if adlx_succeeded((sys_vtbl.GetI2C)(sys, gpu, &mut i2c)) {
                    let v = &*(*i2c).pVtbl;
                    println!("\n  === I2C ===");
                    let mut major: adlx_int = 0;
                    let mut minor: adlx_int = 0;
                    if adlx_succeeded((v.Version)(i2c, &mut major, &mut minor)) {
                        println!("\tI2C interface version: {}.{}", major, minor);
                    }
                    (v.Release)(i2c);
                } else {
                    println!("Failed to get the I2C interface for this GPU");
                }

                ((&*(*gpu).pVtbl).Release)(gpu);
            }
            (list_vtbl.Release)(gpus);
        }
    }

    drop(helper);
    println!("Destroy ADLX finished");
    pause();
}
