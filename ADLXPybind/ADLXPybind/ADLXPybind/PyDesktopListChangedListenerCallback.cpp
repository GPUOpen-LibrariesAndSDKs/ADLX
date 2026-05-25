// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDesktops.h"
#include <iostream>


namespace py = pybind11;
using namespace adlx;


// Callback
class PyDesktopListChangedListenerCallback : public IADLXDesktopListChangedListener
{
public:
    using IADLXDesktopListChangedListener::IADLXDesktopListChangedListener;

    adlx_bool OnDesktopListChanged(IADLXDesktopList* pNewDesktop) override
    {

        if (pNewDesktop == nullptr)
        {
            return false;
        }
        
        std::cout << "desktop list has been changed\n";
        adlx_bool slsActive = false;
        IADLXDesktopPtr desktop = nullptr;
        for (adlx_uint crt = pNewDesktop->Begin(); crt != pNewDesktop->End(); crt++)
        {
            ADLX_RESULT res = pNewDesktop->At(crt, &desktop);
            if (ADLX_SUCCEEDED(res) && nullptr != desktop)
            {
                ADLX_DESKTOP_TYPE desktopType;
                desktop->Type(&desktopType);
                if (desktopType == DESKTOP_EYEFINITY)
                {
                    std::cout << "Eyefinity Creation Event is received" << std::endl;
                    slsActive = true;
                    break;
                }
            }
        }

        if (false == slsActive)
        {
            std::cout << "Eyefinity Destruction Event is received" << std::endl;
        }
            
        return true;
        
    }
};
