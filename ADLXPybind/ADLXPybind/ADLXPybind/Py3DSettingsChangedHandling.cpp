// Copyright Advanced Micro Devices, Inc. All rights reserved.
// Include pybind11 depends
#include <pybind11/pybind11.h>

// Include SDK depends
#include "../../../SDK/Include/I3DSettings.h"


namespace py = pybind11;
using namespace adlx;


class Py3DSettingsChangedHandling : IADLX3DSettingsChangedHandling
{
public:
	using IADLX3DSettingsChangedHandling::IADLX3DSettingsChangedHandling;

	ADLX_RESULT Add3DSettingsEventListener(IADLX3DSettingsChangedListener* p3DSettingsChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsChangedHandling, Add3DSettingsEventListener);
	}

	ADLX_RESULT Remove3DSettingsEventListener(IADLX3DSettingsChangedListener* p3DSettingsChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLX3DSettingsChangedHandling, Remove3DSettingsEventListener);
	}
};
