//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

import out.*;

public class mainDisplayInfo {

    // Load ADLXJavaBind.dll
    static {
        try {
            System.loadLibrary("ADLXJavaBind");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("Native code library failed to load. See the chapter on Dynamic Linking Problems in the SWIG Java documentation for help.\n" + e);
            System.exit(1);
        }
    }

    // Iterate display list
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
                    // Get display list
                    SWIGTYPE_p_p_adlx__IADLXDisplayList ppDisplayList = ADLX.new_displayListP_Ptr();
                    res = displayService.GetDisplays(ppDisplayList);
                    IADLXDisplayList displayList = ADLX.displayListP_Ptr_value(ppDisplayList);

                    if (res == ADLX_RESULT.ADLX_OK) {
                        // Iterate through the display list
                        long it = displayList.Begin();
                        for(; it != displayList.Size(); it++) {
                            SWIGTYPE_p_p_adlx__IADLXDisplay ppDisplay = ADLX.new_displayP_Ptr();
                            res = displayList.At(it, ppDisplay);
                            IADLXDisplay display = ADLX.displayP_Ptr_value(ppDisplay);

                            if (res == ADLX_RESULT.ADLX_OK) {
                                SWIGTYPE_p_p_char ppName = ADLX.new_charP_Ptr();
                                display.Name(ppName);
                                String name = ADLX.charP_Ptr_value(ppName);

                                SWIGTYPE_p_ADLX_DISPLAY_TYPE pDisType = ADLX.new_displayTypeP();
                                display.DisplayType(pDisType);
                                ADLX_DISPLAY_TYPE disType = ADLX.displayTypeP_value(pDisType);

                                SWIGTYPE_p_unsigned_int pMID = ADLX.new_uintP();
                                display.ManufacturerID(pMID);
                                long mid = ADLX.uintP_value(pMID);

                                SWIGTYPE_p_ADLX_DISPLAY_CONNECTOR_TYPE pConnect = ADLX.new_disConnectTypeP();
                                display.ConnectorType(pConnect);
                                ADLX_DISPLAY_CONNECTOR_TYPE connect = ADLX.disConnectTypeP_value(pConnect);

                                SWIGTYPE_p_p_char ppEDIE = ADLX.new_charP_Ptr();
                                display.EDID(ppEDIE);
                                String edid = ADLX.charP_Ptr_value(ppEDIE);

                                SWIGTYPE_p_int pH = ADLX.new_intP();
                                SWIGTYPE_p_int pV = ADLX.new_intP();
                                display.NativeResolution(pH, pV);
                                int h = ADLX.intP_value(pH);
                                int v = ADLX.intP_value(pV);

                                SWIGTYPE_p_double pRefRate = ADLX.new_doubleP();
                                display.RefreshRate(pRefRate);
                                double refRate = ADLX.doubleP_value(pRefRate);

                                SWIGTYPE_p_unsigned_int pPixClock = ADLX.new_uintP();
                                display.PixelClock(pPixClock);
                                long pixClock = ADLX.uintP_value(pPixClock);

                                SWIGTYPE_p_ADLX_DISPLAY_SCAN_TYPE pScanType = ADLX.new_disScanTypeP();
                                display.ScanType(pScanType);
                                ADLX_DISPLAY_SCAN_TYPE scanType = ADLX.disScanTypeP_value(pScanType);

                                SWIGTYPE_p_size_t pID = ADLX.new_adlx_sizeP();
                                display.UniqueId(pID);
                                long id = ADLX.adlx_sizeP_value(pID);

                                System.out.printf("\nThe display [%d]:\n", it);
                                System.out.printf("\tName: %s\n", name);
                                System.out.printf("\tType: %s\n", disType.toString());
                                System.out.printf("\tConnector type: %s\n", connect.toString());
                                System.out.printf("\tManufacturer id: %d\n", mid);
                                System.out.printf("\tEDID: %s\n", edid);
                                System.out.printf("\tResolution:  h: %d  v: %d\n", h, v);
                                System.out.printf("\tRefresh rate: %f\n", refRate);
                                System.out.printf("\tPixel clock: %d\n", pixClock);
                                System.out.printf("\tScan type: %s\n", scanType.toString());
                                System.out.printf("\tUnique id: %d\n", id);

                                // Release display interface
                                display.Release();
                          }
                        }

                      // Release display list interface
                      displayList.Release();
                    }

                    // Release display services interface
                    displayService.Release();
                }
            }
        } else {
            System.out.printf("ADLX helper initialization res: %s\n", res.toString());
        }

        // Terminate ADLX
        res = help.Terminate();
        System.out.printf("ADLX Terminate: %s\n", res.toString());
    }
}
