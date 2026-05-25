// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/chrono.h>

// Include SDK depends
#include "../../../SDK/Include/IDisplays.h"


namespace py = pybind11;
using namespace adlx;


// Callback
class PyDisplayListChangedListenerCallback : public IADLXDisplayListChangedListener
{
public:

	adlx_bool OnDisplayListChanged(IADLXDisplayList* pNewDisplay) override {
		std::vector<IADLXDisplayPtr> list;
		for (adlx_uint s = pNewDisplay->Begin(); s != pNewDisplay->End(); s++) {
			IADLXDisplayPtr item;
			pNewDisplay->At(s, &item);
			list.emplace_back(item);
		}
		if (m_call) {
			return m_call(list);
		}
		return true;
	}

	std::function<bool(std::vector<IADLXDisplayPtr>)> m_call;
};
