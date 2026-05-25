// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IGPUManualPowerTuning.h"


namespace py = pybind11;
using namespace adlx;


class PyManualPowerTuning : public IADLXManualPowerTuning1
{
public:
	using IADLXManualPowerTuning1::IADLXManualPowerTuning1;

	ADLX_RESULT    GetPowerLimit(adlx_int* curVal) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualPowerTuning1, GetPowerLimit);
	}

	ADLX_RESULT    GetPowerLimitRange(ADLX_IntRange* tuningRange) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualPowerTuning1, GetPowerLimitRange);
	}

	ADLX_RESULT    GetTDCLimit(adlx_int* curVal) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualPowerTuning1, GetTDCLimit);
	}

	ADLX_RESULT    GetTDCLimitRange(ADLX_IntRange* tuningRange) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualPowerTuning1, GetTDCLimitRange);
	}

	ADLX_RESULT    IsSupportedTDCLimit(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualPowerTuning1, IsSupportedTDCLimit);
	}

	ADLX_RESULT    SetPowerLimit(adlx_int curVal) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualPowerTuning1, SetPowerLimit);
	}

	ADLX_RESULT    SetTDCLimit(adlx_int curVal) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualPowerTuning1, SetTDCLimit);
	}

	ADLX_RESULT    GetPowerLimitDefault(adlx_int* defaultVal) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualPowerTuning1, GetPowerLimitDefault);
	}

	ADLX_RESULT    GetTDCLimitDefault(adlx_int* defaultVal) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualPowerTuning1, GetTDCLimitDefault);
	}
};
