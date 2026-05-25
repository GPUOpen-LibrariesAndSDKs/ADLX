//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to receive synchronous power tuning change notifications with
//! ADLX. This is the Rust counterpart of `Samples/C/ReceivingEventsNotifications/SyncPowerTuning`.

use std::io::{self, Read};
use std::os::raw::c_void;

use amd_adlx::*;

/// Callback invoked by ADLX when a power tuning setting changes.
///
/// # Safety
/// Called by ADLX with valid listener and event pointers.
unsafe extern "system" fn on_power_tuning_changed(
    _p_this: *mut IADLXPowerTuningChangedListener,
    _p_event: *mut IADLXPowerTuningChangedEvent,
) -> adlx_bool {
    println!("Power tuning has been changed");
    1
}

fn wait_for_quit() {
    println!("->Change a power tuning setting (e.g. SmartShift) to trigger a notification.");
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

    static LISTENER_VTBL: IADLXPowerTuningChangedListenerVtbl =
        IADLXPowerTuningChangedListenerVtbl {
            OnPowerTuningChanged: on_power_tuning_changed,
        };
    let mut listener = IADLXPowerTuningChangedListener {
        pVtbl: &LISTENER_VTBL,
    };

    unsafe {
        let sys = helper.system_services();
        let sys_vtbl = &*(*sys).pVtbl;

        // Power tuning lives on IADLXSystem1.
        let iid = iid::wide("IADLXSystem1");
        let mut sys1_ptr: *mut c_void = std::ptr::null_mut();
        if !adlx_succeeded((sys_vtbl.QueryInterface)(sys, iid.as_ptr(), &mut sys1_ptr))
            || sys1_ptr.is_null()
        {
            wait_and_exit("IADLXSystem1 (power tuning) not available");
            return;
        }
        let sys1 = sys1_ptr as *mut IADLXSystem1;
        let sys1_vtbl = &*(*sys1).pVtbl;

        let mut power: *mut IADLXPowerTuningServices = std::ptr::null_mut();
        if adlx_succeeded((sys1_vtbl.GetPowerTuningServices)(sys1, &mut power)) {
            let power_vtbl = &*(*power).pVtbl;

            let mut handling: *mut IADLXPowerTuningChangedHandling = std::ptr::null_mut();
            if adlx_succeeded((power_vtbl.GetPowerTuningChangedHandling)(power, &mut handling)) {
                let h = &*(*handling).pVtbl;
                (h.AddPowerTuningEventListener)(handling, &mut listener);
                wait_for_quit();
                (h.RemovePowerTuningEventListener)(handling, &mut listener);
                (h.Release)(handling);
            }

            (power_vtbl.Release)(power);
        } else {
            println!("Failed to get power tuning services");
        }

        (sys1_vtbl.Release)(sys1);
    }

    drop(helper);
    println!("Destroy ADLX finished");
    wait_and_exit("");
}
