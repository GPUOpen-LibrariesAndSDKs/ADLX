// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IPerformanceMonitoring.h"


namespace py = pybind11;
using namespace adlx;


class PyFPSList : public IADLXFPSList
{
public:
	using IADLXFPSList::IADLXFPSList;

	ADLX_RESULT Add_Back(IADLXFPS* pItem) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXFPSList, Add_Back);
	}

	ADLX_RESULT At(const adlx_uint location, IADLXFPS** ppItem) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXFPSList, At);
	}
};
