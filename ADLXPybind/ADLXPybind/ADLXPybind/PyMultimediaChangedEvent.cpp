// Copyright Advanced Micro Devices, Inc. All rights reserved.
#include <pybind11/pybind11.h>
#include "../../../SDK/Include/IMultiMedia.h"

namespace py = pybind11;
using namespace adlx;

class PyMultimediaChangedEvent : public IADLXMultimediaChangedEvent
{
public:
    using IADLXMultimediaChangedEvent::IADLXMultimediaChangedEvent;

    ADLX_RESULT GetGPU(IADLXGPU** ppGPU) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXMultimediaChangedEvent, GetGPU);
    }
    adlx_bool IsVideoUpscaleChanged() override {
        PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXMultimediaChangedEvent, IsVideoUpscaleChanged);
    }
    adlx_bool IsVideoSuperResolutionChanged() override {
        PYBIND11_OVERRIDE_PURE(adlx_bool, IADLXMultimediaChangedEvent, IsVideoSuperResolutionChanged);
    }
};
