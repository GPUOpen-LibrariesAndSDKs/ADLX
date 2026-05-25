// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/IChangedEvent.h"


namespace py = pybind11;
using namespace adlx;


class PyChangedEvent : public IADLXChangedEvent
{
public:
	using IADLXChangedEvent::IADLXChangedEvent;

	ADLX_SYNC_ORIGIN GetOrigin() override {
		PYBIND11_OVERRIDE_PURE(ADLX_SYNC_ORIGIN, IADLXChangedEvent, GetOrigin);
	}
};
