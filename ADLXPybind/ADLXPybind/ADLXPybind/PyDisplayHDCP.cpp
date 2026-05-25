// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDisplaySettings.h"


namespace py = pybind11;
using namespace adlx;


class PyDisplayHDCP : public IADLXDisplayHDCP
{
public:
	using IADLXDisplayHDCP::IADLXDisplayHDCP;

	ADLX_RESULT IsEnabled(adlx_bool* enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayHDCP, IsEnabled);
	}

	ADLX_RESULT IsSupported(adlx_bool* enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayHDCP, IsSupported);
	}

	ADLX_RESULT SetEnabled(adlx_bool enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayHDCP, SetEnabled);
	}
};
