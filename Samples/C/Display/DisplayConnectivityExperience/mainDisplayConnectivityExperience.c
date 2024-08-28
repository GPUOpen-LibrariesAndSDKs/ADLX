//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayConnectivityExperience.c
/// \brief Demonstrates how to access Connectivity-Experience when programming with ADLX and perform related operations.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/IDisplaySettings.h"
#include "SDK/Include/IDisplays2.h"

// Display supported HDMI quality detection
void ShowSupportedHDMIQualityDetection(const IADLXDisplayServices2* displayService2, const IADLXDisplay* display);

// Display supported DP link
void ShowSupportedDPLink(const IADLXDisplayServices2* displayService2, const IADLXDisplay* display);

// Display current HDMI quality detection state
void GetEnabledHDMIQualityDetection(const IADLXDisplayServices2* displayService2, const IADLXDisplay* display);

// Set displayVariBright status to enable/disable
void SetEnabledHDMIQualityDetection(const IADLXDisplayServices2* displayService2, const IADLXDisplay* display, adlx_bool enableDisable);

// Display DP link rate value
void GetDPLinkRate(const IADLXDisplayServices2* displayService2, const IADLXDisplay* display);

// Display number of active lanes
void GetNumberOfActiveLanes(const IADLXDisplayServices2* displayService2, const IADLXDisplay* display);

// Display number of total lanes
void GetNumberOfTotalLanes(const IADLXDisplayServices2* displayService2, const IADLXDisplay* display);

// Display relative pre-emphasis
void GetRelativePreEmphasis(const IADLXDisplayServices2* displayService2, const IADLXDisplay* display);

// Relative pre-emphasis setting menu control
void RelativePreEmphasisSettingMenuControl(const IADLXDisplayServices2* displayService2, const IADLXDisplay* display);

// Set relative pre-emphasis
void SetRelativePreEmphasis(const IADLXDisplayServices2* displayService2, const IADLXDisplay* display, int relativePreEmphasis);

// Display relative pre-emphasis
void GetRelativeVoltageSwing(const IADLXDisplayServices2* displayService2, const IADLXDisplay* display);

// Relative voltage swing setting menu control
void RelativeVoltageSwingSettingMenuControl(const IADLXDisplayServices2* displayService2, const IADLXDisplay* display);

// Set relative pre-emphasis
void SetRelativeVoltageSwing(const IADLXDisplayServices2* displayService2, const IADLXDisplay* display, int relativeVoltageSwing);

// Display current link protection statue
void GetEnabledLinkProtection(const IADLXDisplayServices2* displayService2, const IADLXDisplay* display);

// Main menu
void MainMenu();

// Menu action control
void MenuControl(const IADLXDisplayServices2* displayService2, const IADLXDisplay* display);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

int main()
{
    // Define return code
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = ADLXHelper_Initialize ();
    if (ADLX_SUCCEEDED (res))
    {
        // Get system service
        IADLXSystem* sys = ADLXHelper_GetSystemServices ();

        // Get display service
        IADLXDisplayServices* displayService = NULL;
        res = sys->pVtbl->GetDisplaysServices (sys, &displayService);
        if (ADLX_SUCCEEDED (res))
        {
            IADLXDisplayServices2* displayServices2 = NULL;
            ADLX_RESULT res2 = displayService->pVtbl->QueryInterface(displayService, IID_IADLXDisplayServices2(), (void**)&displayServices2);

            // Get display list
            IADLXDisplayList* displayList = NULL;
            res = displayService->pVtbl->GetDisplays (displayService, &displayList);
            if (ADLX_SUCCEEDED (res) && ADLX_SUCCEEDED(res2))
            {
                // Inspect for the first display in the list
                adlx_uint it = 0;
                IADLXDisplay* display = NULL;
                res = displayList->pVtbl->At_DisplayList (displayList, it, &display);
                if (ADLX_SUCCEEDED (res))
                {
                    // Display main menu options
                    MainMenu ();
                    // Get and execute the choice
                    MenuControl (displayServices2, display);
                }

                // Release the display interface
                if (NULL != display)
                {
                    display->pVtbl->Release (display);
                    display = NULL;
                }
            }

            // Release the displayList interface
            if (NULL != displayList)
            {
                displayList->pVtbl->Release (displayList);
                displayList = NULL;
            }

            if (NULL != displayServices2)
            {
                displayServices2->pVtbl->Release(displayServices2);
                displayServices2 = NULL;
            }
        }

        // Release the displayService interface
        if (NULL != displayService)
        {
            displayService->pVtbl->Release (displayService);
            displayService = NULL;
        }
    }
    else
    {
        return WaitAndExit ("ADLX initialization failed", 0);
    }

    // Destroy ADLX
    res = ADLXHelper_Terminate ();
    printf ("Destroy ADLX res: %d\n", res);

    // Pause to see the print out
    system ("pause");

    return 0;
}

void ShowSupportedHDMIQualityDetection(const IADLXDisplayServices2* displayService2, const IADLXDisplay* display)
{
    IADLXDisplayConnectivityExperience* displayConnectivityExperience;
    ADLX_RESULT res = displayService2->pVtbl->GetDisplayConnectivityExperience(displayService2, display, &displayConnectivityExperience);
    if (ADLX_SUCCEEDED(res))
    {
        printf("  === Get HDMI quality detection Supported ===\n");
        adlx_bool supported = false;
        res = displayConnectivityExperience->pVtbl->IsSupportedHDMIQualityDetection(displayConnectivityExperience, &supported);
        printf ("\tHDMI quality detection is supported on the display: %s, return code: %d (0 means success)\n", supported ? "true" : "false", res);
        displayConnectivityExperience->pVtbl->Release(displayConnectivityExperience);
    }
}

void ShowSupportedDPLink(const IADLXDisplayServices2* displayService2, const IADLXDisplay* display)
{
    IADLXDisplayConnectivityExperience* displayConnectivityExperience;
    ADLX_RESULT res = displayService2->pVtbl->GetDisplayConnectivityExperience(displayService2, display, &displayConnectivityExperience);
    if (ADLX_SUCCEEDED(res))
    {
        printf ("  === Get DP Link Supported ===\n");
        adlx_bool supported = false;
        res = displayConnectivityExperience->pVtbl->IsSupportedDPLink(displayConnectivityExperience, &supported);
        printf ("\tDP Link is supported on the display: %s, return code: %d (0 means success)\n", supported ? "true" : "false", res);
        displayConnectivityExperience->pVtbl->Release(displayConnectivityExperience);
    }
}

void GetEnabledHDMIQualityDetection(const IADLXDisplayServices2* displayService2, const IADLXDisplay* display)
{
    IADLXDisplayConnectivityExperience* displayConnectivityExperience;
    ADLX_RESULT res = displayService2->pVtbl->GetDisplayConnectivityExperience(displayService2, display, &displayConnectivityExperience);
    if (ADLX_SUCCEEDED(res))
    {
        printf ("  === Get HDMI quality detection enabled ===\n");
        adlx_bool enabled = false;
        res = displayConnectivityExperience->pVtbl->IsEnabledHDMIQualityDetection(displayConnectivityExperience, &enabled);
        printf ("\tGetEnabled, result: %d enabled: %s\n", res, enabled ? "true" : "false");
        displayConnectivityExperience->pVtbl->Release(displayConnectivityExperience);
    }
}

void SetEnabledHDMIQualityDetection(const IADLXDisplayServices2* displayService2, const IADLXDisplay* display, adlx_bool enableDisable)
{
    IADLXDisplayConnectivityExperience* displayConnectivityExperience;
    ADLX_RESULT res = displayService2->pVtbl->GetDisplayConnectivityExperience(displayService2, display, &displayConnectivityExperience);
    if (ADLX_SUCCEEDED (res))
    {
        if (!enableDisable)
        {
            res = displayConnectivityExperience->pVtbl->SetEnabledHDMIQualityDetection(displayConnectivityExperience, false);
            printf ("\tSet enabled to false, result: %d (0 means success)\n", res);
        }
        else
        {
            res = displayConnectivityExperience->pVtbl->SetEnabledHDMIQualityDetection (displayConnectivityExperience, true);
            printf ("\tSet enabled to true, result: %d (0 means success)\n", res);
        }
        displayConnectivityExperience->pVtbl->Release(displayConnectivityExperience);
    }
}

void GetDPLinkRate(const IADLXDisplayServices2* displayService2, const IADLXDisplay* display)
{
    IADLXDisplayConnectivityExperience* displayConnectivityExperience;
    ADLX_RESULT res = displayService2->pVtbl->GetDisplayConnectivityExperience(displayService2, display, &displayConnectivityExperience);
    if (ADLX_SUCCEEDED(res))
    {
        printf ("  === Get DP link rate ===\n");
        ADLX_DP_LINK_RATE DPLinkRate = DP_LINK_RATE_UNKNOWN;
        res = displayConnectivityExperience->pVtbl->GetDPLinkRate(displayConnectivityExperience, &DPLinkRate);
        char *DPLinkRateStr = "DP_LINK_RATE_UNKNOWN";
        switch (DPLinkRate)
        {
        case DP_LINK_RATE_RBR:
            DPLinkRateStr = "DP_LINK_RATE_RBR";
            break;
        case DP_LINK_RATE_2_16GBPS:
            DPLinkRateStr = "DP_LINK_RATE_2_16GBPS";
            break;
        case DP_LINK_RATE_2_43GBPS:
            DPLinkRateStr = "DP_LINK_RATE_2_16GBPS";
            break;
        case DP_LINK_RATE_HBR:
            DPLinkRateStr = "DP_LINK_RATE_HBR";
            break;
        case DP_LINK_RATE_4_32GBPS:
            DPLinkRateStr = "DP_LINK_RATE_4_32GBPS";
            break;
        case DP_LINK_RATE_HBR2:
            DPLinkRateStr = "DP_LINK_RATE_HBR2";
            break;
        case DP_LINK_RATE_HBR3:
            DPLinkRateStr = "DP_LINK_RATE_HBR3";
            break;
        case DP_LINK_RATE_UHBR10:
            DPLinkRateStr = "DP_LINK_RATE_UHBR10";
            break;
        case DP_LINK_RATE_UHBR13D5:
            DPLinkRateStr = "DP_LINK_RATE_UHBR13D5";
            break;
        case DP_LINK_RATE_UHBR20:
            DPLinkRateStr = "DP_LINK_RATE_UHBR20";
            break;
        default:
            break;
        }
        printf("\tThe DP link rate on the display is %s , return code: %d (0 means success)\n", DPLinkRateStr, res);
        displayConnectivityExperience->pVtbl->Release(displayConnectivityExperience);
    }
}

void GetNumberOfActiveLanes(const IADLXDisplayServices2* displayService2, const IADLXDisplay* display)
{
    IADLXDisplayConnectivityExperience* displayConnectivityExperience;
    ADLX_RESULT res = displayService2->pVtbl->GetDisplayConnectivityExperience(displayService2, display, &displayConnectivityExperience);
    if (ADLX_SUCCEEDED(res))
    {
        printf ("  === Get number of active lanes ===\n");
        adlx_uint numberOfActiveLanes;
        res = displayConnectivityExperience->pVtbl->GetNumberOfActiveLanes(displayConnectivityExperience, &numberOfActiveLanes);
        printf ("\tGetValue, result: %d value: %d\n", res, numberOfActiveLanes);
    }
}

void GetNumberOfTotalLanes(const IADLXDisplayServices2* displayService2, const IADLXDisplay* display)
{
    IADLXDisplayConnectivityExperience* displayConnectivityExperience;
    ADLX_RESULT res = displayService2->pVtbl->GetDisplayConnectivityExperience(displayService2, display, &displayConnectivityExperience);
    if (ADLX_SUCCEEDED(res))
    {
        printf ("  === Get number of total lanes ===\n");
        adlx_uint numberOfTotalLanes;
        res = displayConnectivityExperience->pVtbl->GetNumberOfTotalLanes(displayConnectivityExperience, &numberOfTotalLanes);
        printf ("\tGetValue, result: %d value %d\n", res, numberOfTotalLanes);
        displayConnectivityExperience->pVtbl->Release(displayConnectivityExperience);
    }
}

void GetRelativePreEmphasis(const IADLXDisplayServices2* displayService2, const IADLXDisplay* display)
{
    IADLXDisplayConnectivityExperience* displayConnectivityExperience;
    ADLX_RESULT res = displayService2->pVtbl->GetDisplayConnectivityExperience(displayService2, display, &displayConnectivityExperience);
    if (ADLX_SUCCEEDED(res))
    {
        printf ("  === Get relative pre-emphasis ===\n");
        adlx_int relativePreEmphasis;
        res = displayConnectivityExperience->pVtbl->GetRelativePreEmphasis(displayConnectivityExperience, &relativePreEmphasis);
        printf( "\tGetValue, result: %d value: %d\n", res, relativePreEmphasis);
        displayConnectivityExperience->pVtbl->Release(displayConnectivityExperience);
    }
}

void RelativePreEmphasisSettingMenuControl(const IADLXDisplayServices2* displayService2, const IADLXDisplay* display)
{
    printf ("  === relative pre-emphasis setting ===\n");
    printf ("\t->Press integer in [-2:2] to set relative pre-emphasis or return main menu\n");
    int num = 0;
    if (scanf_s("%d", &num) && (-2 <= num && num <= 2))
    {
        SetRelativePreEmphasis(displayService2, display, num);
    }
}

void SetRelativePreEmphasis(const IADLXDisplayServices2* displayService2, const IADLXDisplay* display, int relativePreEmphasis)
{
    IADLXDisplayConnectivityExperience* displayConnectivityExperience;
    ADLX_RESULT res = displayService2->pVtbl->GetDisplayConnectivityExperience(displayService2, display, &displayConnectivityExperience);
    if (ADLX_SUCCEEDED(res))
    {
        printf ("  === Set relative pre-emphasis ===\n");
        res = displayConnectivityExperience->pVtbl->SetRelativePreEmphasis(displayConnectivityExperience, relativePreEmphasis);
        printf ("\tReturn code is: %d (0 means success)\n", res);
        displayConnectivityExperience->pVtbl->Release(displayConnectivityExperience);
    }
}

void GetRelativeVoltageSwing(const IADLXDisplayServices2* displayService2, const IADLXDisplay* display)
{
    IADLXDisplayConnectivityExperience* displayConnectivityExperience;
    ADLX_RESULT res = displayService2->pVtbl->GetDisplayConnectivityExperience(displayService2, display, &displayConnectivityExperience);
    if (ADLX_SUCCEEDED(res))
    {
        printf ("  === Get relative voltage swing ===\n");
        adlx_int relativeVoltageSwing;
        res = displayConnectivityExperience->pVtbl->GetRelativeVoltageSwing(displayConnectivityExperience, &relativeVoltageSwing);
        printf ("\tGetValue, result: %d value: %d\n", res, relativeVoltageSwing);
        displayConnectivityExperience->pVtbl->Release(displayConnectivityExperience);
    }
}

void RelativeVoltageSwingSettingMenuControl(const IADLXDisplayServices2* displayService2, const IADLXDisplay* display)
{
    printf ("  === relative voltage swing setting ===\n");
    printf ("\t->Press integer in [-2:2] to set relative voltage swing or return main menu\n");
    int num = 0;
    if (scanf_s("%d", &num) && (-2 <= num && num <= 2))
    {
        SetRelativeVoltageSwing(displayService2, display, num);
    }
}

void SetRelativeVoltageSwing(const IADLXDisplayServices2* displayService2, const IADLXDisplay* display, int relativeVoltageSwing)
{
    IADLXDisplayConnectivityExperience* displayConnectivityExperience;
    ADLX_RESULT res = displayService2->pVtbl->GetDisplayConnectivityExperience(displayService2, display, &displayConnectivityExperience);
    if (ADLX_SUCCEEDED(res))
    {
        printf ("  === Set relative voltage swing ===\n");
        res = displayConnectivityExperience->pVtbl->SetRelativeVoltageSwing(displayConnectivityExperience, relativeVoltageSwing);
        printf ("\tReturn code is: %d (0 means success)\n", res);
        displayConnectivityExperience->pVtbl->Release(displayConnectivityExperience);
    }
}

void GetEnabledLinkProtection(const IADLXDisplayServices2* displayService2, const IADLXDisplay* display)
{
    IADLXDisplayConnectivityExperience* displayConnectivityExperience;
    ADLX_RESULT res = displayService2->pVtbl->GetDisplayConnectivityExperience(displayService2, display, &displayConnectivityExperience);
    if (ADLX_SUCCEEDED(res))
    {
        printf ("  === Get link protection enabled ===\n");
        adlx_bool enabled = false;
        res = displayConnectivityExperience->pVtbl->IsEnabledLinkProtection(displayConnectivityExperience, &enabled);
        printf ("\tGetEnabled, result: %d enabled: %s\n", res, enabled ? "true" : "false");
        displayConnectivityExperience->pVtbl->Release(displayConnectivityExperience);
    }
}


void MainMenu()
{
    printf ("\tChoose from following options\n");

    printf ("\t->Press 1 to display HDMI quality detection support\n");
    printf ("\t->Press 2 to display DP link support\n");
    printf ("\t->Press 3 to get HDMI quality detection status\n");
    printf ("\t->Press 4 to set HDMI quality detection status to Enable\n");
    printf ("\t->Press 5 to set HDMI quality detection status to Disable\n");
    printf ("\t->Press 6 to display DP link rate\n");
    printf ("\t->Press 7 to display number of active lanes\n");
    printf ("\t->Press 8 to display number of total lanes\n");
    printf ("\t->Press 9 to display relative pre-emphasis\n");
    printf ("\t->Press a to enter the Relative Pre-emphasis settings menu\n");
    printf ("\t->Press b to display relative voltage swing\n");
    printf ("\t->Press c to enter the Relative Voltage Swing settings menu\n");
    printf ("\t->Press d to display is link protection is enabled\n");

    printf ("\t->Press Q/q to terminate the application\n");
    printf ("\t->Press M/m to display main menu options\n");
}

// Menu action control
void MenuControl(const IADLXDisplayServices2* displayService2, const IADLXDisplay* display)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display supported HDMI quality detection
        case '1':
            ShowSupportedHDMIQualityDetection(displayService2, display);
            break;

            // Display ssupported DP link
        case '2':
            ShowSupportedDPLink(displayService2, display);
            break;

            // Get HDMI quality detection enable
        case '3':
             GetEnabledHDMIQualityDetection(displayService2, display);
            break;

            // Set HDMI quality detection enable
        case '4':
            SetEnabledHDMIQualityDetection(displayService2, display, true);
            break;

            // Set HDMI quality detection disable
        case '5':
            SetEnabledHDMIQualityDetection(displayService2, display, false);
            break;

            // Display DP link rate
        case '6':
            GetDPLinkRate(displayService2, display);
            break;

            // Display number of active lanes
        case '7':
            GetNumberOfActiveLanes(displayService2, display);
            break;

            // Display number of totla lanes
        case '8':
            GetNumberOfTotalLanes(displayService2, display);
            break;

            // Display relative pre-emphasis
        case '9':
            GetRelativePreEmphasis(displayService2, display);
            break;

            // Enter relative pre-emphasis setting control
        case 'a':
            RelativePreEmphasisSettingMenuControl(displayService2, display);
            break;

            // Display relative voltage swing
        case 'b':
            GetRelativeVoltageSwing(displayService2, display);
            break;

            // Enter relative voltage swing setting control
        case 'c':
            RelativeVoltageSwingSettingMenuControl(displayService2, display);
            break;

            // Display link protection status
        case 'd':
            GetEnabledLinkProtection(displayService2, display);
            break;

        case 'm':
        case 'M':
            MainMenu();
            break;

        default:
            break;
        }
    }
}

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode)
{
    // Printout the message and pause to see it before returning the desired code
    if (NULL != msg)
        printf ("%s\n", msg);

    system("Pause");
    return retCode;
}
