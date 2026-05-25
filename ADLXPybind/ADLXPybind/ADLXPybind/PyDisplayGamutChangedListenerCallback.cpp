// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/chrono.h>

// Include SDK depends
#include "../../../SDK/Include/IDisplays.h"


namespace py = pybind11;
using namespace adlx;


// Callback
class PyDisplayGamutChangedListenerCallback : public IADLXDisplayGamutChangedListener
{
public:

	std::function<bool(IADLXDisplayGamutChangedEventPtr)> m_call;

	adlx_bool OnDisplayGamutChanged(IADLXDisplayGamutChangedEvent* pDisplayGamutChangedEvent) override {

		if (pDisplayGamutChangedEvent == nullptr)
		{
			return false;
		}

		if (m_call)
		{
			return m_call(pDisplayGamutChangedEvent);
		}

		return true;
	}
};
