//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

#include "bind_common.h"

void bind_3d_settings(py::module_& m)
{
    // IADLX3DSettingsChangedEvent
    py::class_<IADLX3DSettingsChangedEvent, IADLXChangedEvent, Py3DSettingsChangedEvent, IADLXInterfacePtr_T<IADLX3DSettingsChangedEvent>>(m, "IADLX3DSettingsChangedEvent")
        //.def(py::init<>())
        .def("GetGPU", [](py::object self) {
        IADLX3DSettingsChangedEvent* threeDEvent = self.cast<IADLX3DSettingsChangedEvent*>();
        IADLXGPUPtr gpu;
        threeDEvent->GetGPU(&gpu);
        return gpu;
        }, py::return_value_policy::move)
        .def("IsAntiLagChanged", [](py::object self) {
        IADLX3DSettingsChangedEventPtr settingsEvent = self.cast<IADLX3DSettingsChangedEvent*>();
        adlx_bool anti_lag_changed = settingsEvent->IsAntiLagChanged();
        return anti_lag_changed;
        })
        .def("IsChillChanged", [](py::object self) {
        IADLX3DSettingsChangedEventPtr settingsEvent = self.cast<IADLX3DSettingsChangedEvent*>();
        adlx_bool chill_changed = settingsEvent->IsChillChanged();
        return chill_changed;
        })
        .def("IsBoostChanged", [](py::object self) {
        IADLX3DSettingsChangedEventPtr settingsEvent = self.cast<IADLX3DSettingsChangedEvent*>();
        adlx_bool boost_changed = settingsEvent->IsBoostChanged();
        return boost_changed;
        })
        .def("IsImageSharpeningChanged", [](py::object self) {
        IADLX3DSettingsChangedEventPtr settingsEvent = self.cast<IADLX3DSettingsChangedEvent*>();
        adlx_bool image_sharpening_changed = settingsEvent->IsImageSharpeningChanged();
        return image_sharpening_changed;
        })
        .def("IsEnhancedSyncChanged", [](py::object self) {
        IADLX3DSettingsChangedEventPtr settingsEvent = self.cast<IADLX3DSettingsChangedEvent*>();
        adlx_bool enhanced_sync_changed = settingsEvent->IsEnhancedSyncChanged();
        return enhanced_sync_changed;
        })
        .def("IsWaitForVerticalRefreshChanged", [](py::object self) {
        IADLX3DSettingsChangedEventPtr settingsEvent = self.cast<IADLX3DSettingsChangedEvent*>();
        adlx_bool wait_for_vertical_refresh_changed = settingsEvent->IsWaitForVerticalRefreshChanged();
        return wait_for_vertical_refresh_changed;
        })
        .def("IsFrameRateTargetControlChanged", [](py::object self) {
        IADLX3DSettingsChangedEventPtr settingsEvent = self.cast<IADLX3DSettingsChangedEvent*>();
        adlx_bool frame_rate_target_control_changed = settingsEvent->IsFrameRateTargetControlChanged();
        return frame_rate_target_control_changed;
        })
        .def("IsAntiAliasingChanged", [](py::object self) {
        IADLX3DSettingsChangedEventPtr settingsEvent = self.cast<IADLX3DSettingsChangedEvent*>();
        adlx_bool anti_aliasing_changed = settingsEvent->IsAntiAliasingChanged();
        return anti_aliasing_changed;
        })
        .def("IsMorphologicalAntiAliasingChanged", [](py::object self) {
        IADLX3DSettingsChangedEventPtr settingsEvent = self.cast<IADLX3DSettingsChangedEvent*>();
        adlx_bool morphological_anti_aliasing_changed = settingsEvent->IsMorphologicalAntiAliasingChanged();
        return morphological_anti_aliasing_changed;
        })
        .def("IsAnisotropicFilteringChanged", [](py::object self) {
        IADLX3DSettingsChangedEventPtr settingsEvent = self.cast<IADLX3DSettingsChangedEvent*>();
        adlx_bool anisotropic_filtering_changed = settingsEvent->IsAnisotropicFilteringChanged();
        return anisotropic_filtering_changed;
        })
        .def("IsTessellationModeChanged", [](py::object self) {
        IADLX3DSettingsChangedEventPtr settingsEvent = self.cast<IADLX3DSettingsChangedEvent*>();
        adlx_bool tessellation_mode_changed = settingsEvent->IsTessellationModeChanged();
        return tessellation_mode_changed;
        })
        .def("IsRadeonSuperResolutionChanged", [](py::object self) {
        IADLX3DSettingsChangedEventPtr settingsEvent = self.cast<IADLX3DSettingsChangedEvent*>();
        adlx_bool radeon_super_resolution_changed = settingsEvent->IsRadeonSuperResolutionChanged();
        return radeon_super_resolution_changed;
        })
        .def("IsResetShaderCache", [](py::object self) {
        IADLX3DSettingsChangedEventPtr settingsEvent = self.cast<IADLX3DSettingsChangedEvent*>();
        adlx_bool reset_shader_cache_changed = settingsEvent->IsResetShaderCache();
        return reset_shader_cache_changed;
        })
        .def("IsAMDFluidMotionFramesChanged", [](py::object self) {
        IADLX3DSettingsChangedEventPtr settingsEvent = self.cast<IADLX3DSettingsChangedEvent*>();
        IADLX3DSettingsChangedEvent1Ptr ppsettingsEvent1Ptr(settingsEvent);
        if (ppsettingsEvent1Ptr == nullptr)
        {
            return false;
        }
        return ppsettingsEvent1Ptr->IsAMDFluidMotionFramesChanged();
        })
        .def("IsImageSharpenDesktopChanged", [](py::object self) {
        IADLX3DSettingsChangedEventPtr settingsEvent = self.cast<IADLX3DSettingsChangedEvent*>();
        IADLX3DSettingsChangedEvent2Ptr ppsettingsEvent2Ptr(settingsEvent);
        if (ppsettingsEvent2Ptr == nullptr)
        {
            return false;
        }
        return ppsettingsEvent2Ptr->IsImageSharpenDesktopChanged();
        })
        .def("IsFidelityFXSuperResolutionChanged", [](py::object self) {
        IADLX3DSettingsChangedEventPtr settingsEvent = self.cast<IADLX3DSettingsChangedEvent*>();
        IADLX3DSettingsChangedEvent3Ptr ppsettingsEvent3Ptr(settingsEvent);
        if (ppsettingsEvent3Ptr == nullptr)
        {
            return false;
        }
        return ppsettingsEvent3Ptr->IsFidelityFXSuperResolutionChanged();
        })
        .def("IsFidelityFXFrameGenUpgradeChanged", [](py::object self) {
        IADLX3DSettingsChangedEventPtr settingsEvent = self.cast<IADLX3DSettingsChangedEvent*>();
        IADLX3DSettingsChangedEvent3Ptr ppsettingsEvent3Ptr(settingsEvent);
        if (ppsettingsEvent3Ptr == nullptr)
        {
            return false;
        }
        return ppsettingsEvent3Ptr->IsFidelityFXFrameGenUpgradeChanged();
        });


    // Callback for 3DSettingsChangedListener
    py::class_<Py3DSettingsChangedListenerCallback>(m, "Py3DSettingsChangedListenerCallback")
        .def(py::init<>())
        .def_readwrite("call", &Py3DSettingsChangedListenerCallback::m_call);


    // 3D Settings
    py::class_<IADLX3DSettingsServices, IADLXInterface, Py3DSettingsServices, IADLXInterfacePtr_T<IADLX3DSettingsServices>>(m, "IADLX3DSettingsServices")
        //.def(py::init<>())
        .def("Get3DSettingsChangedHandling", [](py::object self) {
        IADLX3DSettingsServicesPtr threeDSettingsServices = self.cast<IADLX3DSettingsServices*>();
        IADLX3DSettingsChangedHandlingPtr settingsChangedHandling;
        threeDSettingsServices->Get3DSettingsChangedHandling(&settingsChangedHandling);
        return settingsChangedHandling;
        }, py::return_value_policy::move)
        .def("GetAnisotropicFiltering", [](py::object self, IADLXGPU* pGPU) {
        IADLX3DSettingsServicesPtr threeDSettingsServices = self.cast<IADLX3DSettingsServices*>();
        IADLX3DAnisotropicFilteringPtr anisotropicFiltering;
        threeDSettingsServices->GetAnisotropicFiltering(pGPU, &anisotropicFiltering);
        return anisotropicFiltering;
        }, py::return_value_policy::move)
        .def("GetAntiAliasing", [](py::object self, IADLXGPU* pGPU) {
        IADLX3DSettingsServicesPtr threeDSettingsServices = self.cast<IADLX3DSettingsServices*>();
        IADLX3DAntiAliasingPtr pp3DAntiAliasing;
        threeDSettingsServices->GetAntiAliasing(pGPU, &pp3DAntiAliasing);
        return pp3DAntiAliasing;
        }, py::return_value_policy::move)
        .def("GetAntiLag", [](py::object self, IADLXGPU* pGPU) {
        IADLX3DSettingsServicesPtr threeDSettingsServices = self.cast<IADLX3DSettingsServices*>();
        IADLX3DAntiLagPtr pp3DAntiLag;
        threeDSettingsServices->GetAntiLag(pGPU, &pp3DAntiLag);
        return pp3DAntiLag;
        }, py::return_value_policy::move)
        .def("GetBoost", [](py::object self, IADLXGPU* pGPU) {
        IADLX3DSettingsServicesPtr threeDSettingsServices = self.cast<IADLX3DSettingsServices*>();
        IADLX3DBoostPtr pp3DBoostPtr;
        threeDSettingsServices->GetBoost(pGPU, &pp3DBoostPtr);
        return pp3DBoostPtr;
        }, py::return_value_policy::move)
        .def("GetChill", [](py::object self, IADLXGPU* pGPU) {
        IADLX3DSettingsServicesPtr threeDSettingsServices = self.cast<IADLX3DSettingsServices*>();
        IADLX3DChillPtr pp3DChill;
        threeDSettingsServices->GetChill(pGPU, &pp3DChill);
        return pp3DChill;
        }, py::return_value_policy::move)
        .def("GetEnhancedSync", [](py::object self, IADLXGPU* pGPU) {
        IADLX3DSettingsServicesPtr threeDSettingsServices = self.cast<IADLX3DSettingsServices*>();
        IADLX3DEnhancedSyncPtr pp3DEnhancedSync;
        threeDSettingsServices->GetEnhancedSync(pGPU, &pp3DEnhancedSync);
        return pp3DEnhancedSync;
        }, py::return_value_policy::move)
        .def("GetFrameRateTargetControl", [](py::object self, IADLXGPU* pGPU) {
        IADLX3DSettingsServicesPtr threeDSettingsServices = self.cast<IADLX3DSettingsServices*>();
        IADLX3DFrameRateTargetControlPtr pp3DFrameRateTargetControl;
        threeDSettingsServices->GetFrameRateTargetControl(pGPU, &pp3DFrameRateTargetControl);
        return pp3DFrameRateTargetControl;
        }, py::return_value_policy::move)
        .def("GetImageSharpening", [](py::object self, IADLXGPU* pGPU) {
        IADLX3DSettingsServicesPtr threeDSettingsServices = self.cast<IADLX3DSettingsServices*>();
        IADLX3DImageSharpeningPtr pp3DImageSharpening;
        threeDSettingsServices->GetImageSharpening(pGPU, &pp3DImageSharpening);
        return pp3DImageSharpening;
        }, py::return_value_policy::move)
        .def("GetMorphologicalAntiAliasing", [](py::object self, IADLXGPU* pGPU) {
        IADLX3DSettingsServicesPtr threeDSettingsServices = self.cast<IADLX3DSettingsServices*>();
        IADLX3DMorphologicalAntiAliasingPtr morphologicalAntiAliasing;
        threeDSettingsServices->GetMorphologicalAntiAliasing(pGPU, &morphologicalAntiAliasing);
        return morphologicalAntiAliasing;
        }, py::return_value_policy::move)
        .def("GetRadeonSuperResolution", [](py::object self) {
        IADLX3DSettingsServicesPtr threeDSettingsServices = self.cast<IADLX3DSettingsServices*>();
        IADLX3DRadeonSuperResolutionPtr radeonSuperResolution;
        threeDSettingsServices->GetRadeonSuperResolution(&radeonSuperResolution);
        return radeonSuperResolution;
        }, py::return_value_policy::move)
        .def("GetResetShaderCache", [](py::object self, IADLXGPU* pGPU) {
        IADLX3DSettingsServicesPtr threeDSettingsServices = self.cast<IADLX3DSettingsServices*>();
        IADLX3DResetShaderCachePtr resetShaderCache;
        threeDSettingsServices->GetResetShaderCache(pGPU, &resetShaderCache);
        return resetShaderCache;
        }, py::return_value_policy::move)
        .def("GetTessellation", [](py::object self, IADLXGPU* pGPU) {
        IADLX3DSettingsServicesPtr threeDSettingsServices = self.cast<IADLX3DSettingsServices*>();
        IADLX3DTessellationPtr tessellation;
        threeDSettingsServices->GetTessellation(pGPU, &tessellation);
        return tessellation;
        }, py::return_value_policy::move)
        .def("GetWaitForVerticalRefresh", [](py::object self, IADLXGPU* pGPU) {
        IADLX3DSettingsServicesPtr threeDSettingsServices = self.cast<IADLX3DSettingsServices*>();
        IADLX3DWaitForVerticalRefreshPtr waitForVerticalRefresh;
        threeDSettingsServices->GetWaitForVerticalRefresh(pGPU, &waitForVerticalRefresh);
        return waitForVerticalRefresh;
        }, py::return_value_policy::move)
        .def("GetAMDFluidMotionFrames", [](py::object self) {
        IADLX3DSettingsServicesPtr threeDSettingsServices = self.cast<IADLX3DSettingsServices*>();
        IADLX3DAMDFluidMotionFramesPtr afmf;
        IADLX3DSettingsServices1Ptr threeDSettingsServices1(threeDSettingsServices);
        if (threeDSettingsServices1)
        {
            threeDSettingsServices1->GetAMDFluidMotionFrames(&afmf);
        }
        return afmf;
        }, py::return_value_policy::move)
        .def("GetImageSharpenDesktop", [](py::object self, IADLXGPU* pGPU) {
        IADLX3DSettingsServicesPtr threeDSettingsServices = self.cast<IADLX3DSettingsServices*>();
        IADLX3DImageSharpenDesktopPtr pp3DImageSharpenDesktop = nullptr;
        IADLX3DSettingsServices2Ptr threeDSettingsServices2(threeDSettingsServices);
        if (threeDSettingsServices2)
        {
            threeDSettingsServices2->GetImageSharpenDesktop(pGPU, &pp3DImageSharpenDesktop);
        }
        return pp3DImageSharpenDesktop;
        }, py::return_value_policy::move)
        .def("GetFidelityFXSuperResolution", [](py::object self, IADLXGPU* pGPU) {
        IADLX3DSettingsServicesPtr threeDSettingsServices = self.cast<IADLX3DSettingsServices*>();
        IADLX3DFidelityFXSuperResolutionPtr fidelityFXSuperResolution = nullptr;
        IADLX3DSettingsServices3Ptr threeDSettingsServices3(threeDSettingsServices);
        if (threeDSettingsServices3)
        {
            threeDSettingsServices3->GetFidelityFXSuperResolution(pGPU, &fidelityFXSuperResolution);
        }
        return fidelityFXSuperResolution;
        }, py::return_value_policy::move)
        .def("GetFidelityFXFrameGenUpgrade", [](py::object self, IADLXGPU* pGPU) {
        IADLX3DSettingsServicesPtr threeDSettingsServices = self.cast<IADLX3DSettingsServices*>();
        IADLX3DFidelityFXFrameGenUpgradePtr fidelityFXFrameGenUpgrade = nullptr;
        IADLX3DSettingsServices3Ptr threeDSettingsServices3(threeDSettingsServices);
        if (threeDSettingsServices3)
        {
            threeDSettingsServices3->GetFidelityFXFrameGenUpgrade(pGPU, &fidelityFXFrameGenUpgrade);
        }
        return fidelityFXFrameGenUpgrade;
        }, py::return_value_policy::move)
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLX3DSettingsServicesPtr threeDSettingsServices = self.cast<IADLX3DSettingsServices*>();
        IADLX3DSettingsServicesPtr ppInterface = nullptr;
        threeDSettingsServices->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


    // 3DSettingsChangedHandling
    py::class_<IADLX3DSettingsChangedHandling, IADLXInterface, Py3DSettingsChangedHandling, IADLXInterfacePtr_T<IADLX3DSettingsChangedHandling>>(m, "IADLX3DSettingsChangedHandling")
        //.def(py::init<>())
        .def("Add3DSettingsEventListener", [](py::object self, Py3DSettingsChangedListenerCallback* p3DSettingsChangedListener) {
        IADLX3DSettingsChangedHandlingPtr threeDSettingsChanged = self.cast<IADLX3DSettingsChangedHandling*>();
        ADLX_RESULT retAddSettingsListener = threeDSettingsChanged->Add3DSettingsEventListener(p3DSettingsChangedListener);
        return retAddSettingsListener;
        })
        .def("Remove3DSettingsEventListener", [](py::object self, Py3DSettingsChangedListenerCallback* p3DSettingsChangedListener) {
        IADLX3DSettingsChangedHandlingPtr threeDSettingsChanged = self.cast<IADLX3DSettingsChangedHandling*>();
        ADLX_RESULT retRemoveSettingsListener = threeDSettingsChanged->Remove3DSettingsEventListener(p3DSettingsChangedListener);
        return retRemoveSettingsListener;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLX3DSettingsChangedHandlingPtr threeDSettingsChanged = self.cast<IADLX3DSettingsChangedHandling*>();
        IADLX3DSettingsChangedHandlingPtr ppInterface = nullptr;
        threeDSettingsChanged->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


    // 3DAnisotropicFiltering
    py::class_<IADLX3DAnisotropicFiltering, IADLXInterface, Py3DAnisotropicFiltering, IADLXInterfacePtr_T<IADLX3DAnisotropicFiltering>>(m, "IADLX3DAnisotropicFiltering")
        //.def(py::init<>())
        .def("GetLevel", [](py::object self) -> std::variant<ADLX_ANISOTROPIC_FILTERING_LEVEL, py::none> {
        IADLX3DAnisotropicFilteringPtr anisotropicFiltering = self.cast<IADLX3DAnisotropicFiltering*>();
        ADLX_ANISOTROPIC_FILTERING_LEVEL currentLevel;
        ADLX_RESULT ret = anisotropicFiltering->GetLevel(&currentLevel);
        if (ADLX_SUCCEEDED(ret))
            return currentLevel;
        return py::none();
        })
        .def("IsEnabled", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLX3DAnisotropicFilteringPtr anisotropicFiltering = self.cast<IADLX3DAnisotropicFiltering*>();
        adlx_bool isEnabled;
        ADLX_RESULT ret = anisotropicFiltering->IsEnabled(&isEnabled);
        if (ADLX_SUCCEEDED(ret))
            return isEnabled;
        return py::none();
        })
        .def("IsSupported", [](py::object self) {
        IADLX3DAnisotropicFilteringPtr anisotropicFiltering = self.cast<IADLX3DAnisotropicFiltering*>();
        adlx_bool supported = false;
        anisotropicFiltering->IsSupported(&supported);
        return supported;
        })
        .def("SetEnabled", [](py::object self, adlx_bool enable) {
        IADLX3DAnisotropicFilteringPtr anisotropicFiltering = self.cast<IADLX3DAnisotropicFiltering*>();
        ADLX_RESULT retSetEnable = anisotropicFiltering->SetEnabled(enable);
        return retSetEnable;
        })
        .def("SetLevel", [](py::object self, ADLX_ANISOTROPIC_FILTERING_LEVEL level) {
        IADLX3DAnisotropicFilteringPtr anisotropicFiltering = self.cast<IADLX3DAnisotropicFiltering*>();	
        ADLX_RESULT retSetLevel = anisotropicFiltering->SetLevel(level);
        return retSetLevel;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLX3DAnisotropicFilteringPtr anisotropicFiltering = self.cast<IADLX3DAnisotropicFiltering*>();
        IADLX3DAnisotropicFilteringPtr ppInterface = nullptr;
        anisotropicFiltering->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


    // 3DAntiAliasing
    py::class_<IADLX3DAntiAliasing, IADLXInterface, Py3DAntiAliasing, IADLXInterfacePtr_T<IADLX3DAntiAliasing>>(m, "IADLX3DAntiAliasing")
        //.def(py::init<>())
        .def("GetLevel", [](py::object self) -> std::variant<ADLX_ANTI_ALIASING_LEVEL, py::none> {
        IADLX3DAntiAliasingPtr antiAliasing = self.cast<IADLX3DAntiAliasing*>();
        ADLX_ANTI_ALIASING_LEVEL currentLevel;
        ADLX_RESULT ret = antiAliasing->GetLevel(&currentLevel);
        if (ADLX_SUCCEEDED(ret))
            return currentLevel;
        return py::none();
        })
        .def("GetMethod", [](py::object self) -> std::variant<ADLX_ANTI_ALIASING_METHOD, py::none> {
        IADLX3DAntiAliasingPtr antiAliasing = self.cast<IADLX3DAntiAliasing*>();
        ADLX_ANTI_ALIASING_METHOD currentMethod;
        ADLX_RESULT ret = antiAliasing->GetMethod(&currentMethod);
        if (ADLX_SUCCEEDED(ret))
            return currentMethod;
        return py::none();
        })
        .def("GetMode", [](py::object self) -> std::variant<ADLX_ANTI_ALIASING_MODE, py::none> {
        IADLX3DAntiAliasingPtr antiAliasing = self.cast<IADLX3DAntiAliasing*>();
        ADLX_ANTI_ALIASING_MODE currentMode;
        ADLX_RESULT ret = antiAliasing->GetMode(&currentMode);
        if (ADLX_SUCCEEDED(ret))
            return currentMode;
        return py::none();
        })
        .def("IsSupported", [](py::object self) {
        IADLX3DAntiAliasingPtr antiAliasing = self.cast<IADLX3DAntiAliasing*>();
        adlx_bool supported = false;
        antiAliasing->IsSupported(&supported);
        return supported;
        })
        .def("SetLevel", [](py::object self, ADLX_ANTI_ALIASING_LEVEL level) {
        IADLX3DAntiAliasingPtr antiAliasing = self.cast<IADLX3DAntiAliasing*>();
        ADLX_RESULT retSetLevel = antiAliasing->SetLevel(level);
        return retSetLevel;
        })
        .def("SetMethod", [](py::object self, ADLX_ANTI_ALIASING_METHOD method) {
        IADLX3DAntiAliasingPtr antiAliasing = self.cast<IADLX3DAntiAliasing*>();
        ADLX_RESULT retSetMethod = antiAliasing->SetMethod(method);
        return retSetMethod;
        })
        .def("SetMode", [](py::object self, ADLX_ANTI_ALIASING_MODE mode) {
        IADLX3DAntiAliasingPtr antiAliasing = self.cast<IADLX3DAntiAliasing*>();
        ADLX_RESULT retSetMode = antiAliasing->SetMode(mode);
        return retSetMode;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLX3DAntiAliasingPtr antiAliasing = self.cast<IADLX3DAntiAliasing*>();
        IADLX3DAntiAliasingPtr ppInterface = nullptr;
        antiAliasing->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


    // 3DAntiLag
    py::class_<IADLX3DAntiLag, IADLXInterface, Py3DAntiLag, IADLXInterfacePtr_T<IADLX3DAntiLag>>(m, "IADLX3DAntiLag")
        //.def(py::init<>())
        .def("IsEnabled", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLX3DAntiLagPtr antiLag = self.cast<IADLX3DAntiLag*>();
        adlx_bool enabled;
        ADLX_RESULT ret = antiLag->IsEnabled(&enabled);
        if (ADLX_SUCCEEDED(ret))
            return enabled;
        return py::none();
        })
        .def("IsSupported", [](py::object self) {
        IADLX3DAntiLagPtr antiLag = self.cast<IADLX3DAntiLag*>();
        adlx_bool supported = false;
        antiLag->IsSupported(&supported);
        return supported;
        })
        .def("SetEnabled", [](py::object self, adlx_bool enable) {
        IADLX3DAntiLagPtr antiLag = self.cast<IADLX3DAntiLag*>();
        ADLX_RESULT retSetEnabled = antiLag->SetEnabled(enable);
        return retSetEnabled;
        })
        .def("GetLevel", [](py::object self) -> std::variant<ADLX_ANTILAG_STATE, py::none> {
        IADLX3DAntiLagPtr antiLag = self.cast<IADLX3DAntiLag*>();
        ADLX_ANTILAG_STATE level = ANTILAG;
        IADLX3DAntiLag1Ptr antiLag1(antiLag);
        if (antiLag1)
        {
            ADLX_RESULT ret = antiLag1->GetLevel(&level);
            if (ADLX_SUCCEEDED(ret))
                return level;
        }
        return py::none();
        })
        .def("SetLevel", [](py::object self, ADLX_ANTILAG_STATE level) {
        IADLX3DAntiLagPtr antiLag = self.cast<IADLX3DAntiLag*>();
        IADLX3DAntiLag1Ptr antiLag1(antiLag);
        ADLX_RESULT retSetLevel = ADLX_NOT_SUPPORTED;
        if (antiLag1)
        {
            retSetLevel = antiLag1->SetLevel(level);
        }
        return retSetLevel;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLX3DAntiLagPtr antiLag = self.cast<IADLX3DAntiLag*>();
        IADLX3DAntiLagPtr ppInterface = nullptr;
        antiLag->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


    // 3DBoost
    py::class_<IADLX3DBoost, IADLXInterface, Py3DBoost, IADLXInterfacePtr_T<IADLX3DBoost>>(m, "IADLX3DBoost")
        //.def(py::init<>())
        .def("GetResolution", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLX3DBoostPtr threeDBoost = self.cast<IADLX3DBoost*>();
        adlx_int currentMinRes;
        ADLX_RESULT ret = threeDBoost->GetResolution(&currentMinRes);
        if (ADLX_SUCCEEDED(ret))
            return currentMinRes;
        return py::none();
        })
        .def("GetResolutionRange", [](py::object self) {
        IADLX3DBoostPtr threeDBoost = self.cast<IADLX3DBoost*>();
        ADLX_IntRange range;
        threeDBoost->GetResolutionRange(&range);
        py::dict dict;
        dict["maxValue"] = range.maxValue;
        dict["minValue"] = range.minValue;
        dict["step"] = range.step;
        return dict;
        })
        .def("IsEnabled", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLX3DBoostPtr threeDBoost = self.cast<IADLX3DBoost*>();
        adlx_bool enabled;
        ADLX_RESULT ret = threeDBoost->IsEnabled(&enabled);
        if (ADLX_SUCCEEDED(ret))
            return enabled;
        return py::none();
        })
        .def("IsSupported", [](py::object self) {
        IADLX3DBoostPtr threeDBoost = self.cast<IADLX3DBoost*>();
        adlx_bool supported = false;
        threeDBoost->IsSupported(&supported);
        return supported;
        })
        .def("SetEnabled", [](py::object self, adlx_bool enable) {
        IADLX3DBoostPtr threeDBoost = self.cast<IADLX3DBoost*>();
        ADLX_RESULT retSetEnabled = threeDBoost->SetEnabled(enable);
        return retSetEnabled;
        })
        .def("SetResolution", [](py::object self, adlx_int minRes) {
        IADLX3DBoostPtr threeDBoost = self.cast<IADLX3DBoost*>();
        ADLX_RESULT retSetResolution = threeDBoost->SetResolution(minRes);
        return retSetResolution;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLX3DBoostPtr threeDBoost = self.cast<IADLX3DBoost*>();
        IADLX3DBoostPtr ppInterface = nullptr;
        threeDBoost->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);

    // 3DChill
    py::class_<IADLX3DChill, IADLXInterface, Py3DChill, IADLXInterfacePtr_T<IADLX3DChill>>(m, "IADLX3DChill")
        //.def(py::init<>())0
        .def("GetFPSRange", [](py::object self) {
        IADLX3DChillPtr threeDChill = self.cast<IADLX3DChill*>();
        ADLX_IntRange range;
        threeDChill->GetFPSRange(&range);
        py::dict dict;
        dict["maxValue"] = range.maxValue;
        dict["minValue"] = range.minValue;
        dict["step"] = range.step;
        return dict;
        })
        .def("GetMaxFPS", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLX3DChillPtr threeDChill = self.cast<IADLX3DChill*>();
        adlx_int currentMaxFPS;
        ADLX_RESULT ret = threeDChill->GetMaxFPS(&currentMaxFPS);
        if (ADLX_SUCCEEDED(ret))
            return currentMaxFPS;
        return py::none();
        })
        .def("GetMinFPS", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLX3DChillPtr threeDChill = self.cast<IADLX3DChill*>();
        adlx_int currentMinFPS;
        ADLX_RESULT ret = threeDChill->GetMinFPS(&currentMinFPS);
        if (ADLX_SUCCEEDED(ret))
            return currentMinFPS;
        return py::none();
        })
        .def("IsEnabled", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLX3DChillPtr threeDChill = self.cast<IADLX3DChill*>();
        adlx_bool enabled;
        ADLX_RESULT ret = threeDChill->IsEnabled(&enabled);
        if (ADLX_SUCCEEDED(ret))
            return enabled;
        return py::none();
        })
        .def("IsSupported", [](py::object self) {
        IADLX3DChillPtr threeDChill = self.cast<IADLX3DChill*>();
        adlx_bool supported = false;
        threeDChill->IsSupported(&supported);
        return supported;
        })
        .def("SetEnabled", [](py::object self, adlx_bool enable) {
        IADLX3DChillPtr threeDChill = self.cast<IADLX3DChill*>();
        ADLX_RESULT retSetEnabled = threeDChill->SetEnabled(enable);
        return retSetEnabled;
        })
        .def("SetMaxFPS", [](py::object self, adlx_int maxFPS) {
        IADLX3DChillPtr threeDChill = self.cast<IADLX3DChill*>();
        ADLX_RESULT retSetMaxFPS = threeDChill->SetMaxFPS(maxFPS);
        return retSetMaxFPS;
        })
        .def("SetMinFPS", [](py::object self, adlx_int minFPS) {
        IADLX3DChillPtr threeDChill = self.cast<IADLX3DChill*>();
        ADLX_RESULT retSetMinFPS = threeDChill->SetMinFPS(minFPS);
        return retSetMinFPS;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLX3DChillPtr threeDChill = self.cast<IADLX3DChill*>();
        IADLX3DChillPtr ppInterface = nullptr;
        threeDChill->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


    // 3DEnhancedSync
    py::class_<IADLX3DEnhancedSync, IADLXInterface, Py3DEnhancedSync, IADLXInterfacePtr_T<IADLX3DEnhancedSync>>(m, "IADLX3DEnhancedSync")
        //.def(py::init<>())
        .def("IsEnabled", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLX3DEnhancedSyncPtr threeDEnhancedSync = self.cast<IADLX3DEnhancedSync*>();
        adlx_bool enabled;
        ADLX_RESULT ret = threeDEnhancedSync->IsEnabled(&enabled);
        if (ADLX_SUCCEEDED(ret))
            return enabled;
        return py::none();
        })
        .def("IsSupported", [](py::object self) {
        IADLX3DEnhancedSyncPtr threeDEnhancedSync = self.cast<IADLX3DEnhancedSync*>();
        adlx_bool supported = false;
        threeDEnhancedSync->IsSupported(&supported);
        return supported;
        })
        .def("SetEnabled", [](py::object self, adlx_bool enable) {
        IADLX3DEnhancedSyncPtr threeDEnhancedSync = self.cast<IADLX3DEnhancedSync*>();
        ADLX_RESULT retSetEnabled = threeDEnhancedSync->SetEnabled(enable);
        return retSetEnabled;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLX3DEnhancedSyncPtr threeDEnhancedSync = self.cast<IADLX3DEnhancedSync*>();
        IADLX3DEnhancedSyncPtr ppInterface = nullptr;
        threeDEnhancedSync->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


    // 3DFrameRateTargetControl
    py::class_<IADLX3DFrameRateTargetControl, IADLXInterface, Py3DFrameRateTargetControl, IADLXInterfacePtr_T<IADLX3DFrameRateTargetControl>>(m, "IADLX3DFrameRateTargetControl")
        //.def(py::init<>())
        .def("GetFPS", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLX3DFrameRateTargetControlPtr threeDFrameRateTargetControl = self.cast<IADLX3DFrameRateTargetControl*>();
        adlx_int currentFPS;
        ADLX_RESULT ret = threeDFrameRateTargetControl->GetFPS(&currentFPS);
        if (ADLX_SUCCEEDED(ret))
            return currentFPS;
        return py::none();
        })
        .def("GetFPSRange", [](py::object self) {
        IADLX3DFrameRateTargetControlPtr threeDFrameRateTargetControl = self.cast<IADLX3DFrameRateTargetControl*>();
        ADLX_IntRange range;
        threeDFrameRateTargetControl->GetFPSRange(&range);
        py::dict dict;
        dict["maxValue"] = range.maxValue;
        dict["minValue"] = range.minValue;
        dict["step"] = range.step;
        return dict;
        })
        .def("IsEnabled", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLX3DFrameRateTargetControlPtr threeDFrameRateTargetControl = self.cast<IADLX3DFrameRateTargetControl*>();
        adlx_bool enabled;
        ADLX_RESULT ret = threeDFrameRateTargetControl->IsEnabled(&enabled);
        if (ADLX_SUCCEEDED(ret))
            return enabled;
        return py::none();
        })
        .def("IsSupported", [](py::object self) {
        IADLX3DFrameRateTargetControlPtr threeDFrameRateTargetControl = self.cast<IADLX3DFrameRateTargetControl*>();
        adlx_bool supported = false;
        threeDFrameRateTargetControl->IsSupported(&supported);
        return supported;
        })
        .def("SetEnabled", [](py::object self, adlx_bool enable) {
        IADLX3DFrameRateTargetControlPtr threeDFrameRateTargetControl = self.cast<IADLX3DFrameRateTargetControl*>();
        ADLX_RESULT retSetEnabled = threeDFrameRateTargetControl->SetEnabled(enable);
        return retSetEnabled;
        })
        .def("SetFPS", [](py::object self, adlx_int maxFPS) {
        IADLX3DFrameRateTargetControlPtr threeDFrameRateTargetControl = self.cast<IADLX3DFrameRateTargetControl*>();
        ADLX_RESULT retSetFPS = threeDFrameRateTargetControl->SetFPS(maxFPS);
        return retSetFPS;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLX3DFrameRateTargetControlPtr threeDFrameRateTargetControl = self.cast<IADLX3DFrameRateTargetControl*>();
        IADLX3DFrameRateTargetControlPtr ppInterface = nullptr;
        threeDFrameRateTargetControl->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);
        

    // 3DImageSharpening
    py::class_<IADLX3DImageSharpening, IADLXInterface, Py3DImageSharpening, IADLXInterfacePtr_T<IADLX3DImageSharpening>>(m, "IADLX3DImageSharpening")
        //.def(py::init<>())
        .def("GetSharpness", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLX3DImageSharpeningPtr threeDImageSharpening = self.cast<IADLX3DImageSharpening*>();
        adlx_int currentSharpness;
        ADLX_RESULT ret = threeDImageSharpening->GetSharpness(&currentSharpness);
        if (ADLX_SUCCEEDED(ret))
            return currentSharpness;
        return py::none();
        })
        .def("GetSharpnessRange", [](py::object self) {
        IADLX3DImageSharpeningPtr threeDImageSharpening = self.cast<IADLX3DImageSharpening*>();
        ADLX_IntRange range;
        threeDImageSharpening->GetSharpnessRange(&range);
        py::dict dict;
        dict["maxValue"] = range.maxValue;
        dict["minValue"] = range.minValue;
        dict["step"] = range.step;
        return dict;
        })
        .def("IsEnabled", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLX3DImageSharpeningPtr threeDImageSharpening = self.cast<IADLX3DImageSharpening*>();
        adlx_bool enabled;
        ADLX_RESULT ret = threeDImageSharpening->IsEnabled(&enabled);
        if (ADLX_SUCCEEDED(ret))
            return enabled;
        return py::none();
        })
        .def("IsSupported", [](py::object self) {
        IADLX3DImageSharpeningPtr threeDImageSharpening = self.cast<IADLX3DImageSharpening*>();
        adlx_bool supported = false;
        threeDImageSharpening->IsSupported(&supported);
        return supported;
        })
        .def("SetEnabled", [](py::object self, adlx_bool enable) {
        IADLX3DImageSharpeningPtr threeDImageSharpening = self.cast<IADLX3DImageSharpening*>();
        ADLX_RESULT retSetEnabled = threeDImageSharpening->SetEnabled(enable);
        return retSetEnabled;
        })
        .def("SetSharpness", [](py::object self, adlx_int sharpness) {
        IADLX3DImageSharpeningPtr threeDImageSharpening = self.cast<IADLX3DImageSharpening*>();
        ADLX_RESULT retSetSharpness = threeDImageSharpening->SetSharpness(sharpness);
        return retSetSharpness;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLX3DImageSharpeningPtr threeDImageSharpening = self.cast<IADLX3DImageSharpening*>();
        IADLX3DImageSharpeningPtr ppInterface = nullptr;
        threeDImageSharpening->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);

    // 3DImageSharpeningDesktop
    py::class_<IADLX3DImageSharpenDesktop, IADLXInterface, Py3DImageSharpenDesktop, IADLXInterfacePtr_T<IADLX3DImageSharpenDesktop>>(m, "IADLX3DImageSharpenDesktop")
        //.def(py::init<>())
        .def("IsEnabled", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLX3DImageSharpenDesktopPtr threeDImageSharpenDesktop = self.cast<IADLX3DImageSharpenDesktop*>();
        adlx_bool enabled;
        ADLX_RESULT ret = threeDImageSharpenDesktop->IsEnabled(&enabled);
        if (ADLX_SUCCEEDED(ret))
            return enabled;
        return py::none();
        })
        .def("IsSupported", [](py::object self) {
        IADLX3DImageSharpenDesktopPtr threeDImageSharpenDesktop = self.cast<IADLX3DImageSharpenDesktop*>();
        adlx_bool supported = false;
        threeDImageSharpenDesktop->IsSupported(&supported);
        return supported;
        })
        .def("SetEnabled", [](py::object self, adlx_bool enable) {
        IADLX3DImageSharpenDesktopPtr threeDImageSharpenDesktop = self.cast<IADLX3DImageSharpenDesktop*>();
        ADLX_RESULT retSetEnabled = threeDImageSharpenDesktop->SetEnabled(enable);
        return retSetEnabled;
        });

    // 3DFidelityFXSuperResolution
    py::class_<IADLX3DFidelityFXSuperResolution, IADLXInterface, Py3DFidelityFXSuperResolution, IADLXInterfacePtr_T<IADLX3DFidelityFXSuperResolution>>(m, "IADLX3DFidelityFXSuperResolution")
        //.def(py::init<>())
        .def("IsEnabled", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLX3DFidelityFXSuperResolutionPtr fidelityFXSuperResolution = self.cast<IADLX3DFidelityFXSuperResolution*>();
        adlx_bool enabled;
        ADLX_RESULT ret = fidelityFXSuperResolution->IsEnabled(&enabled);
        if (ADLX_SUCCEEDED(ret))
            return enabled;
        return py::none();
        })
        .def("IsSupported", [](py::object self) {
        IADLX3DFidelityFXSuperResolutionPtr fidelityFXSuperResolution = self.cast<IADLX3DFidelityFXSuperResolution*>();
        adlx_bool supported = false;
        fidelityFXSuperResolution->IsSupported(&supported);
        return supported;
        })
        .def("SetEnabled", [](py::object self, adlx_bool enable) {
        IADLX3DFidelityFXSuperResolutionPtr fidelityFXSuperResolution = self.cast<IADLX3DFidelityFXSuperResolution*>();
        ADLX_RESULT retSetEnabled = fidelityFXSuperResolution->SetEnabled(enable);
        return retSetEnabled;
        });


    // 3DFidelityFXFrameGenUpgrade
    py::class_<IADLX3DFidelityFXFrameGenUpgrade, IADLXInterface, Py3DFidelityFXFrameGenUpgrade, IADLXInterfacePtr_T<IADLX3DFidelityFXFrameGenUpgrade>>(m, "IADLX3DFidelityFXFrameGenUpgrade")
        //.def(py::init<>())
        .def("IsEnabled", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLX3DFidelityFXFrameGenUpgradePtr frameGenUpgrade = self.cast<IADLX3DFidelityFXFrameGenUpgrade*>();
        adlx_bool enabled;
        ADLX_RESULT ret = frameGenUpgrade->IsEnabled(&enabled);
        if (ADLX_SUCCEEDED(ret))
            return enabled;
        return py::none();
        })
        .def("IsSupported", [](py::object self) {
        IADLX3DFidelityFXFrameGenUpgradePtr frameGenUpgrade = self.cast<IADLX3DFidelityFXFrameGenUpgrade*>();
        adlx_bool supported = false;
        frameGenUpgrade->IsSupported(&supported);
        return supported;
        })
        .def("SetEnabled", [](py::object self, adlx_bool enable) {
        IADLX3DFidelityFXFrameGenUpgradePtr frameGenUpgrade = self.cast<IADLX3DFidelityFXFrameGenUpgrade*>();
        ADLX_RESULT retSetEnabled = frameGenUpgrade->SetEnabled(enable);
        return retSetEnabled;
        });

    // 3DMorphologicalAntiAliasing
    py::class_<IADLX3DMorphologicalAntiAliasing, IADLXInterface, Py3DMorphologicalAntiAliasing, IADLXInterfacePtr_T<IADLX3DMorphologicalAntiAliasing>>(m, "IADLX3DMorphologicalAntiAliasing")
        //.def(py::init<>())
        .def("IsEnabled", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLX3DMorphologicalAntiAliasingPtr morphoAA = self.cast<IADLX3DMorphologicalAntiAliasing*>();
        adlx_bool enabled;
        ADLX_RESULT ret = morphoAA->IsEnabled(&enabled);
        if (ADLX_SUCCEEDED(ret))
            return enabled;
        return py::none();
        })
        .def("IsSupported", [](py::object self) {
        IADLX3DMorphologicalAntiAliasingPtr morphoAA = self.cast<IADLX3DMorphologicalAntiAliasing*>();
        adlx_bool supported = false;
        morphoAA->IsSupported(&supported);
        return supported;
        })
        .def("SetEnabled", [](py::object self, adlx_bool enable) {
        IADLX3DMorphologicalAntiAliasingPtr morphoAA = self.cast<IADLX3DMorphologicalAntiAliasing*>();
        ADLX_RESULT retSetEnabled = morphoAA->SetEnabled(enable);
        return retSetEnabled;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLX3DMorphologicalAntiAliasingPtr morphoAA = self.cast<IADLX3DMorphologicalAntiAliasing*>();
        IADLX3DMorphologicalAntiAliasingPtr ppInterface = nullptr;
        morphoAA->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


    // 3DRadeonSuperResolution
    py::class_<IADLX3DRadeonSuperResolution, IADLXInterface, Py3DRadeonSuperResolution, IADLXInterfacePtr_T<IADLX3DRadeonSuperResolution>>(m, "IADLX3DRadeonSuperResolution")
        //.def(py::init<>())
        .def("GetSharpness", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLX3DRadeonSuperResolutionPtr radeonSuperResolution = self.cast<IADLX3DRadeonSuperResolution*>();
        adlx_int currentSharpness;
        ADLX_RESULT ret = radeonSuperResolution->GetSharpness(&currentSharpness);
        if (ADLX_SUCCEEDED(ret))
            return currentSharpness;
        return py::none();
        })
        .def("GetSharpnessRange", [](py::object self) {
        IADLX3DRadeonSuperResolutionPtr radeonSuperResolution = self.cast<IADLX3DRadeonSuperResolution*>();
        ADLX_IntRange range;
        radeonSuperResolution->GetSharpnessRange(&range);
        py::dict dict;
        dict["maxValue"] = range.maxValue;
        dict["minValue"] = range.minValue;
        dict["step"] = range.step;
        return dict;
        })
        .def("IsEnabled", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLX3DRadeonSuperResolutionPtr radeonSuperResolution = self.cast<IADLX3DRadeonSuperResolution*>();
        adlx_bool enabled;
        ADLX_RESULT ret = radeonSuperResolution->IsEnabled(&enabled);
        if (ADLX_SUCCEEDED(ret))
            return enabled;
        return py::none();
        })
        .def("IsSupported", [](py::object self) {
        IADLX3DRadeonSuperResolutionPtr radeonSuperResolution = self.cast<IADLX3DRadeonSuperResolution*>();
        adlx_bool supported = false;
        radeonSuperResolution->IsSupported(&supported);
        return supported;
        })
        .def("SetEnabled", [](py::object self, adlx_bool enable) {
        IADLX3DRadeonSuperResolutionPtr radeonSuperResolution = self.cast<IADLX3DRadeonSuperResolution*>();
        ADLX_RESULT retSetEnabled = radeonSuperResolution->SetEnabled(enable);
        return retSetEnabled;
        })
        .def("SetSharpness", [](py::object self, adlx_int sharpness) {
        IADLX3DRadeonSuperResolutionPtr radeonSuperResolution = self.cast<IADLX3DRadeonSuperResolution*>();
        ADLX_RESULT retSetSharpness = radeonSuperResolution->SetSharpness(sharpness);
        return retSetSharpness;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLX3DRadeonSuperResolutionPtr radeonSuperResolution = self.cast<IADLX3DRadeonSuperResolution*>();
        IADLX3DRadeonSuperResolutionPtr ppInterface = nullptr;
        radeonSuperResolution->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


    // 3DResetShaderCache
    py::class_<IADLX3DResetShaderCache, IADLXInterface, Py3DResetShaderCache, IADLXInterfacePtr_T<IADLX3DResetShaderCache>>(m, "IADLX3DResetShaderCache")
        //.def(py::init<>())
        .def("IsSupported", [](py::object self) {
        IADLX3DResetShaderCachePtr resetShaderCache = self.cast<IADLX3DResetShaderCache*>();
        adlx_bool supported = false;
        resetShaderCache->IsSupported(&supported);
        return supported;
        })
        .def("ResetShaderCache", [](py::object self) {
        IADLX3DResetShaderCachePtr resetShaderCache = self.cast<IADLX3DResetShaderCache*>();
        ADLX_RESULT retResetShaderCache = resetShaderCache->ResetShaderCache();
        return retResetShaderCache;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLX3DResetShaderCachePtr resetShaderCache = self.cast<IADLX3DResetShaderCache*>();
        IADLX3DResetShaderCachePtr ppInterface = nullptr;
        resetShaderCache->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);
            
        
    // X3DTessellation
    py::class_<IADLX3DTessellation, IADLXInterface, Py3DTessellation, IADLXInterfacePtr_T<IADLX3DTessellation>>(m, "IADLX3DTessellation")
        //.def(py::init<>())
        .def("GetLevel", [](py::object self) -> std::variant<ADLX_TESSELLATION_LEVEL, py::none> {
        IADLX3DTessellationPtr tessellation = self.cast<IADLX3DTessellation*>();
        ADLX_TESSELLATION_LEVEL currentLevel;
        ADLX_RESULT ret = tessellation->GetLevel(&currentLevel);
        if (ADLX_SUCCEEDED(ret))
            return currentLevel;
        return py::none();
        })
        .def("GetMode", [](py::object self) -> std::variant<ADLX_TESSELLATION_MODE, py::none> {
        IADLX3DTessellationPtr tessellation = self.cast<IADLX3DTessellation*>();
        ADLX_TESSELLATION_MODE currentMode;
        ADLX_RESULT ret = tessellation->GetMode(&currentMode);
        if (ADLX_SUCCEEDED(ret))
            return currentMode;
        return py::none();
        })
        .def("IsSupported", [](py::object self) {
        IADLX3DTessellationPtr tessellation = self.cast<IADLX3DTessellation*>();
        adlx_bool supported = false;
        tessellation->IsSupported(&supported);
        return supported;
        })
        .def("SetLevel", [](py::object self, ADLX_TESSELLATION_LEVEL level) {
        IADLX3DTessellationPtr tessellation = self.cast<IADLX3DTessellation*>();
        ADLX_RESULT retSetLevel = tessellation->SetLevel(level);
        return retSetLevel;
        })
        .def("SetMode", [](py::object self, ADLX_TESSELLATION_MODE mode) {
        IADLX3DTessellationPtr tessellation = self.cast<IADLX3DTessellation*>();
        ADLX_RESULT retSetMode = tessellation->SetMode(mode);
        return retSetMode;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLX3DTessellationPtr tessellation = self.cast<IADLX3DTessellation*>();
        IADLX3DTessellationPtr ppInterface = nullptr;
        tessellation->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


    // 3DWaitForVerticalRefresh
    py::class_<IADLX3DWaitForVerticalRefresh, IADLXInterface, Py3DWaitForVerticalRefresh, IADLXInterfacePtr_T<IADLX3DWaitForVerticalRefresh>>(m, "IADLX3DWaitForVerticalRefresh")
        //.def(py::init<>())
        .def("GetMode", [](py::object self) -> std::variant<ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE, py::none> {
        IADLX3DWaitForVerticalRefreshPtr waitForVerticalRefreshPtr = self.cast<IADLX3DWaitForVerticalRefresh*>();
        ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE currentMode;
        ADLX_RESULT ret = waitForVerticalRefreshPtr->GetMode(&currentMode);
        if (ADLX_SUCCEEDED(ret))
            return currentMode;
        return py::none();
        })
        .def("IsEnabled", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLX3DWaitForVerticalRefreshPtr waitForVerticalRefreshPtr = self.cast<IADLX3DWaitForVerticalRefresh*>();
        adlx_bool enabled;
        ADLX_RESULT ret = waitForVerticalRefreshPtr->IsEnabled(&enabled);
        if (ADLX_SUCCEEDED(ret))
            return enabled;
        return py::none();
        })
        .def("IsSupported", [](py::object self) {
        IADLX3DWaitForVerticalRefreshPtr waitForVerticalRefreshPtr = self.cast<IADLX3DWaitForVerticalRefresh*>();
        adlx_bool supported = false;
        waitForVerticalRefreshPtr->IsSupported(&supported);
        return supported;
        })
        .def("SetMode", [](py::object self, ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE mode) {
        IADLX3DWaitForVerticalRefreshPtr waitForVerticalRefreshPtr = self.cast<IADLX3DWaitForVerticalRefresh*>();
        ADLX_RESULT retSetMode = waitForVerticalRefreshPtr->SetMode(mode);
        return retSetMode;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLX3DWaitForVerticalRefreshPtr waitForVerticalRefreshPtr = self.cast<IADLX3DWaitForVerticalRefresh*>();
        IADLX3DWaitForVerticalRefreshPtr ppInterface = nullptr;
        waitForVerticalRefreshPtr->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


    // 3DAMDFluidMotionFrames
    py::class_<IADLX3DAMDFluidMotionFrames, IADLXInterface, Py3DAMDFluidMotionFrames, IADLXInterfacePtr_T<IADLX3DAMDFluidMotionFrames>>(m, "IADLX3DAMDFluidMotionFrames")
        //.def(py::init<>())
        .def("IsSupported", [](py::object self) {
        IADLX3DAMDFluidMotionFramesPtr afmf = self.cast<IADLX3DAMDFluidMotionFrames*>();
        adlx_bool supported = false;
        afmf->IsSupported(&supported);
        return supported;
            })
        .def("IsEnabled", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLX3DAMDFluidMotionFramesPtr afmf = self.cast<IADLX3DAMDFluidMotionFrames*>();
        adlx_bool enabled;
        ADLX_RESULT ret = afmf->IsEnabled(&enabled);
        if (ADLX_SUCCEEDED(ret))
            return enabled;
        return py::none();
            })
        .def("SetEnabled", [](py::object self, adlx_bool enable) {
        IADLX3DAMDFluidMotionFramesPtr afmf = self.cast<IADLX3DAMDFluidMotionFrames*>();
        ADLX_RESULT retSetEnabled = afmf->SetEnabled(enable);
        return retSetEnabled;
            })
        .def("IsSupportedAlgorithm", [](py::object self) {
        IADLX3DAMDFluidMotionFramesPtr afmf = self.cast<IADLX3DAMDFluidMotionFrames*>();
        adlx_bool supported = false;
        IADLX3DAMDFluidMotionFrames1Ptr afmf1(afmf);
        if (afmf1)
            afmf1->IsSupportedAlgorithm(&supported);
        return supported;
            })
        .def("GetAlgorithm", [](py::object self) -> std::variant<ADLX_AFMF_ALGORITHM, py::none> {
        IADLX3DAMDFluidMotionFramesPtr afmf = self.cast<IADLX3DAMDFluidMotionFrames*>();
        ADLX_AFMF_ALGORITHM algorithm = AFMF_ALGORITHM_AUTO;
        IADLX3DAMDFluidMotionFrames1Ptr afmf1(afmf);
        if (afmf1) {
            ADLX_RESULT ret = afmf1->GetAlgorithm(&algorithm);
            if (ADLX_SUCCEEDED(ret))
                return algorithm;
        }
        return py::none();
            })
        .def("SetAlgorithm", [](py::object self, ADLX_AFMF_ALGORITHM algorithm) {
        IADLX3DAMDFluidMotionFramesPtr afmf = self.cast<IADLX3DAMDFluidMotionFrames*>();
        ADLX_RESULT retSetStatus = ADLX_FAIL;
        IADLX3DAMDFluidMotionFrames1Ptr afmf1(afmf);
        if (afmf1)
            retSetStatus = afmf1->SetAlgorithm(algorithm);
        return retSetStatus;
            })
        .def("GetSearchMode", [](py::object self) -> std::variant<ADLX_AFMF_SEARCH_MODE_TYPE, py::none> {
        IADLX3DAMDFluidMotionFramesPtr afmf = self.cast<IADLX3DAMDFluidMotionFrames*>();
        ADLX_AFMF_SEARCH_MODE_TYPE mode = AFMF_SEARCH_MODE_AUTO;
        IADLX3DAMDFluidMotionFrames1Ptr afmf1(afmf);
        if (afmf1) {
            ADLX_RESULT ret = afmf1->GetSearchMode(&mode);
            if (ADLX_SUCCEEDED(ret))
                return mode;
        }
        return py::none();
            })
        .def("SetSearchMode", [](py::object self, ADLX_AFMF_SEARCH_MODE_TYPE mode) {
        IADLX3DAMDFluidMotionFramesPtr afmf = self.cast<IADLX3DAMDFluidMotionFrames*>();
        ADLX_RESULT retSetStatus = ADLX_FAIL;
        IADLX3DAMDFluidMotionFrames1Ptr afmf1(afmf);
        if (afmf1)
            retSetStatus = afmf1->SetSearchMode(mode);
        return retSetStatus;
            })
        .def("GetPerformanceMode", [](py::object self) -> std::variant<ADLX_AFMF_PERFORMANCE_MODE_TYPE, py::none> {
        IADLX3DAMDFluidMotionFramesPtr afmf = self.cast<IADLX3DAMDFluidMotionFrames*>();
        ADLX_AFMF_PERFORMANCE_MODE_TYPE mode = AFMF_PERFORMANCE_MODE_AUTO;
        IADLX3DAMDFluidMotionFrames1Ptr afmf1(afmf);
        if (afmf1) {
            ADLX_RESULT ret = afmf1->GetPerformanceMode(&mode);
            if (ADLX_SUCCEEDED(ret))
                return mode;
        }
        return py::none();
            })
        .def("SetPerformanceMode", [](py::object self, ADLX_AFMF_PERFORMANCE_MODE_TYPE mode) {
        IADLX3DAMDFluidMotionFramesPtr afmf = self.cast<IADLX3DAMDFluidMotionFrames*>();
        ADLX_RESULT retSetStatus = ADLX_FAIL;
        IADLX3DAMDFluidMotionFrames1Ptr afmf1(afmf);
        if (afmf1)
            retSetStatus = afmf1->SetPerformanceMode(mode);
        return retSetStatus;
            })
        .def("GetFastMotionResponse", [](py::object self) -> std::variant<ADLX_AFMF_FAST_MOTION_RESP, py::none> {
        IADLX3DAMDFluidMotionFramesPtr afmf = self.cast<IADLX3DAMDFluidMotionFrames*>();
        ADLX_AFMF_FAST_MOTION_RESP response = AFMF_RESP_REPEAT_FRAMES;
        IADLX3DAMDFluidMotionFrames1Ptr afmf1(afmf);
        if (afmf1) {
            ADLX_RESULT ret = afmf1->GetFastMotionResponse(&response);
            if (ADLX_SUCCEEDED(ret))
                return response;
        }
        return py::none();
            })
        .def("SetFastMotionResponse", [](py::object self, ADLX_AFMF_FAST_MOTION_RESP response) {
        IADLX3DAMDFluidMotionFramesPtr afmf = self.cast<IADLX3DAMDFluidMotionFrames*>();
        ADLX_RESULT retSetStatus = ADLX_FAIL;
        IADLX3DAMDFluidMotionFrames1Ptr afmf1(afmf);
        if (afmf1)
            retSetStatus = afmf1->SetFastMotionResponse(response);
        return retSetStatus;
            })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLX3DAMDFluidMotionFramesPtr afmf = self.cast<IADLX3DAMDFluidMotionFrames*>();
        IADLX3DAMDFluidMotionFramesPtr ppInterface = nullptr;
        afmf->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
            }, py::return_value_policy::move);
}
