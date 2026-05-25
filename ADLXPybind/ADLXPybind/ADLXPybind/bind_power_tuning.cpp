//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

#include "bind_common.h"

void bind_power_tuning(py::module_& m)
{
    // IADLXSmartShiftMax
    py::class_<IADLXSmartShiftMax, IADLXInterface, PySmartShiftMax, IADLXInterfacePtr_T<IADLXSmartShiftMax>>(m, "IADLXSmartShiftMax")
        .def("IsSupported", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXSmartShiftMaxPtr ssm = self.cast<IADLXSmartShiftMax*>();
        adlx_bool supported = false;
        ADLX_RESULT ret = ssm->IsSupported(&supported);
        if (ADLX_SUCCEEDED(ret))
            return supported;
        return py::none();
    })
        .def("GetBiasMode", [](py::object self) -> std::variant<ADLX_SSM_BIAS_MODE, py::none> {
        IADLXSmartShiftMaxPtr ssm = self.cast<IADLXSmartShiftMax*>();
        ADLX_SSM_BIAS_MODE mode;
        ADLX_RESULT ret = ssm->GetBiasMode(&mode);
        if (ADLX_SUCCEEDED(ret))
            return mode;
        return py::none();
    })
        .def("SetBiasMode", [](py::object self, ADLX_SSM_BIAS_MODE mode) {
        IADLXSmartShiftMaxPtr ssm = self.cast<IADLXSmartShiftMax*>();
        return ssm->SetBiasMode(mode);
    })
        .def("GetBiasRange", [](py::object self) {
        IADLXSmartShiftMaxPtr ssm = self.cast<IADLXSmartShiftMax*>();
        ADLX_IntRange range;
        ADLX_RESULT ret = ssm->GetBiasRange(&range);
        py::dict dict;
        dict["return"] = ret;
        dict["min_value"] = range.minValue;
        dict["max_value"] = range.maxValue;
        dict["step"] = range.step;
        return dict;
    })
        .def("GetBias", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXSmartShiftMaxPtr ssm = self.cast<IADLXSmartShiftMax*>();
        adlx_int bias;
        ADLX_RESULT ret = ssm->GetBias(&bias);
        if (ADLX_SUCCEEDED(ret))
            return bias;
        return py::none();
    })
        .def("SetBias", [](py::object self, adlx_int bias) {
        IADLXSmartShiftMaxPtr ssm = self.cast<IADLXSmartShiftMax*>();
        return ssm->SetBias(bias);
    });

    // IADLXSmartShiftEco
    py::class_<IADLXSmartShiftEco, IADLXInterface, PySmartShiftEco, IADLXInterfacePtr_T<IADLXSmartShiftEco>>(m, "IADLXSmartShiftEco")
        .def("IsSupported", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXSmartShiftEcoPtr sse = self.cast<IADLXSmartShiftEco*>();
        adlx_bool supported = false;
        ADLX_RESULT ret = sse->IsSupported(&supported);
        if (ADLX_SUCCEEDED(ret))
            return supported;
        return py::none();
    })
        .def("IsEnabled", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXSmartShiftEcoPtr sse = self.cast<IADLXSmartShiftEco*>();
        adlx_bool enabled = false;
        ADLX_RESULT ret = sse->IsEnabled(&enabled);
        if (ADLX_SUCCEEDED(ret))
            return enabled;
        return py::none();
    })
        .def("SetEnabled", [](py::object self, adlx_bool enabled) {
        IADLXSmartShiftEcoPtr sse = self.cast<IADLXSmartShiftEco*>();
        return sse->SetEnabled(enabled);
    })
        .def("IsInactive", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXSmartShiftEcoPtr sse = self.cast<IADLXSmartShiftEco*>();
        adlx_bool inactive = false;
        ADLX_RESULT ret = sse->IsInactive(&inactive);
        if (ADLX_SUCCEEDED(ret))
            return inactive;
        return py::none();
    })
        .def("GetInactiveReason", [](py::object self) -> std::variant<ADLX_SMARTSHIFT_ECO_INACTIVE_REASON, py::none> {
        IADLXSmartShiftEcoPtr sse = self.cast<IADLXSmartShiftEco*>();
        ADLX_SMARTSHIFT_ECO_INACTIVE_REASON reason;
        ADLX_RESULT ret = sse->GetInactiveReason(&reason);
        if (ADLX_SUCCEEDED(ret))
            return reason;
        return py::none();
    });

    // IADLXPowerTuningChangedEvent (base) with QI-fold for Event1
    py::class_<IADLXPowerTuningChangedEvent, IADLXChangedEvent, PyPowerTuningChangedEvent, IADLXInterfacePtr_T<IADLXPowerTuningChangedEvent>>(m, "IADLXPowerTuningChangedEvent")
        .def("IsSmartShiftMaxChanged", [](py::object self) {
        IADLXPowerTuningChangedEventPtr evt = self.cast<IADLXPowerTuningChangedEvent*>();
        return evt->IsSmartShiftMaxChanged();
    })
        // QI-fold IADLXPowerTuningChangedEvent1
        .def("IsSmartShiftEcoChanged", [](py::object self) {
        IADLXPowerTuningChangedEventPtr evt = self.cast<IADLXPowerTuningChangedEvent*>();
        IADLXPowerTuningChangedEvent1Ptr evt1(evt);
        if (evt1)
        {
            return evt1->IsSmartShiftEcoChanged();
        }
        return adlx_bool(false);
    });

    // Callback for PowerTuningChangedListener
    py::class_<PyPowerTuningChangedListenerCallback>(m, "PyPowerTuningChangedListenerCallback")
        .def(py::init<>())
        .def_readwrite("call", &PyPowerTuningChangedListenerCallback::m_call);

    // IADLXPowerTuningChangedHandling
    py::class_<IADLXPowerTuningChangedHandling, IADLXInterface, PyPowerTuningChangedHandling, IADLXInterfacePtr_T<IADLXPowerTuningChangedHandling>>(m, "IADLXPowerTuningChangedHandling")
        .def("AddPowerTuningEventListener", [](py::object self, PyPowerTuningChangedListenerCallback* pListener) {
        IADLXPowerTuningChangedHandlingPtr handling = self.cast<IADLXPowerTuningChangedHandling*>();
        return handling->AddPowerTuningEventListener(pListener);
    })
        .def("RemovePowerTuningEventListener", [](py::object self, PyPowerTuningChangedListenerCallback* pListener) {
        IADLXPowerTuningChangedHandlingPtr handling = self.cast<IADLXPowerTuningChangedHandling*>();
        return handling->RemovePowerTuningEventListener(pListener);
    });

    // IADLXPowerTuningServices (base) with QI-fold for Services1
    py::class_<IADLXPowerTuningServices, IADLXInterface, PyPowerTuningServices, IADLXInterfacePtr_T<IADLXPowerTuningServices>>(m, "IADLXPowerTuningServices")
        .def("GetPowerTuningChangedHandling", [](py::object self) {
        IADLXPowerTuningServicesPtr svc = self.cast<IADLXPowerTuningServices*>();
        IADLXPowerTuningChangedHandlingPtr handling;
        svc->GetPowerTuningChangedHandling(&handling);
        return handling;
    }, py::return_value_policy::move)
        .def("GetSmartShiftMax", [](py::object self) {
        IADLXPowerTuningServicesPtr svc = self.cast<IADLXPowerTuningServices*>();
        IADLXSmartShiftMaxPtr ssm;
        svc->GetSmartShiftMax(&ssm);
        return ssm;
    }, py::return_value_policy::move)
        // QI-fold IADLXPowerTuningServices1
        .def("GetSmartShiftEco", [](py::object self) {
        IADLXPowerTuningServicesPtr svc = self.cast<IADLXPowerTuningServices*>();
        IADLXPowerTuningServices1Ptr svc1(svc);
        if (svc1)
        {
            IADLXSmartShiftEcoPtr sse;
            svc1->GetSmartShiftEco(&sse);
            return sse;
        }
        return IADLXSmartShiftEcoPtr();
    }, py::return_value_policy::move)
        .def("IsGPUConnectSupported", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXPowerTuningServicesPtr svc = self.cast<IADLXPowerTuningServices*>();
        IADLXPowerTuningServices1Ptr svc1(svc);
        if (svc1)
        {
            adlx_bool supported = false;
            ADLX_RESULT ret = svc1->IsGPUConnectSupported(&supported);
            if (ADLX_SUCCEEDED(ret))
                return supported;
        }
        return py::none();
    })
        .def("GetGPUConnectGPUs", [](py::object self) {
        IADLXPowerTuningServicesPtr svc = self.cast<IADLXPowerTuningServices*>();
        IADLXPowerTuningServices1Ptr svc1(svc);
        if (svc1)
        {
            IADLXGPU2ListPtr gpuList;
            svc1->GetGPUConnectGPUs(&gpuList);
            return gpuList;
        }
        return IADLXGPU2ListPtr();
    }, py::return_value_policy::move);

    // IADLXGPUConnectChangedEvent
    py::class_<IADLXGPUConnectChangedEvent, IADLXChangedEvent, PyGPUConnectChangedEvent, IADLXInterfacePtr_T<IADLXGPUConnectChangedEvent>>(m, "IADLXGPUConnectChangedEvent")
        .def("GetGPU", [](py::object self) {
        IADLXGPUConnectChangedEventPtr evt = self.cast<IADLXGPUConnectChangedEvent*>();
        IADLXGPU2Ptr gpu;
        evt->GetGPU(&gpu);
        return gpu;
    }, py::return_value_policy::move)
        .def("IsGPUAppsListChanged", [](py::object self) {
        IADLXGPUConnectChangedEventPtr evt = self.cast<IADLXGPUConnectChangedEvent*>();
        return evt->IsGPUAppsListChanged();
    })
        .def("IsGPUPowerChanged", [](py::object self) {
        IADLXGPUConnectChangedEventPtr evt = self.cast<IADLXGPUConnectChangedEvent*>();
        return evt->IsGPUPowerChanged();
    })
        .def("IsGPUPowerChangeError", [](py::object self) {
        IADLXGPUConnectChangedEventPtr evt = self.cast<IADLXGPUConnectChangedEvent*>();
        ADLX_RESULT powerChangeError = ADLX_OK;
        adlx_bool hasError = evt->IsGPUPowerChangeError(&powerChangeError);
        return std::make_tuple(hasError, powerChangeError);
    });

    // Callback for GPUConnectChangedListener
    py::class_<PyGPUConnectChangedListenerCallback>(m, "PyGPUConnectChangedListenerCallback")
        .def(py::init<>())
        .def_readwrite("call", &PyGPUConnectChangedListenerCallback::m_call);
}
