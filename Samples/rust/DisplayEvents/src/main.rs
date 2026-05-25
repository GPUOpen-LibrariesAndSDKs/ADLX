//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to handle notifications about display list changes with ADLX.
//! This is the Rust counterpart of `Samples/C/Display/DisplayEvents` (display-list
//! listener only).
//!
//! ADLX calls back into the application through an application-provided interface
//! whose memory layout must match `IADLXDisplayListChangedListener`: a single
//! `pVtbl` pointer to a table holding one `OnDisplayListChanged` function pointer.

use std::io::{self, Read};

use amd_adlx::*;

/// Callback invoked by ADLX when the display list changes.
///
/// # Safety
/// Called by ADLX with a valid listener pointer and a valid display list pointer.
/// Returning a non-zero value tells ADLX to keep notifying the next listener.
unsafe extern "system" fn on_display_list_changed(
    _p_this: *mut IADLXDisplayListChangedListener,
    _p_new_displays: *mut IADLXDisplayList,
) -> adlx_bool {
    println!("Display list has been changed");
    // Return true so ADLX continues to notify the next listener.
    1
}

fn pause_prompt() {
    println!("->Plug or unplug a display to trigger DisplayListChanged.");
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
    print!("Press Enter to continue . . . ");
    use std::io::Write;
    let _ = io::stdout().flush();
    let _ = io::stdin().read(&mut [0u8]);
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

    // The listener vtable is 'static so ADLX can call it for the whole registration.
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

        // Get the display services.
        let mut display_service: *mut IADLXDisplayServices = std::ptr::null_mut();
        let res = (sys_vtbl.GetDisplaysServices)(sys, &mut display_service);
        if adlx_succeeded(res) {
            let ds_vtbl = &*(*display_service).pVtbl;

            // Get the display change handling interface.
            let mut change_handling: *mut IADLXDisplayChangedHandling = std::ptr::null_mut();
            let res = (ds_vtbl.GetDisplayChangedHandling)(display_service, &mut change_handling);
            if adlx_succeeded(res) {
                let ch_vtbl = &*(*change_handling).pVtbl;

                // Register the display-list listener.
                (ch_vtbl.AddDisplayListEventListener)(change_handling, &mut listener);

                // Wait for events until the user quits.
                pause_prompt();

                // Unregister the listener before releasing the handle.
                (ch_vtbl.RemoveDisplayListEventListener)(change_handling, &mut listener);

                // Release the display change handling interface.
                (ch_vtbl.Release)(change_handling);
            }

            // Release the display services interface.
            (ds_vtbl.Release)(display_service);
        }
    }

    // ADLX is terminated and the library is unloaded when `helper` is dropped.
    drop(helper);
    println!("Destroy ADLX finished");

    wait_and_exit("");
}
