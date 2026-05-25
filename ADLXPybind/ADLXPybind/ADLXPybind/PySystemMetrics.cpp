// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IPerformanceMonitoring1.h"


namespace py = pybind11;
using namespace adlx;


class PySystemMetrics : IADLXSystemMetrics1
{
public:
	using IADLXSystemMetrics1::IADLXSystemMetrics1;

	// Methods from IADLXSystemMetrics (IPerformanceMonitoring.h)
	ADLX_RESULT TimeStamp(adlx_int64* ms) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSystemMetrics1, TimeStamp);
	}
	ADLX_RESULT CPUUsage(adlx_double* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSystemMetrics1, CPUUsage);
	}
	ADLX_RESULT SystemRAM(adlx_int* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSystemMetrics1, SystemRAM);
	}
	ADLX_RESULT SmartShift(adlx_int* data) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSystemMetrics1, SmartShift);
	}

	// Methods from IADLXSystemMetrics1 (IPerformanceMonitoring1.h)
	ADLX_RESULT PowerDistribution(adlx_int* apuShiftValue, adlx_int* gpuShiftValue, adlx_int* apuShiftLimit, adlx_int* gpuShiftLimit, adlx_int* totalShiftLimit) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSystemMetrics1, PowerDistribution);
	}
};
