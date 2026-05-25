// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/I3DSettings.h"


namespace py = pybind11;
using namespace adlx;


class Py3DTessellation : IADLX3DTessellation
{
public:
	using IADLX3DTessellation::IADLX3DTessellation;

	ADLX_RESULT GetLevel(ADLX_TESSELLATION_LEVEL* currentLevel) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DTessellation, GetLevel);
	}

	ADLX_RESULT GetMode(ADLX_TESSELLATION_MODE* currentMode) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DTessellation, GetMode);
	}

	ADLX_RESULT IsSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DTessellation, IsSupported);
	}

	ADLX_RESULT SetLevel(ADLX_TESSELLATION_LEVEL level) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DTessellation, SetLevel);
	}
	
	ADLX_RESULT SetMode(ADLX_TESSELLATION_MODE mode) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DTessellation, SetMode);
	}

};
