//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to enumerate GPUs and obtain GPU information with ADLX.
//! This is the Rust counterpart of `Samples/C/Generic/GPUs` (GPU info only).

use std::ffi::CStr;
use std::os::raw::c_char;

use amd_adlx::*;

// GPU type string (see ADLX_GPU_TYPE).
fn gpu_type_str(gpu_type: i32) -> &'static str {
    match gpu_type {
        GPUTYPE_INTEGRATED => "Integrated",
        GPUTYPE_DISCRETE => "Discrete",
        _ => "Undefined",
    }
}

/// Converts an ADLX-owned C string into an owned Rust `String`.
///
/// # Safety
/// `ptr` must be a valid, NUL-terminated C string or null.
unsafe fn c_str_to_string(ptr: *const c_char) -> String {
    if ptr.is_null() {
        String::new()
    } else {
        CStr::from_ptr(ptr).to_string_lossy().into_owned()
    }
}

/// Prints information for a single GPU.
///
/// # Safety
/// `gpu` must be a valid `IADLXGPU` interface pointer.
unsafe fn show_gpu_info(gpu: *mut IADLXGPU) {
    let vtbl = &*(*gpu).pVtbl;
    println!("\n  === GPU info ===");

    let mut name: *const c_char = std::ptr::null();
    if adlx_succeeded((vtbl.Name)(gpu, &mut name)) {
        println!("\tName: {}", c_str_to_string(name));
    }

    let mut vendor_id: *const c_char = std::ptr::null();
    if adlx_succeeded((vtbl.VendorId)(gpu, &mut vendor_id)) {
        println!("\tVendor id: {}", c_str_to_string(vendor_id));
    }

    let mut gpu_type: i32 = 0;
    if adlx_succeeded((vtbl.Type)(gpu, &mut gpu_type)) {
        println!("\tType: {}", gpu_type_str(gpu_type));
    }

    let mut is_external: adlx_bool = 0;
    if adlx_succeeded((vtbl.IsExternal)(gpu, &mut is_external)) {
        println!("\tIs external: {}", is_external != 0);
    }

    let mut driver_path: *const c_char = std::ptr::null();
    if adlx_succeeded((vtbl.DriverPath)(gpu, &mut driver_path)) {
        println!("\tDriver path: {}", c_str_to_string(driver_path));
    }

    let mut pnp_string: *const c_char = std::ptr::null();
    if adlx_succeeded((vtbl.PNPString)(gpu, &mut pnp_string)) {
        println!("\tPNP string: {}", c_str_to_string(pnp_string));
    }

    let mut has_desktops: adlx_bool = 0;
    if adlx_succeeded((vtbl.HasDesktops)(gpu, &mut has_desktops)) {
        println!("\tHas desktops: {}", has_desktops != 0);
    }

    let mut total_vram: adlx_uint = 0;
    if adlx_succeeded((vtbl.TotalVRAM)(gpu, &mut total_vram)) {
        println!("\tTotal VRAM: {} MB", total_vram);
    }

    let mut vram_type: *const c_char = std::ptr::null();
    if adlx_succeeded((vtbl.VRAMType)(gpu, &mut vram_type)) {
        println!("\tVRAM type: {}", c_str_to_string(vram_type));
    }

    let mut device_id: *const c_char = std::ptr::null();
    if adlx_succeeded((vtbl.DeviceId)(gpu, &mut device_id)) {
        println!("\tDevice id: {}", c_str_to_string(device_id));
    }

    let mut revision_id: *const c_char = std::ptr::null();
    if adlx_succeeded((vtbl.RevisionId)(gpu, &mut revision_id)) {
        println!("\tRevision id: {}", c_str_to_string(revision_id));
    }

    let (mut part_number, mut version, mut date): (
        *const c_char,
        *const c_char,
        *const c_char,
    ) = (std::ptr::null(), std::ptr::null(), std::ptr::null());
    if adlx_succeeded((vtbl.BIOSInfo)(gpu, &mut part_number, &mut version, &mut date)) {
        println!(
            "\tVBIOS: part number: {}, version: {}, date: {}",
            c_str_to_string(part_number),
            c_str_to_string(version),
            c_str_to_string(date)
        );
    }

    let mut id: adlx_int = 0;
    if adlx_succeeded((vtbl.UniqueId)(gpu, &mut id)) {
        println!("\tUnique id: {}", id);
    }
}

fn wait_and_exit(msg: &str) {
    if !msg.is_empty() {
        println!("{}", msg);
    }
    pause();
}

fn pause() {
    use std::io::{Read, Write};
    print!("Press Enter to continue . . . ");
    let _ = std::io::stdout().flush();
    let _ = std::io::stdin().read(&mut [0u8]);
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

    unsafe {
        let sys = helper.system_services();
        let sys_vtbl = &*(*sys).pVtbl;

        // Get the GPU list.
        let mut gpus: *mut IADLXGPUList = std::ptr::null_mut();
        let res = (sys_vtbl.GetGPUs)(sys, &mut gpus);
        if adlx_succeeded(res) {
            let list_vtbl = &*(*gpus).pVtbl;

            // Iterate through the GPU list.
            let mut it = (list_vtbl.Begin)(gpus);
            let end = (list_vtbl.End)(gpus);
            while it != end {
                let mut gpu: *mut IADLXGPU = std::ptr::null_mut();
                if adlx_succeeded((list_vtbl.At_GPUList)(gpus, it, &mut gpu)) {
                    show_gpu_info(gpu);
                }

                // Release the GPU interface.
                if !gpu.is_null() {
                    let g_vtbl = &*(*gpu).pVtbl;
                    (g_vtbl.Release)(gpu);
                }

                it += 1;
            }

            // Release the GPU list interface.
            (list_vtbl.Release)(gpus);
        }
    }

    // ADLX is terminated and the library is unloaded when `helper` is dropped.
    drop(helper);
    println!("Destroy ADLX finished");

    // Pause to see the printout.
    pause();
}
