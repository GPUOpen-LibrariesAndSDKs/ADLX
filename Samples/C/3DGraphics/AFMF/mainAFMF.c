//
// Copyright (c) 2023 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainAFMF.c
/// \brief Demonstrates how to access AMD Fluid Motion Frames options, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/I3DSettings1.h"


// Display AFMF support
void ShowAFMFSupport(IADLX3DAMDFluidMotionFrames* d3dAFMF);

// Display current AFMF state
void GetAFMFState(IADLX3DAMDFluidMotionFrames* d3dAFMF);

// Set AFMF state
void SetAFMFState(IADLX3DAMDFluidMotionFrames* d3dAFMF, int index);

// Menu
void MainMenu();

// Menu control
void MenuControl(IADLX3DAMDFluidMotionFrames* d3dAFMF);

int main()
{
    // Define return code
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = ADLXHelper_Initialize();
    if (ADLX_SUCCEEDED(res))
    {
        // Get System Services
        IADLXSystem* sys = ADLXHelper_GetSystemServices();

        // Get 3DSettings service
        IADLX3DSettingsServices* d3dSettingSrv = NULL;
        IADLX3DSettingsServices1* d3dSettingSrv1 = NULL;
        res = sys->pVtbl->Get3DSettingsServices(sys, &d3dSettingSrv);

        if (ADLX_SUCCEEDED(res))
        {
						
            d3dSettingSrv->pVtbl->QueryInterface(d3dSettingSrv, IID_IADLX3DSettingsServices1(),(&d3dSettingSrv1));

            if (d3dSettingSrv1 != NULL)
            {

                // Get AFMF interface
                IADLX3DAMDFluidMotionFrames* d3dAFMF = NULL;
                res = d3dSettingSrv1->pVtbl->GetAMDFluidMotionFrames(d3dSettingSrv1, &d3dAFMF);
                if (ADLX_SUCCEEDED(res))
                {
                    MainMenu();
                    MenuControl(d3dAFMF);
                }

                // Release AFMF interface
                if (d3dAFMF != NULL)
                {
                    d3dAFMF->pVtbl->Release(d3dAFMF);
                    d3dAFMF = NULL;
                }
              
            }
            else
            {
                printf("3DSettings services1 not supported\n");
            }
        }
        else
        {
            printf("Failed to get 3DSettings services\n");
        }
        // Release the 3DSettingsService1 interface
        if (d3dSettingSrv1 != NULL)
        {
            d3dSettingSrv1->pVtbl->Release(d3dSettingSrv1);
            d3dSettingSrv1 = NULL;
        }

        // Release the 3DSettingsService interface
        if (d3dSettingSrv != NULL)
        {
            d3dSettingSrv->pVtbl->Release(d3dSettingSrv);
            d3dSettingSrv = NULL;
        }
    }
    else
    {
        printf("ADLX initialization failed\n");
        return 0;
    }

    // Destroy ADLX
    res = ADLXHelper_Terminate();
    printf("Destroy ADLX res: %d\n", res);

    // Pause to see the print out
    system("pause");

    return 0;
}

void ShowAFMFSupport(IADLX3DAMDFluidMotionFrames* d3dAFMF)
{
    adlx_bool supported = false;
    ADLX_RESULT res = d3dAFMF->pVtbl->IsSupported(d3dAFMF, &supported);
    printf("\tIsSupported: %d, return code is: %d(0 means success)\n", supported, res);
}

void GetAFMFState(IADLX3DAMDFluidMotionFrames* d3dAFMF)
{
    adlx_bool enabled = false;
    ADLX_RESULT res = d3dAFMF->pVtbl->IsEnabled(d3dAFMF, &enabled);
    printf("\tIsEnabled: %d, return code is: %d(0 means success)\n", enabled, res);
}

void SetAFMFState(IADLX3DAMDFluidMotionFrames* d3dAFMF, int index)
{
    ADLX_RESULT res = d3dAFMF->pVtbl->SetEnabled(d3dAFMF, index == 0);
    printf("\tReturn code is: %d (0 means Success)\n", res);

}

void MainMenu()
{
    printf("\tChoose from the following options:\n");

    printf("\t->Press 1 to check if AMD Fluid Motion Frames is supported\n");
    printf("\t->Press 2 to display current AMD Fluid Motion Frames state\n");
    printf("\t->Press 3 to enable AFMF\n");
    printf("\t->Press 4 to disable AFMF\n");

    printf("\t->Press Q/q to quit the application\n");
    printf("\t->Press M/m to display main menu\n");
}

void MenuControl(IADLX3DAMDFluidMotionFrames* d3dAFMF)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display AMD Fluid Motion Frames support
        case '1':
            ShowAFMFSupport(d3dAFMF);
            break;

            // Display current AMD Fluid Motion Frames state
        case '2':
            GetAFMFState(d3dAFMF);
            break;

            // Set AMD Fluid Motion Frames
        case '3':
        case '4':
            SetAFMFState(d3dAFMF, num - '3');
            break;

            // Display menu options
        case 'm':
        case 'M':
            MainMenu();
            break;
        default:
            break;
        }
    }
}