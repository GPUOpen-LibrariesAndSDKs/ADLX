// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IPerformanceMonitoring.h"


namespace py = pybind11;
using namespace adlx;


class PyGPUMetricsList : public IADLXGPUMetricsList
{
public:
	using IADLXGPUMetricsList::IADLXGPUMetricsList;

	ADLX_RESULT Add_Back(IADLXGPUMetrics* pItem) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsList, Add_Back);
	}

	ADLX_RESULT At(const adlx_uint location, IADLXGPUMetrics** ppItem) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUMetricsList, At);
	}
};
