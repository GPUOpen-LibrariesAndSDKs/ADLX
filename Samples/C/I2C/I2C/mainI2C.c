//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainI2C.c
/// \brief Demonstrates how to read and write data with I2C when programming with ADLX.

#include "SDK/ADLXHelper/Windows/C/ADLXHelper.h"
#include "SDK/Include/II2C.h"
#define DATA_SIZE 2

// Display version
void ShowVersion(IADLXI2C* i2c);

// Read
void Read(IADLXI2C* i2c);

// Repeated read
void RepeatedRead(IADLXI2C* i2c);

// Write
void Write(IADLXI2C* i2c);

// Capability
void Capability(IADLXI2C* i2c);

// Menu
void MainMenu();

// Menu control
void MenuControl(IADLXI2C* i2c);

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

        // Get GPU list
        IADLXGPUList* gpus = NULL;
        res = sys->pVtbl->GetGPUs(sys, &gpus);

        // Get GPU interface
        IADLXGPU* gpu = NULL;
        adlx_uint index = 0;
        res = gpus->pVtbl->At_GPUList(gpus, index, &gpu);

        // Get I2C interface
        IADLXI2C* i2c = NULL;
        res = sys->pVtbl->GetI2C(sys, gpu, &i2c);
        if (ADLX_SUCCEEDED(res))
        {
            MainMenu();
            MenuControl(i2c);
        }

        // Release the I2C interface
        if (i2c != NULL)
        {
            i2c->pVtbl->Release(i2c);
            i2c = NULL;
        }

        // Release the GPU interface
        if (gpu != NULL)
        {
            gpu->pVtbl->Release(gpu);
            gpu = NULL;
        }

        // Release the  GPUlist interface
        if (NULL != gpus)
        {
            gpus->pVtbl->Release(gpus);
            gpus = NULL;
        }
    }
    else
    {
        printf("ADLX initialization failed\n");
        return 0;
    }

    // Destroy ADLX
    res = ADLXHelper_Terminate();
    printf("Destroy ADLX result: %d\n", res);

    // Pause to see the print out
    system("pause");

    return 0;
}

void ShowVersion(IADLXI2C* i2c)
{
    adlx_int major;
    adlx_int minor;
    ADLX_RESULT res = i2c->pVtbl->Version(i2c, &major, &minor);
    printf("\tI2C version, major: %d, minor: %d\n", major, minor);
    printf("\tres is: %d\n", res);
}

void Read(IADLXI2C* i2c)
{
    // Specific hardware requirements
    adlx_byte data[DATA_SIZE] = { 0 };
    ADLX_RESULT res = i2c->pVtbl->Read(i2c, I2C_LINE_OEM2, 100, 0x93, 0x30, DATA_SIZE, data);
    printf("\tI2C read info:\n\t\tline: I2C_LINE_OEM2\n\t\tspeed: 100\n\t\taddress: 0x93\n\t\toffset: 0x30");
    printf("\n\t\tdataSize: %d\n\t\tdata: %d\n\tres is: %d\n", DATA_SIZE, (int)data[0], res);
}

void RepeatedRead(IADLXI2C* i2c)
{
    // Specific hardware requirements
    adlx_byte data[DATA_SIZE] = { 0 };
    ADLX_RESULT res = i2c->pVtbl->RepeatedStartRead(i2c, I2C_LINE_OEM2, 100, 0x93, 0x30, DATA_SIZE, data);
    printf("\tI2C read info:\n\t\tline: I2C_LINE_OEM2\n\t\tspeed: 100\n\t\taddress: 0x93\n\t\toffset: 0x30");
    printf("\n\t\tdataSize: %d\n\t\tdata: %d\n\tres is: %d\n", DATA_SIZE, (int)data[0], res);
}

void Write(IADLXI2C* i2c)
{
    // Specific hardware requirements
    adlx_byte data[DATA_SIZE] = { 0 };
    data[0] = 176;
    ADLX_RESULT res = i2c->pVtbl->Write(i2c, I2C_LINE_OEM2, 100, 0x93, 0x30, DATA_SIZE, data);
    printf("\tI2C write info:\n\t\tline: I2C_LINE_OEM2\n\t\tspeed: 100\n\t\taddress: 0x93\n\t\toffset: 0x30");
    printf("\n\t\tdataSize: %d\n\t\tdata: %d\n\tres is: %d\n", DATA_SIZE, (int)data[0], res);
}

void Capability(IADLXI2C* i2c)
{
    adlx_bool isSupported = false;
    ADLX_RESULT res = i2c->pVtbl->IsSupported(i2c, I2C_LINE_OEM2, 0x93, &isSupported);
    printf("\tI2C support info:\n\t\tline: I2C_LINE_OEM2\n\t\taddress: 0x93\n\t\tisSupported: %d\n", isSupported);
    printf("\tres is: %d\n", res);
}

void MainMenu()
{
    printf("\tChoose from the following options:\n");

    printf("\t->Press 1 to display version\n");
    printf("\t->Press 2 to read\n");
    printf("\t->Press 3 to repeated read\n");
    printf("\t->Press 4 to write\n");
    printf("\t->Press 5 to display capability\n");

    printf("\t->Press Q/q to terminate the application\n");
    printf("\t->Press M/m to display main menu options\n");
}

void MenuControl(IADLXI2C* i2c)
{
    int num = 0;
    while ((num = getchar()) != 'q' && num != 'Q')
    {
        switch (num)
        {
            // Display version
        case '1':
            ShowVersion(i2c);
            break;

            // Read
        case '2':
            Read(i2c);
            break;

            // Repeated read
        case '3':
            RepeatedRead(i2c);
            break;

            // Write
        case '4':
            Write(i2c);
            break;

            // Capability
        case '5':
            Capability(i2c);
            break;

            // Display main menu options
        case 'm':
        case 'M':
            MainMenu();
            break;
        default:
            break;
        }
    }
}