#<!--
# Copyright (c) 2021 - 2023 Advanced Micro Devices, Inc. All rights reserved.
#
#-------------------------------------------------------------------------------------------------
#-->

import ADLXPybind as ADLX
import time

# Callback for display list change
def callBackDisplayList(displaylist)->bool:
    print("display list changed, current display count is: ", len(displaylist))
    for index, display in enumerate(displaylist):
            name = display.name()
            print("\t index: {} name: {}".format(index, name))
            del display
    return True

# Iterate display and display event to unplug and plug the display
def displayDemo():
    # Get ADLXHelp and ADLX initialization
    adlxHelper = ADLX.ADLXHelper()
    ret = adlxHelper.Initialize()

    if ret == ADLX.ADLX_RESULT.ADLX_OK:
        # Get systemServices
        system = adlxHelper.GetSystemServices()

        if system is not None:
            # Get displayServices
            displayService = system.GetDisplaysServices()

            if displayService is not None:
                # Get display change handler
                displayChangeHandler = displayService.GetDisplayChangedHandling()

                if displayChangeHandler is not None:
                    # Python call back
                    callback = ADLX.DisplayListCallBack()
                    callback.call = callBackDisplayList
                    # Add call back
                    displayChangeHandler.AddDisplayListEventListener(callback)
                    print("Plug or unplug a display within 20 seconds.")
                    time.sleep(20)
                    # Remove call back
                    displayChangeHandler.RemoveDisplayListEventListener(callback)

                    # Release changeHandler interface
                    del displayChangeHandler

                # Release displayService interface
                del displayService

    # Terminate ADLX
    ret = adlxHelper.Terminate()
    print("ADLX Terminate ret is: {}".format(ret))

displayDemo()