//
// Copyright (c) 2021 - 2022 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainI2C.cpp
/// \brief Demonstrates how to read and write data with I2C when programming with ADLX.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/II2C.h"
#include <iostream>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destroyed.
// Use global variables to ensure validity of the interface.
static ADLXHelper g_ADLXHelp;
constexpr int DATA_SIZE = 2;

// Display version
void ShowVersion(const IADLXI2CPtr& i2c);

// Read
void Read(const IADLXI2CPtr& i2c);

// Repeated read
void RepeatedRead(const IADLXI2CPtr& i2c);

// Write
void Write(const IADLXI2CPtr& i2c);

// Capability
void Capability(const IADLXI2CPtr& i2c);

// Menu
void MainMenu();

// Menu control
void MenuControl(const IADLXI2CPtr& i2c);

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode);

int main()
{
    // Define return code
    ADLX_RESULT res = ADLX_FAIL;

    // Initialize ADLX
    res = g_ADLXHelp.Initialize();
    if (ADLX_SUCCEEDED(res))
    {
        // GetGPUs
        IADLXGPUListPtr gpus;
        res = g_ADLXHelp.GetSystemServices()->GetGPUs(&gpus);

        if (!gpus->Empty() && ADLX_SUCCEEDED(res))
        {
            // Get GPU interface
            IADLXGPUPtr gpuInfo;
            adlx_uint index = 0;
            res = gpus->At(index, &gpuInfo);

            // Get I2C interface
            IADLXI2CPtr i2c;
            res = g_ADLXHelp.GetSystemServices()->GetI2C(gpuInfo, &i2c);
            if (ADLX_SUCCEEDED(res))
            {
                MainMenu();
                MenuControl(i2c);
            }
        }
        else
        {
            // Destroy ADLX
            res = g_ADLXHelp.Terminate();
            std::cout << "Destroy ADLX res: " << res << std::endl;
            return WaitAndExit("Failed to get the GPU list", 0);
        }
    }
    else
    {
        return WaitAndExit("ADLX initialization failed", 0);
    }

    // Destroy ADLX
    res = g_ADLXHelp.Terminate();
    std::cout << "Destroy ADLX res: " << res << std::endl;

    // Pause to see the print out
    system("pause");

    return 0;
}

void ShowVersion(const IADLXI2CPtr& i2c)
{
    adlx_int major;
    adlx_int minor;
    ADLX_RESULT res = i2c->Version(&major, &minor);
    std::cout << "\tI2C version, major: " << major << " , minor: " << minor << std::endl;
    std::cout << "\tres is: " << res << std::endl;
}

void Read(const IADLXI2CPtr& i2c)
{
    // The following is hardware specific
    adlx_byte data[DATA_SIZE] = { 0 };
    ADLX_RESULT res = i2c->Read(I2C_LINE_OEM2, 100, 0x93, 0x30, DATA_SIZE, data);
    std::cout << "\tI2C read info:\n" 
    << "\t\tline: I2C_LINE_OEM2\n\t\tspeed: 100\n\t\taddress: 0x93\n\t\toffset: 0x30\n\t\tdataSize: "
    << DATA_SIZE << "\n\t\tdata: " << (int)data[0] << std::endl;
    std::cout << "\tres is: " << res << std::endl;
}

void RepeatedRead(const IADLXI2CPtr& i2c)
{
    // The following is hardware specific
    adlx_byte data[DATA_SIZE] = { 0 };
    ADLX_RESULT res = i2c->RepeatedStartRead(I2C_LINE_OEM2, 100, 0x93, 0x30, DATA_SIZE, data);
    std::cout << "\tI2C read info:\n"
    << "\t\tline: I2C_LINE_OEM2\n\t\tspeed: 100\n\t\taddress: 0x93\n\t\toffset: 0x30\n\t\tdataSize: "
    << DATA_SIZE << "\n\t\tdata: " << (int)data[0] << std::endl;
    std::cout << "\tres is: " << res << std::endl;
}

void Write(const IADLXI2CPtr& i2c)
{
    // The following is hardware specific
    adlx_byte data[DATA_SIZE] = { 0 };
    data[0] = 176;
    ADLX_RESULT res = i2c->Write(I2C_LINE_OEM2, 100, 0x93, 0x30, DATA_SIZE, data);
    std::cout << "\tI2C write info:\n"
    << "\t\tline: I2C_LINE_OEM2\n\t\tspeed: 100\n\t\taddress: 0x93\n\t\toffset: 0x30\n\t\tdataSize: "
    << DATA_SIZE << "\n\t\tdata: " << (int)data[0] << std::endl;
    std::cout << "\tres is: " << res << std::endl;
}

void Capability(const IADLXI2CPtr& i2c)
{
    adlx_bool isSupported = false;
    ADLX_RESULT res = i2c->IsSupported(I2C_LINE_OEM2, 0x93, &isSupported);
    std::cout << "\tI2C support info:\n"
    << "\t\tline: I2C_LINE_OEM2\n\t\taddress: 0x93\n\t\tisSupported: " << isSupported
    << "\n\tres is: " << res << std::endl;
}

void MainMenu()
{
    std::cout << "\tChoose one from the following options" << std::endl;

    std::cout << "\t->Press 1 to display version" << std::endl;
    std::cout << "\t->Press 2 to read" << std::endl;
    std::cout << "\t->Press 3 to repeated read" << std::endl;
    std::cout << "\t->Press 4 to write" << std::endl;
    std::cout << "\t->Press 5 to display capability" << std::endl;

    std::cout << "\t->Press Q/q to terminate the application" << std::endl;
    std::cout << "\t->Press M/m to display main menu options" << std::endl;
}

void MenuControl(const IADLXI2CPtr& i2c)
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

// Wait for exit with error message
int WaitAndExit(const char* msg, const int retCode)
{
    // Printout the message and pause to see it before returning the desired code
    if (nullptr != msg)
        std::cout << msg << std::endl;

    system("pause");
    return retCode;
}