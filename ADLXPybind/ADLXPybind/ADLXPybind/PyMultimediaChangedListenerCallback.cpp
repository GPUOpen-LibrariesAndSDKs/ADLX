// Copyright Advanced Micro Devices, Inc. All rights reserved.
#include <pybind11/pybind11.h>
#include "../../../SDK/Include/IMultiMedia.h"
#include <functional>

namespace py = pybind11;
using namespace adlx;

class PyMultimediaChangedListenerCallback : public IADLXMultimediaChangedEventListener
{
public:
    std::function<bool(IADLXMultimediaChangedEventPtr)> m_call;

    adlx_bool ADLX_STD_CALL OnMultimediaChanged(IADLXMultimediaChangedEvent* pMultimediaChangedEvent) override
    {
        if (pMultimediaChangedEvent == nullptr) return false;
        if (m_call) return m_call(pMultimediaChangedEvent);
        return true;
    }
};
