// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDesktops.h"


namespace py = pybind11;
using namespace adlx;


class PyDesktopChangedHandling : IADLXDesktopChangedHandling
{
public:
	using IADLXDesktopChangedHandling::IADLXDesktopChangedHandling;

	ADLX_RESULT AddDesktopListEventListener(IADLXDesktopListChangedListener* pDesktopListChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDesktopChangedHandling, AddDesktopListEventListener);
	}

	ADLX_RESULT RemoveDesktopListEventListener(IADLXDesktopListChangedListener* pDesktopListChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDesktopChangedHandling, RemoveDesktopListEventListener);
	}
};
