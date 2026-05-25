// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/I3DSettings.h"


namespace py = pybind11;
using namespace adlx;


class Py3DRadeonSuperResolution : IADLX3DRadeonSuperResolution
{
public:
	using IADLX3DRadeonSuperResolution::IADLX3DRadeonSuperResolution;

	ADLX_RESULT GetSharpness(adlx_int* currentSharpness) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DRadeonSuperResolution, GetSharpness);
	}

	ADLX_RESULT GetSharpnessRange(ADLX_IntRange* range) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DRadeonSuperResolution, GetSharpnessRange);
	}

	ADLX_RESULT IsEnabled(adlx_bool* enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DRadeonSuperResolution, IsEnabled);
	}

	ADLX_RESULT IsSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DRadeonSuperResolution, IsSupported);
	}

	ADLX_RESULT SetEnabled(adlx_bool enable) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DRadeonSuperResolution, SetEnabled);
	}

	ADLX_RESULT SetSharpness(adlx_int sharpness) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DRadeonSuperResolution, SetSharpness);
	}
};
