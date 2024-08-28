//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainInvalidObject.c
/// \brief Demonstrates how to handle invalid objects when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IDisplays.h"

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
    if (ADLX_SUCCEEDED(res))
    {
        // Get system services
        IADLXSystem* sys = ADLXHelper_GetSystemServices();

        // Get display service
        IADLXDisplayServices* displayService = NULL;
        res = sys->pVtbl->GetDisplaysServices(sys, &displayService);
        if (ADLX_SUCCEEDED(res))
        {
            // Get the display list and iterate through the list
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
                        // Save the first display
                        break;
                    }
                }

                // Get the display name and prompt to unplug the display
                const char* dispName;
                res = display->pVtbl->Name(display, &dispName);
                printf("Within 15 seconds, unplug the display %s. \n", dispName);

                // Block for 15s
                Sleep(15 * 1000);

                // After 15 seconds, reading the display name again. If the display was unplugged, the method will fail and return ADLX_INVALID_OBJECT.
                res = display->pVtbl->Name(display, &dispName);
                printf ("Get display name return code is: %d (%d means that the method was called into an invalid object)\n", res, ADLX_INVALID_OBJECT);
                if (ADLX_INVALID_OBJECT == res)
                {
                    //To do: Handle the invalid display
                    printf ("The display is invalid.\n");
                }
                //Release the display interface
                if (NULL != display)
                {
                    display->pVtbl->Release(display);
                    display = NULL;
                }
            }

            // Release the displayList interface
            if (NULL != displayList)
            {
                displayList->pVtbl->Release(displayList);
                displayList = NULL;
            }
        }

        // Release the displayService interface
        if (NULL != displayService)
        {
            displayService->pVtbl->Release(displayService);
            displayService = NULL;
        }
    }
    else
    {
        return WaitAndExit("ADLX initialization failed", 0);
    }

    // Destroy ADLX
    res = ADLXHelper_Terminate();
    printf("Destroy ADLX result: %d\n", res);

    // Pause to see the print out
    system("pause");

    return 0;
}