#<!--
# Copyright (c) 2021 - 2023 Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------
#-->

import ADLXPybind as ADLX

# Iterate display and display event:plug and unplug the display
def displayDemo():
    # Get ADLXHelp and ADLX initialization
    adlxHelper = ADLX.ADLXHelper()
    ret = adlxHelper.Initialize()

    if ret == ADLX.ADLX_RESULT.ADLX_OK:
        # Get system services
        system = adlxHelper.GetSystemServices()

        if system is not None:
            # Get display services
            displayService = system.GetDisplaysServices()

            if displayService is not None:
                # Iterate through the display list
                count = displayService.GetNumberOfDisplays()
                print("display count: {}".format(count))
                disList = displayService.GetDisplays()
                if disList is not None:
                    for index, display in enumerate(disList):
                        if display is not None:
                            name = display.name()
                            type = display.type()
                            connectType = display.connectType()
                            mid = display.ManufacturerID()
                            edid = display.EDID()
                            h,v = display.resolution()
                            refreshRate = display.RefreshRate()
                            pclock = display.PixelClock()
                            scanType = display.ScanType()
                            id = display.UniqueId()
                            print("\nThe display [{}]:".format(index))
                            print("\tName: {}".format(name))
                            print("\tType: {}".format(type))
                            print("\tConnector type: {}".format(connectType))
                            print("\tManufacturer id: {}".format(mid))
                            print("\tEDID: {}".format(edid))
                            print("\tResolution:  h: {}  v: {}".format(h,v))
                            print("\tRefresh rate: {}".format(refreshRate))
                            print("\tPixel clock: {}".format(pclock))
                            print("\tScan type: {}".format(scanType))
                            print("\tUnique id: {}".format(id))
                            # Release display interface
                            del display

                    # Release displayList interface
                    del disList

                # Release displayService interface
                del displayService

    # Terminate ADLX
    ret = adlxHelper.Terminate()
    print("ADLX Terminate ret is: {}".format(ret))

displayDemo()