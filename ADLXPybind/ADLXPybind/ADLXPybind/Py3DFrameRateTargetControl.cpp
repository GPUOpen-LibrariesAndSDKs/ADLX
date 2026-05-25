// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/I3DSettings.h"


namespace py = pybind11;
using namespace adlx;


class Py3DFrameRateTargetControl : IADLX3DFrameRateTargetControl
{
public:
	using IADLX3DFrameRateTargetControl::IADLX3DFrameRateTargetControl;

	ADLX_RESULT GetFPS(adlx_int* currentFPS) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DFrameRateTargetControl, GetFPS);
	}

	ADLX_RESULT GetFPSRange(ADLX_IntRange* range) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DFrameRateTargetControl, GetFPSRange);
	}

	ADLX_RESULT IsEnabled(adlx_bool* enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DFrameRateTargetControl, IsEnabled);
	}

	ADLX_RESULT IsSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DFrameRateTargetControl, IsSupported);
	}

	ADLX_RESULT SetEnabled(adlx_bool enable) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DFrameRateTargetControl, SetEnabled);
	}

	ADLX_RESULT SetFPS(adlx_int maxFPS) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DFrameRateTargetControl, SetFPS);
	}
};
