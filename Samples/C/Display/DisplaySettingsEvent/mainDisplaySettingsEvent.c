//
// Copyright (c) 2021 - 2023 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplaySettingsEvent.c
/// \brief Demonstartes how to handle notifications about changes in display settings when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/ISystem.h"
#include "SDK/Include/IDisplays.h"
#include "SDK/Include/IDisplaySettings.h"

HANDLE hDisplaySettingsChangeEvt = NULL;

// Get the display unique name
void DisplayUniqueName(IADLXDisplay* display, char* uniqueName);

// Call back to handle changed events
static adlx_bool ADLX_STD_CALL OnDisplaySettingsChanged (IADLXDisplaySettingsChangedListener* pThis, IADLXDisplaySettingsChangedEvent* pDisplaySettingChangedEvent)
{
    if (pDisplaySettingChangedEvent == NULL)
        return false;

    printf ("OnDisplaySettingsChanged(): Display settings change event received.\n");

    IADLXDisplay* pDisplay = NULL;
    ADLX_RESULT res = pDisplaySettingChangedEvent->pVtbl->GetDisplay (pDisplaySettingChangedEvent, &pDisplay);
    char displayName[128] = "Unknown";
    DisplayUniqueName(pDisplay, displayName);
    printf ("Display: %s\n", displayName);
    // Release display interface
    if (pDisplay != NULL)
    {
        pDisplay->pVtbl->Release (pDisplay);
    }

    adlx_bool VSRChanged = pDisplaySettingChangedEvent->pVtbl->IsVSRChanged (pDisplaySettingChangedEvent);
    printf ("OnDisplaySettingsChanged, IsVSRChanged:%s\n", VSRChanged ? "true" : "false");

    SetEvent (hDisplaySettingsChangeEvt);

    return true;
}

static IADLXDisplaySettingsChangedListenerVtbl vt = { &OnDisplaySettingsChanged };
static IADLXDisplaySettingsChangedListener DisplaySetingsEventListener = { &vt };

ADLX_RESULT GetDisplayServices (IADLXDisplayServices** ppDisplayServices)
{
    IADLXSystem* pSys = ADLXHelper_GetSystemServices ();
    if (pSys == NULL)
        return ADLX_FAIL;
    return pSys->pVtbl->GetDisplaysServices (pSys, ppDisplayServices);
}

ADLX_RESULT AddDisplaySettingsListener ()
{
    ADLX_RESULT res = ADLX_FAIL;

    IADLXDisplayServices* pDisplayServices = NULL;
    res = GetDisplayServices (&pDisplayServices);
    if (ADLX_SUCCEEDED (res) && pDisplayServices != NULL)
    {
        IADLXDisplayChangedHandling* pDisplayChangedHandler = NULL;
        res = pDisplayServices->pVtbl->GetDisplayChangedHandling (pDisplayServices, &pDisplayChangedHandler);
        if (ADLX_SUCCEEDED (res) && pDisplayChangedHandler)
        {
            res = pDisplayChangedHandler->pVtbl->AddDisplaySettingsEventListener (pDisplayChangedHandler, &DisplaySetingsEventListener);
            pDisplayChangedHandler->pVtbl->Release (pDisplayChangedHandler);
            pDisplayChangedHandler = NULL;
        }
        pDisplayServices->pVtbl->Release (pDisplayServices);
        pDisplayServices = NULL;
    }

    return res;
}

ADLX_RESULT RemoveDisplaySettingsListener ()
{
    ADLX_RESULT res = ADLX_FAIL;

    IADLXDisplayServices* pDisplayServices = NULL;
    res = GetDisplayServices (&pDisplayServices);
    if (ADLX_SUCCEEDED (res) && pDisplayServices != NULL)
    {
        IADLXDisplayChangedHandling* pDisplayChangedHandler = NULL;
        res = pDisplayServices->pVtbl->GetDisplayChangedHandling (pDisplayServices, &pDisplayChangedHandler);
        if (ADLX_SUCCEEDED (res) && pDisplayChangedHandler)
        {
            res = pDisplayChangedHandler->pVtbl->RemoveDisplaySettingsEventListener (pDisplayChangedHandler, &DisplaySetingsEventListener);
            pDisplayChangedHandler->pVtbl->Release (pDisplayChangedHandler);
            pDisplayChangedHandler = NULL;
        }
        pDisplayServices->pVtbl->Release (pDisplayServices);
        pDisplayServices = NULL;
    }

    return res;
}

// VSR helper
ADLX_RESULT IsVSRSupported (IADLXDisplay* pDisplay, adlx_bool* supported)
{
    ADLX_RESULT res = ADLX_FAIL;
    if (pDisplay == NULL || supported == NULL)
        return res;

    IADLXDisplayServices* pDisplayServices = NULL;
    res = GetDisplayServices (&pDisplayServices);
    if (ADLX_SUCCEEDED (res) && pDisplayServices != NULL)
    {
        IADLXDisplayVSR* pVSR = NULL;
        pDisplayServices->pVtbl->GetVirtualSuperResolution (pDisplayServices, pDisplay, &pVSR);

        res = pVSR->pVtbl->IsSupported (pVSR, supported);
        pVSR->pVtbl->Release (pVSR);
        pDisplayServices->pVtbl->Release (pDisplayServices);
    }

    return res;
}

ADLX_RESULT GetVSREnabled (IADLXDisplay* pDisplay, adlx_bool* enabled)
{
    ADLX_RESULT res = ADLX_FAIL;
    if (pDisplay == NULL || enabled == NULL)
        return res;

    IADLXDisplayServices* pDisplayServices = NULL;
    res = GetDisplayServices (&pDisplayServices);
    if (ADLX_SUCCEEDED (res) && pDisplayServices != NULL)
    {
        IADLXDisplayVSR* pVSR = NULL;
        pDisplayServices->pVtbl->GetVirtualSuperResolution (pDisplayServices, pDisplay, &pVSR);

        res = pVSR->pVtbl->IsEnabled (pVSR, enabled);
        pVSR->pVtbl->Release (pVSR);
        pDisplayServices->pVtbl->Release (pDisplayServices);
    }

    return res;
}

ADLX_RESULT SetVSREnabled (IADLXDisplay* pDisplay, adlx_bool enabled)
{
    ADLX_RESULT res = ADLX_FAIL;
    if (pDisplay == NULL)
        return res;

    IADLXDisplayServices* pDisplayServices = NULL;
    res = GetDisplayServices (&pDisplayServices);
    if (ADLX_SUCCEEDED (res) && pDisplayServices != NULL)
    {
        IADLXDisplayVSR* pVSR = NULL;
        pDisplayServices->pVtbl->GetVirtualSuperResolution (pDisplayServices, pDisplay, &pVSR);

        res = pVSR->pVtbl->SetEnabled (pVSR, enabled);
        pVSR->pVtbl->Release (pVSR);
        pDisplayServices->pVtbl->Release (pDisplayServices);
    }

    return res;
}

int main ()
{
    ADLX_RESULT res = ADLXHelper_Initialize ();
    if (ADLX_SUCCEEDED (res))
    {
        hDisplaySettingsChangeEvt = CreateEvent (NULL, TRUE, FALSE, NULL);

        IADLXDisplayServices* pDisplayService = NULL;
        IADLXDisplayList* pDisplayList = NULL;
        IADLXDisplay* pDisplay = NULL;

        res = GetDisplayServices (&pDisplayService);
        if (ADLX_SUCCEEDED (res) && pDisplayService != NULL)
        {
            res = pDisplayService->pVtbl->GetDisplays (pDisplayService, &pDisplayList);
            if (ADLX_SUCCEEDED (res))
            {
                if (pDisplayList && !pDisplayList->pVtbl->Empty (pDisplayList))
                {
                    IADLXDisplay* pDisplay = NULL;
                    res = pDisplayList->pVtbl->At_DisplayList (pDisplayList, 0, &pDisplay);
                    if (ADLX_SUCCEEDED (res) && pDisplay != NULL)
                    {
                        adlx_bool supported = false;
                        res = IsVSRSupported (pDisplay, &supported);
                        if (ADLX_SUCCEEDED (res) && supported)
                        {
                            adlx_bool enabled = false;
                            res = GetVSREnabled (pDisplay, &enabled);
                            if (ADLX_FAILED (res))
                                goto END;

                            res = AddDisplaySettingsListener ();
                            if (ADLX_FAILED (res))
                                goto END;

                            ResetEvent (hDisplaySettingsChangeEvt);

                            res = SetVSREnabled (pDisplay, !enabled);
                            if (ADLX_FAILED (res))
                                goto END;

                            DWORD r = WaitForSingleObject (hDisplaySettingsChangeEvt, 1000);
                            if (ADLX_FAILED (res))
                                goto END;

                            res = RemoveDisplaySettingsListener ();
                            if (ADLX_FAILED (res))
                                goto END;

                            res = SetVSREnabled (pDisplay, enabled);
                            if (ADLX_FAILED (res))
                                goto END;

                        }
                    END:
                        pDisplay->pVtbl->Release (pDisplay);
                    }
                    pDisplayList->pVtbl->Release (pDisplayList);
                }
            }
            pDisplayService->pVtbl->Release (pDisplayService);
        }
    }
    else
    {
        printf ("ADLX initialization failed\n");
        return 0;
    }

    res = ADLXHelper_Terminate ();
    printf ("Destroy ADLX result: %d\n", res);

    if (hDisplaySettingsChangeEvt)
        CloseHandle(hDisplaySettingsChangeEvt);

    system ("pause");

    return 0;
}

void DisplayUniqueName(IADLXDisplay* display, char* uniqueName)
{
    if (NULL != display && NULL != uniqueName)
    {
        const char* gpuName = NULL;
        ADLX_RESULT res = display->pVtbl->Name(display, &gpuName);
        if (ADLX_SUCCEEDED(res))
            sprintf_s(uniqueName, 128, "name:%s", gpuName);
        adlx_size id;
        res = display->pVtbl->UniqueId(display, &id);
        if (ADLX_SUCCEEDED(res))
            sprintf_s(uniqueName, 128, "id:%zu", id);
    }
}