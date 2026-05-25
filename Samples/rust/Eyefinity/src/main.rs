//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to query AMD Eyefinity support with ADLX. This is the Rust
//! counterpart of `Samples/C/Desktop/Eyefinity` (support query only).
//!
//! Eyefinity is exposed by `IADLXDesktopServices::GetSimpleEyefinity`. This sample
//! only queries support; it does not create or destroy Eyefinity desktops.

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

        let mut desktop_service: *mut IADLXDesktopServices = std::ptr::null_mut();
        if !adlx_succeeded((sys_vtbl.GetDesktopsServices)(sys, &mut desktop_service)) {
            wait_and_exit("Get desktop services failed");
            return;
        }
        let dsk_vtbl = &*(*desktop_service).pVtbl;

        let mut eyefinity: *mut IADLXSimpleEyefinity = std::ptr::null_mut();
        if adlx_succeeded((dsk_vtbl.GetSimpleEyefinity)(desktop_service, &mut eyefinity)) {
            let v = &*(*eyefinity).pVtbl;
            println!("\n  === Eyefinity ===");
            let mut supported: adlx_bool = 0;
            if adlx_succeeded((v.IsSupported)(eyefinity, &mut supported)) {
                println!("\tIs supported: {}", supported != 0);
            }
            (v.Release)(eyefinity);
        } else {
            println!("Failed to get the SimpleEyefinity interface");
        }

        (dsk_vtbl.Release)(desktop_service);
    }

    drop(helper);
    println!("Destroy ADLX finished");
    pause();
}
