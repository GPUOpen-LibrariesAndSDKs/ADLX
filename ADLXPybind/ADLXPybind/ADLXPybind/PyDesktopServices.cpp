// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDesktops.h"


namespace py = pybind11;
using namespace adlx;


class PyDesktopServices : public IADLXDesktopServices
{
public:
	using IADLXDesktopServices::IADLXDesktopServices;

	ADLX_RESULT GetDesktopChangedHandling(IADLXDesktopChangedHandling** ppDesktopChangedHandling) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDesktopServices, GetDesktopChangedHandling);
	}
	
	ADLX_RESULT GetDesktops(IADLXDesktopList** ppDesktops) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDesktopServices, GetDesktops);
	}

	ADLX_RESULT GetNumberOfDesktops(adlx_uint* numDesktops) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDesktopServices, GetNumberOfDesktops);
	}

	ADLX_RESULT GetSimpleEyefinity(IADLXSimpleEyefinity** ppSimpleEyefinity) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDesktopServices, GetSimpleEyefinity);
	}
};
