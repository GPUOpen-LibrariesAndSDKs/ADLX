// Copyright Advanced Micro Devices, Inc. All rights reserved.
#include <pybind11/pybind11.h>
#include "../../../SDK/Include/IApplications.h"

namespace py = pybind11;
using namespace adlx;

class PyGPUAppsListChangedHandling : public IADLXGPUAppsListChangedHandling
{
public:
    using IADLXGPUAppsListChangedHandling::IADLXGPUAppsListChangedHandling;

    ADLX_RESULT AddGPUAppsListEventListener(IADLXGPUAppsListEventListener* pGPUAppsListEventListener) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUAppsListChangedHandling, AddGPUAppsListEventListener);
    }

    ADLX_RESULT RemoveGPUAppsListEventListener(IADLXGPUAppsListEventListener* pGPUAppsListEventListener) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXGPUAppsListChangedHandling, RemoveGPUAppsListEventListener);
    }
};
