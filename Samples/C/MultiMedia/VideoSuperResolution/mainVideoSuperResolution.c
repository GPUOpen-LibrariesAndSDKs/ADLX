//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainVideoSuperResolution.c
/// \brief Demonstrates how to control video upscale when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include//IMultimedia.h"
#include "SDK/Include/ISystem2.h"

// Menu
void MainMenu();

// Menu control
void MenuControl(IADLXVideoSuperResolution* videoSuperResolution);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

// Display video Super Resolution support
void ShowVideoSuperResolutionSupport(IADLXVideoSuperResolution* videoSuperResolution);

// Display current video Super Resolution state
void GetVideoSuperResolutionState(IADLXVideoSuperResolution* videoSuperResolution);

// Set video upscale state
void SetVideoSuperResolutionState(IADLXVideoSuperResolution* videoSuperResolution, int index);


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

        // Get GPUs
        IADLXGPUList* gpus = NULL;
        res = sys->pVtbl->GetGPUs(sys, &gpus);

        // Get IADLXSystem2 interface
        IADLXSystem2* system2 = NULL;
        res = sys->pVtbl->QueryInterface(sys, IID_IADLXSystem2(), (void**)(&system2));

        if (ADLX_SUCCEEDED(res))
        {

            // Get multimedia services
            IADLXMultimediaServices* multimediaServices = NULL;
            res = system2->pVtbl->GetMultimediaServices(system2, &multimediaServices);

            if (ADLX_SUCCEEDED(res))
            {
                // Get GPU interface
                IADLXGPU* gpu = NULL;
                adlx_uint index = 0;
                res = gpus->pVtbl->At_GPUList(gpus, index, &gpu);

                //Get video Super Resolution interface
                IADLXVideoSuperResolution* videoSuperResolution = NULL;
                multimediaServices->pVtbl->GetVideoSuperResolution(multimediaServices, gpu, &videoSuperResolution);

                if (ADLX_SUCCEEDED(res))
                {
                    MainMenu();
                    MenuControl(videoSuperResolution);
                }

                // Release the video Super Resolution interface
                if (videoSuperResolution != NULL)
                {
                    videoSuperResolution->pVtbl->Release(videoSuperResolution);
                    videoSuperResolution = NULL;
                }

                // Release the GPU interface
                if (gpu != NULL)
                {
                    gpu->pVtbl->Release(gpu);
                    gpu = NULL;
                }
            }
            else
            {
                printf("Failed to get multimedia services\n");
            }

            // Release the multimedia services interface
            if (multimediaServices != NULL)
            {
                multimediaServices->pVtbl->Release(multimediaServices);
                multimediaServices = NULL;
            }
        }
        else
        {
            printf("Failed to get IADLXSystem2 interface\n");
        }

        // Release IADLXSystem2 interface
        if (system2 != NULL)
        {
            system2->pVtbl->Release(system2);
            system2 = NULL;
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

void MainMenu()
{
    printf("\tChoose from the following options:\n");

    printf("\t->Press 1 to display VideoSuperResolution support\n");
    printf("\t->Press 2 to display current VideoSuperResolution state\n");
    printf("\t->Press 3 to enable VideoSuperResolution\n");
    printf("\t->Press 4 to disable VideoSuperResolution\n");

    printf("\t->Press Q/q to quit the application\n");
    printf("\t->Press M/m to display menu options\n");
}

void ShowVideoSuperResolutionSupport(IADLXVideoSuperResolution* videoSuperResolution)
{
    adlx_bool supported = false;
    ADLX_RESULT res = videoSuperResolution->pVtbl->IsSupported(videoSuperResolution, &supported);
    if (ADLX_SUCCEEDED(res))
        printf("\tIsSupported: %d\n", supported);
}

void GetVideoSuperResolutionState(IADLXVideoSuperResolution* videoSuperResolution)
{
    adlx_bool enabled = false;
    ADLX_RESULT res = videoSuperResolution->pVtbl->IsEnabled(videoSuperResolution, &enabled);
    if (ADLX_SUCCEEDED(res))
        printf("\tIsEnabled: %d\n", enabled);
    printf("\tReturn code is: %d (0 means success)\n", res);
}

void SetVideoSuperResolutionState(IADLXVideoSuperResolution* videoSuperResolution, int index)
{
    ADLX_RESULT res = videoSuperResolution->pVtbl->SetEnabled(videoSuperResolution, index == 0);
    printf("\tReturn code is: %d (0 means success)\n", res);
}


void MenuControl(IADLXVideoSuperResolution* videoSuperResolution)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display video Super Resolution support
        case '1':
            ShowVideoSuperResolutionSupport(videoSuperResolution);
            break;

            // Display current video Super Resolution state
        case '2':
            GetVideoSuperResolutionState(videoSuperResolution);
            break;

            // Set video Super Resolution
        case '3':
        case '4':
            SetVideoSuperResolutionState(videoSuperResolution, num - '3');
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
