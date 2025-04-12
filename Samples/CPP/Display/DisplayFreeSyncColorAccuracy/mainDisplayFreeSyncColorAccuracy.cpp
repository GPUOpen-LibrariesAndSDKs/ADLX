//
// Copyright (c) 2021 - 2025 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

/// \file mainDisplayFreeSyncColorAccuracy.cpp
/// \brief This document describes how to obtain the FreeSync color accuracy through ADLX and perform related tests.

#include "SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "SDK/Include/IDisplaySettings.h"
#include "SDK/Include/IDisplays.h"
#include "SDK/Include/IDisplays3.h"
#include <iostream>
#include <string>
#include <thread>

// Use ADLX namespace
using namespace adlx;

// ADLXHelper instance
// No outstanding interfaces from ADLX must exist when ADLX is destoryed.
// so we use global variables to ensure the validity of the interface.
static ADLXHelper g_ADLXHelp;

// thread quit event
static HANDLE quitEvent = nullptr;

// thread quit flag
static std::atomic<bool>  g_quit = false;

// thread for timeout
static std::thread* g_thread = nullptr;

// Show FreeSync color accuracy support
void ShowFreeSyncColorAccuracySupport(const IADLXDisplayServices3Ptr& displayService3, const IADLXDisplayPtr& display);

// Get current FreeSync color accuracy state
void GetFreeSyncColorAccuracyState(const IADLXDisplayServices3Ptr& displayService3, const IADLXDisplayPtr& display);

// Set FreeSync color accuracy state
void SetFreeSyncColorAccuracyState(const IADLXDisplayServices3Ptr& displayService3, const IADLXDisplayPtr& display, const int key);

// Main menu
void MainMenu();

// Menu action control
void MenuControl(const IADLXDisplayServices3Ptr& displayService3, const IADLXDisplayPtr& display);

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
		// Get display service
		IADLXDisplayServicesPtr displayService;
		res = g_ADLXHelp.GetSystemServices()->GetDisplaysServices(&displayService);
		if (ADLX_SUCCEEDED(res))
		{
			IADLXDisplayServices3Ptr displayServices3(displayService);

			if (nullptr != displayServices3)
			{
				// Get display list
				IADLXDisplayListPtr displayList;
				res = displayServices3->GetDisplays(&displayList);
				if (ADLX_FAILED(res))
				{
					std::cout << "Failed to get the display list: " << res << std::endl;
                    goto EXIT;
				}
				// Inspect for the first display in the list
				adlx_uint it = 0;
				IADLXDisplayPtr display;
				res = displayList->At(it, &display);
				if (ADLX_SUCCEEDED(res))
				{
					// Display main menu options
					MainMenu();
					// Get and parse the selection
					MenuControl(displayServices3, display);
				}
			}
		}
		else
		{
			std::cout << "Failed to get the display services: " << res << std::endl;
		}
	}
	else
	{
		return WaitAndExit("ADLX initialization failed", 0);
	}

EXIT:
	// Destroy ADLX
	res = g_ADLXHelp.Terminate();
	std::cout << "Destroy ADLX result: " << res << std::endl;

	// Pause to see the print out
	system("Pause");

	return 0;
}

void ShowFreeSyncColorAccuracySupport(const IADLXDisplayServices3Ptr& displayService3, const IADLXDisplayPtr& display)
{
	IADLXDisplayFreeSyncColorAccuracyPtr displayFreeSyncColorAccuracy;
	ADLX_RESULT res = displayService3->GetFreeSyncColorAccuracy(display, &displayFreeSyncColorAccuracy);
	if (ADLX_SUCCEEDED(res))
	{
		std::cout << "  === Get display FreeSync color accuracy supported status ===" << std::endl;
		adlx_bool supported = false;
		res = displayFreeSyncColorAccuracy->IsSupported(&supported);
		std::cout << "\tIsSupported, res " << res << ", supported: " << supported << std::endl;
	}
}

void GetFreeSyncColorAccuracyState(const IADLXDisplayServices3Ptr& displayService3, const IADLXDisplayPtr& display)
{
	IADLXDisplayFreeSyncColorAccuracyPtr displayFreeSyncColorAccuracy;
	ADLX_RESULT res = displayService3->GetFreeSyncColorAccuracy(display, &displayFreeSyncColorAccuracy);
	if (ADLX_SUCCEEDED(res))
	{
		std::cout << "  === Get display FreeSync color accuracy enabled ===" << std::endl;
		adlx_bool enabled = false;
		res = displayFreeSyncColorAccuracy->IsEnabled(&enabled);
		std::cout << "\tGetEnabled, result: " << res << " enabled: " << (enabled ? "true" : "false") << std::endl;
	}
}

void SetFreeSyncColorAccuracyState(const IADLXDisplayServices3Ptr& displayService3, const IADLXDisplayPtr& display, const int key)
{
	IADLXDisplayFreeSyncColorAccuracyPtr displayFreeSyncColorAccuracy;
	ADLX_RESULT res = displayService3->GetFreeSyncColorAccuracy(display, &displayFreeSyncColorAccuracy);
	if (ADLX_SUCCEEDED(res))
	{
		ADLX_RESULT res = ADLX_FAIL;

		switch (key)
		{
			// Set FreeSync color accuracy disabled
		case 0:
			std::cout << "  === Set FreeSync color accuracy disabled: false" << std::endl;
			res = displayFreeSyncColorAccuracy->SetEnabled(false);
			break;
			// Set FreeSync color accuracy enabled
		case 1:
			std::cout << "  === Set FreeSync color accuracy enabled: true" << std::endl;
			res = displayFreeSyncColorAccuracy->SetEnabled(true);
			break;
		default:
			break;
		}
		std::cout << "\tReturn code is: " << res << " (0 means success)" << std::endl;
	}
}

void MainMenu()
{
	std::cout << "\tChoose from the following options:" << std::endl;

	std::cout << "\t->Press 1 to FreeSync color accuracy support" << std::endl;

	std::cout << "\t->Press 2 to get FreeSync color accuracy state" << std::endl;

	std::cout << "\t->Press 3 to set FreeSync color accuracy state disabled" << std::endl;

	std::cout << "\t->Press 4 to set FreeSync color accuracy state enabled" << std::endl;

	std::cout << "\t->Press Q/q to terminate the application" << std::endl;
	std::cout << "\t->Press M/m to display main menu options" << std::endl;
}

// Menu action control
void MenuControl(const IADLXDisplayServices3Ptr& displayService3, const IADLXDisplayPtr& display)
{
	int num = 0;
	while ((num = getchar()) != 'q' && num != 'Q')
	{
		switch (num)
		{
			// Show FreeSync color accuracy support
		case '1':
			ShowFreeSyncColorAccuracySupport(displayService3, display);
			break;

			// Display current FreeSync color accuracy state
		case '2':
			GetFreeSyncColorAccuracyState(displayService3, display);
			break;

			// Set FreeSync color accuracy state
		case '3':
		case '4':
			SetFreeSyncColorAccuracyState(displayService3, display, num - '3');
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

	system("Pause");
	return retCode;
}