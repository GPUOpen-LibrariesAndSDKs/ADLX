//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

#include "bind_common.h"

void bind_gpu(py::module_& m)
{
    // Callback for GPUsEventListener
    py::class_<PyGPUsEventListenerCallback>(m, "PyGPUsEventListenerCallback")
        .def(py::init<>())
        .def_readwrite("call", &PyGPUsEventListenerCallback::m_call);

        // IADLXApplication
    py::class_<IADLXApplication, IADLXInterface, PyApplication, IADLXInterfacePtr_T<IADLXApplication>>(m, "IADLXApplication")
        //.def(py::init<>())
        .def("ProcessID", [](py::object self) {
        IADLXApplication* application = self.cast<IADLXApplication*>();
        adlx_ulong pid = 0;
        application->ProcessID(&pid);
        return pid;
    })
        .def("Name", [](py::object self) {
        IADLXApplication* application = self.cast<IADLXApplication*>();
        const wchar_t* appName = nullptr;
        application->Name(&appName);
        // Convert wide string to UTF-8
        return py::str(wlocal_to_utf8(appName));
    })
        .def("FullPath", [](py::object self) {
        IADLXApplication* application = self.cast<IADLXApplication*>();
        const wchar_t* appPath = nullptr;
        application->FullPath(&appPath);
        // Convert wide string to UTF-8
        return py::str(wlocal_to_utf8(appPath));
    })
        .def("GPUDependencyType", [](py::object self) {
        IADLXApplication* application = self.cast<IADLXApplication*>();
        ADLX_APP_GPU_DEPENDENCY gpuDependency = APP_GPU_UNKNOWN;
        application->GPUDependencyType(&gpuDependency);
        return gpuDependency;
    })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXApplication* application = self.cast<IADLXApplication*>();
        IADLXApplicationPtr ppInterface = nullptr;
        application->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
    }, py::return_value_policy::move);

    // ADLX_LUID
    py::class_<ADLX_LUID>(m, "ADLX_LUID")
        .def(py::init<>())
        .def_readwrite("lowPart", &ADLX_LUID::lowPart)
        .def_readwrite("highPart", &ADLX_LUID::highPart);

    // GPU
    py::class_<IADLXGPU, IADLXInterface, PyGPU, IADLXInterfacePtr_T<IADLXGPU>>(m, "IADLXGPU")
        //.def(py::init<>())
        .def("VendorId", [](py::object self) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        const char* vendorid = nullptr;
        gpu->VendorId(&vendorid);
        return py::str(local_to_utf8(vendorid));
    })
        .def("ASICFamilyType", [](py::object self) -> std::variant<ADLX_ASIC_FAMILY_TYPE, py::none> {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        ADLX_ASIC_FAMILY_TYPE asicFamilyType;
        ADLX_RESULT ret = gpu->ASICFamilyType(&asicFamilyType);
        if (ADLX_SUCCEEDED(ret))
            return asicFamilyType;
        return py::none();
    })
        .def("Type", [](py::object self) -> std::variant<ADLX_GPU_TYPE, py::none> {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        ADLX_GPU_TYPE gpuType;
        ADLX_RESULT ret = gpu->Type(&gpuType);
        if (ADLX_SUCCEEDED(ret))
            return gpuType;
        return py::none();
    })
        .def("IsExternal", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        adlx_bool isexternal;
        ADLX_RESULT ret = gpu->IsExternal(&isexternal);
        if (ADLX_SUCCEEDED(ret))
            return isexternal;
        return py::none();
    })
        .def("Name", [](py::object self) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        const char* name = nullptr;
        gpu->Name(&name);
        return py::str(local_to_utf8(name));
    })
        .def("DriverPath", [](py::object self) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        const char* driverpath = nullptr;
        gpu->DriverPath(&driverpath);
        return py::str(local_to_utf8(driverpath));
    })
        .def("PNPString", [](py::object self) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        const char* pnpstring = nullptr;
        gpu->PNPString(&pnpstring);
        return py::str(local_to_utf8(pnpstring));
    })
        .def("HasDesktops", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        adlx_bool hasdesktops;
        ADLX_RESULT ret = gpu->HasDesktops(&hasdesktops);
        if (ADLX_SUCCEEDED(ret))
            return hasdesktops;
        return py::none();
    })
        .def("TotalVRAM", [](py::object self) -> std::variant<adlx_uint, py::none> {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        adlx_uint vramb;
        ADLX_RESULT ret = gpu->TotalVRAM(&vramb);
        if (ADLX_SUCCEEDED(ret))
            return vramb;
        return py::none();
    })
        .def("VRAMType", [](py::object self) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        const char* type = nullptr;
        gpu->VRAMType(&type);
        return py::str(local_to_utf8(type));
    })
        .def("BIOSInfo", [](py::object self) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        const char* partnumber = nullptr;
        const char* version = nullptr;
        const char* date = nullptr;
        gpu->BIOSInfo(&partnumber, &version, &date);
        return std::tuple<std::string, std::string, std::string>(local_to_utf8(partnumber), local_to_utf8(version), local_to_utf8(date));
    })
        .def("DeviceId", [](py::object self) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        const char* deviceid = nullptr;
        gpu->DeviceId(&deviceid);
        return py::str(local_to_utf8(deviceid));
    })
        .def("RevisionId", [](py::object self) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        const char* revisionid = nullptr;
        gpu->RevisionId(&revisionid);
        return py::str(local_to_utf8(revisionid));
    })
        .def("SubSystemId", [](py::object self) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        const char* subsystemid = nullptr;
        gpu->SubSystemId(&subsystemid);
        return py::str(local_to_utf8(subsystemid));
    })
        .def("SubSystemVendorId", [](py::object self) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        const char* subsystemvendorid = nullptr;
        gpu->SubSystemVendorId(&subsystemvendorid);
        return py::str(local_to_utf8(subsystemvendorid));
    })
        .def("UniqueId", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        adlx_int uniqueid;
        ADLX_RESULT ret = gpu->UniqueId(&uniqueid);
        if (ADLX_SUCCEEDED(ret))
            return uniqueid;
        return py::none();
    })
        .def("PCIBusType", [](py::object self) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        ADLX_PCI_BUS_TYPE busType = ADLX_PCI_BUS_TYPE::UNDEFINED;
        IADLXGPU1Ptr gpu1(gpu);
        if (gpu1)
        {
            gpu1->PCIBusType(&busType);
        }
        return busType;
    })
        .def("PCIBusLaneWidth", [](py::object self) -> std::variant<adlx_uint, py::none> {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        adlx_uint laneWidth = 0;
        IADLXGPU1Ptr gpu1(gpu);
        if (gpu1)
        {
            ADLX_RESULT ret = gpu1->PCIBusLaneWidth(&laneWidth);
            if (ADLX_SUCCEEDED(ret))
                return laneWidth;
        }
        return py::none();
    })
        .def("MultiGPUMode", [](py::object self) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        ADLX_MGPU_MODE mode = ADLX_MGPU_MODE::MGPU_NONE;
        IADLXGPU1Ptr gpu1(gpu);
        if (gpu1)
        {
            gpu1->MultiGPUMode(&mode);
        }
        return mode;
    })
        .def("ProductName", [](py::object self) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        const char* productName = nullptr;
        IADLXGPU1Ptr gpu1(gpu);
        if (gpu1)
        {
            gpu1->ProductName(&productName);
            return py::str(local_to_utf8(productName));
        }
        else
        {
            return py::str();
        }
    })
        .def("IsSupportedApplicationList", [](py::object self) {
        adlx_bool supported = false;
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        IADLXGPU2Ptr gpu2(gpu);
        if (gpu2)
        {
            gpu2->IsSupportedApplicationList(&supported);
        }
        return supported;
    })
        .def("GetApplications", [](py::object self) {
            IADLXGPU* gpu = self.cast<IADLXGPU*>();
            IADLXApplicationListPtr applicationList = nullptr;
            std::vector<IADLXApplicationPtr> list;
            IADLXGPU2Ptr gpu2(gpu);
            if (gpu2)
            {
                gpu2->GetApplications(&applicationList);
                if (applicationList)
                {
                    for (adlx_uint s = applicationList->Begin(); s != applicationList->End(); s++) {
                        IADLXApplicationPtr item;
                        applicationList->At(s, &item);
                        list.emplace_back(std::move(item));
                    }
                }
            }
        return list;
    }, py::return_value_policy::move)
        .def("AMDSoftwareReleaseDate", [](py::object self) {
        adlx_uint year = 0, month = 0, day = 0;
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        IADLXGPU2Ptr gpu2(gpu);
        if (gpu2)
        {
            gpu2->AMDSoftwareReleaseDate(&year, &month, &day);
        }
        return std::tuple(year, month, day);
    })
        .def("AMDSoftwareEdition", [](py::object self) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        IADLXGPU2Ptr gpu2(gpu);
        if (gpu2)
        {
            const char* version = nullptr;
            gpu2->AMDSoftwareEdition(&version);
            return py::str(local_to_utf8(version));
        }
        return py::str();
    })
        .def("AMDSoftwareVersion", [](py::object self) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        IADLXGPU2Ptr gpu2(gpu);
        if (gpu2)
        {
            const char* version = nullptr;
            gpu2->AMDSoftwareVersion(&version);
            return py::str(local_to_utf8(version));
        }
        return py::str();
    })
        .def("DriverVersion", [](py::object self) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        IADLXGPU2Ptr gpu2(gpu);
        if (gpu2)
        {
            const char* version = nullptr;
            gpu2->DriverVersion(&version);
            return py::str(local_to_utf8(version));
        }
        return py::str();
    })
        .def("AMDWindowsDriverVersion", [](py::object self) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        IADLXGPU2Ptr gpu2(gpu);
        if (gpu2)
        {
            const char* version = nullptr;
            gpu2->AMDWindowsDriverVersion(&version);
            return py::str(local_to_utf8(version));
        }
        return py::str();
    })
        .def("LUID", [](py::object self) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        IADLXGPU2Ptr gpu2(gpu);
        ADLX_LUID luid = {};
        if (gpu2)
        {
            gpu2->LUID(&luid);
        }
        return luid;
    })
        // IADLXGPU2
        .def("IsPowerOff", [](py::object self) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        IADLXGPU2Ptr gpu2(gpu);
        if (gpu2)
        {
            adlx_bool state = false;
            gpu2->IsPowerOff(&state);
            return state;
        }
        return adlx_bool(false);
    })
        .def("PowerOn", [](py::object self) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        IADLXGPU2Ptr gpu2(gpu);
        if (gpu2)
        {
            return gpu2->PowerOn();
        }
        return ADLX_RESULT(ADLX_FAIL);
    })
        .def("AbortPowerOff", [](py::object self) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        IADLXGPU2Ptr gpu2(gpu);
        if (gpu2)
        {
            return gpu2->AbortPowerOff();
        }
        return ADLX_RESULT(ADLX_FAIL);
    })

        // IADLXGPU3
        .def("MicroArchitecture", [](py::object self) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        IADLXGPU3Ptr gpu3(gpu);
        if (gpu3)
        {
            const char* microArchitecture = nullptr;
            gpu3->MicroArchitecture(&microArchitecture);
            return py::str(local_to_utf8(microArchitecture ? microArchitecture : ""));
        }
        return py::str();
    })
        .def("HighestVRAMBandwidth", [](py::object self) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        IADLXGPU3Ptr gpu3(gpu);
        adlx_uint data = 0;
        if (gpu3)
        {
            gpu3->HighestVRAMBandwidth(&data);
        }
        return data;
    })
        .def("InvisibleVRAM", [](py::object self) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        IADLXGPU3Ptr gpu3(gpu);
        adlx_uint data = 0;
        if (gpu3)
        {
            gpu3->InvisibleVRAM(&data);
        }
        return data;
    })
        .def("VisibleVRAM", [](py::object self) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        IADLXGPU3Ptr gpu3(gpu);
        adlx_uint data = 0;
        if (gpu3)
        {
            gpu3->VisibleVRAM(&data);
        }
        return data;
    })
        .def("VRAMVendorRevId", [](py::object self) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        IADLXGPU3Ptr gpu3(gpu);
        adlx_uint data = 0;
        if (gpu3)
        {
            gpu3->VRAMVendorRevId(&data);
        }
        return data;
    })
        .def("VRAMBandwidth", [](py::object self) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        IADLXGPU3Ptr gpu3(gpu);
        adlx_uint data = 0;
        if (gpu3)
        {
            gpu3->VRAMBandwidth(&data);
        }
        return data;
    })
        .def("VRAMBitRate", [](py::object self) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        IADLXGPU3Ptr gpu3(gpu);
        adlx_uint data = 0;
        if (gpu3)
        {
            gpu3->VRAMBitRate(&data);
        }
        return data;
    })
        .def("IsSupportedStressTest", [](py::object self) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        IADLXGPU3Ptr gpu3(gpu);
        if (gpu3)
        {
            adlx_bool supported = false;
            gpu3->IsSupportedStressTest(&supported);
            return supported;
        }
        return adlx_bool(false);
    })
        // IADLXGPU2::StartPowerOff
        .def("StartPowerOff", [](py::object self, IADLXGPUConnectChangedListener* pListener, adlx_int timeout) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        IADLXGPU2Ptr gpu2(gpu);
        if (gpu2)
        {
            return gpu2->StartPowerOff(pListener, timeout);
        }
        return ADLX_RESULT(ADLX_FAIL);
    })
        // IADLXGPU3::StartStressTest
        .def("StartStressTest", [](py::object self, PyGPUStressTestFinishedListenerCallback* pListener, adlx_uint duration) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        IADLXGPU3Ptr gpu3(gpu);
        if (gpu3)
        {
            return gpu3->StartStressTest(pListener, duration);
        }
        return ADLX_RESULT(ADLX_FAIL);
    })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXGPU* gpu = self.cast<IADLXGPU*>();
        IADLXGPUPtr ppInterface = nullptr;
        gpu->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
    }, py::return_value_policy::move);

    // GPUList
        py::class_<IADLXGPUList, IADLXList, PyGPUList, IADLXInterfacePtr_T<IADLXGPUList>>(m, "IADLXGPUList")
        //.def(py::init<>())
        .def("Add_Back", [](py::object self, IADLXGPU* pItem) {
        IADLXGPUListPtr gpuList = self.cast<IADLXGPUList*>();
        ADLX_RESULT retGPUList = gpuList->Add_Back(pItem);
        return retGPUList;
        })
        .def("At", [](py::object self, const adlx_uint location) {
        IADLXGPUListPtr gpuList = self.cast<IADLXGPUList*>();
        IADLXGPUPtr ppItem;
        gpuList->At(location, &ppItem);
        return ppItem;
        });

    // IADLXGPUsChangedHandling
        py::class_<IADLXGPUsChangedHandling, IADLXInterface, PyGPUsChangedHandling, IADLXInterfacePtr_T<IADLXGPUsChangedHandling>>(m, "IADLXGPUsChangedHandling")
        .def("AddGPUsListEventListener", [](py::object self, py::object pyListener) {
        IADLXGPUsChangedHandlingPtr gpusChangedHandling = self.cast< IADLXGPUsChangedHandling*>();
        auto* callback = pyListener.cast<PyGPUsEventListenerCallback*>();
        IADLXGPUsEventListener* pListener = static_cast<IADLXGPUsEventListener*>(callback);
        ADLX_RESULT ret_add_gpus_list_event = gpusChangedHandling->AddGPUsListEventListener(pListener);
        return ret_add_gpus_list_event;
        })
        .def("RemoveGPUsListEventListener", [](py::object self, py::object pyListener) {
        IADLXGPUsChangedHandlingPtr gpusChangedHandling = self.cast< IADLXGPUsChangedHandling*>();
        auto* callback = pyListener.cast<PyGPUsEventListenerCallback*>();
        IADLXGPUsEventListener* pListener = static_cast<IADLXGPUsEventListener*>(callback);
        ADLX_RESULT ret_remove_gpus_list_event = gpusChangedHandling->RemoveGPUsListEventListener(pListener);
        return ret_remove_gpus_list_event;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXGPUsChangedHandlingPtr gpusChangedHandling = self.cast< IADLXGPUsChangedHandling*>();
        IADLXGPUsChangedHandlingPtr ppInterface = nullptr;
        gpusChangedHandling->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);

    // IADLXApplicationList
    py::class_<IADLXApplicationList, IADLXList, PyApplicationList, IADLXInterfacePtr_T<IADLXApplicationList>>(m, "IADLXApplicationList")
        .def("At", [](py::object self, const adlx_uint location) {
        IADLXApplicationListPtr appList = self.cast<IADLXApplicationList*>();
        IADLXApplicationPtr ppItem;
        appList->At(location, &ppItem);
        return ppItem;
        }, py::return_value_policy::move)
        .def("Add_Back", [](py::object self, IADLXApplication* pItem) {
        IADLXApplicationListPtr appList = self.cast<IADLXApplicationList*>();
        return appList->Add_Back(pItem);
        });

    // IADLXGPU2List
    py::class_<IADLXGPU2List, IADLXList, PyGPU2List, IADLXInterfacePtr_T<IADLXGPU2List>>(m, "IADLXGPU2List")
        .def("At", [](py::object self, const adlx_uint location) {
        IADLXGPU2ListPtr gpuList = self.cast<IADLXGPU2List*>();
        IADLXGPU2Ptr ppItem;
        gpuList->At(location, &ppItem);
        return ppItem;
        }, py::return_value_policy::move)
        .def("Add_Back", [](py::object self, IADLXGPU2* pItem) {
        IADLXGPU2ListPtr gpuList = self.cast<IADLXGPU2List*>();
        return gpuList->Add_Back(pItem);
        });

    // IADLXGPUAppsListChangedHandling
    py::class_<IADLXGPUAppsListChangedHandling, IADLXInterface, PyGPUAppsListChangedHandling, IADLXInterfacePtr_T<IADLXGPUAppsListChangedHandling>>(m, "IADLXGPUAppsListChangedHandling")
        .def("AddGPUAppsListEventListener", [](py::object self, PyGPUAppsListEventListenerCallback* pListener) {
        IADLXGPUAppsListChangedHandlingPtr handling = self.cast<IADLXGPUAppsListChangedHandling*>();
        return handling->AddGPUAppsListEventListener(pListener);
        })
        .def("RemoveGPUAppsListEventListener", [](py::object self, PyGPUAppsListEventListenerCallback* pListener) {
        IADLXGPUAppsListChangedHandlingPtr handling = self.cast<IADLXGPUAppsListChangedHandling*>();
        return handling->RemoveGPUAppsListEventListener(pListener);
        });

    // Callback for GPUAppsListEventListener
    py::class_<PyGPUAppsListEventListenerCallback>(m, "PyGPUAppsListEventListenerCallback")
        .def(py::init<>())
        .def_readwrite("call", &PyGPUAppsListEventListenerCallback::m_call);

    // Callback for GPUStressTestFinishedListener
    py::class_<PyGPUStressTestFinishedListenerCallback>(m, "PyGPUStressTestFinishedListenerCallback")
        .def(py::init<>())
        .def_readwrite("call", &PyGPUStressTestFinishedListenerCallback::m_call);
}
