//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainAFMF.c
/// \brief Demonstrates how to access AMD Fluid Motion Frames options, and perform related testing when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/I3DSettings3.h"


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

void GetAFMF1Status(IADLX3DAMDFluidMotionFrames* d3dAFMF)
{
    // Get AFMF1 interface
    IADLX3DAMDFluidMotionFrames1* d3dAFMF1 = NULL;
    ADLX_RESULT res = d3dAFMF->pVtbl->QueryInterface(d3dAFMF, IID_IADLX3DAMDFluidMotionFrames1(), (void**)&d3dAFMF1);
    if (ADLX_SUCCEEDED(res) && d3dAFMF1)
    {
        // Get AFMF1 status
        adlx_bool supported = false;
        res = d3dAFMF1->pVtbl->IsSupportedAlgorithm(d3dAFMF1, &supported);
        printf("\tIsSupportedAlgorithm: %d, return code is: %d(0 means success)\n", supported, res);

        // Get AFMF1 algorithm
        ADLX_AFMF_ALGORITHM algorithm;
        res = d3dAFMF1->pVtbl->GetAlgorithm(d3dAFMF1, &algorithm);
        printf("\tGetAlgorithm: %d, return code is: %d(0 means success)\n", algorithm, res);
        // Get AFMF1 search mode
        ADLX_AFMF_SEARCH_MODE_TYPE searchMode;
        res = d3dAFMF1->pVtbl->GetSearchMode(d3dAFMF1, &searchMode);
        printf("\tGetSearchMode: %d, return code is: %d(0 means success)\n", searchMode, res);
        // Get AFMF1 performance mode
        ADLX_AFMF_PERFORMANCE_MODE_TYPE performanceMode;
        res = d3dAFMF1->pVtbl->GetPerformanceMode(d3dAFMF1, &performanceMode);
        printf("\tGetPerformanceMode: %d, return code is: %d(0 means success)\n", performanceMode, res);
        // Get AFMF1 fast motion response
        ADLX_AFMF_FAST_MOTION_RESP fastMotionResponse;
        res = d3dAFMF1->pVtbl->GetFastMotionResponse(d3dAFMF1, &fastMotionResponse);
        printf("\tGetFastMotionResponse: %d, return code is: %d(0 means success)\n", fastMotionResponse, res);

        // Release AFMF1 interface
        d3dAFMF1->pVtbl->Release(d3dAFMF1);
    }
    else
    {
        printf("Failed to get AFMF1 interface\n");
    }
}

void SetAlgorithmCapabilities(IADLX3DAMDFluidMotionFrames* d3dAFMF)
{
    // Get AFMF1 interface
    IADLX3DAMDFluidMotionFrames1* d3dAFMF1 = NULL;
    ADLX_RESULT res = d3dAFMF->pVtbl->QueryInterface(d3dAFMF, IID_IADLX3DAMDFluidMotionFrames1(), (void**)&d3dAFMF1);
    if (ADLX_SUCCEEDED(res) && d3dAFMF1)
    {
        ADLX_AFMF_ALGORITHM algorithm;
        res = d3dAFMF1->pVtbl->GetAlgorithm(d3dAFMF1, &algorithm);
        // Set algorithm to a different value
        if (AFMF_ALGORITHM_AUTO == algorithm)
            algorithm = AFMF_ALGORITHM_STANDARD;
        else if (AFMF_ALGORITHM_ENHANCED == algorithm)
            algorithm = AFMF_ALGORITHM_STANDARD;
        else
            algorithm = AFMF_ALGORITHM_ENHANCED;

        // Set AFMF1 algorithm
        res = d3dAFMF1->pVtbl->SetAlgorithm(d3dAFMF1, algorithm);
        printf("\tSetAlgorithm: %d, return code is: %d(0 means success)\n", algorithm, res);
        // Release AFMF1 interface
        d3dAFMF1->pVtbl->Release(d3dAFMF1);
    }
    else
    {
        printf("Failed to get AFMF1 interface\n");
    }
}

void SetSearchMode(IADLX3DAMDFluidMotionFrames* d3dAFMF)
{
    // Get AFMF1 interface
    IADLX3DAMDFluidMotionFrames1* d3dAFMF1 = NULL;
    ADLX_RESULT res = d3dAFMF->pVtbl->QueryInterface(d3dAFMF, IID_IADLX3DAMDFluidMotionFrames1(), (void**)&d3dAFMF1);
    if (ADLX_SUCCEEDED(res) && d3dAFMF1)
    {
        ADLX_AFMF_SEARCH_MODE_TYPE searchMode;
        res = d3dAFMF1->pVtbl->GetSearchMode(d3dAFMF1, &searchMode);
        // Set search mode to a different value
        if (AFMF_SEARCH_MODE_AUTO == searchMode)
            searchMode = AFMF_SEARCH_MODE_STANDARD;
        else if (AFMF_SEARCH_MODE_STANDARD == searchMode)
            searchMode = AFMF_SEARCH_MODE_HIGH;
        else
            searchMode = AFMF_SEARCH_MODE_AUTO;
        // Set AFMF1 search mode
        res = d3dAFMF1->pVtbl->SetSearchMode(d3dAFMF1, searchMode);
        printf("\tSetSearchMode: %d, return code is: %d(0 means success)\n", searchMode, res);
        // Release AFMF1 interface
        d3dAFMF1->pVtbl->Release(d3dAFMF1);
    }
    else
    {
        printf("Failed to get AFMF1 interface\n");
    }
}

void SetPerformanceMode(IADLX3DAMDFluidMotionFrames* d3dAFMF)
{
    // Get AFMF1 interface
    IADLX3DAMDFluidMotionFrames1* d3dAFMF1 = NULL;
    ADLX_RESULT res = d3dAFMF->pVtbl->QueryInterface(d3dAFMF, IID_IADLX3DAMDFluidMotionFrames1(), (void**)&d3dAFMF1);
    if (ADLX_SUCCEEDED(res) && d3dAFMF1)
    {
        ADLX_AFMF_PERFORMANCE_MODE_TYPE performanceMode;
        res = d3dAFMF1->pVtbl->GetPerformanceMode(d3dAFMF1, &performanceMode);
        // Set performance mode to a different value
        if (AFMF_PERFORMANCE_MODE_AUTO == performanceMode)
            performanceMode = AFMF_PERFORMANCE_MODE_QUALITY;
        else if (AFMF_PERFORMANCE_MODE_QUALITY == performanceMode)
            performanceMode = AFMF_PERFORMANCE_MODE_PERFORMANCE;
        else
            performanceMode = AFMF_PERFORMANCE_MODE_AUTO;

        // Set AFMF1 performance mode
        res = d3dAFMF1->pVtbl->SetPerformanceMode(d3dAFMF1, performanceMode);
        printf("\tSetPerformanceMode: %d, return code is: %d(0 means success)\n", performanceMode, res);
        // Release AFMF1 interface
        d3dAFMF1->pVtbl->Release(d3dAFMF1);
    }
    else
    {
        printf("Failed to get AFMF1 interface\n");
    }
}

void SetFastMotionResponse(IADLX3DAMDFluidMotionFrames* d3dAFMF)
{
    // Get AFMF1 interface
    IADLX3DAMDFluidMotionFrames1* d3dAFMF1 = NULL;
    ADLX_RESULT res = d3dAFMF->pVtbl->QueryInterface(d3dAFMF, IID_IADLX3DAMDFluidMotionFrames1(), (void**)&d3dAFMF1);
    if (ADLX_SUCCEEDED(res) && d3dAFMF1)
    {
        ADLX_AFMF_FAST_MOTION_RESP fastMotionResponse;
        res = d3dAFMF1->pVtbl->GetFastMotionResponse(d3dAFMF1, &fastMotionResponse);
        // Set fast motion response to a different value
        if (AFMF_RESP_REPEAT_FRAMES == fastMotionResponse)
            fastMotionResponse = AFMF_RESP_BLENDED_FRAMES;
        else
            fastMotionResponse = AFMF_RESP_REPEAT_FRAMES;
        // Set AFMF1 fast motion response
        res = d3dAFMF1->pVtbl->SetFastMotionResponse(d3dAFMF1, fastMotionResponse);
        printf("\tSetFastMotionResponse: %d, return code is: %d(0 means success)\n", fastMotionResponse, res);
        // Release AFMF1 interface
        d3dAFMF1->pVtbl->Release(d3dAFMF1);
    }
    else
    {
        printf("Failed to get AFMF1 interface\n");
    }
}
void MainMenu()
{
    printf("\tChoose from the following options:\n");

    printf("\t->Press 1 to check if AMD Fluid Motion Frames is supported\n");
    printf("\t->Press 2 to display current AMD Fluid Motion Frames state\n");
    printf("\t->Press 3 to enable AFMF\n");
    printf("\t->Press 4 to disable AFMF\n");
    printf("\t->Press 5 to display AFMF1 capabilities and state\n");
    printf("\t->Press 6 to set algorithm\n");
    printf("\t->Press 7 to set search mode\n");
    printf("\t->Press 8 to set performance mode\n");
    printf("\t->Press 9 to set fast motion response\n");

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

            // Get AFMF2.1 capabilities and state
        case '5':
            GetAFMF1Status(d3dAFMF);
            break;

            // Set AFMF1 algorithm
        case '6':
            SetAlgorithmCapabilities(d3dAFMF);
            break;

            // Set AFMF1 search mode
        case '7':
            SetSearchMode(d3dAFMF);
            break;
            // Set AFMF1 performance mode
        case '8':
            SetPerformanceMode(d3dAFMF);
            break;
            // Set AFMF1 fast motion response
        case '9':
            SetFastMotionResponse(d3dAFMF);
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
