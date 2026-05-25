// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/chrono.h>

// Include SDK depends
#include "../../../SDK/Include/IGPUTuning.h"


namespace py = pybind11;
using namespace adlx;


// Callback
class PyGPUTuningChangedListenerCallback : public IADLXGPUTuningChangedListener
{
public:

	std::function<bool(IADLXGPUTuningChangedEventPtr)> m_call;

	adlx_bool OnGPUTuningChanged(IADLXGPUTuningChangedEvent* pGPUTuningChangedEvent) override
	{
		if (pGPUTuningChangedEvent == nullptr)
		{
			return false;
		}

		if (m_call)
		{
			return m_call(pGPUTuningChangedEvent);
		}

		return true;
	}
};
