// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/ISystem.h"
#include <functional>


namespace py = pybind11;
using namespace adlx;


// Callback
class PyGPUsEventListenerCallback : public IADLXGPUsEventListener
{
public:
	std::function<bool(IADLXGPUList*)> m_call;

	adlx_bool OnGPUListChanged(IADLXGPUList* pNewGPUs) override
	{
		if (pNewGPUs == nullptr)
			return false;
		if (m_call)
			return m_call(pNewGPUs);
		return true;
	}
};
