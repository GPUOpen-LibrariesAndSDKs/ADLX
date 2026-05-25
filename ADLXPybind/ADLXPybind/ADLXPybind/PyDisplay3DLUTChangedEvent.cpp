// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IDisplays.h"


namespace py = pybind11;
using namespace adlx;


class PyDisplay3DLUTChangedEvent : public IADLXDisplay3DLUTChangedEvent
{
public:
	using IADLXDisplay3DLUTChangedEvent::IADLXDisplay3DLUTChangedEvent;

	ADLX_RESULT GetDisplay(IADLXDisplay** ppDisplay) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay3DLUTChangedEvent, GetDisplay);
	}

	adlx_bool IsCustom3DLUTChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXDisplay3DLUTChangedEvent, IsCustom3DLUTChanged);
	}

	adlx_bool IsSCEChanged() override {
		PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXDisplay3DLUTChangedEvent, IsSCEChanged);
	}

	ADLX_SYNC_ORIGIN GetOrigin() override {
		PYBIND11_OVERRIDE_PURE(ADLX_SYNC_ORIGIN, IADLXDisplay3DLUTChangedEvent, GetOrigin);
	}
};
