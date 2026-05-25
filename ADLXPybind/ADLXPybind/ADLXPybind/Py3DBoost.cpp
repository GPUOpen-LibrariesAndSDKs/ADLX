// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/I3DSettings3.h"


namespace py = pybind11;
using namespace adlx;


class Py3DBoost : public IADLX3DBoost
{
public:
	using IADLX3DBoost::IADLX3DBoost;

	ADLX_RESULT GetResolution(adlx_int* currentMinRes) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DBoost, GetResolution);
	}

	ADLX_RESULT GetResolutionRange(ADLX_IntRange* range) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DBoost, GetResolutionRange);
	}

	ADLX_RESULT IsEnabled(adlx_bool* enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DBoost, IsEnabled);
	}

	ADLX_RESULT IsSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DBoost, IsSupported);
	}

	ADLX_RESULT SetEnabled(adlx_bool enable) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DBoost, SetEnabled);
	}

	ADLX_RESULT SetResolution(adlx_int minRes) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DBoost, SetResolution);
	}
};