// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IGPUTuning1.h"

namespace py = pybind11;
using namespace adlx;


class PyGPUTuningServices : IADLXGPUTuningServices1
{
public:
	using IADLXGPUTuningServices1::IADLXGPUTuningServices1;

	ADLX_RESULT IsAtFactory(IADLXGPU* pGPU, adlx_bool* isFactory) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUTuningServices1, IsAtFactory);
	}

	ADLX_RESULT ResetToFactory(IADLXGPU* pGPU) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUTuningServices1, ResetToFactory);
	}

	ADLX_RESULT IsSupportedAutoTuning(IADLXGPU* pGPU, adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUTuningServices1, IsSupportedAutoTuning);
	}

	ADLX_RESULT IsSupportedManualFanTuning(IADLXGPU* pGPU, adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUTuningServices1, IsSupportedManualFanTuning);
	}

	ADLX_RESULT IsSupportedManualGFXTuning(IADLXGPU* pGPU, adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUTuningServices1, IsSupportedManualGFXTuning);
	}

	ADLX_RESULT IsSupportedManualPowerTuning(IADLXGPU* pGPU, adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUTuningServices1, IsSupportedManualPowerTuning);
	}

	ADLX_RESULT IsSupportedManualVRAMTuning(IADLXGPU* pGPU, adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUTuningServices1, IsSupportedManualVRAMTuning);
	}

	ADLX_RESULT IsSupportedPresetTuning(IADLXGPU* pGPU, adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUTuningServices1, IsSupportedPresetTuning);
	}

	// IADLXGPUTuningServices1
	ADLX_RESULT GetSmartAccessMemory(IADLXGPU* pGPU, IADLXSmartAccessMemory** ppSmartAccessMemory) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUTuningServices1, GetSmartAccessMemory);
	}
};
