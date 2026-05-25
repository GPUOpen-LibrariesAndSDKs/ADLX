//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

#include "bind_common.h"

void bind_multimedia(py::module_& m)
{
    // IADLXVideoUpscale
    py::class_<IADLXVideoUpscale, IADLXInterface, PyVideoUpscale, IADLXInterfacePtr_T<IADLXVideoUpscale>>(m, "IADLXVideoUpscale")
        .def("IsSupported", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXVideoUpscalePtr vu = self.cast<IADLXVideoUpscale*>();
        adlx_bool supported = false;
        ADLX_RESULT ret = vu->IsSupported(&supported);
        if (ADLX_SUCCEEDED(ret))
            return supported;
        return py::none();
    })
        .def("IsEnabled", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXVideoUpscalePtr vu = self.cast<IADLXVideoUpscale*>();
        adlx_bool enabled = false;
        ADLX_RESULT ret = vu->IsEnabled(&enabled);
        if (ADLX_SUCCEEDED(ret))
            return enabled;
        return py::none();
    })
        .def("GetSharpnessRange", [](py::object self) {
        IADLXVideoUpscalePtr vu = self.cast<IADLXVideoUpscale*>();
        ADLX_IntRange range;
        ADLX_RESULT ret = vu->GetSharpnessRange(&range);
        py::dict dict;
        dict["return"] = ret;
        dict["min_value"] = range.minValue;
        dict["max_value"] = range.maxValue;
        dict["step"] = range.step;
        return dict;
    })
        .def("GetSharpness", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXVideoUpscalePtr vu = self.cast<IADLXVideoUpscale*>();
        adlx_int sharpness;
        ADLX_RESULT ret = vu->GetSharpness(&sharpness);
        if (ADLX_SUCCEEDED(ret))
            return sharpness;
        return py::none();
    })
        .def("SetEnabled", [](py::object self, adlx_bool enabled) {
        IADLXVideoUpscalePtr vu = self.cast<IADLXVideoUpscale*>();
        return vu->SetEnabled(enabled);
    })
        .def("SetSharpness", [](py::object self, adlx_int sharpness) {
        IADLXVideoUpscalePtr vu = self.cast<IADLXVideoUpscale*>();
        return vu->SetSharpness(sharpness);
    });

    // IADLXVideoSuperResolution
    py::class_<IADLXVideoSuperResolution, IADLXInterface, PyVideoSuperResolution, IADLXInterfacePtr_T<IADLXVideoSuperResolution>>(m, "IADLXVideoSuperResolution")
        .def("IsSupported", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXVideoSuperResolutionPtr vsr = self.cast<IADLXVideoSuperResolution*>();
        adlx_bool supported = false;
        ADLX_RESULT ret = vsr->IsSupported(&supported);
        if (ADLX_SUCCEEDED(ret))
            return supported;
        return py::none();
    })
        .def("IsEnabled", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXVideoSuperResolutionPtr vsr = self.cast<IADLXVideoSuperResolution*>();
        adlx_bool enabled = false;
        ADLX_RESULT ret = vsr->IsEnabled(&enabled);
        if (ADLX_SUCCEEDED(ret))
            return enabled;
        return py::none();
    })
        .def("SetEnabled", [](py::object self, adlx_bool enabled) {
        IADLXVideoSuperResolutionPtr vsr = self.cast<IADLXVideoSuperResolution*>();
        return vsr->SetEnabled(enabled);
    });

    // IADLXMultimediaChangedEvent
    py::class_<IADLXMultimediaChangedEvent, IADLXInterface, PyMultimediaChangedEvent, IADLXInterfacePtr_T<IADLXMultimediaChangedEvent>>(m, "IADLXMultimediaChangedEvent")
        .def("GetGPU", [](py::object self) {
        IADLXMultimediaChangedEventPtr evt = self.cast<IADLXMultimediaChangedEvent*>();
        IADLXGPUPtr gpu;
        evt->GetGPU(&gpu);
        return gpu;
    }, py::return_value_policy::move)
        .def("IsVideoUpscaleChanged", [](py::object self) {
        IADLXMultimediaChangedEventPtr evt = self.cast<IADLXMultimediaChangedEvent*>();
        return evt->IsVideoUpscaleChanged();
    })
        .def("IsVideoSuperResolutionChanged", [](py::object self) {
        IADLXMultimediaChangedEventPtr evt = self.cast<IADLXMultimediaChangedEvent*>();
        return evt->IsVideoSuperResolutionChanged();
    });

    // Callback for MultimediaChangedListener
    py::class_<PyMultimediaChangedListenerCallback>(m, "PyMultimediaChangedListenerCallback")
        .def(py::init<>())
        .def_readwrite("call", &PyMultimediaChangedListenerCallback::m_call);

    // IADLXMultimediaChangedHandling
    py::class_<IADLXMultimediaChangedHandling, IADLXInterface, PyMultimediaChangedHandling, IADLXInterfacePtr_T<IADLXMultimediaChangedHandling>>(m, "IADLXMultimediaChangedHandling")
        .def("AddMultimediaEventListener", [](py::object self, PyMultimediaChangedListenerCallback* pListener) {
        IADLXMultimediaChangedHandlingPtr handling = self.cast<IADLXMultimediaChangedHandling*>();
        return handling->AddMultimediaEventListener(static_cast<IADLXMultimediaChangedEventListener*>(pListener));
    })
        .def("RemoveMultimediaEventListener", [](py::object self, PyMultimediaChangedListenerCallback* pListener) {
        IADLXMultimediaChangedHandlingPtr handling = self.cast<IADLXMultimediaChangedHandling*>();
        return handling->RemoveMultimediaEventListener(static_cast<IADLXMultimediaChangedEventListener*>(pListener));
    });

    // IADLXMultimediaServices
    py::class_<IADLXMultimediaServices, IADLXInterface, PyMultimediaServices, IADLXInterfacePtr_T<IADLXMultimediaServices>>(m, "IADLXMultimediaServices")
        .def("GetMultimediaChangedHandling", [](py::object self) {
        IADLXMultimediaServicesPtr svc = self.cast<IADLXMultimediaServices*>();
        IADLXMultimediaChangedHandlingPtr handling;
        svc->GetMultimediaChangedHandling(&handling);
        return handling;
    }, py::return_value_policy::move)
        .def("GetVideoUpscale", [](py::object self, IADLXGPUPtr gpu) {
        IADLXMultimediaServicesPtr svc = self.cast<IADLXMultimediaServices*>();
        IADLXVideoUpscalePtr vu;
        svc->GetVideoUpscale(gpu, &vu);
        return vu;
    }, py::return_value_policy::move)
        .def("GetVideoSuperResolution", [](py::object self, IADLXGPUPtr gpu) {
        IADLXMultimediaServicesPtr svc = self.cast<IADLXMultimediaServices*>();
        IADLXVideoSuperResolutionPtr vsr;
        svc->GetVideoSuperResolution(gpu, &vsr);
        return vsr;
    }, py::return_value_policy::move);
}
