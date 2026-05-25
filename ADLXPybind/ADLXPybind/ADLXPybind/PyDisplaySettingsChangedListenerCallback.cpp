// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/chrono.h>

// Include SDK depends
#include "../../../SDK/Include/IDisplays.h"


namespace py = pybind11;
using namespace adlx;


// Callback
class PyDisplaySettingsChangedListenerCallback : public IADLXDisplaySettingsChangedListener
{
public:

	std::function<bool(IADLXDisplaySettingsChangedEventPtr)> m_call;

	adlx_bool OnDisplaySettingsChanged(IADLXDisplaySettingsChangedEvent* pDisplaySettingChangedEvent) override {

		if (pDisplaySettingChangedEvent == nullptr)
		{
			return false;
		}

		if (m_call)
		{
			return m_call(pDisplaySettingChangedEvent);
		}

		return true;
	}
};
