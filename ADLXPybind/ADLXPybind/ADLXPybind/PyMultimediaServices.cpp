// Copyright Advanced Micro Devices, Inc. All rights reserved.
#include <pybind11/pybind11.h>
#include "../../../SDK/Include/IMultiMedia.h"

namespace py = pybind11;
using namespace adlx;

class PyMultimediaServices : public IADLXMultimediaServices
{
public:
    using IADLXMultimediaServices::IADLXMultimediaServices;

    ADLX_RESULT GetMultimediaChangedHandling(IADLXMultimediaChangedHandling** ppMultimediaChangedHandling) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXMultimediaServices, GetMultimediaChangedHandling);
    }
    ADLX_RESULT GetVideoUpscale(IADLXGPU* pGPU, IADLXVideoUpscale** ppVideoUpscale) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXMultimediaServices, GetVideoUpscale);
    }
    ADLX_RESULT GetVideoSuperResolution(IADLXGPU* pGPU, IADLXVideoSuperResolution** ppVideoSuperResolution) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXMultimediaServices, GetVideoSuperResolution);
    }
};
