// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IPerformanceMonitoring3.h"


namespace py = pybind11;
using namespace adlx;


class PyGPUMetrics : public IADLXGPUMetrics3
{
public:
	using IADLXGPUMetrics3::IADLXGPUMetrics3;

	
	ADLX_RESULT GPUClockSpeed(adlx_int* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics3, GPUClockSpeed);
	}

	ADLX_RESULT GPUFanSpeed(adlx_int* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics3, GPUFanSpeed);
	}

	ADLX_RESULT GPUHotspotTemperature(adlx_double* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics3, GPUHotspotTemperature);
	}

	ADLX_RESULT GPUPower(adlx_double* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics3, GPUPower);
	}

	ADLX_RESULT GPUTemperature(adlx_double* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics3, GPUTemperature);
	}
			
	ADLX_RESULT GPUTotalBoardPower(adlx_double* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics3, GPUTotalBoardPower);
	}

	ADLX_RESULT GPUUsage(adlx_double* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics3, GPUUsage);
	}

	ADLX_RESULT GPUVRAM(adlx_int* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics3, GPUVRAM);
	}
	
	ADLX_RESULT GPUVRAMClockSpeed(adlx_int* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics3, GPUVRAMClockSpeed);
	}

	ADLX_RESULT GPUVoltage(adlx_int* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics3, GPUVoltage);
	}

	ADLX_RESULT TimeStamp(adlx_int64* ms) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics3, TimeStamp);
	}

	ADLX_RESULT GPUIntakeTemperature(adlx_double* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics3, GPUIntakeTemperature);
	}

	// Methods from IADLXGPUMetrics1 (IPerformanceMonitoring2.h)
	ADLX_RESULT GPUMemoryTemperature(adlx_double* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics3, GPUMemoryTemperature);
	}

	ADLX_RESULT NPUFrequency(adlx_int* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics3, NPUFrequency);
	}

	ADLX_RESULT NPUActivityLevel(adlx_int* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics3, NPUActivityLevel);
	}

	// Methods from IADLXGPUMetrics2 (IPerformanceMonitoring3.h)
	ADLX_RESULT GPUSharedMemory(adlx_int* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics3, GPUSharedMemory);
	}

	// Methods from IADLXGPUMetrics3 (IPerformanceMonitoring3.h)
	ADLX_RESULT GPUFanDuty(adlx_int* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetrics3, GPUFanDuty);
	}
};
