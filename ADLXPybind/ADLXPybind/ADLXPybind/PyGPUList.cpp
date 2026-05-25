// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"


namespace py = pybind11;
using namespace adlx;


class PyGPUList : public IADLXGPUList
{
public:
	using IADLXGPUList::IADLXGPUList;

	ADLX_RESULT Add_Back(IADLXGPU* pItem) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUList, Add_Back);
	}

	ADLX_RESULT At(const adlx_uint location, IADLXGPU** ppItem) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUList, At);
	}
};
