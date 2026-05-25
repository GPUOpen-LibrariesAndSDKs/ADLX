//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

#include "bind_common.h"

void bind_tuning(py::module_& m)
{
    // tuningService
    py::class_<IADLXGPUTuningServices, IADLXInterface, PyGPUTuningServices, IADLXInterfacePtr_T<IADLXGPUTuningServices>>(m, "IADLXGPUTuningServices")
        //.def(py::init<>())
        .def("GetAutoTuning", [](py::object self, IADLXGPUPtr oneGPU) {
        IADLXGPUTuningServicesPtr tunService = self.cast<IADLXGPUTuningServices*>();
        IADLXInterfacePtr autoTuningIfc;
        tunService->GetAutoTuning(oneGPU, &autoTuningIfc);
        IADLXGPUAutoTuningPtr autoTuning(autoTuningIfc);
        return autoTuning;
        }, py::return_value_policy::move)
        .def("GetGPUTuningChangedHandling", [](py::object self) {
        IADLXGPUTuningServicesPtr tunService = self.cast<IADLXGPUTuningServices*>();
        IADLXGPUTuningChangedHandlingPtr ppGPUTuningChangedHandling;
        tunService->GetGPUTuningChangedHandling(&ppGPUTuningChangedHandling);
        return ppGPUTuningChangedHandling;
    }, py::return_value_policy::move)
        .def("GetManualFanTuning", [](py::object self, IADLXGPUPtr oneGPU) {
        IADLXGPUTuningServicesPtr tunService = self.cast<IADLXGPUTuningServices*>();
        IADLXInterfacePtr ppManualFanTuning;
        tunService->GetManualFanTuning(oneGPU, &ppManualFanTuning);
        IADLXManualFanTuningPtr manualTuning(ppManualFanTuning);
        return manualTuning;
    }, py::return_value_policy::move)
        .def("GetManualGFXTuning1", [](py::object self, IADLXGPUPtr oneGPU) {
        IADLXGPUTuningServicesPtr tunService = self.cast<IADLXGPUTuningServices*>();
        IADLXInterfacePtr ppManualGFXTuning;
        tunService->GetManualGFXTuning(oneGPU, &ppManualGFXTuning);
        // Pre-Navi ASIC
        IADLXManualGraphicsTuning1Ptr manualGFXTuning1(ppManualGFXTuning);
        return manualGFXTuning1;
    }, py::return_value_policy::move)
        .def("GetManualGFXTuning2", [](py::object self, IADLXGPUPtr oneGPU) {
        IADLXGPUTuningServicesPtr tunService = self.cast<IADLXGPUTuningServices*>();
        IADLXInterfacePtr ppManualGFXTuning;
        tunService->GetManualGFXTuning(oneGPU, &ppManualGFXTuning);
        // Post-Navi ASIC
        IADLXManualGraphicsTuning2Ptr manualGFXTuning2(ppManualGFXTuning);
        return manualGFXTuning2;
    }, py::return_value_policy::move)
        .def("GetManualPowerTuning", [](py::object self, IADLXGPUPtr oneGPU) {
        IADLXGPUTuningServicesPtr tunService = self.cast<IADLXGPUTuningServices*>();
        IADLXInterfacePtr ppManualPowerTuning;
        tunService->GetManualPowerTuning(oneGPU, &ppManualPowerTuning);
        IADLXManualPowerTuningPtr manualPowerTuning(ppManualPowerTuning);
        return manualPowerTuning;
    }, py::return_value_policy::move)
        .def("GetManualVRAMTuning1", [](py::object self, IADLXGPUPtr oneGPU) {
        IADLXGPUTuningServicesPtr tunService = self.cast<IADLXGPUTuningServices*>();
        IADLXInterfacePtr ppManualVRAMTuning;
        tunService->GetManualVRAMTuning(oneGPU, &ppManualVRAMTuning);
        // pre-Navi ASIC
        IADLXManualVRAMTuning1Ptr manualVRAMTuning1(ppManualVRAMTuning);
        return manualVRAMTuning1;
    }, py::return_value_policy::move)
        .def("GetManualVRAMTuning2", [](py::object self, IADLXGPUPtr oneGPU) {
        IADLXGPUTuningServicesPtr tunService = self.cast<IADLXGPUTuningServices*>();
        IADLXInterfacePtr ppManualVRAMTuning;
        tunService->GetManualVRAMTuning(oneGPU, &ppManualVRAMTuning);
        // post-Navi ASIC
        IADLXManualVRAMTuning2Ptr manualVRAMTuning2(ppManualVRAMTuning);
        return manualVRAMTuning2;
    }, py::return_value_policy::move)
        .def("GetPresetTuning", [](py::object self, IADLXGPUPtr oneGPU) {
        IADLXGPUTuningServicesPtr tunService = self.cast<IADLXGPUTuningServices*>();
        IADLXInterfacePtr ppPresetTuning;
        tunService->GetPresetTuning(oneGPU, &ppPresetTuning);
        IADLXGPUPresetTuningPtr presetTuning(ppPresetTuning);
        return presetTuning;
    }, py::return_value_policy::move)
        .def("IsAtFactory", [](py::object self, IADLXGPUPtr oneGPU) -> std::variant<adlx_bool, py::none> {
        IADLXGPUTuningServicesPtr tunService = self.cast<IADLXGPUTuningServices*>();
        adlx_bool isAtFactory;
        ADLX_RESULT ret = tunService->IsAtFactory(oneGPU, &isAtFactory);
        if (ADLX_SUCCEEDED(ret))
            return isAtFactory;
        return py::none();
    })
        .def("IsSupportedAutoTuning", [](py::object self, IADLXGPUPtr oneGPU) {
        IADLXGPUTuningServicesPtr tunService = self.cast<IADLXGPUTuningServices*>();
        adlx_bool isSupportedAutoTuning = false;
        tunService->IsSupportedAutoTuning(oneGPU, &isSupportedAutoTuning);
        return isSupportedAutoTuning;
    })
        .def("IsSupportedManualFanTuning", [](py::object self, IADLXGPUPtr oneGPU) {
        IADLXGPUTuningServicesPtr tunService = self.cast<IADLXGPUTuningServices*>();
        adlx_bool isSupportedManualFanTuning = false;
        tunService->IsSupportedManualFanTuning(oneGPU, &isSupportedManualFanTuning);
        return isSupportedManualFanTuning;
    })
        .def("IsSupportedManualGFXTuning", [](py::object self, IADLXGPUPtr oneGPU) {
        IADLXGPUTuningServicesPtr tunService = self.cast<IADLXGPUTuningServices*>();
        adlx_bool isSupportedManualGFXTuning = false;
        tunService->IsSupportedManualGFXTuning(oneGPU, &isSupportedManualGFXTuning);
        return isSupportedManualGFXTuning;
    })
        .def("IsSupportedManualPowerTuning", [](py::object self, IADLXGPUPtr oneGPU) {
        IADLXGPUTuningServicesPtr tunService = self.cast<IADLXGPUTuningServices*>();
        adlx_bool isSupportedManualPowerTuning = false;
        tunService->IsSupportedManualPowerTuning(oneGPU, &isSupportedManualPowerTuning);
        return isSupportedManualPowerTuning;
    })
        .def("IsSupportedManualVRAMTuning", [](py::object self, IADLXGPUPtr oneGPU) {
        IADLXGPUTuningServicesPtr tunService = self.cast<IADLXGPUTuningServices*>();
        adlx_bool isSupportedManualVRAMTuning = false;
        tunService->IsSupportedManualVRAMTuning(oneGPU, &isSupportedManualVRAMTuning);
        return isSupportedManualVRAMTuning;
    })
        .def("IsSupportedPresetTuning", [](py::object self, IADLXGPUPtr oneGPU) {
        IADLXGPUTuningServicesPtr tunService = self.cast<IADLXGPUTuningServices*>();
        adlx_bool isSupportedPresetTuning = false;
        tunService->IsSupportedPresetTuning(oneGPU, &isSupportedPresetTuning);
        return isSupportedPresetTuning;
    })
        .def("ResetToFactory", [](py::object self, IADLXGPUPtr oneGPU) {
        IADLXGPUTuningServicesPtr tunService = self.cast<IADLXGPUTuningServices*>();
        ADLX_RESULT ret_reset = tunService->ResetToFactory(oneGPU);
        return ret_reset;
    })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXGPUTuningServicesPtr tunService = self.cast<IADLXGPUTuningServices*>();
        IADLXGPUTuningServicesPtr ppInterface = nullptr;
        tunService->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
    }, py::return_value_policy::move)
        // QI-fold IADLXGPUTuningServices1::GetSmartAccessMemory
        .def("GetSmartAccessMemory", [](py::object self, IADLXGPUPtr oneGPU) {
        IADLXGPUTuningServicesPtr tunService = self.cast<IADLXGPUTuningServices*>();
        IADLXGPUTuningServices1Ptr tunService1(tunService);
        if (tunService1)
        {
            IADLXSmartAccessMemoryPtr sam;
            tunService1->GetSmartAccessMemory(oneGPU, &sam);
            return sam;
        }
        return IADLXSmartAccessMemoryPtr();
    }, py::return_value_policy::move);


    // Callback for GPUAutoTuningCompleteListener
    py::class_<PyGPUAutoTuningCompleteListenerCallback>(m, "PyGPUAutoTuningCompleteListenerCallback")
        .def(py::init<>())
        .def_readwrite("call", &PyGPUAutoTuningCompleteListenerCallback::m_call);


    // Callback for GPUTuningChangedListener
    py::class_<PyGPUTuningChangedListenerCallback>(m, "PyGPUTuningChangedListenerCallback")
        .def(py::init<>())
        .def_readwrite("call", &PyGPUTuningChangedListenerCallback::m_call);

        // IADLXGPUAutoTuning
        py::class_<IADLXGPUAutoTuning, IADLXInterface, PyGPUAutoTuning, IADLXInterfacePtr_T<IADLXGPUAutoTuning>>(m, "IADLXGPUAutoTuning")
        //.def(py::init<>())
        .def("IsCurrentOverclockGPU", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXGPUAutoTuning* gpuAutoTuning = self.cast<IADLXGPUAutoTuning*>();
        adlx_bool isOverclockGPU;
        ADLX_RESULT result = gpuAutoTuning->IsCurrentOverclockGPU(&isOverclockGPU);
        if (ADLX_SUCCEEDED(result)) {
            return isOverclockGPU;
        }
        return py::none();
        })
        .def("IsCurrentOverclockVRAM", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXGPUAutoTuning* gpuAutoTuning = self.cast<IADLXGPUAutoTuning*>();
        adlx_bool isOverclockVRAM;
        ADLX_RESULT result = gpuAutoTuning->IsCurrentOverclockVRAM(&isOverclockVRAM);
        if (ADLX_SUCCEEDED(result)) {
            return isOverclockVRAM;
        }
        return py::none();
        })
        .def("IsCurrentUndervoltGPU", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXGPUAutoTuning* gpuAutoTuning = self.cast<IADLXGPUAutoTuning*>();
        adlx_bool isUndervoltGPU;
        ADLX_RESULT result = gpuAutoTuning->IsCurrentUndervoltGPU(&isUndervoltGPU);
        if (ADLX_SUCCEEDED(result)) {
            return isUndervoltGPU;
        }
        return py::none();
        })
        .def("IsSupportedOverclockGPU", [](py::object self) {
        IADLXGPUAutoTuning* gpuAutoTuning = self.cast<IADLXGPUAutoTuning*>();
        adlx_bool supported = false;
        gpuAutoTuning->IsSupportedOverclockGPU(&supported);
        return supported;
        })
        .def("IsSupportedOverclockVRAM", [](py::object self) {
        IADLXGPUAutoTuning* gpuAutoTuning = self.cast<IADLXGPUAutoTuning*>();
        adlx_bool supported = false;
        gpuAutoTuning->IsSupportedOverclockVRAM(&supported);
        return supported;
        })
        .def("IsSupportedUndervoltGPU", [](py::object self) {
        IADLXGPUAutoTuning* gpuAutoTuning = self.cast<IADLXGPUAutoTuning*>();
        bool modeIsSupported = false;
        gpuAutoTuning->IsSupportedUndervoltGPU(&modeIsSupported);
        return modeIsSupported;
        })
        .def("StartOverclockGPU", [](py::object self, PyGPUAutoTuningCompleteListenerCallback* pCompleteListener) {
        IADLXGPUAutoTuning* gpuAutoTuning = self.cast<IADLXGPUAutoTuning*>();
        ADLX_RESULT res_start_overclock_gpu = gpuAutoTuning->StartOverclockGPU(pCompleteListener);
        return res_start_overclock_gpu;
        })
        .def("StartOverclockVRAM", [](py::object self, PyGPUAutoTuningCompleteListenerCallback* pCompleteListener) {
        IADLXGPUAutoTuning* gpuAutoTuning = self.cast<IADLXGPUAutoTuning*>();
        ADLX_RESULT res_start_overclock_gpu = gpuAutoTuning->StartOverclockVRAM(pCompleteListener);
        return res_start_overclock_gpu;
        })
        .def("StartUndervoltGPU", [](py::object self, PyGPUAutoTuningCompleteListenerCallback* pCompleteListener) {
        IADLXGPUAutoTuning* gpuAutoTuning = self.cast<IADLXGPUAutoTuning*>();
        ADLX_RESULT res_start_overclock_gpu = gpuAutoTuning->StartUndervoltGPU(pCompleteListener);
        return res_start_overclock_gpu;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXGPUAutoTuning* gpuAutoTuning = self.cast<IADLXGPUAutoTuning*>();
        IADLXGPUAutoTuningPtr ppInterface = nullptr;
        gpuAutoTuning->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);

    // IADLXGPUAutoTuningCompleteEvent
        py::class_<IADLXGPUAutoTuningCompleteEvent, IADLXInterface, PyGPUAutoTuningCompleteEvent, IADLXInterfacePtr_T<IADLXGPUAutoTuningCompleteEvent>>(m, "IADLXGPUAutoTuningCompleteEvent")
        //.def(py::init<>())
        .def("IsOverclockGPUCompleted", [](py::object self) {
        IADLXGPUAutoTuningCompleteEventPtr auto_tuning_event = self.cast<IADLXGPUAutoTuningCompleteEvent*>();
        adlx_bool overclock_completed = auto_tuning_event->IsOverclockGPUCompleted();
        return overclock_completed;
        })
        .def("IsOverclockVRAMCompleted", [](py::object self) {
        IADLXGPUAutoTuningCompleteEventPtr auto_tuning_event = self.cast<IADLXGPUAutoTuningCompleteEvent*>();
        adlx_bool overclock_completed = auto_tuning_event->IsOverclockVRAMCompleted();
        return overclock_completed;
        })
        .def("IsUndervoltGPUCompleted", [](py::object self) {
        IADLXGPUAutoTuningCompleteEventPtr auto_tuning_event = self.cast<IADLXGPUAutoTuningCompleteEvent*>();
        adlx_bool undervolt_completed = auto_tuning_event->IsUndervoltGPUCompleted();
        return undervolt_completed;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXGPUAutoTuningCompleteEventPtr auto_tuning_event = self.cast<IADLXGPUAutoTuningCompleteEvent*>();
        IADLXGPUAutoTuningCompleteEventPtr ppInterface = nullptr;
        auto_tuning_event->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


        // IADLXGPUPresetTuning
        py::class_<IADLXGPUPresetTuning, IADLXInterface, PyGPUPresetTuning, IADLXInterfacePtr_T<IADLXGPUPresetTuning>>(m, "IADLXGPUPresetTuning")
        //.def(py::init<>())
        .def("IsCurrentBalanced", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXGPUPresetTuningPtr preset_tuning = self.cast<IADLXGPUPresetTuning*>();
        adlx_bool isBalanced;
        ADLX_RESULT result = preset_tuning->IsCurrentBalanced(&isBalanced);
        if (ADLX_SUCCEEDED(result)) {
            return isBalanced;
        }
        return py::none();
        })
        .def("IsCurrentPowerSaver", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXGPUPresetTuningPtr preset_tuning = self.cast<IADLXGPUPresetTuning*>();
        adlx_bool isPowerSaver;
        ADLX_RESULT result = preset_tuning->IsCurrentPowerSaver(&isPowerSaver);
        if (ADLX_SUCCEEDED(result)) {
            return isPowerSaver;
        }
        return py::none();
        })
        .def("IsCurrentQuiet", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXGPUPresetTuningPtr preset_tuning = self.cast<IADLXGPUPresetTuning*>();
        adlx_bool isQuiet;
        ADLX_RESULT result = preset_tuning->IsCurrentQuiet(&isQuiet);
        if (ADLX_SUCCEEDED(result)) {
            return isQuiet;
        }
        return py::none();
        })
        .def("IsCurrentRage", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXGPUPresetTuningPtr preset_tuning = self.cast<IADLXGPUPresetTuning*>();
        adlx_bool isRage;
        ADLX_RESULT result = preset_tuning->IsCurrentRage(&isRage);
        if (ADLX_SUCCEEDED(result)) {
            return isRage;
        }
        return py::none();
        })
        .def("IsCurrentTurbo", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXGPUPresetTuningPtr preset_tuning = self.cast<IADLXGPUPresetTuning*>();
        adlx_bool isTurbo;
        ADLX_RESULT result = preset_tuning->IsCurrentTurbo(&isTurbo);
        if (ADLX_SUCCEEDED(result)) {
            return isTurbo;
        }
        return py::none();
        })
        .def("IsSupportedBalanced", [](py::object self) {
        IADLXGPUPresetTuningPtr preset_tuning = self.cast<IADLXGPUPresetTuning*>();
        adlx_bool supported = false;
        preset_tuning->IsSupportedBalanced(&supported);
        return supported;
        })
        .def("IsSupportedPowerSaver", [](py::object self) {
        IADLXGPUPresetTuningPtr preset_tuning = self.cast<IADLXGPUPresetTuning*>();
        adlx_bool supported = false;
        preset_tuning->IsSupportedPowerSaver(&supported);
        return supported;
        })
        .def("IsSupportedQuiet", [](py::object self) {
        IADLXGPUPresetTuningPtr preset_tuning = self.cast<IADLXGPUPresetTuning*>();
        adlx_bool supported = false;
        preset_tuning->IsSupportedQuiet(&supported);
        return supported;
        })
        .def("IsSupportedRage", [](py::object self) {
        IADLXGPUPresetTuningPtr preset_tuning = self.cast<IADLXGPUPresetTuning*>();
        adlx_bool supported = false;
        preset_tuning->IsSupportedRage(&supported);
        return supported;
        })
        .def("IsSupportedTurbo", [](py::object self) {
        IADLXGPUPresetTuningPtr preset_tuning = self.cast<IADLXGPUPresetTuning*>();
        adlx_bool supported = false;
        preset_tuning->IsSupportedTurbo(&supported);
        return supported;
        })
        .def("SetBalanced", [](py::object self) {
        IADLXGPUPresetTuningPtr preset_tuning = self.cast<IADLXGPUPresetTuning*>();
        ADLX_RESULT ret_set = preset_tuning->SetBalanced();
        return ret_set;
        })
        .def("SetPowerSaver", [](py::object self) {
        IADLXGPUPresetTuningPtr preset_tuning = self.cast<IADLXGPUPresetTuning*>();
        ADLX_RESULT ret_set = preset_tuning->SetPowerSaver();
        return ret_set;
        })
        .def("SetQuiet", [](py::object self) {
        IADLXGPUPresetTuningPtr preset_tuning = self.cast<IADLXGPUPresetTuning*>();
        ADLX_RESULT ret_set = preset_tuning->SetQuiet();
        return ret_set;
        })
        .def("SetRage", [](py::object self) {
        IADLXGPUPresetTuningPtr preset_tuning = self.cast<IADLXGPUPresetTuning*>();
        ADLX_RESULT ret_set = preset_tuning->SetRage();
        return ret_set;
        })
        .def("SetTurbo", [](py::object self) {
        IADLXGPUPresetTuningPtr preset_tuning = self.cast<IADLXGPUPresetTuning*>();
        ADLX_RESULT ret_set = preset_tuning->SetTurbo();
        return ret_set;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXGPUPresetTuningPtr preset_tuning = self.cast<IADLXGPUPresetTuning*>();
        IADLXGPUPresetTuningPtr ppInterface = nullptr;
        preset_tuning->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


        // IADLXGPUTuningChangedHandling
        py::class_<IADLXGPUTuningChangedHandling, IADLXInterface, PyGPUTuningChangedHandling, IADLXInterfacePtr_T<IADLXGPUTuningChangedHandling>>(m, "IADLXGPUTuningChangedHandling")
        .def("AddGPUTuningEventListener", [](py::object self, PyGPUTuningChangedListenerCallback* call) {
        IADLXGPUTuningChangedHandlingPtr gpusTuningChangedHandling = self.cast< IADLXGPUTuningChangedHandling*>();
        ADLX_RESULT ret_add_tuning_event = gpusTuningChangedHandling->AddGPUTuningEventListener(call);
        return ret_add_tuning_event;
        })
        .def("RemoveGPUTuningEventListener", [](py::object self, PyGPUTuningChangedListenerCallback* call) {
        IADLXGPUTuningChangedHandlingPtr gpusTuningChangedHandling = self.cast< IADLXGPUTuningChangedHandling*>();
        ADLX_RESULT ret_remove_tuning_event = gpusTuningChangedHandling->RemoveGPUTuningEventListener(call);
        return ret_remove_tuning_event;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXGPUTuningChangedHandlingPtr gpusTuningChangedHandling = self.cast< IADLXGPUTuningChangedHandling*>();
        IADLXGPUTuningChangedHandlingPtr ppInterface = nullptr;
        gpusTuningChangedHandling->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


        // IADLXGPUTuningChangedEvent
        py::class_<IADLXGPUTuningChangedEvent, IADLXChangedEvent, PyGPUTuningChangedEvent, IADLXInterfacePtr_T<IADLXGPUTuningChangedEvent>>(m, "IADLXGPUTuningChangedEvent")
        //.def(py::init<>())
        .def("GetGPU", [](py::object self) {
        IADLXGPUTuningChangedEventPtr gpu_tuning_event = self.cast<IADLXGPUTuningChangedEvent*>();
        IADLXGPUPtr gpu;
        gpu_tuning_event->GetGPU(&gpu);
        return gpu;
        }, py::return_value_policy::move)
        .def("IsAutomaticTuningChanged", [](py::object self) {
        IADLXGPUTuningChangedEventPtr gpu_tuning_event = self.cast<IADLXGPUTuningChangedEvent*>();
        adlx_bool is_bool = gpu_tuning_event->IsAutomaticTuningChanged();
        return is_bool;
        })
        .def("IsManualFanTuningChanged", [](py::object self) {
        IADLXGPUTuningChangedEventPtr gpu_tuning_event = self.cast<IADLXGPUTuningChangedEvent*>();
        adlx_bool is_bool = gpu_tuning_event->IsManualFanTuningChanged();
        return is_bool;
        })
        .def("IsManualGPUCLKTuningChanged", [](py::object self) {
        IADLXGPUTuningChangedEventPtr gpu_tuning_event = self.cast<IADLXGPUTuningChangedEvent*>();
        adlx_bool is_bool = gpu_tuning_event->IsManualGPUCLKTuningChanged();
        return is_bool;
        })
        .def("IsManualPowerTuningChanged", [](py::object self) {
        IADLXGPUTuningChangedEventPtr gpu_tuning_event = self.cast<IADLXGPUTuningChangedEvent*>();
        adlx_bool is_bool = gpu_tuning_event->IsManualPowerTuningChanged();
        return is_bool;
        })
        .def("IsManualVRAMTuningChanged", [](py::object self) {
        IADLXGPUTuningChangedEventPtr gpu_tuning_event = self.cast<IADLXGPUTuningChangedEvent*>();
        adlx_bool is_bool = gpu_tuning_event->IsManualVRAMTuningChanged();
        return is_bool;
        })
        .def("IsPresetTuningChanged", [](py::object self) {
        IADLXGPUTuningChangedEventPtr gpu_tuning_event = self.cast<IADLXGPUTuningChangedEvent*>();
        adlx_bool is_bool = gpu_tuning_event->IsPresetTuningChanged();
        return is_bool;
        })
        // IADLXGPUTuningChangedEvent1
        .def("IsSmartAccessMemoryChanged", [](py::object self) {
        IADLXGPUTuningChangedEventPtr gpu_tuning_event = self.cast<IADLXGPUTuningChangedEvent*>();
        IADLXGPUTuningChangedEvent1Ptr gpu_tuning_event1(gpu_tuning_event);
        if (gpu_tuning_event1)
        {
            return gpu_tuning_event1->IsSmartAccessMemoryChanged();
        }
        return adlx_bool(false);
        })
        .def("GetSmartAccessMemoryStatus", [](py::object self) {
        IADLXGPUTuningChangedEventPtr gpu_tuning_event = self.cast<IADLXGPUTuningChangedEvent*>();
        IADLXGPUTuningChangedEvent1Ptr gpu_tuning_event1(gpu_tuning_event);
        adlx_bool enabled = false;
        adlx_bool completed = false;
        if (gpu_tuning_event1)
        {
            gpu_tuning_event1->GetSmartAccessMemoryStatus(&enabled, &completed);
        }
        return py::make_tuple(enabled, completed);
        });


        // IADLXManualFanTuning
        py::class_<IADLXManualFanTuning, IADLXInterface, PyManualFanTuning, IADLXInterfacePtr_T<IADLXManualFanTuning>>(m, "IADLXManualFanTuning")
        .def("GetEmptyFanTuningStates", [](py::object self) {
        IADLXManualFanTuningPtr manual_tuning = self.cast<IADLXManualFanTuning*>();
        IADLXManualFanTuningStateListPtr states;
        manual_tuning->GetEmptyFanTuningStates(&states);
        std::vector<IADLXManualFanTuningStatePtr> list;
        if (states)
        {
            for (adlx_uint crt = states->Begin(); crt != states->End(); ++crt) {
                IADLXManualFanTuningStatePtr oneState;
                states->At(crt, &oneState);
                list.emplace_back(std::move(oneState));
            }
        }
        return list;
        }, py::return_value_policy::move)
        .def("GetFanTuningRanges", [](py::object self) {
        IADLXManualFanTuningPtr manual_tuning = self.cast<IADLXManualFanTuning*>();
        ADLX_IntRange speedRange;
        ADLX_IntRange temperatureRange;
        manual_tuning->GetFanTuningRanges(&speedRange, &temperatureRange);
        
        pybind11::dict dict_speed_range;
        dict_speed_range["max_value"] = speedRange.maxValue;
        dict_speed_range["min_value"] = speedRange.minValue;
        dict_speed_range["step"] = speedRange.step;

        pybind11::dict dict_temperature_range;
        dict_temperature_range["max_value"] = temperatureRange.maxValue;
        dict_temperature_range["min_value"] = temperatureRange.minValue;
        dict_temperature_range["step"] = temperatureRange.step;

        pybind11::dict dict;
        dict["speed_range"] = dict_speed_range;
        dict["temperature_range"] = dict_temperature_range;
        
        return dict;
        })
        .def("GetFanTuningStates", [](py::object self) {
        IADLXManualFanTuningPtr manual_tuning = self.cast<IADLXManualFanTuning*>();
        IADLXManualFanTuningStateListPtr states;
        manual_tuning->GetFanTuningStates(&states);
        std::vector<IADLXManualFanTuningStatePtr> list;
        for (adlx_uint crt = states->Begin(); crt != states->End(); ++crt) {
            IADLXManualFanTuningStatePtr oneState;
            states->At(crt, &oneState);
            list.emplace_back(std::move(oneState));
        }
        return list;
        }, py::return_value_policy::move)	
        .def("GetMinAcousticLimit", [](py::object self) {
        IADLXManualFanTuningPtr manual_tuning = self.cast<IADLXManualFanTuning*>();
        adlx_int value;
        manual_tuning->GetMinAcousticLimit(&value);
        return value;
        })
        .def("GetMinAcousticLimitRange", [](py::object self) {
        IADLXManualFanTuningPtr manual_tuning = self.cast<IADLXManualFanTuning*>();
        ADLX_IntRange tuningRange;
        manual_tuning->GetMinAcousticLimitRange(&tuningRange);
        pybind11::dict dict;
        dict["max_value"] = tuningRange.maxValue;
        dict["min_value"] = tuningRange.minValue;
        dict["step"] = tuningRange.step;
        return dict;
        })
        .def("GetMinFanSpeed", [](py::object self) {
        IADLXManualFanTuningPtr manual_tuning = self.cast<IADLXManualFanTuning*>();
        adlx_int value;
        manual_tuning->GetMinFanSpeed(&value);
        return value;
        })
        .def("GetMinFanSpeedRange", [](py::object self) {
        IADLXManualFanTuningPtr manual_tuning = self.cast<IADLXManualFanTuning*>();
        ADLX_IntRange tuningRange;
        manual_tuning->GetMinFanSpeedRange(&tuningRange);
        pybind11::dict dict;
        dict["max_value"] = tuningRange.maxValue;
        dict["min_value"] = tuningRange.minValue;
        dict["step"] = tuningRange.step;
        return dict;
        })
        .def("GetTargetFanSpeed", [](py::object self) {
        IADLXManualFanTuningPtr manual_tuning = self.cast<IADLXManualFanTuning*>();
        adlx_int value;
        manual_tuning->GetTargetFanSpeed(&value);
        return value;
        })
        .def("GetTargetFanSpeedRange", [](py::object self) {
        IADLXManualFanTuningPtr manual_tuning = self.cast<IADLXManualFanTuning*>();
        ADLX_IntRange tuningRange;
        manual_tuning->GetTargetFanSpeedRange(&tuningRange);
        pybind11::dict dict;
        dict["max_value"] = tuningRange.maxValue;
        dict["min_value"] = tuningRange.minValue;
        dict["step"] = tuningRange.step;
        return dict;
        })
        .def("GetZeroRPMState", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXManualFanTuningPtr manual_tuning = self.cast<IADLXManualFanTuning*>();
        adlx_bool isSet;
        ADLX_RESULT result = manual_tuning->GetZeroRPMState(&isSet);
        if (ADLX_SUCCEEDED(result)) {
            return isSet;
        }
        return py::none();
        })
        .def("IsSupportedMinAcousticLimit", [](py::object self) {
        IADLXManualFanTuningPtr manual_tuning = self.cast<IADLXManualFanTuning*>();
        adlx_bool supported = false;
        manual_tuning->IsSupportedMinAcousticLimit(&supported);
        return supported;
        })
        .def("IsSupportedMinFanSpeed", [](py::object self) {
        IADLXManualFanTuningPtr manual_tuning = self.cast<IADLXManualFanTuning*>();
        adlx_bool supported = false;
        manual_tuning->IsSupportedMinFanSpeed(&supported);
        return supported;
        })
        .def("IsSupportedTargetFanSpeed", [](py::object self) {
        IADLXManualFanTuningPtr manual_tuning = self.cast<IADLXManualFanTuning*>();
        adlx_bool supported = false;
        manual_tuning->IsSupportedTargetFanSpeed(&supported);
        return supported;
        })
        .def("IsSupportedZeroRPM", [](py::object self) {
        IADLXManualFanTuningPtr manual_tuning = self.cast<IADLXManualFanTuning*>();
        adlx_bool supported = false;
        manual_tuning->IsSupportedZeroRPM(&supported);
        return supported;
        })
        .def("IsValidFanTuningStates", [](py::object self, std::vector<IADLXManualFanTuningStatePtr> list) {
        IADLXManualFanTuningPtr manual_tuning = self.cast<IADLXManualFanTuning*>();
        IADLXManualFanTuningStateListPtr pStates;
        manual_tuning->GetEmptyFanTuningStates(&pStates);
        pStates->Clear();
        size_t vecSize = list.size();
        for (unsigned int i = 0; i < vecSize; i++)
        {
            pStates->Add_Back(list[i]);
        }
        adlx_int errorIndex = -1;
        manual_tuning->IsValidFanTuningStates(pStates, &errorIndex);
        return errorIndex;
        })		
        .def("SetFanTuningStates", [](py::object self, std::vector<IADLXManualFanTuningStatePtr> list) {
        IADLXManualFanTuningPtr manual_tuning = self.cast<IADLXManualFanTuning*>();
        IADLXManualFanTuningStateListPtr pStates;
        manual_tuning->GetEmptyFanTuningStates(&pStates);
        pStates->Clear();
        size_t vecSize = list.size();
        for (unsigned int i = 0; i < vecSize; i++)
        {
            pStates->Add_Back(list[i]);
        }
        ADLX_RESULT ret_set = manual_tuning->SetFanTuningStates(pStates);
        return ret_set;
        })
        .def("SetMinAcousticLimit", [](py::object self, adlx_int value) {
        IADLXManualFanTuningPtr manual_tuning = self.cast<IADLXManualFanTuning*>();
        ADLX_RESULT ret_set = manual_tuning->SetMinAcousticLimit(value);
        return ret_set;
        })
        .def("SetMinFanSpeed", [](py::object self, adlx_int value) {
        IADLXManualFanTuningPtr manual_tuning = self.cast<IADLXManualFanTuning*>();
        ADLX_RESULT ret_set = manual_tuning->SetMinFanSpeed(value);
        return ret_set;
        })
        .def("SetTargetFanSpeed", [](py::object self, adlx_int value) {
        IADLXManualFanTuningPtr manual_tuning = self.cast<IADLXManualFanTuning*>();
        ADLX_RESULT ret_set = manual_tuning->SetTargetFanSpeed(value);
        return ret_set;
        })
        .def("SetZeroRPMState", [](py::object self, adlx_int value) {
        IADLXManualFanTuningPtr manual_tuning = self.cast<IADLXManualFanTuning*>();	
        ADLX_RESULT ret_set = manual_tuning->SetZeroRPMState(value);
        return ret_set;
        })
        .def("GetDefaultFanTuningStates", [](py::object self) {
        IADLXManualFanTuningPtr manual_tuning = self.cast<IADLXManualFanTuning*>();
        std::vector<IADLXManualFanTuningStatePtr> list;
        IADLXManualFanTuning1Ptr manual_tuning1(manual_tuning);
        if (manual_tuning1)
        {
            IADLXManualFanTuningStateListPtr ppStates;
            manual_tuning1->GetDefaultFanTuningStates(&ppStates);
            for (adlx_uint crt = ppStates->Begin(); crt != ppStates->End(); ++crt) {
                IADLXManualFanTuningStatePtr oneState;
                ppStates->At(crt, &oneState);
                list.emplace_back(std::move(oneState));
            }
        }
        return list;
        }, py::return_value_policy::move)
        .def("GetMinAcousticLimitDefault", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXManualFanTuningPtr manual_tuning = self.cast<IADLXManualFanTuning*>();
        adlx_int defaultVal;
        IADLXManualFanTuning1Ptr manual_tuning1(manual_tuning);
        if (manual_tuning1)
        {
            ADLX_RESULT result = manual_tuning1->GetMinAcousticLimitDefault(&defaultVal);
            if (ADLX_SUCCEEDED(result)) {
                return defaultVal;
            }
        }
        return py::none();
        })
        .def("GetMinFanSpeedDefault", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXManualFanTuningPtr manual_tuning = self.cast<IADLXManualFanTuning*>();
        adlx_int defaultVal;
        IADLXManualFanTuning1Ptr manual_tuning1(manual_tuning);
        if (manual_tuning1)
        {
            ADLX_RESULT result = manual_tuning1->GetMinFanSpeedDefault(&defaultVal);
            if (ADLX_SUCCEEDED(result)) {
                return defaultVal;
            }
        }
        return py::none();
        })
        .def("GetTargetFanSpeedDefault", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXManualFanTuningPtr manual_tuning = self.cast<IADLXManualFanTuning*>();
        adlx_int defaultVal;
        IADLXManualFanTuning1Ptr manual_tuning1(manual_tuning);
        if (manual_tuning1)
        {
            ADLX_RESULT result = manual_tuning1->GetTargetFanSpeedDefault(&defaultVal);
            if (ADLX_SUCCEEDED(result)) {
                return defaultVal;
            }
        }
        return py::none();
        })
        .def("GetDefaultZeroRPMState", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXManualFanTuningPtr manual_tuning = self.cast<IADLXManualFanTuning*>();
        adlx_bool defaultVal;
        IADLXManualFanTuning1Ptr manual_tuning1(manual_tuning);
        if (manual_tuning1)
        {
            ADLX_RESULT result = manual_tuning1->GetDefaultZeroRPMState(&defaultVal);
            if (ADLX_SUCCEEDED(result)) {
                return defaultVal;
            }
        }
        return py::none();
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXManualFanTuningPtr manual_tuning = self.cast<IADLXManualFanTuning*>();
        IADLXManualFanTuningPtr ppInterface = nullptr;
        manual_tuning->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move)
        // Custom methods
        .def("GetFanTuningStatesRaw", [](py::object self) {
        IADLXManualFanTuningPtr manual_tuning = self.cast<IADLXManualFanTuning*>();
        IADLXManualFanTuningStateListPtr states;
        manual_tuning->GetFanTuningStates(&states);
        return states;
        }, py::return_value_policy::move)
        .def("GetDefaultFanTuningStatesRaw", [](py::object self) {
        IADLXManualFanTuningPtr manual_tuning = self.cast<IADLXManualFanTuning*>();
        IADLXManualFanTuningStateListPtr ppStates;
        IADLXManualFanTuning1Ptr manual_tuning1(manual_tuning);
        if (manual_tuning1)
        {
            manual_tuning1->GetDefaultFanTuningStates(&ppStates);
        }
        return ppStates;
        }, py::return_value_policy::move);


        // IADLXManualFanTuningStateList
        py::class_<IADLXManualFanTuningStateList, IADLXList, PyManualFanTuningStateList, IADLXInterfacePtr_T<IADLXManualFanTuningStateList>>(m, "IADLXManualFanTuningStateList")
        //.def(py::init<>())
        .def("Add_Back", [](py::object self, IADLXManualFanTuningState* pItem) {
        IADLXManualFanTuningStateListPtr manual_fan_tuning_state_list = self.cast<IADLXManualFanTuningStateList*>();
        ADLX_RESULT ret_add_back = manual_fan_tuning_state_list->Add_Back(pItem);
        return ret_add_back;
        })
        .def("At", [](py::object self, const adlx_uint location) {
        IADLXManualFanTuningStateListPtr manual_fan_tuning_state_list = self.cast<IADLXManualFanTuningStateList*>();
        IADLXManualFanTuningStatePtr ppItem;
        manual_fan_tuning_state_list->At(location, &ppItem);
        return ppItem;
        });


        // PyManualFanTuningState
        py::class_<IADLXManualFanTuningState, IADLXInterface, PyManualFanTuningState, IADLXInterfacePtr_T<IADLXManualFanTuningState>>(m, "IADLXManualFanTuningState")
        //.def(py::init<>())
        .def("GetFanSpeed", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXManualFanTuningStatePtr manual_fan_tuning_state = self.cast<IADLXManualFanTuningState*>();
        adlx_int value;
        ADLX_RESULT result = manual_fan_tuning_state->GetFanSpeed(&value);
        if (ADLX_SUCCEEDED(result)) {
            return value;
        }
        return py::none();
        })
        .def("GetTemperature", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXManualFanTuningStatePtr manual_fan_tuning_state = self.cast<IADLXManualFanTuningState*>();
        adlx_int value;
        ADLX_RESULT result = manual_fan_tuning_state->GetTemperature(&value);
        if (ADLX_SUCCEEDED(result)) {
            return value;
        }
        return py::none();
        })
        .def("SetFanSpeed", [](py::object self, adlx_int value) {
        IADLXManualFanTuningStatePtr manual_fan_tuning_state = self.cast<IADLXManualFanTuningState*>();
        ADLX_RESULT ret_api = manual_fan_tuning_state->SetFanSpeed(value);
        return ret_api;
        })
        .def("SetTemperature", [](py::object self, adlx_int value) {
        IADLXManualFanTuningStatePtr manual_fan_tuning_state = self.cast<IADLXManualFanTuningState*>();
        ADLX_RESULT ret_api = manual_fan_tuning_state->SetTemperature(value);
        return ret_api;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXManualFanTuningStatePtr manual_fan_tuning_state = self.cast<IADLXManualFanTuningState*>();
        IADLXManualFanTuningStatePtr ppInterface = nullptr;
        manual_fan_tuning_state->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


        // IADLXManualTuningStateList
        py::class_<IADLXManualTuningStateList, IADLXList, PyManualTuningStateList, IADLXInterfacePtr_T<IADLXManualTuningStateList>>(m, "IADLXManualTuningStateList")
        //.def(py::init<>())
        .def("Add_Back", [](py::object self, IADLXManualTuningState* pItem) {
        IADLXManualTuningStateListPtr manual_fan_tuning_state_list = self.cast<IADLXManualTuningStateList*>();
        ADLX_RESULT ret_add_back = manual_fan_tuning_state_list->Add_Back(pItem);
        return ret_add_back;
        })
        .def("At", [](py::object self, const adlx_uint location) {
        IADLXManualTuningStateListPtr manual_fan_tuning_state_list = self.cast<IADLXManualTuningStateList*>();
        IADLXManualTuningStatePtr ppItem;
        manual_fan_tuning_state_list->At(location, &ppItem);
        return ppItem;
        });


        // IADLXManualTuningState
        py::class_<IADLXManualTuningState, IADLXInterface, PyManualTuningState, IADLXInterfacePtr_T<IADLXManualTuningState>>(m, "IADLXManualTuningState")
        //.def(py::init<>())
        .def("GetFrequency", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXManualTuningStatePtr manual_tuning_state = self.cast<IADLXManualTuningState*>();
        adlx_int value;
        ADLX_RESULT result = manual_tuning_state->GetFrequency(&value);
        if (ADLX_SUCCEEDED(result)) {
            return value;
        }
        return py::none();
        })
        .def("GetVoltage", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXManualTuningStatePtr manual_tuning_state = self.cast<IADLXManualTuningState*>();
        adlx_int value;
        ADLX_RESULT result = manual_tuning_state->GetVoltage(&value);
        if (ADLX_SUCCEEDED(result)) {
            return value;
        }
        return py::none();
        })
        .def("SetFrequency", [](py::object self, adlx_int value) {
        IADLXManualTuningStatePtr manual_tuning_state = self.cast<IADLXManualTuningState*>();
        ADLX_RESULT ret_api = manual_tuning_state->SetFrequency(value);
        return ret_api;
        })
        .def("SetVoltage", [](py::object self, adlx_int value) {
        IADLXManualTuningStatePtr manual_tuning_state = self.cast<IADLXManualTuningState*>();
        ADLX_RESULT ret_api = manual_tuning_state->SetVoltage(value);
        return ret_api;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXManualTuningStatePtr manual_tuning_state = self.cast<IADLXManualTuningState*>();
        IADLXManualTuningStatePtr ppInterface = nullptr;
        manual_tuning_state->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


        // IADLXManualGraphicsTuning1
        py::class_<IADLXManualGraphicsTuning1, IADLXInterface, PyManualGraphicsTuning1, IADLXInterfacePtr_T<IADLXManualGraphicsTuning1>>(m, "IADLXManualGraphicsTuning1")
        //.def(py::init<>())
        .def("GetEmptyGPUTuningStates", [](py::object self) {
        IADLXManualGraphicsTuning1Ptr gfx_tuning1 = self.cast<IADLXManualGraphicsTuning1*>();
        IADLXManualTuningStateListPtr manual_tuning_state_list;
        gfx_tuning1->GetEmptyGPUTuningStates(&manual_tuning_state_list);
        std::vector<IADLXManualTuningStatePtr> list;
        for (adlx_uint crt = manual_tuning_state_list->Begin(); crt != manual_tuning_state_list->End(); ++crt) {
            IADLXManualTuningStatePtr oneState;
            manual_tuning_state_list->At(crt, &oneState);
            list.emplace_back(std::move(oneState));
        }
        return list;
        }, py::return_value_policy::move)
        .def("GetGPUTuningRanges", [](py::object self) {
        IADLXManualGraphicsTuning1Ptr gfx_tuning1 = self.cast<IADLXManualGraphicsTuning1*>();
        ADLX_IntRange frequencyRange;
        ADLX_IntRange voltageRange;
        gfx_tuning1->GetGPUTuningRanges(&frequencyRange, &voltageRange);

        pybind11::dict dict_frequency_range;
        dict_frequency_range["max_value"] = frequencyRange.maxValue;
        dict_frequency_range["min_value"] = frequencyRange.minValue;
        dict_frequency_range["step"] = frequencyRange.step;

        pybind11::dict dict_voltage_range;
        dict_voltage_range["max_value"] = voltageRange.maxValue;
        dict_voltage_range["min_value"] = voltageRange.minValue;
        dict_voltage_range["step"] = voltageRange.step;

        pybind11::dict dict;
        dict["frequency_range"] = frequencyRange;
        dict["voltage_range"] = voltageRange;

        return dict; 
        })
        .def("GetGPUTuningStates", [](py::object self) {
        IADLXManualGraphicsTuning1Ptr gfx_tuning1 = self.cast<IADLXManualGraphicsTuning1*>();
        IADLXManualTuningStateListPtr manual_tuning_state_list;
        gfx_tuning1->GetGPUTuningStates(&manual_tuning_state_list);
        std::vector<IADLXManualTuningStatePtr> list;
        for (adlx_uint crt = manual_tuning_state_list->Begin(); crt != manual_tuning_state_list->End(); ++crt) {
            IADLXManualTuningStatePtr oneState;
            manual_tuning_state_list->At(crt, &oneState);
            list.emplace_back(std::move(oneState));
        }
        return list;
        }, py::return_value_policy::move)
        .def("IsValidGPUTuningStates", [](py::object self, std::vector<IADLXManualTuningStatePtr> list) {
        IADLXManualGraphicsTuning1Ptr gfx_tuning1 = self.cast<IADLXManualGraphicsTuning1*>();
        IADLXManualTuningStateListPtr manual_tuning_state_list;
        gfx_tuning1->GetEmptyGPUTuningStates(&manual_tuning_state_list);
        manual_tuning_state_list->Clear();
        size_t vecSize = list.size();
        for (unsigned int i = 0; i < vecSize; i++)
        {
            manual_tuning_state_list->Add_Back(list[i]);
        }
        adlx_int errorIndex = -1;
        gfx_tuning1->IsValidGPUTuningStates(manual_tuning_state_list, &errorIndex);
        return errorIndex;
        })
        .def("SetGPUTuningStates", [](py::object self, std::vector<IADLXManualTuningStatePtr> list) {
        IADLXManualGraphicsTuning1Ptr gfx_tuning1 = self.cast<IADLXManualGraphicsTuning1*>();
        IADLXManualTuningStateListPtr manual_tuning_state_list;
        gfx_tuning1->GetEmptyGPUTuningStates(&manual_tuning_state_list);
        manual_tuning_state_list->Clear();
        size_t vecSize = list.size();
        for (unsigned int i = 0; i < vecSize; i++)
        {
            manual_tuning_state_list->Add_Back(list[i]);
        }
        ADLX_RESULT ret_api = gfx_tuning1->SetGPUTuningStates(manual_tuning_state_list);
        return ret_api;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXManualGraphicsTuning1Ptr gfx_tuning1 = self.cast<IADLXManualGraphicsTuning1*>();
        IADLXManualGraphicsTuning1Ptr ppInterface = nullptr;
        gfx_tuning1->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move)
        // Custom Methods
        .def("GetGPUTuningStatesRaw", [](py::object self) {
        IADLXManualGraphicsTuning1Ptr gfx_tuning1 = self.cast<IADLXManualGraphicsTuning1*>();
        IADLXManualTuningStateListPtr manual_tuning_state_list;
        gfx_tuning1->GetGPUTuningStates(&manual_tuning_state_list);
        return manual_tuning_state_list;
        }, py::return_value_policy::move);


        // IADLXManualGraphicsTuning2
        py::class_<IADLXManualGraphicsTuning2, IADLXInterface, PyManualGraphicsTuning2, IADLXInterfacePtr_T<IADLXManualGraphicsTuning2>>(m, "IADLXManualGraphicsTuning2")
        //.def(py::init<>())
        .def("GetGPUMaxFrequency", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXManualGraphicsTuning2Ptr gfx_tuning2 = self.cast<IADLXManualGraphicsTuning2*>();
        adlx_int maxFreq;
        ADLX_RESULT ret = gfx_tuning2->GetGPUMaxFrequency(&maxFreq);
        if (ADLX_SUCCEEDED(ret))
            return maxFreq;
        return py::none();
        })
        .def("GetGPUMaxFrequencyRange", [](py::object self) -> std::variant<pybind11::dict, py::none> {
        IADLXManualGraphicsTuning2Ptr gfx_tuning2 = self.cast<IADLXManualGraphicsTuning2*>();
        ADLX_IntRange tuningRange;
        ADLX_RESULT ret = gfx_tuning2->GetGPUMaxFrequencyRange(&tuningRange);
        if (ADLX_SUCCEEDED(ret))
        {
            pybind11::dict dict;
            dict["max_value"] = tuningRange.maxValue;
            dict["min_value"] = tuningRange.minValue;
            dict["step"] = tuningRange.step;
            return dict;
        }
        return py::none();
        })
        .def("GetGPUMinFrequency", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXManualGraphicsTuning2Ptr gfx_tuning2 = self.cast<IADLXManualGraphicsTuning2*>();
        adlx_int minFreq;
        ADLX_RESULT ret = gfx_tuning2->GetGPUMinFrequency(&minFreq);
        if (ADLX_SUCCEEDED(ret))
            return minFreq;
        return py::none();
        })
        .def("GetGPUMinFrequencyRange", [](py::object self) -> std::variant<pybind11::dict, py::none> {
        IADLXManualGraphicsTuning2Ptr gfx_tuning2 = self.cast<IADLXManualGraphicsTuning2*>();
        ADLX_IntRange tuningRange;
        ADLX_RESULT ret = gfx_tuning2->GetGPUMinFrequencyRange(&tuningRange);
        if (ADLX_SUCCEEDED(ret))
        {
            pybind11::dict dict;
            dict["max_value"] = tuningRange.maxValue;
            dict["min_value"] = tuningRange.minValue;
            dict["step"] = tuningRange.step;
            return dict;
        }
        return py::none();
        })
        .def("GetGPUVoltage", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXManualGraphicsTuning2Ptr gfx_tuning2 = self.cast<IADLXManualGraphicsTuning2*>();
        adlx_int volt;
        ADLX_RESULT ret = gfx_tuning2->GetGPUVoltage(&volt);
        if (ADLX_SUCCEEDED(ret))
            return volt;
        return py::none();
        })
        .def("GetGPUVoltageRange", [](py::object self) -> std::variant<pybind11::dict, py::none> {
        IADLXManualGraphicsTuning2Ptr gfx_tuning2 = self.cast<IADLXManualGraphicsTuning2*>();
        ADLX_IntRange tuningRange;
        ADLX_RESULT ret = gfx_tuning2->GetGPUVoltageRange(&tuningRange);
        if (ADLX_SUCCEEDED(ret))
        {
            pybind11::dict dict;
            dict["max_value"] = tuningRange.maxValue;
            dict["min_value"] = tuningRange.minValue;
            dict["step"] = tuningRange.step;
            return dict;
        }
        return py::none();
        })
        .def("SetGPUMaxFrequency", [](py::object self, adlx_int maxFreq) {
        IADLXManualGraphicsTuning2Ptr gfx_tuning2 = self.cast<IADLXManualGraphicsTuning2*>();
        ADLX_RESULT ret_api = gfx_tuning2->SetGPUMaxFrequency(maxFreq);
        return ret_api;
        })
        .def("SetGPUMinFrequency", [](py::object self, adlx_int minFreq) {
        IADLXManualGraphicsTuning2Ptr gfx_tuning2 = self.cast<IADLXManualGraphicsTuning2*>();
        ADLX_RESULT ret_api = gfx_tuning2->SetGPUMinFrequency(minFreq);
        return ret_api;
        })
        .def("SetGPUVoltage", [](py::object self, adlx_int volt) {
        IADLXManualGraphicsTuning2Ptr gfx_tuning2 = self.cast<IADLXManualGraphicsTuning2*>();
        ADLX_RESULT ret_api = gfx_tuning2->SetGPUVoltage(volt);
        return ret_api;
        })
        .def("GetGPUMinFrequencyDefault", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXManualGraphicsTuning2Ptr gfx_tuning2 = self.cast<IADLXManualGraphicsTuning2*>();
        adlx_int defaultVal = 0;
        IADLXManualGraphicsTuning2_1Ptr gfx_tuning2_1(gfx_tuning2);
        if (gfx_tuning2_1)
        {
            ADLX_RESULT ret = gfx_tuning2_1->GetGPUMinFrequencyDefault(&defaultVal);
            if (ADLX_SUCCEEDED(ret))
                return defaultVal;
        }
        return py::none();
        })
        .def("GetGPUMaxFrequencyDefault", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXManualGraphicsTuning2Ptr gfx_tuning2 = self.cast<IADLXManualGraphicsTuning2*>();
        adlx_int defaultVal = 0;
        IADLXManualGraphicsTuning2_1Ptr gfx_tuning2_1(gfx_tuning2);
        if (gfx_tuning2_1)
        {
            ADLX_RESULT ret = gfx_tuning2_1->GetGPUMaxFrequencyDefault(&defaultVal);
            if (ADLX_SUCCEEDED(ret))
                return defaultVal;
        }
        return py::none();
        })
        .def("GetGPUVoltageDefault", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXManualGraphicsTuning2Ptr gfx_tuning2 = self.cast<IADLXManualGraphicsTuning2*>();
        adlx_int defaultVal = 0;
        IADLXManualGraphicsTuning2_1Ptr gfx_tuning2_1(gfx_tuning2);
        if (gfx_tuning2_1)
        {
            ADLX_RESULT ret = gfx_tuning2_1->GetGPUVoltageDefault(&defaultVal);
            if (ADLX_SUCCEEDED(ret))
                return defaultVal;
        }
        return py::none();
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXManualGraphicsTuning2Ptr gfx_tuning2 = self.cast<IADLXManualGraphicsTuning2*>();
        IADLXManualGraphicsTuning2Ptr ppInterface = nullptr;
        gfx_tuning2->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


        // IADLXManualPowerTuning
        py::class_<IADLXManualPowerTuning, IADLXInterface, PyManualPowerTuning, IADLXInterfacePtr_T<IADLXManualPowerTuning>>(m, "IADLXManualPowerTuning")
        //.def(py::init<>())
        .def("GetPowerLimit", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXManualPowerTuningPtr power_tuning = self.cast<IADLXManualPowerTuning*>();
        adlx_int curVal;
        ADLX_RESULT result = power_tuning->GetPowerLimit(&curVal);
        if (ADLX_SUCCEEDED(result)) {
            return curVal;
        }
        return py::none();
        })
        .def("GetPowerLimitRange", [](py::object self) {
        IADLXManualPowerTuningPtr power_tuning = self.cast<IADLXManualPowerTuning*>();
        ADLX_IntRange tuningRange;
        power_tuning->GetPowerLimitRange(&tuningRange);
        pybind11::dict dict;
        dict["max_value"] = tuningRange.maxValue;
        dict["min_value"] = tuningRange.minValue;
        dict["step"] = tuningRange.step;
        return dict;
        })
        .def("GetTDCLimit", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXManualPowerTuningPtr power_tuning = self.cast<IADLXManualPowerTuning*>();
        adlx_int curVal;
        ADLX_RESULT result = power_tuning->GetTDCLimit(&curVal);
        if (ADLX_SUCCEEDED(result)) {
            return curVal;
        }
        return py::none();
        })
        .def("GetTDCLimitRange", [](py::object self) {
        IADLXManualPowerTuningPtr power_tuning = self.cast<IADLXManualPowerTuning*>();
        ADLX_IntRange tuningRange;
        power_tuning->GetTDCLimitRange(&tuningRange);
        pybind11::dict dict;
        dict["max_value"] = tuningRange.maxValue;
        dict["min_value"] = tuningRange.minValue;
        dict["step"] = tuningRange.step;
        return dict;
        })
        .def("IsSupportedTDCLimit", [](py::object self) {
        IADLXManualPowerTuningPtr power_tuning = self.cast<IADLXManualPowerTuning*>();
        adlx_bool supported = false;
        power_tuning->IsSupportedTDCLimit(&supported);
        return supported;
        })
        .def("SetPowerLimit", [](py::object self, adlx_int curVal) {
        IADLXManualPowerTuningPtr power_tuning = self.cast<IADLXManualPowerTuning*>();	
        ADLX_RESULT ret_api = power_tuning->SetPowerLimit(curVal);
        return ret_api;
        })
        .def("SetTDCLimit", [](py::object self, adlx_int curVal) {
        IADLXManualPowerTuningPtr power_tuning = self.cast<IADLXManualPowerTuning*>();
        ADLX_RESULT ret_api = power_tuning->SetTDCLimit(curVal);
        return ret_api;
        })
        .def("GetPowerLimitDefault", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXManualPowerTuningPtr power_tuning = self.cast<IADLXManualPowerTuning*>();
        adlx_int defaultVal;
        IADLXManualPowerTuning1Ptr power_tuning1(power_tuning);
        if (power_tuning1)
        {
            ADLX_RESULT result = power_tuning1->GetPowerLimitDefault(&defaultVal);
            if (ADLX_SUCCEEDED(result)) {
                return defaultVal;
            }
        }
        return py::none();
        })
        .def("GetTDCLimitDefault", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXManualPowerTuningPtr power_tuning = self.cast<IADLXManualPowerTuning*>();
        adlx_int defaultVal;
        IADLXManualPowerTuning1Ptr power_tuning1(power_tuning);
        if (power_tuning1)
        {
            ADLX_RESULT result = power_tuning1->GetTDCLimitDefault(&defaultVal);
            if (ADLX_SUCCEEDED(result)) {
                return defaultVal;
            }
        }
        return py::none();
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXManualPowerTuningPtr power_tuning = self.cast<IADLXManualPowerTuning*>();
        IADLXManualPowerTuningPtr ppInterface = nullptr;
        power_tuning->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


        // IADLXMemoryTimingDescription
        py::class_<IADLXMemoryTimingDescription, IADLXInterface, PyMemoryTimingDescription, IADLXInterfacePtr_T<IADLXMemoryTimingDescription>>(m, "IADLXMemoryTimingDescription")
        //.def(py::init<>())
        .def("GetDescription", [](py::object self) -> std::variant<ADLX_MEMORYTIMING_DESCRIPTION, py::none> {
        IADLXMemoryTimingDescriptionPtr mem_timing_descpower_tuning = self.cast<IADLXMemoryTimingDescription*>();
        ADLX_MEMORYTIMING_DESCRIPTION description;
        ADLX_RESULT result = mem_timing_descpower_tuning->GetDescription(&description);
        if (ADLX_SUCCEEDED(result))
            return description;
        return py::none();
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXMemoryTimingDescriptionPtr mem_timing_descpower_tuning = self.cast<IADLXMemoryTimingDescription*>();
        IADLXMemoryTimingDescriptionPtr ppInterface = nullptr;
        mem_timing_descpower_tuning->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


        // IADLXMemoryTimingDescriptionList
        py::class_<IADLXMemoryTimingDescriptionList, IADLXList, PyMemoryTimingDescriptionList, IADLXInterfacePtr_T<IADLXMemoryTimingDescriptionList>>(m, "IADLXMemoryTimingDescriptionList")
        //.def(py::init<>())
        .def("Add_Back", [](py::object self, IADLXMemoryTimingDescription* pItem) {
        IADLXMemoryTimingDescriptionListPtr mem_timing_descpower_tuning_list = self.cast<IADLXMemoryTimingDescriptionList*>();
        ADLX_RESULT ret_add_back = mem_timing_descpower_tuning_list->Add_Back(pItem);
        return ret_add_back;
        })
        .def("At", [](py::object self, const adlx_uint location) {
        IADLXMemoryTimingDescriptionListPtr mem_timing_descpower_tuning_list = self.cast<IADLXMemoryTimingDescriptionList*>();
        IADLXMemoryTimingDescriptionPtr pItem;
        mem_timing_descpower_tuning_list->At(location, &pItem);
        return pItem;
        });

        
        // IADLXManualVRAMTuning1
        py::class_<IADLXManualVRAMTuning1, IADLXInterface, PyManualVRAMTuning1, IADLXInterfacePtr_T<IADLXManualVRAMTuning1>>(m, "IADLXManualVRAMTuning1")
        //.def(py::init<>())
        .def("GetEmptyVRAMTuningStates", [](py::object self) {
        IADLXManualVRAMTuning1Ptr vram_tuning1 = self.cast<IADLXManualVRAMTuning1*>();
        IADLXManualTuningStateListPtr manual_tuning_state_list;
        vram_tuning1->GetEmptyVRAMTuningStates(&manual_tuning_state_list);
        std::vector<IADLXManualTuningStatePtr> list;
        if (manual_tuning_state_list) {
            for (adlx_uint crt = manual_tuning_state_list->Begin(); crt != manual_tuning_state_list->End(); ++crt) {
                IADLXManualTuningStatePtr oneState;
                manual_tuning_state_list->At(crt, &oneState);
                list.emplace_back(std::move(oneState));
            }
        }
        return list;
        }, py::return_value_policy::move)
            
        .def("GetMemoryTimingDescription", [](py::object self) -> std::variant<ADLX_MEMORYTIMING_DESCRIPTION, py::none> {
        IADLXManualVRAMTuning1Ptr vram_tuning1 = self.cast<IADLXManualVRAMTuning1*>();
        ADLX_MEMORYTIMING_DESCRIPTION description;
        ADLX_RESULT ret_api = vram_tuning1->GetMemoryTimingDescription(&description);
        if (ADLX_SUCCEEDED(ret_api)) {
            return description;
        }
        return py::none();
        })
        .def("GetSupportedMemoryTimingDescriptionList", [](py::object self) {
        IADLXManualVRAMTuning1Ptr vram_tuning1 = self.cast<IADLXManualVRAMTuning1*>();
        IADLXMemoryTimingDescriptionListPtr ppDescriptionList;
        vram_tuning1->GetSupportedMemoryTimingDescriptionList(&ppDescriptionList);
        std::vector<IADLXMemoryTimingDescriptionPtr> list;
        for (adlx_uint crt = ppDescriptionList->Begin(); crt != ppDescriptionList->End(); ++crt) {
            IADLXMemoryTimingDescriptionPtr memTimingDesc;
            ppDescriptionList->At(crt, &memTimingDesc);
            list.emplace_back(std::move(memTimingDesc));
        }
        return list;
        }, py::return_value_policy::move)
        .def("GetVRAMTuningRanges", [](py::object self) {
        IADLXManualVRAMTuning1Ptr vram_tuning1 = self.cast<IADLXManualVRAMTuning1*>();
        ADLX_IntRange frequencyRange;
        ADLX_IntRange voltageRange;
        vram_tuning1->GetVRAMTuningRanges(&frequencyRange, &voltageRange);

        pybind11::dict dict_frequency_range;
        dict_frequency_range["max_value"] = frequencyRange.maxValue;
        dict_frequency_range["min_value"] = frequencyRange.minValue;
        dict_frequency_range["step"] = frequencyRange.step;

        pybind11::dict dict_voltage_range;
        dict_voltage_range["max_value"] = voltageRange.maxValue;
        dict_voltage_range["min_value"] = voltageRange.minValue;
        dict_voltage_range["step"] = voltageRange.step;

        pybind11::dict dict;
        dict["frequency_range"] = dict_frequency_range;
        dict["voltage_range"] = dict_voltage_range;

        return dict;
        })
        .def("GetVRAMTuningStates", [](py::object self) {
        IADLXManualVRAMTuning1Ptr vram_tuning1 = self.cast<IADLXManualVRAMTuning1*>();
        IADLXManualTuningStateListPtr ppVRAMStates;
        vram_tuning1->GetVRAMTuningStates(&ppVRAMStates);
        std::vector<IADLXManualTuningStatePtr> list;
        for (adlx_uint crt = ppVRAMStates->Begin(); crt != ppVRAMStates->End(); ++crt) {
            IADLXManualTuningStatePtr oneState;
            ppVRAMStates->At(crt, &oneState);
            list.emplace_back(std::move(oneState));
        }
        return list;
        }, py::return_value_policy::move)
        .def("IsSupportedMemoryTiming", [](py::object self) {
        IADLXManualVRAMTuning1Ptr vram_tuning1 = self.cast<IADLXManualVRAMTuning1*>();
        adlx_bool supported = false;
        vram_tuning1->IsSupportedMemoryTiming(&supported);
        return supported;
        })
        .def("IsValidVRAMTuningStates", [](py::object self, std::vector<IADLXManualTuningStatePtr> list) {
        IADLXManualVRAMTuning1Ptr vram_tuning1 = self.cast<IADLXManualVRAMTuning1*>();
        
        IADLXManualTuningStateListPtr pVRAMStates;
        vram_tuning1->GetEmptyVRAMTuningStates(&pVRAMStates);
        pVRAMStates->Clear();
        size_t vecSize = list.size();
        for (unsigned int i = 0; i < vecSize; i++)
        {
            pVRAMStates->Add_Back(list[i]);
        }
        adlx_int errorIndex = -1;
        vram_tuning1->IsValidVRAMTuningStates(pVRAMStates, &errorIndex);
        return errorIndex;
        })
        .def("SetMemoryTimingDescription", [](py::object self, ADLX_MEMORYTIMING_DESCRIPTION description) {
        IADLXManualVRAMTuning1Ptr vram_tuning1 = self.cast<IADLXManualVRAMTuning1*>();
        ADLX_RESULT ret_api = vram_tuning1->SetMemoryTimingDescription(description);
        return ret_api;
        })
        .def("SetVRAMTuningStates", [](py::object self, std::vector<IADLXManualTuningStatePtr> list) {
        IADLXManualVRAMTuning1Ptr vram_tuning1 = self.cast<IADLXManualVRAMTuning1*>();
        IADLXManualTuningStateListPtr pVRAMStates;
        vram_tuning1->GetEmptyVRAMTuningStates(&pVRAMStates);
        pVRAMStates->Clear();
        size_t vecSize = list.size();
        for (unsigned int i = 0; i < vecSize; i++)
        {
            pVRAMStates->Add_Back(list[i]);
        }
        ADLX_RESULT ret_api = vram_tuning1->SetVRAMTuningStates(pVRAMStates);
        return ret_api;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXManualVRAMTuning1Ptr vram_tuning1 = self.cast<IADLXManualVRAMTuning1*>();
        IADLXManualVRAMTuning1Ptr ppInterface = nullptr;
        vram_tuning1->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move)
        // Custom Methods
        .def("GetVRAMTuningStatesRaw", [](py::object self) {
        IADLXManualVRAMTuning1Ptr vram_tuning1 = self.cast<IADLXManualVRAMTuning1*>();
        IADLXManualTuningStateListPtr ppVRAMStates;
        vram_tuning1->GetVRAMTuningStates(&ppVRAMStates);
        return ppVRAMStates;
        }, py::return_value_policy::move)
        .def("GetSupportedMemoryTimingDescriptionListRaw", [](py::object self) {
        IADLXManualVRAMTuning1Ptr vram_tuning2 = self.cast<IADLXManualVRAMTuning1*>();
        IADLXMemoryTimingDescriptionListPtr ppDescriptionList;
        vram_tuning2->GetSupportedMemoryTimingDescriptionList(&ppDescriptionList);
        return ppDescriptionList;
        }, py::return_value_policy::move);


        // IADLXManualVRAMTuning2
        py::class_<IADLXManualVRAMTuning2, IADLXInterface, PyManualVRAMTuning2, IADLXInterfacePtr_T<IADLXManualVRAMTuning2>>(m, "IADLXManualVRAMTuning2")
        //.def(py::init<>())
        .def("GetMaxVRAMFrequency", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXManualVRAMTuning2Ptr vram_tuning2 = self.cast<IADLXManualVRAMTuning2*>();
        adlx_int freq = 0;
        ADLX_RESULT ret_api = vram_tuning2->GetMaxVRAMFrequency(&freq);
        if (ADLX_SUCCEEDED(ret_api)) {
            return freq;
        }
        return py::none();
        })
        .def("GetMaxVRAMFrequencyRange", [](py::object self) {
        IADLXManualVRAMTuning2Ptr vram_tuning2 = self.cast<IADLXManualVRAMTuning2*>();
        ADLX_IntRange tuningRange;
        vram_tuning2->GetMaxVRAMFrequencyRange(&tuningRange);
        pybind11::dict dict;
        dict["max_value"] = tuningRange.maxValue;
        dict["min_value"] = tuningRange.minValue;
        dict["step"] = tuningRange.step;
        return dict;
        })
        .def("GetMemoryTimingDescription", [](py::object self) -> std::variant<ADLX_MEMORYTIMING_DESCRIPTION, py::none> {
        IADLXManualVRAMTuning2Ptr vram_tuning2 = self.cast<IADLXManualVRAMTuning2*>();
        ADLX_MEMORYTIMING_DESCRIPTION description;
        ADLX_RESULT ret_api = vram_tuning2->GetMemoryTimingDescription(&description);
        if (ADLX_SUCCEEDED(ret_api)) {
            return description;
        }
        return py::none();
        })
        .def("GetSupportedMemoryTimingDescriptionList", [](py::object self) {
        IADLXManualVRAMTuning2Ptr vram_tuning2 = self.cast<IADLXManualVRAMTuning2*>();
        IADLXMemoryTimingDescriptionListPtr ppDescriptionList;
        vram_tuning2->GetSupportedMemoryTimingDescriptionList(&ppDescriptionList);
        std::vector<IADLXMemoryTimingDescriptionPtr> list;
        for (adlx_uint crt = ppDescriptionList->Begin(); crt != ppDescriptionList->End(); ++crt) {
            IADLXMemoryTimingDescriptionPtr memTimingDesc;
            ppDescriptionList->At(crt, &memTimingDesc);
            list.emplace_back(std::move(memTimingDesc));
        }
        return list;
        }, py::return_value_policy::move)
        .def("IsSupportedMemoryTiming", [](py::object self) {
        IADLXManualVRAMTuning2Ptr vram_tuning2 = self.cast<IADLXManualVRAMTuning2*>();
        adlx_bool supported = false;
        vram_tuning2->IsSupportedMemoryTiming(&supported);
        return supported;
        })
        .def("SetMaxVRAMFrequency", [](py::object self, adlx_int freq) {
        IADLXManualVRAMTuning2Ptr vram_tuning2 = self.cast<IADLXManualVRAMTuning2*>();
        ADLX_RESULT ret_api = vram_tuning2->SetMaxVRAMFrequency(freq);
        return ret_api;
        })
        .def("SetMemoryTimingDescription", [](py::object self, ADLX_MEMORYTIMING_DESCRIPTION description) {
        IADLXManualVRAMTuning2Ptr vram_tuning2 = self.cast<IADLXManualVRAMTuning2*>();
        ADLX_RESULT ret_api = vram_tuning2->SetMemoryTimingDescription(description);
        return ret_api;
        })
        .def("GetMaxVRAMFrequencyDefault", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXManualVRAMTuning2Ptr vram_tuning2 = self.cast<IADLXManualVRAMTuning2*>();
        adlx_int defaultVal = 0;
        IADLXManualVRAMTuning2_1Ptr vram_tuning2_1(vram_tuning2);
        if (vram_tuning2_1)
        {
            ADLX_RESULT ret_api = vram_tuning2_1->GetMaxVRAMFrequencyDefault(&defaultVal);
            if (ADLX_SUCCEEDED(ret_api)) {
                return defaultVal;
            }
        }
        return py::none();
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXManualVRAMTuning2Ptr vram_tuning2 = self.cast<IADLXManualVRAMTuning2*>();
        IADLXManualVRAMTuning2Ptr ppInterface = nullptr;
        vram_tuning2->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move)
        //custom methods
        .def("GetSupportedMemoryTimingDescriptionListRaw", [](py::object self) {
        IADLXManualVRAMTuning2Ptr vram_tuning2 = self.cast<IADLXManualVRAMTuning2*>();
        IADLXMemoryTimingDescriptionListPtr ppDescriptionList;
        vram_tuning2->GetSupportedMemoryTimingDescriptionList(&ppDescriptionList);
        return ppDescriptionList;
        }, py::return_value_policy::move);
}
