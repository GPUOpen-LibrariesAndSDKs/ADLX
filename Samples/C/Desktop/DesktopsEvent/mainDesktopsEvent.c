//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDesktopEvent.c
/// \brief Demonstrates how to access desktop changed handle options, add/remove call back for changed events, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IDesktops.h"
#include "SDK/Include/IDisplays.h"
#include "conio.h"

// Event to verify call back
HANDLE hDesktopChangedEvent = NULL;
HANDLE hQuitSignal = NULL;

// Call back to handle changed events
adlx_bool ADLX_STD_CALL OnDesktopListChanged(IADLXDesktopListChangedListener* pThis, IADLXDesktopList* pDesktopList)
{
    printf("Desktop list is changed\n");
    ADLX_RESULT res = ADLX_FAIL;
    adlx_bool slsActive = false;
    IADLXDesktop* desktop = NULL;
    for (adlx_uint crt = pDesktopList->pVtbl->Begin(pDesktopList); crt != pDesktopList->pVtbl->End(pDesktopList); crt++)
    {
        res = pDesktopList->pVtbl->At_DesktopList(pDesktopList, crt, &desktop);
        if (NULL != desktop)
        {
            ADLX_DESKTOP_TYPE adlxType;
            desktop->pVtbl->Type(desktop, &adlxType);
            if (adlxType == DESKTOP_EYEFINITY)
            {
                printf("Eyefinity Creation Event is received\n");
                slsActive = true;
                if (desktop != NULL)
                {
                    desktop->pVtbl->Release(desktop);
                    desktop = NULL;
                }
                break;
            }
            if (desktop != NULL)
            {
                desktop->pVtbl->Release(desktop);
                desktop = NULL;
            }
        }
    }

    if (false == slsActive)
    {
        printf("Eyefinity Destruction Event is received\n");
    }
    SetEvent(hDesktopChangedEvent);

    return true;
}

// Thread to detect quit input
DWORD WINAPI QuitWait(LPVOID lpParam);

static IADLXDesktopListChangedListenerVtbl vtbl = {&OnDesktopListChanged};
static IADLXDesktopListChangedListener eventListener = {&vtbl};

int main()
{
    // Add the following code to set environment variable
    LPCSTR EnvironmentVariable = "ADL_4KWORKAROUND_CANCEL";
    SetEnvironmentVariableA(EnvironmentVariable, "TRUE");

    // Define return code
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = ADLXHelper_Initialize();
    IADLXSystem* sys = ADLXHelper_GetSystemServices();
    IADLXDesktopServices* desktopServices = NULL;
    IADLXSimpleEyefinity* eyefinity = NULL;
    IADLXDesktopChangedHandling* eventHandling = NULL;
    IADLXEyefinityDesktop* eyefinityDesktop = NULL;
    if (ADLX_SUCCEEDED(res))
    {
        // Create desktop changed event and user input event
        hDesktopChangedEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        hQuitSignal = CreateEvent(NULL, TRUE, FALSE, NULL);
        HANDLE hSignalArray[2] = { hDesktopChangedEvent, hQuitSignal };

        // Get desktop services
        res = sys->pVtbl->GetDesktopsServices(sys, &desktopServices);

        if (desktopServices != NULL && ADLX_SUCCEEDED(res))
        {
            adlx_uint numDesktop;
            res = desktopServices->pVtbl->GetNumberOfDesktops(desktopServices, &numDesktop);
            printf("The number of desktop is: %d\n", numDesktop);

            desktopServices->pVtbl->GetSimpleEyefinity(desktopServices, &eyefinity);
            if (eyefinity != NULL && ADLX_SUCCEEDED(res))
            {
                // Verify if Eyefinity is supported
                adlx_bool supported = false;
                eyefinity->pVtbl->IsSupported(eyefinity, &supported);
                if (supported)
                {
                    desktopServices->pVtbl->GetDesktopChangedHandling(desktopServices, &eventHandling);
                    eventHandling->pVtbl->AddDesktopListEventListener(eventHandling, &eventListener);

                    printf("Waiting for desktop event... Press Q/q to quit\n");
                    // create a thread to detect user's input for quit
                    adlx_bool loopFlag = true;
                    DWORD threadId = 0;
                    HANDLE hThread = CreateThread(NULL, 0, QuitWait, &loopFlag, 0, &threadId);

                    res = eyefinity->pVtbl->Create(eyefinity, &eyefinityDesktop);

                    while (true)
                    {
                        // Waiting for receiving desktop event or user exit event
                        WaitForMultipleObjects(2, hSignalArray, FALSE, INFINITE);
                        if (!loopFlag)
                        {
                            CloseHandle(hThread);
                            break;
                        }
                        ResetEvent(hDesktopChangedEvent);
                    }

                    res = eyefinity->pVtbl->DestroyAll(eyefinity);
                    eventHandling->pVtbl->RemoveDesktopListEventListener(eventHandling, &eventListener);
                }
                else
                {
                    printf("Do not support eyefinity\n");
                }
            }
            else
            {
                printf("Get simple eyefinity failed\n");
            }
        }
        else
        {
            printf("Failed to get the desktop Services\n");
        }
    }
    else
    {
        printf("ADLX initialize failed\n");
        return 0;
    }

    if (eyefinityDesktop != NULL)
    {
        eyefinityDesktop->pVtbl->Release(eyefinityDesktop);
        eyefinityDesktop = NULL;
    }
    if (eventHandling != NULL)
    {
        eventHandling->pVtbl->Release(eventHandling);
        eventHandling = NULL;
    }
    if (eyefinity != NULL)
    {
        eyefinity->pVtbl->Release(eyefinity);
        eyefinity = NULL;
    }
    if (desktopServices != NULL)
    {
        desktopServices->pVtbl->Release(desktopServices);
        desktopServices = NULL;
    }

    // Destroy ADLX
    res = ADLXHelper_Terminate();
    printf("Destroy ADLX res: %d\n", res);

    // Close event
    if (hDesktopChangedEvent)
        CloseHandle(hDesktopChangedEvent);
    if (hQuitSignal)
        CloseHandle(hQuitSignal);

    // Pause for user see the print out
    system("pause");

    return 0;
}

DWORD WINAPI QuitWait(LPVOID lpParam)
{
    adlx_bool* loopFlag = (adlx_bool*)lpParam;
    while (true)
    {
        // Non-block I/O, check I/O cache whether have characters.
        if (_kbhit())
        {
            char c;
            if ((c = getchar()) == 'q' || c == 'Q')
            {
                *loopFlag = false;
                SetEvent(hQuitSignal);
            }
        }
        Sleep(100);
    }
}