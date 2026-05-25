// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/I3DSettings.h"


namespace py = pybind11;
using namespace adlx;


class Py3DAntiLag : IADLX3DAntiLag1
{
public:
	using IADLX3DAntiLag1::IADLX3DAntiLag1;

	ADLX_RESULT IsEnabled(adlx_bool* enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAntiLag1, IsEnabled);
	}

	ADLX_RESULT IsSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAntiLag1, IsSupported);
	}

	ADLX_RESULT SetEnabled(adlx_bool enable) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAntiLag1, SetEnabled);
	}

    ADLX_RESULT GetLevel(ADLX_ANTILAG_STATE* level) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAntiLag1, GetLevel);
    }

    ADLX_RESULT SetLevel(ADLX_ANTILAG_STATE level) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DAntiLag1, SetLevel);
    }
};
