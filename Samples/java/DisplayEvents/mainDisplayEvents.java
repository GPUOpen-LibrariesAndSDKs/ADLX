//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

import out.*;

public class mainDisplayEvents {

    // load ADLXJavaBind.dll
    static {
        try {
            System.loadLibrary("ADLXJavaBind");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("Native code library failed to load. See the chapter on Dynamic Linking Problems in the SWIG Java documentation for help.\n" + e);
            System.exit(1);
        }
    }

    // Get displaylistchanged
    public static void main(String[] args) {

        // Initialize ADLX with ADLXHelper
        ADLXHelper help = new ADLXHelper();
        ADLX_RESULT res = help.Initialize();

        if (res == ADLX_RESULT.ADLX_OK) {

            // Get system services
            IADLXSystem sys = help.GetSystemServices();

            if (sys != null) {
                // Get display services
                SWIGTYPE_p_p_adlx__IADLXDisplayServices s = ADLX.new_displaySerP_Ptr();
                res = sys.GetDisplaysServices(s);
                IADLXDisplayServices displayService = ADLX.displaySerP_Ptr_value(s);

                if (res == ADLX_RESULT.ADLX_OK) {
                    // Get display changed handling
                    SWIGTYPE_p_p_adlx__IADLXDisplayChangedHandling ppDisChangeHand = ADLX.new_displayChangeHandlP_Ptr();
                    res = displayService.GetDisplayChangedHandling(ppDisChangeHand);
                    IADLXDisplayChangedHandling hand = ADLX.displayChangeHandlP_Ptr_value(ppDisChangeHand);

                    if (res == ADLX_RESULT.ADLX_OK) {
                        // Call back for dislaylistchanged
                        DisplayListCallBack call = new DisplayListCallBack();
                        hand.AddDisplayListEventListener(call);
                        System.out.println("\n\n Plug or unplug a display within 20 seconds.\n");
                        try {
                            Thread.currentThread().sleep(20000);
                        } catch (Exception e) {
                            // Exception handling
                        }
                        hand.RemoveDisplayListEventListener(call);

                        // Release display changed handling interface
                        hand.Release();
                    }

                    // Release display services interface
                    displayService.Release();
                }
            }
        } else {
            System.out.printf("ADLX helper initialize result: %s\n", res.toString());
        }

        // ADLX Terminate
        res = help.Terminate();
        System.out.printf("ADLX Terminate: %s\n", res.toString());
    }
}