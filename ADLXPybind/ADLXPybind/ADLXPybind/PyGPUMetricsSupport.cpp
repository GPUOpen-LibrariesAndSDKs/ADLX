// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IPerformanceMonitoring3.h"


namespace py = pybind11;
using namespace adlx; 


class PyGPUMetricsSupport : IADLXGPUMetricsSupport3
{
public:
	using IADLXGPUMetricsSupport3::IADLXGPUMetricsSupport3;

	// IADLXGPUMetricsSupport methods
	ADLX_RESULT IsSupportedGPUUsage(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, IsSupportedGPUUsage);
	}
	ADLX_RESULT IsSupportedGPUClockSpeed(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, IsSupportedGPUClockSpeed);
	}
	ADLX_RESULT IsSupportedGPUVRAMClockSpeed(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, IsSupportedGPUVRAMClockSpeed);
	}
	ADLX_RESULT IsSupportedGPUTemperature(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, IsSupportedGPUTemperature);
	}
	ADLX_RESULT IsSupportedGPUHotspotTemperature(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, IsSupportedGPUHotspotTemperature);
	}
	ADLX_RESULT IsSupportedGPUPower(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, IsSupportedGPUPower);
	}
	ADLX_RESULT IsSupportedGPUTotalBoardPower(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, IsSupportedGPUTotalBoardPower);
	}
	ADLX_RESULT IsSupportedGPUFanSpeed(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, IsSupportedGPUFanSpeed);
	}
	ADLX_RESULT IsSupportedGPUVRAM(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, IsSupportedGPUVRAM);
	}
	ADLX_RESULT IsSupportedGPUVoltage(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, IsSupportedGPUVoltage);
	}
	ADLX_RESULT GetGPUUsageRange(adlx_int* minValue, adlx_int* maxValue) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, GetGPUUsageRange);
	}
	ADLX_RESULT GetGPUClockSpeedRange(adlx_int* minValue, adlx_int* maxValue) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, GetGPUClockSpeedRange);
	}
	ADLX_RESULT GetGPUVRAMClockSpeedRange(adlx_int* minValue, adlx_int* maxValue) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, GetGPUVRAMClockSpeedRange);
	}
	ADLX_RESULT GetGPUTemperatureRange(adlx_int* minValue, adlx_int* maxValue) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, GetGPUTemperatureRange);
	}
	ADLX_RESULT GetGPUHotspotTemperatureRange(adlx_int* minValue, adlx_int* maxValue) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, GetGPUHotspotTemperatureRange);
	}
	ADLX_RESULT GetGPUPowerRange(adlx_int* minValue, adlx_int* maxValue) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, GetGPUPowerRange);
	}
	ADLX_RESULT GetGPUFanSpeedRange(adlx_int* minValue, adlx_int* maxValue) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, GetGPUFanSpeedRange);
	}
	ADLX_RESULT GetGPUVRAMRange(adlx_int* minValue, adlx_int* maxValue) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, GetGPUVRAMRange);
	}
	ADLX_RESULT GetGPUVoltageRange(adlx_int* minValue, adlx_int* maxValue) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, GetGPUVoltageRange);
	}
	ADLX_RESULT GetGPUTotalBoardPowerRange(adlx_int* minValue, adlx_int* maxValue) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, GetGPUTotalBoardPowerRange);
	}
	ADLX_RESULT GetGPUIntakeTemperatureRange(adlx_int* minValue, adlx_int* maxValue) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, GetGPUIntakeTemperatureRange);
	}
	ADLX_RESULT IsSupportedGPUIntakeTemperature(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport, IsSupportedGPUIntakeTemperature);
	}

	// IADLXGPUMetricsSupport1 methods
	ADLX_RESULT IsSupportedGPUMemoryTemperature(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport1, IsSupportedGPUMemoryTemperature);
	}
	ADLX_RESULT GetGPUMemoryTemperatureRange(adlx_int* minValue, adlx_int* maxValue) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport1, GetGPUMemoryTemperatureRange);
	}
	ADLX_RESULT IsSupportedNPUFrequency(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport1, IsSupportedNPUFrequency);
	}
	ADLX_RESULT GetNPUFrequencyRange(adlx_int* minValue, adlx_int* maxValue) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport1, GetNPUFrequencyRange);
	}
	ADLX_RESULT IsSupportedNPUActivityLevel(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport1, IsSupportedNPUActivityLevel);
	}
	ADLX_RESULT GetNPUActivityLevelRange(adlx_int* minValue, adlx_int* maxValue) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport1, GetNPUActivityLevelRange);
	}

	// IADLXGPUMetricsSupport2 methods
	ADLX_RESULT IsSupportedGPUSharedMemory(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport2, IsSupportedGPUSharedMemory);
	}
	ADLX_RESULT GetGPUSharedMemoryRange(adlx_int* minValue, adlx_int* maxValue) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport2, GetGPUSharedMemoryRange);
	}

	// IADLXGPUMetricsSupport3 methods
	ADLX_RESULT IsSupportedGPUFanDuty(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport3, IsSupportedGPUFanDuty);
	}
	ADLX_RESULT GetGPUFanDutyRange(adlx_int* minValue, adlx_int* maxValue) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsSupport3, GetGPUFanDutyRange);
	}
};
