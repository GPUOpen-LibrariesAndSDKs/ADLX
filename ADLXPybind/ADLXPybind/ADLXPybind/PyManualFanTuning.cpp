// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IGPUManualFanTuning.h"


namespace py = pybind11;
using namespace adlx;


class PyManualFanTuning : public IADLXManualFanTuning1
{
public:
	using IADLXManualFanTuning1::IADLXManualFanTuning1;

	ADLX_RESULT    GetEmptyFanTuningStates(IADLXManualFanTuningStateList** ppStates) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuning1, GetEmptyFanTuningStates);
	}

	ADLX_RESULT    GetFanTuningRanges(ADLX_IntRange* speedRange, ADLX_IntRange* temperatureRange) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuning1, GetFanTuningRanges);
	}

	ADLX_RESULT    GetFanTuningStates(IADLXManualFanTuningStateList** ppStates) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuning1, GetFanTuningStates);
	}

	ADLX_RESULT    GetMinAcousticLimit(adlx_int* value) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuning1, GetMinAcousticLimit);
	}

	ADLX_RESULT    GetMinAcousticLimitRange(ADLX_IntRange* tuningRange) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuning1, GetMinAcousticLimitRange);
	}

	ADLX_RESULT    GetMinFanSpeed(adlx_int* value) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuning1, GetMinFanSpeed);
	}
	ADLX_RESULT    GetMinFanSpeedRange(ADLX_IntRange* tuningRange) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuning1, GetMinFanSpeedRange);
	}

	ADLX_RESULT    GetTargetFanSpeed(adlx_int* value) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuning1, GetTargetFanSpeed);
	}

	ADLX_RESULT    GetTargetFanSpeedRange(ADLX_IntRange* tuningRange) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuning1, GetTargetFanSpeedRange);
	}

	ADLX_RESULT    GetZeroRPMState(adlx_bool* isSet) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuning1, GetZeroRPMState);
	}

	ADLX_RESULT    IsSupportedMinAcousticLimit(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuning1, IsSupportedMinAcousticLimit);
	}

	ADLX_RESULT    IsSupportedMinFanSpeed(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuning1, IsSupportedMinFanSpeed);
	}

	ADLX_RESULT    IsSupportedTargetFanSpeed(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuning1, IsSupportedTargetFanSpeed);
	}

	ADLX_RESULT    IsSupportedZeroRPM(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuning1, IsSupportedZeroRPM);
	}

	ADLX_RESULT    IsValidFanTuningStates(IADLXManualFanTuningStateList* pStates, adlx_int* errorIndex) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuning1, IsValidFanTuningStates);
	}

	ADLX_RESULT    SetFanTuningStates(IADLXManualFanTuningStateList* pStates) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuning1, SetFanTuningStates);
	}

	ADLX_RESULT    SetMinAcousticLimit(adlx_int value) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuning1, SetMinAcousticLimit);
	}

	ADLX_RESULT    SetMinFanSpeed(adlx_int value) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuning1, SetMinFanSpeed);
	}

	ADLX_RESULT    SetTargetFanSpeed(adlx_int value) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuning1, SetTargetFanSpeed);
	}

	ADLX_RESULT    SetZeroRPMState(adlx_bool set) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuning1, SetZeroRPMState);
	}

	ADLX_RESULT    GetDefaultFanTuningStates(IADLXManualFanTuningStateList** ppStates) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuning1, GetDefaultFanTuningStates);
	}

	ADLX_RESULT    GetMinAcousticLimitDefault(adlx_int* defaultVal) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuning1, GetMinAcousticLimitDefault);
	}

	ADLX_RESULT    GetMinFanSpeedDefault(adlx_int* defaultVal) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuning1, GetMinFanSpeedDefault);
	}

	ADLX_RESULT    GetTargetFanSpeedDefault(adlx_int* defaultVal) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuning1, GetTargetFanSpeedDefault);
	}

	ADLX_RESULT    GetDefaultZeroRPMState(adlx_bool* defaultVal) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualFanTuning1, GetDefaultZeroRPMState);
	}
    
};
