// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IPerformanceMonitoring.h"


namespace py = pybind11;
using namespace adlx;


class PyAllMetricsList : public IADLXAllMetricsList
{
public:
	using IADLXAllMetricsList::IADLXAllMetricsList;

	ADLX_RESULT Add_Back(IADLXAllMetrics* pItem) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXAllMetricsList, Add_Back);
	}

	ADLX_RESULT At(const adlx_uint location, IADLXAllMetrics** ppItem) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXAllMetricsList, At);
	}
};
