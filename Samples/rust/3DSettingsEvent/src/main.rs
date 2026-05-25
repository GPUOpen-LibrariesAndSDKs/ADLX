//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to handle notifications about 3D settings changes with ADLX.
//! This is the Rust counterpart of `Samples/C/ReceivingEventsNotifications/Sync3DReceive`
//! (3D settings listener).

use std::io::{self, Read};

use amd_adlx::*;

/// Callback invoked by ADLX when any 3D setting changes.
///
/// # Safety
/// Called by ADLX with valid listener and event pointers.
unsafe extern "system" fn on_3d_settings_changed(
    _p_this: *mut IADLX3DSettingsChangedListener,
    _p_event: *mut IADLX3DSettingsChangedEvent,
) -> adlx_bool {
    println!("3D settings have been changed");
    // Return true so ADLX continues to notify the next listener.
    1
}

fn wait_for_quit() {
    println!("->Change any 3D graphics setting to trigger a notification.");
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

    static LISTENER_VTBL: IADLX3DSettingsChangedListenerVtbl =
        IADLX3DSettingsChangedListenerVtbl {
            On3DSettingsChanged: on_3d_settings_changed,
        };
    let mut listener = IADLX3DSettingsChangedListener {
        pVtbl: &LISTENER_VTBL,
    };

    unsafe {
        let sys = helper.system_services();
        let sys_vtbl = &*(*sys).pVtbl;

        let mut svc: *mut IADLX3DSettingsServices = std::ptr::null_mut();
        if !adlx_succeeded((sys_vtbl.Get3DSettingsServices)(sys, &mut svc)) {
            wait_and_exit("Failed to get 3DSettings services");
            return;
        }
        let svc_vtbl = &*(*svc).pVtbl;

        let mut change_handling: *mut IADLX3DSettingsChangedHandling = std::ptr::null_mut();
        if adlx_succeeded((svc_vtbl.Get3DSettingsChangedHandling)(svc, &mut change_handling)) {
            let ch_vtbl = &*(*change_handling).pVtbl;

            (ch_vtbl.Add3DSettingsEventListener)(change_handling, &mut listener);
            wait_for_quit();
            (ch_vtbl.Remove3DSettingsEventListener)(change_handling, &mut listener);

            (ch_vtbl.Release)(change_handling);
        }

        (svc_vtbl.Release)(svc);
    }

    drop(helper);
    println!("Destroy ADLX finished");
    wait_and_exit("");
}
