//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayEvents.c
/// \brief Demontrates how to handle notifications about display change.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IDisplay3DLUT.h"
#include "SDK/Include/IDisplayGamma.h"
#include "SDK/Include/IDisplayGamut.h"
#include "SDK/Include/IDisplays.h"
#include <windows.h>

// Callback for displayListChanged
adlx_bool ADLX_STD_CALL OnDisplayListChanged(IADLXDisplayListChangedListener* pThis, IADLXDisplayList* pNewDisplays)
{
    printf("Display list has been changed\n");
    
    // If true is returned ADLX continues to notify next listener else if false is retuned ADLX stops the notification.
    return true;
}

// Callback struct for displayListChanged
typedef struct DisplayListCallBack
{
    adlx_bool(ADLX_STD_CALL* OnDisplayListChanged)(IADLXDisplayListChangedListener*, IADLXDisplayList*);
} DisplayListCallBack;

// Callback for displayGamut
adlx_bool ADLX_STD_CALL OnDisplayGamutChanged(IADLXDisplayGamutChangedListener* pThis, IADLXDisplayGamutChangedEvent* pDisplayGamutChangedEvent)
{
    printf("Display gamut has been changed\n");
    // If true is returned ADLX continues to notify next listener else if false is retuned ADLX stops the notification.
    return true;
}

// Callback struct for displayGamut
typedef struct DisplayGamutCallBack
{
    adlx_bool(ADLX_STD_CALL* OnDisplayGamutChanged)(IADLXDisplayGamutChangedListener*, IADLXDisplayGamutChangedEvent*);
} DisplayGamutCallBack;

// Callback for displayGammaChanged
adlx_bool ADLX_STD_CALL OnDisplayGammaChanged(IADLXDisplayGammaChangedListener* pThis, IADLXDisplayGammaChangedEvent* pDisplayGammaChangedEvent)
{
    printf("Display gamma has been changed\n");
    //If true is returned ADLX continues to notify next listener else if false is retuned ADLX stops the notification.
    printf("\tGamma ramp change: %d\n\tGamma coefficient change: %d\n\tRe-gamma change: %d\n\tDeGamma change: %d\n",
        pDisplayGammaChangedEvent->pVtbl->IsGammaRampChanged(pDisplayGammaChangedEvent),
        pDisplayGammaChangedEvent->pVtbl->IsGammaCoefficientChanged(pDisplayGammaChangedEvent),
        pDisplayGammaChangedEvent->pVtbl->IsReGammaChanged(pDisplayGammaChangedEvent),
        pDisplayGammaChangedEvent->pVtbl->IsDeGammaChanged(pDisplayGammaChangedEvent));

    return true;
}

// CallBack struct for displayGammaChanged
typedef struct DisplayGammaCallBack
{
    adlx_bool(ADLX_STD_CALL* OnDisplayGammaChanged)(IADLXDisplayGammaChangedListener*, IADLXDisplayGammaChangedEvent*);
} DisplayGammaCallBack;

// CallBack for display3DLUTChanged
adlx_bool ADLX_STD_CALL OnDisplay3DLUTChanged(IADLXDisplay3DLUTChangedListener* pThis, IADLXDisplay3DLUTChangedEvent* pDisplay3DLUTChangedEvent)
{
    printf("Display 3DLUT has been changed\n");
    // If true is returned ADLX continues to notify next listener else if false is retuned ADLX stops the notification.
    return true;
}

// CallBack struct for display3DLUT
typedef struct Display3DLUTCallBack
{
    adlx_bool(ADLX_STD_CALL* OnDisplay3DLUTChanged)(IADLXDisplay3DLUTChangedListener*, IADLXDisplay3DLUTChangedEvent*);
} Display3DLUTCallBack;

// loop thread
DWORD WINAPI LoopThread(LPVOID lpParam)
{
    printf("Loop thread is currently running.\n");
    printf("->Plug or unplug the display to trigger DisplayListChanged, which will further trigger other changes.\n");
    printf("->Press Q/q to terminate the loop.\n");
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        printf("Wait for the event to get triggered. The display can be pluged or unpluged to trigger DisplayListChange.\n");
        Sleep(1 * 1000);
        num = getchar();
        if (num == 'q' || num == 'Q')
            break;
    }
    return 0;
}

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode)
{
    // Printout the message and pause to see it before returning the desired code
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

        // Get display services
        IADLXDisplayServices* displayService = NULL;
        res = sys->pVtbl->GetDisplaysServices(sys, &displayService);
        if (ADLX_SUCCEEDED(res))
        {
            // Get displayChangeHandling
            IADLXDisplayChangedHandling* displayChangeHandl = NULL;
            res = displayService->pVtbl->GetDisplayChangedHandling(displayService, &displayChangeHandl);
            if (ADLX_SUCCEEDED(res))
            {
                // Create callback
                DisplayListCallBack* displayListCallBack = (DisplayListCallBack*)malloc(sizeof(DisplayListCallBack));
                displayListCallBack->OnDisplayListChanged = &OnDisplayListChanged;

                DisplayGamutCallBack* displayGamutCallBack = (DisplayGamutCallBack*)malloc(sizeof(DisplayGamutCallBack));
                displayGamutCallBack->OnDisplayGamutChanged = &OnDisplayGamutChanged;

                DisplayGammaCallBack* displayGammaCallBack = (DisplayGammaCallBack*)malloc(sizeof(DisplayGammaCallBack));
                displayGammaCallBack->OnDisplayGammaChanged = &OnDisplayGammaChanged;

                Display3DLUTCallBack* display3DLUTCallBack = (Display3DLUTCallBack*)malloc(sizeof(Display3DLUTCallBack));
                display3DLUTCallBack->OnDisplay3DLUTChanged = &OnDisplay3DLUTChanged;

                // Add callback to the handle
                {
                    displayChangeHandl->pVtbl->AddDisplayListEventListener(displayChangeHandl, (IADLXDisplayListChangedListener*)&displayListCallBack);
                    displayChangeHandl->pVtbl->AddDisplayGamutEventListener(displayChangeHandl, (IADLXDisplayGamutChangedListener*)&displayGamutCallBack);
                    displayChangeHandl->pVtbl->AddDisplayGammaEventListener(displayChangeHandl, (IADLXDisplayGammaChangedListener*)&displayGammaCallBack);
                    displayChangeHandl->pVtbl->AddDisplay3DLUTEventListener(displayChangeHandl, (IADLXDisplay3DLUTChangedListener*)&display3DLUTCallBack);
                }

                // Create loop thread for wait event
                HANDLE thread = CreateThread(NULL, 0, LoopThread, NULL, 0, NULL);
                WaitForSingleObject(thread, INFINITE);
                CloseHandle(thread);

                // Remove and destroy callback
                displayChangeHandl->pVtbl->RemoveDisplayListEventListener(displayChangeHandl, (IADLXDisplayListChangedListener*)&displayListCallBack);
                displayChangeHandl->pVtbl->RemoveDisplayGamutEventListener(displayChangeHandl, (IADLXDisplayGamutChangedListener*)&displayGamutCallBack);
                displayChangeHandl->pVtbl->RemoveDisplayGammaEventListener(displayChangeHandl, (IADLXDisplayGammaChangedListener*)&displayGammaCallBack);
                displayChangeHandl->pVtbl->RemoveDisplay3DLUTEventListener(displayChangeHandl, (IADLXDisplay3DLUTChangedListener*)&display3DLUTCallBack);

                if (NULL != displayListCallBack)
                {
                    free(displayListCallBack);
                    displayListCallBack = NULL;
                }

                if (NULL != displayGamutCallBack)
                {
                    free(displayGamutCallBack);
                    displayGamutCallBack = NULL;
                }

                if (NULL != displayGammaCallBack)
                {
                    free(displayGammaCallBack);
                    displayGammaCallBack = NULL;
                }

                if (NULL != display3DLUTCallBack)
                {
                    free(display3DLUTCallBack);
                    display3DLUTCallBack = NULL;
                }
            }

            // Release the  displayChangehandl interface
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

    // Pause to see the print out
    system("pause");

    return 0;
}