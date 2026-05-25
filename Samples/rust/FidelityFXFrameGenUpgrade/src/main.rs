//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

//! Demonstrates how to inspect FidelityFX Frame Generation Upgrade with ADLX.
//! This is the Rust counterpart of `Samples/C/3DGraphics/FidelityFXFrameGenUpgrade`.
//!
//! The C sample offers an interactive menu to also enable/disable the feature and
//! change the frame-generation ratio. This port performs the read-only queries
//! (support, current state, available ratios, current ratio) so it runs unattended;
//! the `SetEnabled`/`SetRatio` methods are bound in `amd-adlx` for callers who need
//! them.

use amd_adlx::*;

fn ratio_str(ratio: i32) -> &'static str {
    match ratio {
        FFX_FRAME_GEN_2X => "2X",
        _ => "Unknown",
    }
}

/// Prints support, state, and ratio information for one upgrade interface.
///
/// # Safety
/// `upgrade` must be a valid `IADLX3DFidelityFXFrameGenUpgrade` interface pointer.
unsafe fn show_upgrade_info(upgrade: *mut IADLX3DFidelityFXFrameGenUpgrade) {
    let vtbl = &*(*upgrade).pVtbl;

    let mut supported: adlx_bool = 0;
    if adlx_succeeded((vtbl.IsSupported)(upgrade, &mut supported)) {
        println!("\tIsSupported: {}", supported != 0);
    }

    let mut enabled: adlx_bool = 0;
    if adlx_succeeded((vtbl.IsEnabled)(upgrade, &mut enabled)) {
        println!("\tIsEnabled: {}", enabled != 0);
    }

    // Current frame-generation ratio.
    let mut ratio: i32 = FFX_FRAME_GEN_UNKNOWN;
    if adlx_succeeded((vtbl.GetRatio)(upgrade, &mut ratio)) {
        println!("\tCurrent ratio: {}", ratio_str(ratio));
    }

    // Available frame-generation ratio options.
    let mut ratio_list: *mut IADLX3DFidelityFXFrameGenUpgradeRatioOptionList =
        std::ptr::null_mut();
    if adlx_succeeded((vtbl.GetAvailableRatios)(upgrade, &mut ratio_list)) && !ratio_list.is_null()
    {
        let list_vtbl = &*(*ratio_list).pVtbl;
        let size = (list_vtbl.Size)(ratio_list);
        println!("\tAvailable ratio options count: {}", size);

        for i in 0..size {
            let mut option: *mut IADLX3DFidelityFXFrameGenUpgradeRatioOption =
                std::ptr::null_mut();
            if adlx_succeeded((list_vtbl.At_OptionList)(ratio_list, i, &mut option))
                && !option.is_null()
            {
                let opt_vtbl = &*(*option).pVtbl;
                let mut opt_ratio: i32 = FFX_FRAME_GEN_UNKNOWN;
                if adlx_succeeded((opt_vtbl.Ratio)(option, &mut opt_ratio)) {
                    println!("\t\tOption {}: ratio = {}", i + 1, ratio_str(opt_ratio));
                }
                (opt_vtbl.Release)(option);
            }
        }

        (list_vtbl.Release)(ratio_list);
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
        if !adlx_succeeded((sys_vtbl.GetGPUs)(sys, &mut gpus)) || gpus.is_null() {
            wait_and_exit("Failed to get the GPU list");
            return;
        }

        // Get the 3D settings services, then query IADLX3DSettingsServices3.
        let mut services: *mut IADLX3DSettingsServices = std::ptr::null_mut();
        if adlx_succeeded((sys_vtbl.Get3DSettingsServices)(sys, &mut services))
            && !services.is_null()
        {
            let svc_vtbl = &*(*services).pVtbl;
            let iid = iid::wide("IADLX3DSettingsServices3");
            let mut services3: *mut IADLX3DSettingsServices3 = std::ptr::null_mut();
            if adlx_succeeded((svc_vtbl.QueryInterface)(
                services,
                iid.as_ptr(),
                &mut services3 as *mut _ as *mut *mut std::os::raw::c_void,
            )) && !services3.is_null()
            {
                let svc3_vtbl = &*(*services3).pVtbl;
                let list_vtbl = &*(*gpus).pVtbl;

                // Use the first GPU.
                let mut gpu: *mut IADLXGPU = std::ptr::null_mut();
                if adlx_succeeded((list_vtbl.At_GPUList)(gpus, (list_vtbl.Begin)(gpus), &mut gpu))
                    && !gpu.is_null()
                {
                    let mut upgrade: *mut IADLX3DFidelityFXFrameGenUpgrade =
                        std::ptr::null_mut();
                    let res = (svc3_vtbl.GetFidelityFXFrameGenUpgrade)(services3, gpu, &mut upgrade);
                    if adlx_succeeded(res) && !upgrade.is_null() {
                        println!("\n=== FidelityFX Frame Generation Upgrade ===");
                        show_upgrade_info(upgrade);
                        let up_vtbl = &*(*upgrade).pVtbl;
                        (up_vtbl.Release)(upgrade);
                    } else {
                        println!(
                            "FidelityFX Frame Generation Upgrade is not available (result: {})",
                            res
                        );
                    }

                    let g_vtbl = &*(*gpu).pVtbl;
                    (g_vtbl.Release)(gpu);
                }

                (svc3_vtbl.Release)(services3);
            } else {
                println!("This driver does not expose IADLX3DSettingsServices3");
            }

            (svc_vtbl.Release)(services);
        } else {
            println!("Failed to get the 3D settings services");
        }

        let list_vtbl = &*(*gpus).pVtbl;
        (list_vtbl.Release)(gpus);
    }

    // ADLX is terminated and the library is unloaded when `helper` is dropped.
    drop(helper);
    println!("Destroy ADLX finished");

    // Pause to see the printout.
    pause();
}
