// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IGPUManualVRAMTuning.h"


namespace py = pybind11;
using namespace adlx;


class PyManualVRAMTuning2 : public IADLXManualVRAMTuning2_1
{
public:
	using IADLXManualVRAMTuning2_1::IADLXManualVRAMTuning2_1;

	ADLX_RESULT    GetMaxVRAMFrequency(adlx_int* freq) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualVRAMTuning2_1, GetMaxVRAMFrequency);
	}

	ADLX_RESULT    GetMaxVRAMFrequencyRange(ADLX_IntRange* tuningRange) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualVRAMTuning2_1, GetMaxVRAMFrequencyRange);
	}

	ADLX_RESULT    GetMemoryTimingDescription(ADLX_MEMORYTIMING_DESCRIPTION* description) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualVRAMTuning2_1, GetMemoryTimingDescription);
	}

	ADLX_RESULT    GetSupportedMemoryTimingDescriptionList(IADLXMemoryTimingDescriptionList** ppDescriptionList) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualVRAMTuning2_1, GetSupportedMemoryTimingDescriptionList);
	}

	ADLX_RESULT    IsSupportedMemoryTiming(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualVRAMTuning2_1, IsSupportedMemoryTiming);
	}

	ADLX_RESULT    SetMaxVRAMFrequency(adlx_int freq) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualVRAMTuning2_1, SetMaxVRAMFrequency);
	}

	ADLX_RESULT    SetMemoryTimingDescription(ADLX_MEMORYTIMING_DESCRIPTION description) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualVRAMTuning2_1, SetMemoryTimingDescription);
	}

	ADLX_RESULT    GetMaxVRAMFrequencyDefault(adlx_int* defaultVal) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXManualVRAMTuning2_1, GetMaxVRAMFrequencyDefault);
	}
};
