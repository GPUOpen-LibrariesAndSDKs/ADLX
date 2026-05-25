// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDesktops.h"


namespace py = pybind11;
using namespace adlx;


class PyEyefinityDesktop : public IADLXEyefinityDesktop
{
public:
	using IADLXEyefinityDesktop::IADLXEyefinityDesktop;

	ADLX_RESULT DisplayOrientation(adlx_uint row, adlx_uint col, ADLX_ORIENTATION* displayOrientation) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXEyefinityDesktop, DisplayOrientation);
	}

	ADLX_RESULT DisplaySize(adlx_uint row, adlx_uint col, adlx_int* displayWidth, adlx_int* displayHeight) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXEyefinityDesktop, DisplaySize);
	}

	ADLX_RESULT DisplayTopLeft(adlx_uint row, adlx_uint col, ADLX_Point* displayLocationTopLeft) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXEyefinityDesktop, DisplayTopLeft);
	}

	ADLX_RESULT GetDisplay(adlx_uint row, adlx_uint col, IADLXDisplay** ppDisplay) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXEyefinityDesktop, GetDisplay);
	}

	ADLX_RESULT GridSize(adlx_uint* rows, adlx_uint* cols) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXEyefinityDesktop, GridSize);
	}
};
