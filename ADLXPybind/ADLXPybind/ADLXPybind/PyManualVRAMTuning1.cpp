// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IGPUManualVRAMTuning.h"


namespace py = pybind11;
using namespace adlx;


class PyManualVRAMTuning1: public IADLXManualVRAMTuning1
{
public:
	using IADLXManualVRAMTuning1::IADLXManualVRAMTuning1;

	ADLX_RESULT    GetEmptyVRAMTuningStates(IADLXManualTuningStateList** ppVRAMStates) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualVRAMTuning1, GetEmptyVRAMTuningStates);
	}

	ADLX_RESULT    GetMemoryTimingDescription(ADLX_MEMORYTIMING_DESCRIPTION* description) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualVRAMTuning1, GetMemoryTimingDescription);
	}

	ADLX_RESULT    GetSupportedMemoryTimingDescriptionList(IADLXMemoryTimingDescriptionList** ppDescriptionList) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualVRAMTuning1, GetSupportedMemoryTimingDescriptionList);
	}

	ADLX_RESULT    GetVRAMTuningRanges(ADLX_IntRange* frequencyRange, ADLX_IntRange* voltageRange) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualVRAMTuning1, GetVRAMTuningRanges);
	}

	ADLX_RESULT    GetVRAMTuningStates(IADLXManualTuningStateList** ppVRAMStates) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualVRAMTuning1, GetVRAMTuningStates);
	}

	ADLX_RESULT    IsSupportedMemoryTiming(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualVRAMTuning1, IsSupportedMemoryTiming);
	}

	ADLX_RESULT    IsValidVRAMTuningStates(IADLXManualTuningStateList* pVRAMStates, adlx_int* errorIndex) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualVRAMTuning1, IsValidVRAMTuningStates);
	}

	ADLX_RESULT    SetMemoryTimingDescription(ADLX_MEMORYTIMING_DESCRIPTION description) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualVRAMTuning1, SetMemoryTimingDescription);
	}

	ADLX_RESULT    SetVRAMTuningStates(IADLXManualTuningStateList* pVRAMStates) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualVRAMTuning1, SetVRAMTuningStates);
	}
};
