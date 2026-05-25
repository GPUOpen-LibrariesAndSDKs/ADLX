// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDisplaySettings.h"


namespace py = pybind11;
using namespace adlx;


class PyDisplayVSR : public IADLXDisplayVSR
{
public:
	using IADLXDisplayVSR::IADLXDisplayVSR;

	ADLX_RESULT IsEnabled(adlx_bool* enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayVSR, IsEnabled);
	}
	ADLX_RESULT IsSupported(adlx_bool* enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayVSR, IsSupported);
	}
	ADLX_RESULT SetEnabled(adlx_bool enable) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayVSR, SetEnabled);
	}
};
