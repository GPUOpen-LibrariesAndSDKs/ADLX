// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IGPUManualGFXTuning.h"


namespace py = pybind11;
using namespace adlx;


class PyManualGraphicsTuning1 : public IADLXManualGraphicsTuning1
{
public:
	using IADLXManualGraphicsTuning1::IADLXManualGraphicsTuning1;

	ADLX_RESULT    GetEmptyGPUTuningStates(IADLXManualTuningStateList** ppGFXStates) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualGraphicsTuning1, GetEmptyGPUTuningStates);
	}
	
	ADLX_RESULT    GetGPUTuningRanges(ADLX_IntRange* frequencyRange, ADLX_IntRange* voltageRange) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualGraphicsTuning1, GetGPUTuningRanges);
	}

	ADLX_RESULT    GetGPUTuningStates(IADLXManualTuningStateList** ppGFXStates) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualGraphicsTuning1, GetGPUTuningStates);
	}

	ADLX_RESULT    IsValidGPUTuningStates(IADLXManualTuningStateList* pGFXStates, adlx_int* errorIndex) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualGraphicsTuning1, IsValidGPUTuningStates);
	}

	ADLX_RESULT    SetGPUTuningStates(IADLXManualTuningStateList* pGFXStates) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualGraphicsTuning1, SetGPUTuningStates);
	}
};
