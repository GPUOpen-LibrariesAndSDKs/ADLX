// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IPerformanceMonitoring1.h"


namespace py = pybind11;
using namespace adlx; 


class PySystemMetricsSupport : IADLXSystemMetricsSupport1
{
public:
	using IADLXSystemMetricsSupport1::IADLXSystemMetricsSupport1;

	ADLX_RESULT IsSupportedCPUUsage(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSystemMetricsSupport1, IsSupportedCPUUsage);
	}

	ADLX_RESULT IsSupportedSystemRAM(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSystemMetricsSupport1, IsSupportedSystemRAM);
	}

	ADLX_RESULT IsSupportedSmartShift(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSystemMetricsSupport1, IsSupportedSmartShift);
	}

	ADLX_RESULT GetCPUUsageRange(adlx_int* minValue, adlx_int* maxValue) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSystemMetricsSupport1, GetCPUUsageRange);
	}

	ADLX_RESULT GetSystemRAMRange(adlx_int* minValue, adlx_int* maxValue) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSystemMetricsSupport1, GetSystemRAMRange);
	}

	ADLX_RESULT GetSmartShiftRange(adlx_int* minValue, adlx_int* maxValue) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSystemMetricsSupport1, GetSmartShiftRange);
	}

	// Methods from IADLXSystemMetricsSupport1
	ADLX_RESULT IsSupportedPowerDistribution(adlx_bool* supported) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSystemMetricsSupport1, IsSupportedPowerDistribution);
	}
};
