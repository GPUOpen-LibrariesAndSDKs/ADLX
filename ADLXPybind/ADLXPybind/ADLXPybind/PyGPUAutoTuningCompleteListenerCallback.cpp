// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/chrono.h>

// Include SDK depends
#include "../../../SDK/Include/IGPUAutoTuning.h"


namespace py = pybind11;
using namespace adlx;


// Callback
class PyGPUAutoTuningCompleteListenerCallback : public IADLXGPUAutoTuningCompleteListener
{
public:

	std::function<bool(IADLXGPUAutoTuningCompleteEventPtr)> m_call;

	adlx_bool OnGPUAutoTuningComplete(IADLXGPUAutoTuningCompleteEvent* pGPUAutoTuningCompleteEvent) override
	{
		if (pGPUAutoTuningCompleteEvent == nullptr)
		{
			return false;
		}

		if (m_call)
		{
			return m_call(pGPUAutoTuningCompleteEvent);
		}

		return true;
	}
};
