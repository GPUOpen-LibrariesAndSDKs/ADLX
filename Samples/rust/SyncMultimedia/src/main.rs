//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to receive synchronous multimedia change notifications with
//! ADLX. This is the Rust counterpart of `Samples/C/ReceivingEventsNotifications/SyncMultimedia`.
//!
//! Multimedia services are reached through `IADLXSystem2`
//! (`QueryInterface("IADLXSystem2")`).

use std::io::{self, Read};
use std::os::raw::c_void;

use amd_adlx::*;

/// Callback invoked by ADLX when a multimedia setting changes.
///
/// # Safety
/// Called by ADLX with valid listener and event pointers.
unsafe extern "system" fn on_multimedia_changed(
    _p_this: *mut IADLXMultimediaChangedEventListener,
    _p_event: *mut IADLXMultimediaChangedEvent,
) -> adlx_bool {
    println!("Multimedia settings have been changed");
    1
}

fn wait_for_quit() {
    println!("->Change a multimedia setting (e.g. Video Super Resolution) to trigger a notification.");
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

    static LISTENER_VTBL: IADLXMultimediaChangedEventListenerVtbl =
        IADLXMultimediaChangedEventListenerVtbl {
            OnMultimediaChanged: on_multimedia_changed,
        };
    let mut listener = IADLXMultimediaChangedEventListener {
        pVtbl: &LISTENER_VTBL,
    };

    unsafe {
        let sys = helper.system_services();
        let sys_vtbl = &*(*sys).pVtbl;

        let iid = iid::wide("IADLXSystem2");
        let mut sys2_ptr: *mut c_void = std::ptr::null_mut();
        if !adlx_succeeded((sys_vtbl.QueryInterface)(sys, iid.as_ptr(), &mut sys2_ptr))
            || sys2_ptr.is_null()
        {
            wait_and_exit("IADLXSystem2 (multimedia) not available");
            return;
        }
        let sys2 = sys2_ptr as *mut IADLXSystem2;
        let sys2_vtbl = &*(*sys2).pVtbl;

        let mut mm: *mut IADLXMultimediaServices = std::ptr::null_mut();
        if adlx_succeeded((sys2_vtbl.GetMultimediaServices)(sys2, &mut mm)) {
            let mm_vtbl = &*(*mm).pVtbl;

            let mut handling: *mut IADLXMultimediaChangedHandling = std::ptr::null_mut();
            if adlx_succeeded((mm_vtbl.GetMultimediaChangedHandling)(mm, &mut handling)) {
                let h = &*(*handling).pVtbl;
                (h.AddMultimediaEventListener)(handling, &mut listener);
                wait_for_quit();
                (h.RemoveMultimediaEventListener)(handling, &mut listener);
                (h.Release)(handling);
            }

            (mm_vtbl.Release)(mm);
        } else {
            println!("Failed to get multimedia services");
        }

        (sys2_vtbl.Release)(sys2);
    }

    drop(helper);
    println!("Destroy ADLX finished");
    wait_and_exit("");
}
