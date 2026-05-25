// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IGPUTuning1.h"


namespace py = pybind11;
using namespace adlx;


class PyGPUTuningChangedEvent : public IADLXGPUTuningChangedEvent1
{
public:
	using IADLXGPUTuningChangedEvent1::IADLXGPUTuningChangedEvent1;

	ADLX_RESULT    GetGPU(IADLXGPU** ppGPU) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUTuningChangedEvent1, GetGPU);
	}

	adlx_bool    IsAutomaticTuningChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXGPUTuningChangedEvent1, IsAutomaticTuningChanged);
	}

	adlx_bool    IsManualFanTuningChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXGPUTuningChangedEvent1, IsManualFanTuningChanged);
	}

	adlx_bool    IsManualGPUCLKTuningChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXGPUTuningChangedEvent1, IsManualGPUCLKTuningChanged);
	}

	adlx_bool    IsManualPowerTuningChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXGPUTuningChangedEvent1, IsManualPowerTuningChanged);
	}

	adlx_bool    IsManualVRAMTuningChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXGPUTuningChangedEvent1, IsManualVRAMTuningChanged);
	}
	
	adlx_bool    IsPresetTuningChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXGPUTuningChangedEvent1, IsPresetTuningChanged);
	}

	ADLX_SYNC_ORIGIN GetOrigin() override {
		PYBIND11_OVERRIDE_PURE(ADLX_SYNC_ORIGIN, IADLXGPUTuningChangedEvent1, GetOrigin);
	}

	// IADLXGPUTuningChangedEvent1
	adlx_bool IsSmartAccessMemoryChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXGPUTuningChangedEvent1, IsSmartAccessMemoryChanged);
	}
	ADLX_RESULT GetSmartAccessMemoryStatus(adlx_bool* pEnabled, adlx_bool* pCompleted) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUTuningChangedEvent1, GetSmartAccessMemoryStatus);
	}
};
