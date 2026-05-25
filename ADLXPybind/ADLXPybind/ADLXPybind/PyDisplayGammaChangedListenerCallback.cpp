// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/chrono.h>

// Include SDK depends
#include "../../../SDK/Include/IDisplays.h"


namespace py = pybind11;
using namespace adlx;


// Callback
class PyDisplayGammaChangedListenerCallback : public IADLXDisplayGammaChangedListener
{
public:

	std::function<bool(IADLXDisplayGammaChangedEventPtr)> m_call;

	adlx_bool OnDisplayGammaChanged(IADLXDisplayGammaChangedEvent* pDisplayGammaChangedEvent) override {

		if (pDisplayGammaChangedEvent == nullptr)
		{
			return false;
		}

		if (m_call)
		{
			return m_call(pDisplayGammaChangedEvent);
		}

		return true;
	}
};
