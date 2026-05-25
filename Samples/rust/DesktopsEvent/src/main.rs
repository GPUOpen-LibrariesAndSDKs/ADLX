//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to handle notifications about desktop configuration changes with
//! ADLX. This is the Rust counterpart of `Samples/C/Desktop/DesktopsEvent`.
//!
//! The application implements an `IADLXDesktopListChangedListener` whose memory
//! layout matches ADLX's expectation: a `pVtbl` pointer to a table holding the
//! single `OnDesktopListChanged` callback.

use std::io::{self, Read};

use amd_adlx::*;

/// Callback invoked by ADLX when the desktop list changes.
///
/// # Safety
/// Called by ADLX with valid listener and desktop-list pointers.
unsafe extern "system" fn on_desktop_list_changed(
    _p_this: *mut IADLXDesktopListChangedListener,
    _p_new_desktops: *mut IADLXDesktopList,
) -> adlx_bool {
    println!("Desktop list has been changed");
    // Return true so ADLX continues to notify the next listener.
    1
}

fn wait_for_quit() {
    println!("->Change the desktop configuration to trigger a desktop list change.");
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

    static LISTENER_VTBL: IADLXDesktopListChangedListenerVtbl =
        IADLXDesktopListChangedListenerVtbl {
            OnDesktopListChanged: on_desktop_list_changed,
        };
    let mut listener = IADLXDesktopListChangedListener {
        pVtbl: &LISTENER_VTBL,
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

        let mut change_handling: *mut IADLXDesktopChangedHandling = std::ptr::null_mut();
        if adlx_succeeded((dsk_vtbl.GetDesktopChangedHandling)(desktop_service, &mut change_handling))
        {
            let ch_vtbl = &*(*change_handling).pVtbl;

            (ch_vtbl.AddDesktopListEventListener)(change_handling, &mut listener);
            wait_for_quit();
            (ch_vtbl.RemoveDesktopListEventListener)(change_handling, &mut listener);

            (ch_vtbl.Release)(change_handling);
        }

        (dsk_vtbl.Release)(desktop_service);
    }

    drop(helper);
    println!("Destroy ADLX finished");
    wait_and_exit("");
}
