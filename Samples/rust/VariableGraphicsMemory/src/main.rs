//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to query Variable Graphics Memory (VGM) with ADLX. This is the
//! Rust counterpart of `Samples/C/VariableGraphicsMemory`.
//!
//! VGM is reached through `IADLXSystem3` (`QueryInterface("IADLXSystem3")`).

use std::ffi::CStr;
use std::os::raw::{c_char, c_void};

use amd_adlx::*;

/// Prints the fields of a VGM option.
///
/// # Safety
/// `option` must be a valid `IADLXVariableGraphicsMemoryOption` interface pointer.
unsafe fn show_option(label: &str, option: *mut IADLXVariableGraphicsMemoryOption) {
    let v = &*(*option).pVtbl;

    let mut name: *const c_char = std::ptr::null();
    let name_str = if adlx_succeeded((v.Name)(option, &mut name)) && !name.is_null() {
        CStr::from_ptr(name).to_string_lossy().into_owned()
    } else {
        String::from("<unknown>")
    };

    let mut mode: i32 = 0;
    let _ = (v.Mode)(option, &mut mode);

    let mut carved: adlx_double = 0.0;
    let _ = (v.MemoryCarved)(option, &mut carved);

    let mut remaining: adlx_double = 0.0;
    let _ = (v.MemoryRemaining)(option, &mut remaining);

    println!(
        "\t{}: name='{}', mode(enum)={}, carved={:.2} GB, remaining={:.2} GB",
        label, name_str, mode, carved, remaining
    );
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

        let iid = iid::wide("IADLXSystem3");
        let mut sys3_ptr: *mut c_void = std::ptr::null_mut();
        if !adlx_succeeded((sys_vtbl.QueryInterface)(sys, iid.as_ptr(), &mut sys3_ptr))
            || sys3_ptr.is_null()
        {
            wait_and_exit("IADLXSystem3 (variable graphics memory) not available");
            return;
        }
        let sys3 = sys3_ptr as *mut IADLXSystem3;
        let sys3_vtbl = &*(*sys3).pVtbl;

        let mut vgm: *mut IADLXVariableGraphicsMemory = std::ptr::null_mut();
        if adlx_succeeded((sys3_vtbl.GetVariableGraphicsMemory)(sys3, &mut vgm)) {
            let v = &*(*vgm).pVtbl;
            println!("\n  === Variable Graphics Memory ===");

            let mut supported: adlx_bool = 0;
            if adlx_succeeded((v.IsSupported)(vgm, &mut supported)) {
                println!("\tIs supported: {}", supported != 0);
            }

            let mut default_opt: *mut IADLXVariableGraphicsMemoryOption = std::ptr::null_mut();
            if adlx_succeeded((v.GetDefaultOption)(vgm, &mut default_opt)) {
                show_option("Default option", default_opt);
                ((&*(*default_opt).pVtbl).Release)(default_opt);
            }

            let mut current_opt: *mut IADLXVariableGraphicsMemoryOption = std::ptr::null_mut();
            if adlx_succeeded((v.GetOption)(vgm, &mut current_opt)) {
                show_option("Current option", current_opt);
                ((&*(*current_opt).pVtbl).Release)(current_opt);
            }

            (v.Release)(vgm);
        } else {
            println!("Failed to get Variable Graphics Memory interface");
        }

        (sys3_vtbl.Release)(sys3);
    }

    drop(helper);
    println!("Destroy ADLX finished");
    pause();
}
