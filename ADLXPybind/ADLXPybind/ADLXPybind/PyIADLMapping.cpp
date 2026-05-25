// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/ISystem.h"


namespace py = pybind11;
using namespace adlx;


class PyIADLMapping : IADLMapping
{
public:
	using IADLMapping::IADLMapping;

	ADLX_RESULT ADLIdsFromADLXDesktop(IADLXDesktop* pDesktop, adlx_int* adapterIndex, adlx_int* VidPnSourceId, adlx_int* bus, adlx_int* device, adlx_int* function) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLMapping, ADLIdsFromADLXDesktop);
	}

	ADLX_RESULT ADLIdsFromADLXDisplay(IADLXDisplay* pDisplay, adlx_int* adapterIndex, adlx_int* displayIndex, adlx_int* bus, adlx_int* device, adlx_int* function) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLMapping, ADLIdsFromADLXDisplay);
	}

	ADLX_RESULT AdlAdapterIndexFromADLXGPU(IADLXGPU* ppGPU, adlx_int* adlAdapterIndex) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLMapping, AdlAdapterIndexFromADLXGPU);
	}

	ADLX_RESULT BdfFromADLXGPU(IADLXGPU* ppGPU, adlx_int* bus, adlx_int* device, adlx_int* function) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLMapping, BdfFromADLXGPU);
	}

	ADLX_RESULT GetADLXDesktopFromADLIds(adlx_int adapterIndex, adlx_int VidPnSource, adlx_int bus, adlx_int device, adlx_int function, IADLXDesktop** ppDesktop) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLMapping, GetADLXDesktopFromADLIds);
	}

	ADLX_RESULT GetADLXDisplayFromADLIds(adlx_int adapterIndex, adlx_int displayIndex, adlx_int bus, adlx_int device, adlx_int function, IADLXDisplay** ppDisplay) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLMapping, GetADLXDisplayFromADLIds);
	}

	ADLX_RESULT GetADLXGPUFromAdlAdapterIndex(adlx_int adlAdapterIndex, IADLXGPU** ppGPU) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLMapping, GetADLXGPUFromAdlAdapterIndex);
	}

	ADLX_RESULT GetADLXGPUFromBdf(adlx_int bus, adlx_int device, adlx_int function, IADLXGPU** ppGPU) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLMapping, GetADLXGPUFromBdf);
	}
};
