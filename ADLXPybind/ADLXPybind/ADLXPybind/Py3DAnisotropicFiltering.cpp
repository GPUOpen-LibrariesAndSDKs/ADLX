// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/I3DSettings.h"


namespace py = pybind11;
using namespace adlx;


class Py3DAnisotropicFiltering : IADLX3DAnisotropicFiltering
{
public:
	using IADLX3DAnisotropicFiltering::IADLX3DAnisotropicFiltering;

	ADLX_RESULT GetLevel(ADLX_ANISOTROPIC_FILTERING_LEVEL* currentLevel) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAnisotropicFiltering, GetLevel);
	}

	ADLX_RESULT IsEnabled(adlx_bool* enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAnisotropicFiltering, IsEnabled);
	}

	ADLX_RESULT IsSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAnisotropicFiltering, IsSupported);
	}

	ADLX_RESULT SetEnabled(adlx_bool enable) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAnisotropicFiltering, SetEnabled);
	}

	ADLX_RESULT SetLevel(ADLX_ANISOTROPIC_FILTERING_LEVEL level) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAnisotropicFiltering, SetLevel);
	}
};
