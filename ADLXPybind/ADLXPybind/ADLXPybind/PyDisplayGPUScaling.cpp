// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDisplaySettings.h"


namespace py = pybind11;
using namespace adlx;


class PyDisplayGPUScaling : public IADLXDisplayGPUScaling
{
public:
	using IADLXDisplayGPUScaling::IADLXDisplayGPUScaling;

	ADLX_RESULT IsSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGPUScaling, IsSupported);
	}

	ADLX_RESULT IsEnabled(adlx_bool* enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGPUScaling, IsEnabled);
	}

	ADLX_RESULT SetEnabled(adlx_bool enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayGPUScaling, SetEnabled);
	}
};
