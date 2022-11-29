//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplaySettingsEvent.cpp
/// \brief Demonstartes how to handle notifications about changes in display settings.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IDisplays.h"
#include "SDK/Include/IDisplaySettings.h"
#include <unordered_map>
#include <iostream>
#include <string>

using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// so we use global variables to ensure the validity of the interface.
static ADLXHelper g_ADLXHelp;

// Block event to verify call back
HANDLE hDisplaySettingsChangeEvt = nullptr;

// Get the display unique name
void DisplayUniqueName(IADLXDisplayPtr display, char* uniqueName);

// Call back to handle changed events
class DisplaySettingsListener : public IADLXDisplaySettingsChangedListener
{
public:
    adlx_bool ADLX_STD_CALL OnDisplaySettingsChanged (IADLXDisplaySettingsChangedEvent* pDisplaySettingChangedEvent)
    {
        if (pDisplaySettingChangedEvent == nullptr)
            return false;

        IADLXDisplayPtr pDisplay;
        ADLX_RESULT res = pDisplaySettingChangedEvent->GetDisplay (&pDisplay);
        char displayName[128] = "Unknown";
        DisplayUniqueName(pDisplay, displayName);
        adlx_bool VSRChanged = pDisplaySettingChangedEvent->IsVSRChanged ();
        std::cout <<"Display: " << displayName << "\nOnDisplaySettingsChanged(), VSR changed: " << (VSRChanged ? "true" : "false") << std::endl;

        SetEvent (hDisplaySettingsChangeEvt);

        return true;
    }
};

// Wait for exit with error message
int WaitAndExit (const char* msg, const int retCode);

int main ()
{
    ADLX_RESULT res = ADLX_FAIL;

    res = g_ADLXHelp.Initialize ();
    if (ADLX_SUCCEEDED (res))
    {
        hDisplaySettingsChangeEvt = CreateEvent(NULL, TRUE, FALSE, NULL);

        IADLXDisplayServicesPtr pDisplayService = nullptr;
        IADLXDisplayListPtr pDisplayList = nullptr;
        IADLXDisplayPtr pDisplay = nullptr;

        ADLX_RESULT res = g_ADLXHelp.GetSystemServices ()->GetDisplaysServices (&pDisplayService);
        if (ADLX_SUCCEEDED (res))
        {
            // Taking VSR event change as an example
            IADLXDisplayVSRPtr pDisplayVSR = nullptr;
            res = pDisplayService->GetDisplays (&pDisplayList);
            if (ADLX_SUCCEEDED (res) && !pDisplayList->Empty ())
            {
                res = pDisplayList->At (0, &pDisplay);
                if ((ADLX_SUCCEEDED (res)) && pDisplay != nullptr)
                {
                    res = pDisplayService->GetVirtualSuperResolution (pDisplay, &pDisplayVSR);
                    if (ADLX_FAILED (res))
                        return -1;

                    adlx_bool supported = false;
                    res = pDisplayVSR->IsSupported (&supported);
                    if (ADLX_FAILED (res))
                        return -1;

                    if (supported)
                    {
                        adlx_bool enabled = false;
                        res = pDisplayVSR->IsEnabled (&enabled);
                        if (ADLX_FAILED (res))
                            return -1;

                        IADLXDisplayChangedHandlingPtr pHandler;
                        res = pDisplayService->GetDisplayChangedHandling (&pHandler);
                        if (ADLX_FAILED (res))
                            return -1;

                        if (pHandler != nullptr)
                        {
                            IADLXDisplaySettingsChangedListener* pListener = new DisplaySettingsListener;
                            pHandler->AddDisplaySettingsEventListener (pListener);

                            ResetEvent (hDisplaySettingsChangeEvt);

                            res = pDisplayVSR->SetEnabled (!enabled);
                            if (ADLX_FAILED (res))
                                goto END;

                            DWORD r = WaitForSingleObject (hDisplaySettingsChangeEvt, 1000);
                            if (WAIT_OBJECT_0 == r)
                                std::cout << "Received VSR changed event." << std::endl;

                            res = pHandler->RemoveDisplaySettingsEventListener (pListener);
                            if (ADLX_FAILED (res))
                                goto END;

                            res = pDisplayVSR->SetEnabled (enabled);
                            if (ADLX_FAILED (res))
                                goto END;

                        END:
                            delete pListener;
                        }
                    }
                }
            }
        }
    }

    if (hDisplaySettingsChangeEvt)
        CloseHandle (hDisplaySettingsChangeEvt);

    res = g_ADLXHelp.Terminate ();
    std::cout << "Destroy ADLX result: " << res << std::endl;

    system ("pause");

    return 0;
}

void DisplayUniqueName(IADLXDisplayPtr display, char* uniqueName)
{
    if (nullptr != display && nullptr != uniqueName)
    {
        const char* gpuName = nullptr;
        display->Name(&gpuName);
        adlx_size id;
        display->UniqueId(&id);
        sprintf_s(uniqueName, 128, "name:%s, id:%zu", gpuName, id);
    }
}