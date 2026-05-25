// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDisplaySettings.h"


namespace py = pybind11;
using namespace adlx;


class PyDisplayScalingMode : public IADLXDisplayScalingMode
{
public:
	using IADLXDisplayScalingMode::IADLXDisplayScalingMode;

	ADLX_RESULT GetMode(ADLX_SCALE_MODE* currentMode) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayScalingMode, GetMode);
	}
	ADLX_RESULT IsSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayScalingMode, IsSupported);
	}
	ADLX_RESULT SetMode(ADLX_SCALE_MODE mode) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayScalingMode, SetMode);
	}
};
