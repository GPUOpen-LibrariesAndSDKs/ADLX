// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/chrono.h>

// Include SDK depends
#include "../../../SDK/Include/IDisplays.h"


namespace py = pybind11;
using namespace adlx;


// Callback
class PyDisplay3DLUTChangedListenerCallback : public IADLXDisplay3DLUTChangedListener
{
public:

	std::function<bool(IADLXDisplay3DLUTChangedEventPtr)> m_call;

	adlx_bool OnDisplay3DLUTChanged(IADLXDisplay3DLUTChangedEvent* pDisplay3DLUTChangedEvent) override {
		
		if (pDisplay3DLUTChangedEvent == nullptr) 
		{
			return false;
		}

		if (m_call) 
		{
			return m_call(pDisplay3DLUTChangedEvent);
		}
		
		return true;
	}	
};
