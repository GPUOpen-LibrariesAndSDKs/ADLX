// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/I3DSettings2.h"


namespace py = pybind11;
using namespace adlx;


class Py3DImageSharpening : IADLX3DImageSharpening
{
public:
	using IADLX3DImageSharpening::IADLX3DImageSharpening;

	ADLX_RESULT GetSharpness(adlx_int* currentSharpness) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DImageSharpening, GetSharpness);
	}

	ADLX_RESULT GetSharpnessRange(ADLX_IntRange* range) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DImageSharpening, GetSharpnessRange);
	}

	ADLX_RESULT IsEnabled(adlx_bool* enabled) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DImageSharpening, IsEnabled);
	}

	ADLX_RESULT IsSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DImageSharpening, IsSupported);
	}

	ADLX_RESULT SetEnabled(adlx_bool enable) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DImageSharpening, SetEnabled);
	}
	
	ADLX_RESULT SetSharpness(adlx_int sharpness) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DImageSharpening, SetSharpness);
	}
};


class Py3DImageSharpenDesktop : IADLX3DImageSharpenDesktop
{
public:
    using IADLX3DImageSharpenDesktop::IADLX3DImageSharpenDesktop;

    ADLX_RESULT IsSupported(adlx_bool* supported) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DImageSharpenDesktop, IsSupported);
    }
    ADLX_RESULT IsEnabled(adlx_bool* enabled) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DImageSharpenDesktop, IsEnabled);
    }
    ADLX_RESULT SetEnabled(adlx_bool enable) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DImageSharpenDesktop, SetEnabled);
    }
};