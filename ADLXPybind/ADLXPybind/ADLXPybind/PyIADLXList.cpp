// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/ICollections.h"


namespace py = pybind11;
using namespace adlx;


class PyIADLXList : public IADLXList
{
public:
	using IADLXList::IADLXList;

	adlx_uint Size() override {
		PYBIND11_OVERRIDE_PURE(adlx_uint, IADLXList, Size);
	}

	adlx_bool Empty() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXList, Empty);
	}

	adlx_uint Begin()  override {
		PYBIND11_OVERRIDE_PURE(adlx_uint, IADLXList, Begin);
	}

	adlx_uint End() override {
		PYBIND11_OVERRIDE_PURE(adlx_uint, IADLXList, End);
	}

	ADLX_RESULT At(const adlx_uint location, IADLXInterface** ppItem) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXList, At);
	}

	ADLX_RESULT Clear()  override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXList, Clear);
	}

	ADLX_RESULT Remove_Back() override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXList, Remove_Back);
	}

	ADLX_RESULT Add_Back(IADLXInterface* pItem) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXList, Add_Back);
	}
};
