//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

#include "bind_common.h"

void bind_core(py::module_& m)
{
    //ADLX_IntRange
    py::class_<ADLX_IntRange>(m, "ADLX_IntRange")
    .def(py::init<>())
    .def_readwrite("maxValue", &ADLX_IntRange::maxValue)
    .def_readwrite("minValue", &ADLX_IntRange::minValue)
    .def_readwrite("step", &ADLX_IntRange::step);

    // ADLX_UINT16_RGB
    py::class_<ADLX_UINT16_RGB>(m, "ADLX_UINT16_RGB")
    .def(py::init<>())
    .def_readwrite("red", &ADLX_UINT16_RGB::red)
    .def_readwrite("green", &ADLX_UINT16_RGB::green)
    .def_readwrite("blue", &ADLX_UINT16_RGB::blue);

    // ADLX_helper
    py::class_<ADLXHelper>(m, "ADLXHelper")
        .def(py::init<>())
        .def("Initialize", &ADLXHelper::Initialize)
        .def("InitializeWithIncompatibleDriver", &ADLXHelper::InitializeWithIncompatibleDriver)
        .def("Terminate", &ADLXHelper::Terminate)
        .def("QueryVersion", &ADLXHelper::QueryVersion)
        .def("QueryFullVersion", &ADLXHelper::QueryFullVersion)
        .def("GetSystemServices", &ADLXHelper::GetSystemServices, py::return_value_policy::reference)
        .def("GetAdlMapping", &ADLXHelper::GetAdlMapping, py::return_value_policy::reference);

    //IADLXInterface
    py::class_<IADLXInterface, PyInterface, IADLXInterfacePtr_T<IADLXInterface>>(m, "IADLXInterface")
    //.def(py::init<>())
    .def("Acquire", [](py::object self) {
    IADLXInterfacePtr pinterface = self.cast<IADLXInterface*>();
    adlx_long count = pinterface->Acquire();
    return count;
    }, py::return_value_policy::move)
    .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
    IADLXInterfacePtr pinterface = self.cast<IADLXInterface*>();
    IADLXInterfacePtr ppInterface = nullptr;
    pinterface->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
    return ppInterface;
    }, py::return_value_policy::move)
    .def("Release", [](py::object self) {
    IADLXInterfacePtr pinterface = self.cast<IADLXInterface*>();
    adlx_long count = pinterface->Release();
    return count;
    }, py::return_value_policy::move);


    // IADLXList
    py::class_<IADLXList, IADLXInterface, PyIADLXList, IADLXInterfacePtr_T<IADLXList>>(m, "IADLXList")
    //.def(py::init<>())
    .def("Size", [] (py::object self){
    IADLXListPtr rawList = self.cast<IADLXList*>();
    adlx_uint size = rawList->Size();
    return size;
    })
    .def("Empty", [] (py::object self){
    IADLXListPtr rawList = self.cast<IADLXList*>();
    adlx_bool isEmpty = rawList->Empty();
    return isEmpty;
    })
    .def("Begin", [] (py::object self) {
    IADLXListPtr rawList = self.cast<IADLXList*>();
    adlx_uint begin = rawList->Begin();
    return begin;
    })
    .def("End", [] (py::object self){
    IADLXListPtr rawList = self.cast<IADLXList*>();
    adlx_uint end = rawList->End();
    return end;
    })
    .def("At", [] (py::object self, const adlx_uint location){
    IADLXListPtr rawList = self.cast<IADLXList*>();
    IADLXInterfacePtr ppItem;
    rawList->At(location, &ppItem);
    return ppItem;
    })
    .def("Clear", [] (py::object self) {
    IADLXListPtr rawList = self.cast<IADLXList*>();
    IADLXInterfacePtr ppItem;
    ADLX_RESULT retList = rawList->Clear();
    return retList;
    })
    .def("Remove_Back", [] (py::object self){
    IADLXListPtr rawList = self.cast<IADLXList*>();
    IADLXInterfacePtr ppItem;
    ADLX_RESULT retList = rawList->Remove_Back();
    return retList;
    })
    .def("Add_Back", [] (py::object self, IADLXInterface* pItem){
    IADLXListPtr rawList = self.cast<IADLXList*>();
    IADLXInterfacePtr ppItem;
    ADLX_RESULT retList = rawList->Add_Back(pItem);
    return retList;
    })
    .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
    IADLXListPtr rawList = self.cast<IADLXList*>();
    IADLXListPtr ppInterface = nullptr;
    rawList->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
    return ppInterface;
    }, py::return_value_policy::move);

    // Callback for log
    py::class_<PyLogCallback>(m, "PyLogCallback")
        .def(py::init<>())
        .def_readwrite("call", &PyLogCallback::m_call);

    // System
    py::class_<IADLXSystem, PySystem>(m, "IADLXSystem")
        .def(py::init<>()) 
        .def("EnableLog", [](py::object self, ADLX_LOG_DESTINATION mode, ADLX_LOG_SEVERITY severity, py::object pyLogger, const wchar_t* fileName) {
        IADLXSystem* sys = self.cast<IADLXSystem*>();
        IADLXLog* pLogger = nullptr;
        PyLogCallback* callback = nullptr;
        if (!pyLogger.is_none()) {
            callback = pyLogger.cast<PyLogCallback*>();
            pLogger = static_cast<IADLXLog*>(callback);
        }
        ADLX_RESULT ret_enable_log = sys->EnableLog(mode, severity, pLogger, fileName);
        return ret_enable_log;
        })
        //Get3DSettingsServices
        .def("Get3DSettingsServices", [](py::object self) {
        IADLXSystem* sys = self.cast<IADLXSystem*>();
        IADLX3DSettingsServicesPtr threeDSservices = nullptr;
        sys->Get3DSettingsServices(&threeDSservices);
        return threeDSservices;
        }, py::return_value_policy::move)
        //
        .def("GetDisplaysServices", [](py::object self) {
        IADLXSystem *sys = self.cast<IADLXSystem*>();
        IADLXDisplayServicesPtr displayService = nullptr;
        sys->GetDisplaysServices(&displayService);
        return displayService;
        }, py::return_value_policy::move)
        .def("GetDesktopsServices", [](py::object self) {
        IADLXSystem* sys = self.cast<IADLXSystem*>();
        IADLXDesktopServicesPtr desktop_service = nullptr;
        sys->GetDesktopsServices(&desktop_service);
        return desktop_service;
        }, py::return_value_policy::move)
        .def("GetGPUs", [](py::object self) {
        IADLXSystem* sys = self.cast<IADLXSystem*>();
        IADLXGPUListPtr gpuList = nullptr;
        sys->GetGPUs(&gpuList);
        std::vector<IADLXGPUPtr> list;
        if (gpuList)
        {
            for (adlx_uint s = gpuList->Begin(); s != gpuList->End(); s++) {
                IADLXGPUPtr item;
                gpuList->At(s, &item);
                list.emplace_back(std::move(item));
            }
        }
        return list;
    }, py::return_value_policy::move)
        .def("GetGPUTuningServices", [](py::object self) {
        IADLXSystem* sys = self.cast<IADLXSystem*>();
        IADLXGPUTuningServicesPtr gpuTuningService = nullptr;
        sys->GetGPUTuningServices(&gpuTuningService);
        return gpuTuningService;
    }, py::return_value_policy::move)
        .def("GetPerformanceMonitoringServices", [](py::object self) {
        IADLXSystem* sys = self.cast<IADLXSystem*>();
        IADLXPerformanceMonitoringServicesPtr perfMonitService = nullptr;
        sys->GetPerformanceMonitoringServices(&perfMonitService);
        return perfMonitService;
    }, py::return_value_policy::move)
        .def("TotalSystemRAM", [](py::object self) -> std::variant<adlx_uint, py::none> {
        IADLXSystem* sys = self.cast<IADLXSystem*>();
        adlx_uint ramMB;
        ADLX_RESULT ret = sys->TotalSystemRAM(&ramMB);
        if (ADLX_SUCCEEDED(ret))
            return ramMB;
        return py::none();
    })
        .def("GetI2C", [](py::object self, IADLXGPUPtr oneGPU) {
        IADLXSystem* sys = self.cast<IADLXSystem*>();
        IADLXI2CPtr i2ecService = nullptr;
        sys->GetI2C(oneGPU, &i2ecService);
        return i2ecService;
    }, py::return_value_policy::move)
        .def("HybridGraphicsType", [](py::object self) -> std::variant<ADLX_HG_TYPE, py::none> {
        IADLXSystem* sys = self.cast<IADLXSystem*>();
        ADLX_HG_TYPE hgType;
        ADLX_RESULT ret = sys->HybridGraphicsType(&hgType);
        if (ADLX_SUCCEEDED(ret))
            return hgType;
        return py::none();
    })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXSystem* sys = self.cast<IADLXSystem*>();
        IADLXSystem* ppInterface = nullptr;
        sys->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
    }, py::return_value_policy::move)
        .def("GetGPUsChangedHandling", [](py::object self) {
        IADLXSystem* sys = self.cast<IADLXSystem*>();
        IADLXGPUsChangedHandlingPtr ppGPUsChangedHandling = nullptr;
        sys->GetGPUsChangedHandling(&ppGPUsChangedHandling);
        return ppGPUsChangedHandling;
    }, py::return_value_policy::move)
    // Custom methods
        .def("GetGPUsRaw", [](py::object self) {
        IADLXSystem* sys = self.cast<IADLXSystem*>();
        IADLXGPUListPtr gpuList = nullptr;
        sys->GetGPUs(&gpuList);
        return gpuList;
    }, py::return_value_policy::move)
    // QI-fold IADLXSystem1::GetPowerTuningServices
        .def("GetPowerTuningServices", [](py::object self) {
        IADLXSystem* sys = self.cast<IADLXSystem*>();
        IADLXSystem1Ptr system1;
        IADLXPowerTuningServicesPtr svc;
        ADLX_RESULT res = sys->QueryInterface(IADLXSystem1::IID(), reinterpret_cast<void**>(&system1));
        if (ADLX_SUCCEEDED(res) && system1)
        {
            system1->GetPowerTuningServices(&svc);
        }
        return svc;
    }, py::return_value_policy::move)
    // QI-fold IADLXSystem2::GetMultimediaServices
        .def("GetMultimediaServices", [](py::object self) {
        IADLXSystem* sys = self.cast<IADLXSystem*>();
        IADLXSystem2Ptr system2;
        IADLXMultimediaServicesPtr svc;
        ADLX_RESULT res = sys->QueryInterface(IADLXSystem2::IID(), reinterpret_cast<void**>(&system2));
        if (ADLX_SUCCEEDED(res) && system2)
        {
            system2->GetMultimediaServices(&svc);
        }
        return svc;
    }, py::return_value_policy::move)
    // QI-fold IADLXSystem2::GetGPUAppsListChangedHandling
        .def("GetGPUAppsListChangedHandling", [](py::object self) {
        IADLXSystem* sys = self.cast<IADLXSystem*>();
        IADLXSystem2Ptr system2;
        IADLXGPUAppsListChangedHandlingPtr handling;
        ADLX_RESULT res = sys->QueryInterface(IADLXSystem2::IID(), reinterpret_cast<void**>(&system2));
        if (ADLX_SUCCEEDED(res) && system2)
        {
            system2->GetGPUAppsListChangedHandling(&handling);
        }
        return handling;
    }, py::return_value_policy::move)
    // QI-fold IADLXSystem3::GetVariableGraphicsMemory
        .def("GetVariableGraphicsMemory", [](py::object self) {
        IADLXSystem* sys = self.cast<IADLXSystem*>();
        IADLXSystem3Ptr system3;
        IADLXVariableGraphicsMemoryPtr vgm;
        ADLX_RESULT res = sys->QueryInterface(IADLXSystem3::IID(), reinterpret_cast<void**>(&system3));
        if (ADLX_SUCCEEDED(res) && system3)
        {
            system3->GetVariableGraphicsMemory(&vgm);
        }
        return vgm;
    }, py::return_value_policy::move);

    // IADLXSmartAccessMemory
    py::class_<IADLXSmartAccessMemory, IADLXInterface, PySmartAccessMemory, IADLXInterfacePtr_T<IADLXSmartAccessMemory>>(m, "IADLXSmartAccessMemory")
        .def("IsSupported", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXSmartAccessMemoryPtr sam = self.cast<IADLXSmartAccessMemory*>();
        adlx_bool supported = false;
        ADLX_RESULT ret = sam->IsSupported(&supported);
        if (ADLX_SUCCEEDED(ret))
            return supported;
        return py::none();
    })
        .def("IsEnabled", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXSmartAccessMemoryPtr sam = self.cast<IADLXSmartAccessMemory*>();
        adlx_bool enabled = false;
        ADLX_RESULT ret = sam->IsEnabled(&enabled);
        if (ADLX_SUCCEEDED(ret))
            return enabled;
        return py::none();
    })
        .def("SetEnabled", [](py::object self, adlx_bool enabled) {
        IADLXSmartAccessMemoryPtr sam = self.cast<IADLXSmartAccessMemory*>();
        return sam->SetEnabled(enabled);
    });

    // IADLXVariableGraphicsMemoryOption
    py::class_<IADLXVariableGraphicsMemoryOption, IADLXInterface, PyVariableGraphicsMemoryOption, IADLXInterfacePtr_T<IADLXVariableGraphicsMemoryOption>>(m, "IADLXVariableGraphicsMemoryOption")
        .def("Name", [](py::object self) -> std::variant<std::string, py::none> {
        IADLXVariableGraphicsMemoryOptionPtr opt = self.cast<IADLXVariableGraphicsMemoryOption*>();
        const char* name = nullptr;
        ADLX_RESULT ret = opt->Name(&name);
        if (ADLX_SUCCEEDED(ret) && name)
            return std::string(name);
        return py::none();
    })
        .def("Mode", [](py::object self) -> std::variant<ADLX_VARIABLE_GRAPHICS_MEMORY_MODE, py::none> {
        IADLXVariableGraphicsMemoryOptionPtr opt = self.cast<IADLXVariableGraphicsMemoryOption*>();
        ADLX_VARIABLE_GRAPHICS_MEMORY_MODE mode;
        ADLX_RESULT ret = opt->Mode(&mode);
        if (ADLX_SUCCEEDED(ret))
            return mode;
        return py::none();
    })
        .def("MemoryCarved", [](py::object self) -> std::variant<adlx_double, py::none> {
        IADLXVariableGraphicsMemoryOptionPtr opt = self.cast<IADLXVariableGraphicsMemoryOption*>();
        adlx_double memoryCarvedGb;
        ADLX_RESULT ret = opt->MemoryCarved(&memoryCarvedGb);
        if (ADLX_SUCCEEDED(ret))
            return memoryCarvedGb;
        return py::none();
    })
        .def("MemoryRemaining", [](py::object self) -> std::variant<adlx_double, py::none> {
        IADLXVariableGraphicsMemoryOptionPtr opt = self.cast<IADLXVariableGraphicsMemoryOption*>();
        adlx_double memoryRemainingGb;
        ADLX_RESULT ret = opt->MemoryRemaining(&memoryRemainingGb);
        if (ADLX_SUCCEEDED(ret))
            return memoryRemainingGb;
        return py::none();
    });

    // IADLXVariableGraphicsMemoryOptionList
    py::class_<IADLXVariableGraphicsMemoryOptionList, IADLXList, PyVariableGraphicsMemoryOptionList, IADLXInterfacePtr_T<IADLXVariableGraphicsMemoryOptionList>>(m, "IADLXVariableGraphicsMemoryOptionList")
        .def("At", [](py::object self, adlx_uint location) {
        IADLXVariableGraphicsMemoryOptionListPtr list = self.cast<IADLXVariableGraphicsMemoryOptionList*>();
        IADLXVariableGraphicsMemoryOptionPtr item;
        list->At(location, &item);
        return item;
    }, py::return_value_policy::move)
        .def("Add_Back", [](py::object self, IADLXVariableGraphicsMemoryOptionPtr pItem) {
        IADLXVariableGraphicsMemoryOptionListPtr list = self.cast<IADLXVariableGraphicsMemoryOptionList*>();
        return list->Add_Back(pItem);
    });

    // IADLXVariableGraphicsMemory
    py::class_<IADLXVariableGraphicsMemory, IADLXInterface, PyVariableGraphicsMemory, IADLXInterfacePtr_T<IADLXVariableGraphicsMemory>>(m, "IADLXVariableGraphicsMemory")
        .def("IsSupported", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXVariableGraphicsMemoryPtr vgm = self.cast<IADLXVariableGraphicsMemory*>();
        adlx_bool supported = false;
        ADLX_RESULT ret = vgm->IsSupported(&supported);
        if (ADLX_SUCCEEDED(ret))
            return supported;
        return py::none();
    })
        .def("GetDefaultOption", [](py::object self) {
        IADLXVariableGraphicsMemoryPtr vgm = self.cast<IADLXVariableGraphicsMemory*>();
        IADLXVariableGraphicsMemoryOptionPtr opt;
        vgm->GetDefaultOption(&opt);
        return opt;
    }, py::return_value_policy::move)
        .def("GetOption", [](py::object self) {
        IADLXVariableGraphicsMemoryPtr vgm = self.cast<IADLXVariableGraphicsMemory*>();
        IADLXVariableGraphicsMemoryOptionPtr opt;
        vgm->GetOption(&opt);
        return opt;
    }, py::return_value_policy::move)
        .def("GetAvailableOptions", [](py::object self) {
        IADLXVariableGraphicsMemoryPtr vgm = self.cast<IADLXVariableGraphicsMemory*>();
        IADLXVariableGraphicsMemoryOptionListPtr opts;
        vgm->GetAvailableOptions(&opts);
        return opts;
    }, py::return_value_policy::move)
        .def("SetOption", [](py::object self, IADLXVariableGraphicsMemoryOptionPtr opt) {
        IADLXVariableGraphicsMemoryPtr vgm = self.cast<IADLXVariableGraphicsMemory*>();
        return vgm->SetOption(opt);
    });

    // IADLXChangedEvent
    py::class_<IADLXChangedEvent, IADLXInterface, PyChangedEvent, IADLXInterfacePtr_T<IADLXChangedEvent>>(m, "IADLXChangedEvent")
    //.def(py::init<>())
    .def("GetOrigin", [](py::object self) {
    IADLXChangedEventPtr change_event = self.cast<IADLXChangedEvent*>();
    ADLX_SYNC_ORIGIN origin = change_event->GetOrigin();
    return origin;
    })
    .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
    IADLXChangedEventPtr change_event = self.cast<IADLXChangedEvent*>();
    IADLXChangedEventPtr ppInterface = nullptr;
    change_event->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
    return ppInterface;
    }, py::return_value_policy::move);
}
