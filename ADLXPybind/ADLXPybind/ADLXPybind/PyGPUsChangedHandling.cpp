//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"


namespace py = pybind11;
using namespace adlx;


class PyGPUsChangedHandling : public IADLXGPUsChangedHandling
{
public:
	using IADLXGPUsChangedHandling::IADLXGPUsChangedHandling;

	ADLX_RESULT AddGPUsListEventListener(IADLXGPUsEventListener* pListener) override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXGPUsChangedHandling,
			AddGPUsListEventListener
		);
	}

	ADLX_RESULT RemoveGPUsListEventListener(IADLXGPUsEventListener* pListener) override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXGPUsChangedHandling,
			AddGPUsListEventListener
		);
	}

};
