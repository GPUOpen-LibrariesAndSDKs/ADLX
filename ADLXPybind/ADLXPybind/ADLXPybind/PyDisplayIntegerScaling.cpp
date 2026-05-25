// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDisplaySettings.h"


namespace py = pybind11;
using namespace adlx;


class PyDisplayIntegerScaling : public IADLXDisplayIntegerScaling
{
public:
	using IADLXDisplayIntegerScaling::IADLXDisplayIntegerScaling;

	ADLX_RESULT IsEnabled(adlx_bool* enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayIntegerScaling, IsEnabled);
	}
	ADLX_RESULT IsSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayIntegerScaling, IsSupported);
	}
	ADLX_RESULT SetEnabled (adlx_bool enable) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayIntegerScaling, SetEnabled);
	}
};
