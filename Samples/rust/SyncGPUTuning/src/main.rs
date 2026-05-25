//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to receive synchronous GPU tuning change notifications with
//! ADLX. This is the Rust counterpart of `Samples/C/ReceivingEventsNotifications/SyncGPUTuning`.

use std::io::{self, Read};

use amd_adlx::*;

/// Callback invoked by ADLX when a GPU tuning setting changes.
///
/// # Safety
/// Called by ADLX with valid listener and event pointers.
unsafe extern "system" fn on_gpu_tuning_changed(
    _p_this: *mut IADLXGPUTuningChangedListener,
    _p_event: *mut IADLXGPUTuningChangedEvent,
) -> adlx_bool {
    println!("GPU tuning has been changed");
    1
}

fn wait_for_quit() {
    println!("->Change a GPU tuning setting to trigger a notification.");
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

    static LISTENER_VTBL: IADLXGPUTuningChangedListenerVtbl =
        IADLXGPUTuningChangedListenerVtbl {
            OnGPUTuningChanged: on_gpu_tuning_changed,
        };
    let mut listener = IADLXGPUTuningChangedListener {
        pVtbl: &LISTENER_VTBL,
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

        let mut handling: *mut IADLXGPUTuningChangedHandling = std::ptr::null_mut();
        if adlx_succeeded((svc_vtbl.GetGPUTuningChangedHandling)(tuning_svc, &mut handling)) {
            let h = &*(*handling).pVtbl;
            (h.AddGPUTuningEventListener)(handling, &mut listener);
            wait_for_quit();
            (h.RemoveGPUTuningEventListener)(handling, &mut listener);
            (h.Release)(handling);
        }

        (svc_vtbl.Release)(tuning_svc);
    }

    drop(helper);
    println!("Destroy ADLX finished");
    wait_and_exit("");
}
