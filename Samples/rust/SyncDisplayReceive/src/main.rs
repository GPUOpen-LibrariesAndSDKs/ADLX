//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to receive synchronous display change notifications with ADLX.
//! This is the Rust counterpart of
//! `Samples/C/ReceivingEventsNotifications/SyncDisplayReceive` (display list events).

use std::io::{self, Read};

use amd_adlx::*;

/// Callback invoked by ADLX when the display list changes.
///
/// # Safety
/// Called by ADLX with valid listener and display-list pointers.
unsafe extern "system" fn on_display_list_changed(
    _p_this: *mut IADLXDisplayListChangedListener,
    _p_new_displays: *mut IADLXDisplayList,
) -> adlx_bool {
    println!("Display list has been changed");
    1
}

fn wait_for_quit() {
    println!("->Plug or unplug a display to trigger a display list change.");
    println!("->Press Q/q then Enter to terminate the loop.");
    let stdin = io::stdin();
    let mut byte = [0u8; 1];
    loop {
        if stdin.lock().read_exact(&mut byte).is_err() {
            break;
        }
        if byte[0] == b'q' || byte[0] == b'Q' {
            break;
        }
    }
}

fn wait_and_exit(msg: &str) {
    if !msg.is_empty() {
        println!("{}", msg);
    }
    use std::io::Write;
    print!("Press Enter to continue . . . ");
    let _ = io::stdout().flush();
    let _ = io::stdin().read(&mut [0u8]);
}

fn main() {
    let helper = match AdlxHelper::new() {
        Ok(helper) => helper,
        Err(_) => {
            wait_and_exit("ADLX initialization failed");
            return;
        }
    };

    static LISTENER_VTBL: IADLXDisplayListChangedListenerVtbl =
        IADLXDisplayListChangedListenerVtbl {
            OnDisplayListChanged: on_display_list_changed,
        };
    let mut listener = IADLXDisplayListChangedListener {
        pVtbl: &LISTENER_VTBL,
    };

    unsafe {
        let sys = helper.system_services();
        let sys_vtbl = &*(*sys).pVtbl;

        let mut display_service: *mut IADLXDisplayServices = std::ptr::null_mut();
        if !adlx_succeeded((sys_vtbl.GetDisplaysServices)(sys, &mut display_service)) {
            wait_and_exit("Get display services failed");
            return;
        }
        let ds_vtbl = &*(*display_service).pVtbl;

        let mut change_handling: *mut IADLXDisplayChangedHandling = std::ptr::null_mut();
        if adlx_succeeded((ds_vtbl.GetDisplayChangedHandling)(display_service, &mut change_handling)) {
            let ch = &*(*change_handling).pVtbl;
            (ch.AddDisplayListEventListener)(change_handling, &mut listener);
            wait_for_quit();
            (ch.RemoveDisplayListEventListener)(change_handling, &mut listener);
            (ch.Release)(change_handling);
        }

        (ds_vtbl.Release)(display_service);
    }

    drop(helper);
    println!("Destroy ADLX finished");
    wait_and_exit("");
}
