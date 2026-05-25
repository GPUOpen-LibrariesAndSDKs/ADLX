// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/I3DSettings.h"


namespace py = pybind11;
using namespace adlx;


class Py3DChill : IADLX3DChill
{
public:
	using IADLX3DChill::IADLX3DChill;

	ADLX_RESULT GetFPSRange(ADLX_IntRange* range) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DChill, GetFPSRange);
	}

	ADLX_RESULT GetMaxFPS(adlx_int* currentMaxFPS) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DChill, GetMaxFPS);
	}

	ADLX_RESULT GetMinFPS(adlx_int* currentMinFPS) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DChill, GetMinFPS);
	}

	ADLX_RESULT IsEnabled(adlx_bool* enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DChill, IsEnabled);
	}

	ADLX_RESULT IsSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DChill, IsSupported);
	}

	ADLX_RESULT SetEnabled(adlx_bool enable) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DChill, SetEnabled);
	}

	ADLX_RESULT SetMaxFPS(adlx_int maxFPS) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DChill, SetMaxFPS);
	}

	ADLX_RESULT SetMinFPS(adlx_int minFPS) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DChill, SetMinFPS);
	}
};
