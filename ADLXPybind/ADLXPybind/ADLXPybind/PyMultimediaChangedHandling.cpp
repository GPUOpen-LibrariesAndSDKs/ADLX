// Copyright Advanced Micro Devices, Inc. All rights reserved.
#include <pybind11/pybind11.h>
#include "../../../SDK/Include/IMultiMedia.h"

namespace py = pybind11;
using namespace adlx;

class PyMultimediaChangedHandling : public IADLXMultimediaChangedHandling
{
public:
    using IADLXMultimediaChangedHandling::IADLXMultimediaChangedHandling;

    ADLX_RESULT AddMultimediaEventListener(IADLXMultimediaChangedEventListener* pMultimediaChangedEventListener) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXMultimediaChangedHandling, AddMultimediaEventListener);
    }
    ADLX_RESULT RemoveMultimediaEventListener(IADLXMultimediaChangedEventListener* pMultimediaChangedEventListener) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXMultimediaChangedHandling, RemoveMultimediaEventListener);
    }
};
