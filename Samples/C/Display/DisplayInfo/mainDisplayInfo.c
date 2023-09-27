//
// Copyright (c) 2021 - 2023 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayInfo.c
/// \brief Demonstrates how to obtain the display info when programming with ADLX and perform related operations.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IDisplays.h"

// Extra data
// Get display type string
static const char* GetDisplayTypeStr(const ADLX_DISPLAY_TYPE type)
{
    switch (type)
    {
    case DISPLAY_TYPE_MONITOR:
        return "CRT";
    case DISPLAY_TYPE_TELEVISION:
        return "TV";
    case DISPLAY_TYPE_LCD_PANEL:
        return "LCD";
    case DISPLAY_TYPE_DIGITAL_FLAT_PANEL:
        return "DFP";
    case DISPLAY_TYPE_COMPONENT_VIDEO:
        return "CV";
    default:
        return "UNKNOWN";
    }
}

// Get display connect type string
static const char* GetDisplayConnectorStr(const ADLX_DISPLAY_CONNECTOR_TYPE type)
{
    switch (type)
    {
    case DISPLAY_CONTYPE_UNKNOWN:
        return "UNKNOWN";
    case DISPLAY_CONTYPE_VGA:
        return "VGA";
    case DISPLAY_CONTYPE_DVI_D:
        return "DVI D";
    case DISPLAY_CONTYPE_DVI_I:
        return "DVI I";
    case DISPLAY_CONTYPE_CVDONGLE_NTSC:
        return "ATICVDONGLE NTSC";
    case DISPLAY_CONTYPE_CVDONGLE_JPN:
        return "ATICVDONGLE JPN";
    case DISPLAY_CONTYPE_CVDONGLE_NONI2C_JPN:
        return "ATICVDONGLE NONI2C JPN";
    case DISPLAY_CONTYPE_CVDONGLE_NONI2C_NTSC:
        return "ATICVDONGLE NONI2C NTSC";
    case DISPLAY_CONTYPE_PROPRIETARY:
        return "PROPRIETARY";
    case DISPLAY_CONTYPE_HDMI_TYPE_A:
        return "HDMI TYPE A";
    case DISPLAY_CONTYPE_HDMI_TYPE_B:
        return "HDMI TYPE B";
    case DISPLAY_CONTYPE_SVIDEO:
        return "SVIDEO";
    case DISPLAY_CONTYPE_COMPOSITE:
        return "COMPOSITE";
    case DISPLAY_CONTYPE_RCA_3COMPONENT:
        return "RCA 3COMPONENT";
    case DISPLAY_CONTYPE_DISPLAYPORT:
        return "DISPLAYPORT";
    case DISPLAY_CONTYPE_EDP:
        return "EDP";
    case DISPLAY_CONTYPE_WIRELESSDISPLAY:
        return "WIRELESSDISPLAY";
    case DISPLAY_CONTYPE_USB_TYPE_C:
        return "USB TYPE C";
    default:
        return "UNKNOWN";
    }
};

// Get scan type string
static const char* GetScanTypeStr(const ADLX_DISPLAY_SCAN_TYPE type)
{
    if (PROGRESSIVE == type)
    {
        return "PROGRESSIVE";
    }
    else if (INTERLACED == type)
    {
        return "INTERLACED";
    }
    return "UNKNOWN";
};

// Print displayInfo information
void ShowDisplayInfo(IADLXDisplay* display)
{
    ADLX_RESULT res = ADLX_OK;

    printf("\n  === Display info ===\n");
    const char* dispName;
    res = display->pVtbl->Name(display, &dispName);
    if (ADLX_SUCCEEDED(res))
        printf("\tDisplay name: %s\n", dispName);

    adlx_uint manufacturerID;
    res = display->pVtbl->ManufacturerID(display, &manufacturerID);
    if (ADLX_SUCCEEDED(res))
        printf("\tManufacturer id: %d\n", manufacturerID);

    ADLX_DISPLAY_TYPE displayType;
    res = display->pVtbl->DisplayType(display, &displayType);
    if (ADLX_SUCCEEDED(res))
        printf("\tDisplay type: %s\n", GetDisplayTypeStr(displayType));

    ADLX_DISPLAY_CONNECTOR_TYPE connectType;
    res = display->pVtbl->ConnectorType(display, &connectType);
    if (ADLX_SUCCEEDED(res))
        printf("\tConnector type: %s\n", GetDisplayConnectorStr(connectType));

    const char* edid;
    res = display->pVtbl->EDID(display, &edid);
    if (ADLX_OK != res)
        printf("\tDisplay EDID, error code is: %d\n", res);
    else
        printf("\tEDID: %s\n", edid);

    adlx_double refreshRate;
    res = display->pVtbl->RefreshRate(display, &refreshRate);
    if (ADLX_SUCCEEDED(res))
        printf("\tRefresh rate: %f\n", refreshRate);

    adlx_uint pixelClock;
    res = display->pVtbl->PixelClock(display, &pixelClock);
    if (ADLX_SUCCEEDED(res))
        printf("\tPixel clock: %d\n", pixelClock);

    adlx_int maxHResolution = 0;
    adlx_int maxVResolution = 0;
    res = display->pVtbl->NativeResolution(display, &maxHResolution, &maxVResolution);
    if (ADLX_SUCCEEDED(res))
        printf("\tNative resolution[h*v]: %d  %d\n", maxHResolution, maxVResolution);

    ADLX_DISPLAY_SCAN_TYPE scanType;
    res = display->pVtbl->ScanType(display, &scanType);
    if (ADLX_SUCCEEDED(res))
        printf("\tScan type: %s\n", GetScanTypeStr(scanType));

    adlx_size id;
    res = display->pVtbl->UniqueId(display, &id);
    if (ADLX_SUCCEEDED(res))
        printf("\tUniqueId: %zu\n", id);
}

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode)
{
    // Printout the message and pause to see it before returning the desired code
    if (NULL != msg)
        printf("%s\n", msg);

    system("pause");
    return retCode;
}

int main()
{
    // Define return code
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = ADLXHelper_Initialize();
    if (ADLX_OK != res)
        return WaitAndExit("ADLX initialization failed", 0);

    // Get system services
    IADLXSystem* sys = ADLXHelper_GetSystemServices();

    // Get display service
    IADLXDisplayServices* displayService = NULL;
    res = sys->pVtbl->GetDisplaysServices(sys, &displayService);
    if (ADLX_SUCCEEDED(res))
    {
        // Get display list and iterate through the list
        IADLXDisplayList* displayList = NULL;
        res = displayService->pVtbl->GetDisplays(displayService, &displayList);
        if (ADLX_SUCCEEDED(res))
        {
            adlx_uint it = displayList->pVtbl->Begin(displayList);
            IADLXDisplay* display = NULL;
            for (; it != displayList->pVtbl->End(displayList); it++)
            {
                res = displayList->pVtbl->At_DisplayList(displayList, it, &display);
                if (ADLX_SUCCEEDED(res))
                {
                    // Display data on console for each display
                    ShowDisplayInfo(display);
                }

                // Release the display interface
                if (NULL != display)
                {
                    display->pVtbl->Release(display);
                    display = NULL;
                }
            }
        }

        // Release the  displayList interface
        if (NULL != displayList)
        {
            displayList->pVtbl->Release(displayList);
            displayList = NULL;
        }
    }

    // Release the  displayService interface
    if (NULL != displayService)
    {
        displayService->pVtbl->Release(displayService);
        displayService = NULL;
    }

    // Destroy ADLX
    res = ADLXHelper_Terminate();
    printf("Destroy ADLX res: %d\n", res);

    // Pause to see the print out
    system("pause");

    return 0;
}
