// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/I3DSettings.h"


namespace py = pybind11;
using namespace adlx;


class Py3DWaitForVerticalRefresh : IADLX3DWaitForVerticalRefresh
{
public:
	using IADLX3DWaitForVerticalRefresh::IADLX3DWaitForVerticalRefresh;

	ADLX_RESULT GetMode(ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE* currentMode) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DWaitForVerticalRefresh, GetMode);
	}

	ADLX_RESULT IsEnabled(adlx_bool* enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DWaitForVerticalRefresh, IsEnabled);
	}

	ADLX_RESULT IsSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DWaitForVerticalRefresh, IsSupported);
	}

	ADLX_RESULT SetMode(ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE mode) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DWaitForVerticalRefresh, SetMode);
	}
};
