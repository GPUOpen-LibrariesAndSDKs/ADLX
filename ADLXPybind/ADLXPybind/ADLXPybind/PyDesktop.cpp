// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDesktops.h"


namespace py = pybind11;
using namespace adlx;


class PyDesktop : public IADLXDesktop
{
public:
	using IADLXDesktop::IADLXDesktop;

	ADLX_RESULT GetDisplays(IADLXDisplayList** ppDisplays) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDesktop, GetDisplays);
	}

	ADLX_RESULT GetNumberOfDisplays(adlx_uint* numDisplays) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDesktop, GetNumberOfDisplays);
	}

	ADLX_RESULT Orientation(ADLX_ORIENTATION* orientation) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDesktop, Orientation);
	}

	ADLX_RESULT Size(adlx_int* width, adlx_int* height) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDesktop, Size);
	}

	ADLX_RESULT TopLeft(ADLX_Point* locationTopLeft) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDesktop, TopLeft);
	}

	ADLX_RESULT Type(ADLX_DESKTOP_TYPE* desktopType) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDesktop, Type);
	}
};
