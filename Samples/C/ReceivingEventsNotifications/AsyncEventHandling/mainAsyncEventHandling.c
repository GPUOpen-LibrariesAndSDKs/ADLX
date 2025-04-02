//
// Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainAsyncEventHandling.c
/// \brief Demonstrates how to handle long processing for an event on a separate thread when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IDisplay3DLUT.h"
#include "SDK/Include/IDisplayGamma.h"
#include "SDK/Include/IDisplayGamut.h"
#include "SDK/Include/IDisplays.h"
#include <windows.h>

// Handle thread
HANDLE thread = NULL;

// Gamut changed event
HANDLE gamutChangedEvent = NULL;

// Work thread
DWORD WINAPI WorkThread(LPVOID lpParam)
{
    // Some time-consuming operations
    Sleep(5000);
    IADLXDisplayGamutChangedEvent* gamutChanged = (IADLXDisplayGamutChangedEvent*)(lpParam);
    printf ("On the asynchronous thread: Thread Id: %d : After the time-consuming operations, get the display gamut changed event:\n", GetCurrentThreadId());
    printf("\tColor space change: %d\n\tWhite point change: %d\n",
        gamutChanged->pVtbl->IsColorSpaceChanged(gamutChanged),
        gamutChanged->pVtbl->IsWhitePointChanged(gamutChanged));

    // Release the interface when the task is completed.
    gamutChanged->pVtbl->Release(gamutChanged);

    SetEvent(gamutChangedEvent);

    return 0;
}

// CallBack for displayGamut
adlx_bool ADLX_STD_CALL OnDisplayGamutChanged(IADLXDisplayGamutChangedListener* pThis, IADLXDisplayGamutChangedEvent* pDisplayGamutChangedEvent)
{
    // Acquire the interface before passing to the asynchronous thread
    pDisplayGamutChangedEvent->pVtbl->Acquire(pDisplayGamutChangedEvent);
    thread = CreateThread(NULL, 0, WorkThread, pDisplayGamutChangedEvent, 0, NULL);
    
    // Returns true will make ADLX continue to notify next listener or false to stop to notify
    return true;
}

// CallBack struct for displayGamut
typedef struct DisplayGamutCallBack
{
    adlx_bool(ADLX_STD_CALL* OnDisplayGamutChanged)(IADLXDisplayGamutChangedListener*, IADLXDisplayGamutChangedEvent*);
} DisplayGamutCallBack;

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
        // Create event
        gamutChangedEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

        // Get system services
        IADLXSystem* sys = ADLXHelper_GetSystemServices();

        // Get display service
        IADLXDisplayServices* displayService = NULL;
        res = sys->pVtbl->GetDisplaysServices(sys, &displayService);
        if (ADLX_SUCCEEDED(res))
        {
            // Get display change handling
            IADLXDisplayChangedHandling* displayChangeHandl = NULL;
            res = displayService->pVtbl->GetDisplayChangedHandling(displayService, &displayChangeHandl);
            if (ADLX_SUCCEEDED(res))
            {
                DisplayGamutCallBack* displayGamutCallBack = (DisplayGamutCallBack*)malloc(sizeof(DisplayGamutCallBack));
                displayGamutCallBack->OnDisplayGamutChanged = &OnDisplayGamutChanged;

                // ADD callback to the handl
                ADLX_RESULT addListenerRes = ADLX_FAIL;
                {
                    addListenerRes = displayChangeHandl->pVtbl->AddDisplayGamutEventListener(displayChangeHandl, (IADLXDisplayGamutChangedListener*)&displayGamutCallBack);
                }

                // Set gamut for the first display
                IADLXDisplayList* displays = NULL;
                displayService->pVtbl->GetDisplays(displayService , &displays);
                adlx_uint it = 0;
                IADLXDisplay* display = NULL;
                displays->pVtbl->At_DisplayList(displays, it, &display);
                IADLXDisplayGamut* dispGamut = NULL;
                res = displayService->pVtbl->GetGamut(displayService, display, &dispGamut);
                res = dispGamut->pVtbl->SetGamut_PW_PG(dispGamut, WHITE_POINT_5000K, GAMUT_SPACE_CIE_RGB);
                printf("set gamut ret: %d\n", res);
                if (ADLX_SUCCEEDED(res))
                {
                    printf("This will trigger gamut change and send gamut change in thread: %d\n", GetCurrentThreadId());
                }
                if (NULL != dispGamut)
                {
                    dispGamut->pVtbl->Release(dispGamut);
                }
                if (NULL != display)
                {
                    display->pVtbl->Release(display);
                    display = NULL;
                }
                if (NULL != displays)
                {
                    displays->pVtbl->Release(displays);
                    displays = NULL;
                }

                if (ADLX_SUCCEEDED (addListenerRes))
                {
                    // Wait for gamut change
                    WaitForSingleObject(gamutChangedEvent, INFINITE);
                    CloseHandle(thread);

                    // Remove and destroy callback
                    res = displayChangeHandl->pVtbl->RemoveDisplayGamutEventListener(displayChangeHandl, (IADLXDisplayGamutChangedListener*)&displayGamutCallBack);
                    if (ADLX_FAILED (res))
                        printf("Remove display gamut event listener failed\n");
                }

                if (NULL != displayGamutCallBack)
                {
                    free(displayGamutCallBack);
                    displayGamutCallBack = NULL;
                }
            }

            // Release the displayChangeHandl interface
            if (NULL != displayChangeHandl)
            {
                displayChangeHandl->pVtbl->Release(displayChangeHandl);
                displayChangeHandl = NULL;
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

    // Close event
    if (gamutChangedEvent)
        CloseHandle(gamutChangedEvent);

    // Pause to see the print out
    system("pause");

    return 0;
}
