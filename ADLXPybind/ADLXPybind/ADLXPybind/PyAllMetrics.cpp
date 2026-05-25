// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IPerformanceMonitoring.h"


namespace py = pybind11;
using namespace adlx;


class PyAllMetrics : IADLXAllMetrics
{
public:
	using IADLXAllMetrics::IADLXAllMetrics;

	ADLX_RESULT GetSystemMetrics(IADLXSystemMetrics** ppSystemMetrics) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXAllMetrics, GetSystemMetrics);
	}

	ADLX_RESULT GetFPS(IADLXFPS** ppFPS) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXAllMetrics, GetSystemMetrics);
	}

	ADLX_RESULT GetGPUMetrics(IADLXGPU* pGPU, IADLXGPUMetrics** ppGPUMetrics) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXAllMetrics, GetSystemMetrics);
	}

	ADLX_RESULT TimeStamp(adlx_int64* ms) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXAllMetrics, TimeStamp);
	}
};
