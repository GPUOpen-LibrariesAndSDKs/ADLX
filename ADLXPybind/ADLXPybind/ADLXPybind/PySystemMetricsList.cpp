// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IPerformanceMonitoring.h"


namespace py = pybind11;
using namespace adlx;


class PySystemMetricsList : public IADLXSystemMetricsList
{
public:
	using IADLXSystemMetricsList::IADLXSystemMetricsList;

	ADLX_RESULT Add_Back(IADLXSystemMetrics* pItem) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSystemMetricsList, Add_Back);
	}

	ADLX_RESULT At(const adlx_uint location, IADLXSystemMetrics** ppItem) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXSystemMetricsList, At);
	}
};
