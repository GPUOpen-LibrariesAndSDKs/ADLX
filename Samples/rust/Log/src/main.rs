//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to enable ADLX logging and capture log data. This is the Rust
//! counterpart of `Samples/C/Generic/Log`.
//!
//! ADLX can send its internal log traces to a local file, to the debugger
//! (DebugView), or to the application through an `IADLXLog` callback. This sample
//! registers an application callback, then performs some ADLX calls to generate log
//! output that is printed by the callback.

use std::os::raw::c_int;

use amd_adlx::*;

/// Application log callback invoked by ADLX for every log message.
///
/// # Safety
/// Called by ADLX with a valid wide (UTF-16) NUL-terminated `msg`.
unsafe extern "system" fn write_log(_p_this: *mut IADLXLog, msg: *const u16) -> ADLX_RESULT {
    if !msg.is_null() {
        // Measure the NUL-terminated wide string, then decode it.
        let mut len = 0usize;
        while *msg.add(len) != 0 {
            len += 1;
        }
        let slice = std::slice::from_raw_parts(msg, len);
        print!("{}", String::from_utf16_lossy(slice));
    }
    ADLX_OK
}

/// Wide (UTF-16, NUL-terminated) string helper for file paths.
fn wide(s: &str) -> Vec<u16> {
    s.encode_utf16().chain(std::iter::once(0)).collect()
}

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
    // Initialize ADLX.
    let helper = match AdlxHelper::new() {
        Ok(helper) => helper,
        Err(_) => {
            wait_and_exit("ADLX initialization failed");
            return;
        }
    };

    // Application log object: `pVtbl` points to a table with the WriteLog callback.
    static LOG_VTBL: IADLXLogVtbl = IADLXLogVtbl {
        WriteLog: write_log,
    };
    let mut app_log = IADLXLog { pVtbl: &LOG_VTBL };

    unsafe {
        let sys = helper.system_services();
        let sys_vtbl = &*(*sys).pVtbl;

        // Example: enabling logging to a local file (commented out so the two
        // destinations do not overwrite each other; the last EnableLog call wins).
        //
        //   let file = wide("./ADLX.log");
        //   (sys_vtbl.EnableLog)(sys, LOCALFILE, LDEBUG, std::ptr::null_mut(), file.as_ptr());
        let _ = wide; // keep helper referenced for the documented example above.

        // Enable logging to the application callback.
        let res = (sys_vtbl.EnableLog)(
            sys,
            APPLICATION as c_int,
            LDEBUG as c_int,
            &mut app_log,
            std::ptr::null(),
        );
        println!("Enable application log result: {} (0 means success)", res);

        // Perform some ADLX activity to generate log traces.
        let mut display_service: *mut IADLXDisplayServices = std::ptr::null_mut();
        if adlx_succeeded((sys_vtbl.GetDisplaysServices)(sys, &mut display_service)) {
            let ds_vtbl = &*(*display_service).pVtbl;
            let mut count: adlx_uint = 0;
            let _ = (ds_vtbl.GetNumberOfDisplays)(display_service, &mut count);
            println!("Number of displays: {}", count);
            (ds_vtbl.Release)(display_service);
        }
    }

    // ADLX is terminated and the library is unloaded when `helper` is dropped.
    drop(helper);
    println!("Destroy ADLX finished");

    pause();
}
