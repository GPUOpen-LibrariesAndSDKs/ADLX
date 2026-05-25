// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/I3DSettings.h"


namespace py = pybind11;
using namespace adlx;


class Py3DAntiAliasing : IADLX3DAntiAliasing
{
public:
	using IADLX3DAntiAliasing::IADLX3DAntiAliasing;

	ADLX_RESULT GetLevel(ADLX_ANTI_ALIASING_LEVEL* currentLevel) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAntiAliasing, GetLevel);
	}

	ADLX_RESULT GetMethod(ADLX_ANTI_ALIASING_METHOD* currentMethod) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAntiAliasing, GetMethod);
	}

	ADLX_RESULT GetMode(ADLX_ANTI_ALIASING_MODE* currentMode) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAntiAliasing, GetMode);
	}

	ADLX_RESULT IsSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAntiAliasing, IsSupported);
	}

	ADLX_RESULT SetLevel(ADLX_ANTI_ALIASING_LEVEL level) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAntiAliasing, SetLevel);
	}

	ADLX_RESULT SetMethod(ADLX_ANTI_ALIASING_METHOD method) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAntiAliasing, SetMethod);
	}

	ADLX_RESULT SetMode(ADLX_ANTI_ALIASING_MODE mode) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAntiAliasing, SetMode);
	}
};
