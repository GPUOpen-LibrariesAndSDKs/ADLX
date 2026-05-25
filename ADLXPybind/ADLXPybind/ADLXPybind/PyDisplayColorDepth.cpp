// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDisplaySettings.h"


namespace py = pybind11;
using namespace adlx;


class PyDisplayColorDepth : public IADLXDisplayColorDepth
{
public:
	using IADLXDisplayColorDepth::IADLXDisplayColorDepth;

	ADLX_RESULT GetValue(ADLX_COLOR_DEPTH* currentColorDepth) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayColorDepth, GetValue);
	}

	ADLX_RESULT IsSupported(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayColorDepth, IsSupported);
	}

	ADLX_RESULT IsSupportedBPC_6(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayColorDepth, IsSupportedBPC_6);
	}

	ADLX_RESULT IsSupportedBPC_8(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayColorDepth, IsSupportedBPC_8);
	}

	ADLX_RESULT IsSupportedBPC_10(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayColorDepth, IsSupportedBPC_10);
	}

	ADLX_RESULT IsSupportedBPC_12(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayColorDepth, IsSupportedBPC_12);
	}

	ADLX_RESULT IsSupportedBPC_14(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayColorDepth, IsSupportedBPC_14);
	}

	ADLX_RESULT IsSupportedBPC_16(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayColorDepth, IsSupportedBPC_16);
	}

	ADLX_RESULT IsSupportedColorDepth(ADLX_COLOR_DEPTH colorDepth, adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayColorDepth, IsSupportedColorDepth);
	}

	ADLX_RESULT SetValue(ADLX_COLOR_DEPTH colorDepth) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayColorDepth, SetValue);
	}
};
