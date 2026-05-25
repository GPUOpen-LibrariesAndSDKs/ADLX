// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/I3DSettings3.h"
#include "../../../SDK/Include/ISystem.h"
#include <iostream>


namespace py = pybind11;
using namespace adlx;


// Callback
class Py3DSettingsChangedListenerCallback : public IADLX3DSettingsChangedListener
{
public:

	std::function<bool(IADLX3DSettingsChangedEventPtr)> m_call;

	adlx_bool On3DSettingsChanged(IADLX3DSettingsChangedEvent* p3DSettingsChangedEvent) override
	{
		if (p3DSettingsChangedEvent == nullptr)
		{
			return false;
		}

		if (m_call)
		{
			return m_call(p3DSettingsChangedEvent);
		}

		return true;
	}
};
