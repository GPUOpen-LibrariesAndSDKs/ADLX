//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"


namespace py = pybind11;
using namespace adlx;


class PySystem : public IADLXSystem
{
public:
	using IADLXSystem::IADLXSystem;

	ADLX_RESULT  HybridGraphicsType(ADLX_HG_TYPE* hgType)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			HybridGraphicsType
		);
	}

	ADLX_RESULT  GetGPUs(IADLXGPUList** ppGPUs)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			GetGPUs
		);
	}

	ADLX_RESULT  QueryInterface(const wchar_t* interfaceId, void** ppInterface)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			QueryInterface
		);
	}

	ADLX_RESULT  GetDisplaysServices(IADLXDisplayServices** ppDispServices)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			GetDisplaysServices
		);
	}

	ADLX_RESULT  GetDesktopsServices(IADLXDesktopServices** ppDeskServices)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			GetDesktopsServices
		);
	}

	ADLX_RESULT  GetGPUsChangedHandling(IADLXGPUsChangedHandling** ppGPUsChangedHandling)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			GetGPUsChangedHandling
		);
	}

	ADLX_RESULT  EnableLog(ADLX_LOG_DESTINATION mode, ADLX_LOG_SEVERITY severity, IADLXLog* pLogger, const wchar_t* fileName)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			EnableLog
		);
	}

	ADLX_RESULT  Get3DSettingsServices(IADLX3DSettingsServices** pp3DSettingsServices)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			Get3DSettingsServices
		);
	}

	ADLX_RESULT  GetGPUTuningServices(IADLXGPUTuningServices** ppGPUTuningServices)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			GetGPUTuningServices
		);
	}

	ADLX_RESULT  GetPerformanceMonitoringServices(IADLXPerformanceMonitoringServices** ppPerformanceMonitoringServices)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			GetPerformanceMonitoringServices
		);
	}

	ADLX_RESULT  TotalSystemRAM(adlx_uint* ramMB)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			TotalSystemRAM
		);
	}

	ADLX_RESULT  GetI2C(IADLXGPU *pGPU, IADLXI2C **ppI2C) override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			GetI2C
		);
	}


};
