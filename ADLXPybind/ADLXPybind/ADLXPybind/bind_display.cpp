//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

#include "bind_common.h"



void bind_display(py::module_& m)
{
    // displayService
    py::class_<IADLXDisplayServices, IADLXInterface, PyDisplayService, IADLXInterfacePtr_T<IADLXDisplayServices>>(m, "IADLXDisplayServices")
        .def(py::init<>())
        .def("Get3DLUT", [](py::object self, IADLXDisplay* pDisplay) {
        IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
        IADLXDisplay3DLUTPtr dis3DOLut = nullptr;
        disService->Get3DLUT(pDisplay, &dis3DOLut);
        return dis3DOLut;
    }, py::return_value_policy::move)
        .def("GetColorDepth", [](py::object self, IADLXDisplay* pDisplay) {
        IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
        IADLXDisplayColorDepthPtr ppColorDepth;
        disService->GetColorDepth(pDisplay, &ppColorDepth);
        return ppColorDepth;
    }, py::return_value_policy::move)
        .def("GetCustomColor", [](py::object self, IADLXDisplay* pDisplay) {
        IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
        IADLXDisplayCustomColorPtr ppCustomColor;
        disService->GetCustomColor(pDisplay, &ppCustomColor);
        return ppCustomColor;
    }, py::return_value_policy::move)
        .def("GetCustomResolution", [](py::object self, IADLXDisplay* pDisplay) {
        IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
        IADLXDisplayCustomResolutionPtr ppCustomRes;
        disService->GetCustomResolution(pDisplay, &ppCustomRes);
        return ppCustomRes;
    }, py::return_value_policy::move)
        .def("GetDisplayChangedHandling", [](py::object self) {
        IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
        IADLXDisplayChangedHandlingPtr handler = nullptr;
        disService->GetDisplayChangedHandling(&handler);
        return handler;
    }, py::return_value_policy::move)
        .def("GetDisplays", [](py::object self) {
        IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
        IADLXDisplayListPtr displayList = nullptr;
        disService->GetDisplays(&displayList);
        std::vector<IADLXDisplayPtr> list;
        if (displayList)
        {
            for (adlx_uint s = displayList->Begin(); s != displayList->End(); s++) {
                IADLXDisplayPtr item;
                displayList->At(s, &item);
                list.emplace_back(std::move(item));
            }
        }
        return list;
    }, py::return_value_policy::move)
        .def("GetFreeSync", [](py::object self, IADLXDisplay* pDisplay) {
        IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
        IADLXDisplayFreeSyncPtr displayFreeSync;
        disService->GetFreeSync(pDisplay, &displayFreeSync);
        return displayFreeSync;
    }, py::return_value_policy::move)
        .def("GetGPUScaling", [](py::object self, IADLXDisplay* pDisplay) {
        IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
        IADLXDisplayGPUScalingPtr gpuScaling;
        disService->GetGPUScaling(pDisplay, &gpuScaling);
        return gpuScaling;
    }, py::return_value_policy::move)
        .def("GetGamma", [](py::object self, IADLXDisplay* pDisplay) {
        IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
        IADLXDisplayGammaPtr diplayGamma;
        disService->GetGamma(pDisplay, &diplayGamma);
        return diplayGamma;
    }, py::return_value_policy::move)
        .def("GetGamut", [](py::object self, IADLXDisplay* pDisplay) {
        IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
        IADLXDisplayGamutPtr diplayGamut;
        disService->GetGamut(pDisplay, &diplayGamut);
        return diplayGamut;
    }, py::return_value_policy::move)
        .def("GetHDCP", [](py::object self, IADLXDisplay* pDisplay) {
        IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
        IADLXDisplayHDCPPtr diplayHDCPPtr;
        disService->GetHDCP(pDisplay, &diplayHDCPPtr);
        return diplayHDCPPtr;
    }, py::return_value_policy::move)
        .def("GetIntegerScaling", [](py::object self, IADLXDisplay* pDisplay) {
        IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
        IADLXDisplayIntegerScalingPtr diplayIntegerScaling;
        disService->GetIntegerScaling(pDisplay, &diplayIntegerScaling);
        return diplayIntegerScaling;
    }, py::return_value_policy::move)
        .def("GetNumberOfDisplays", [](py::object self) -> std::variant<adlx_uint, py::none> {
        IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
        adlx_uint num;
        ADLX_RESULT ret = disService->GetNumberOfDisplays(&num);
        if (ADLX_SUCCEEDED(ret))
            return num;
        return py::none();
    })
        .def("GetPixelFormat", [](py::object self, IADLXDisplay* pDisplay) {
        IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
        IADLXDisplayPixelFormatPtr diplayPixelFormat;
        disService->GetPixelFormat(pDisplay, &diplayPixelFormat);
        return diplayPixelFormat;
    }, py::return_value_policy::move)
        .def("GetScalingMode", [](py::object self, IADLXDisplay* pDisplay) {
        IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
        IADLXDisplayScalingModePtr diplayScalingMode;
        disService->GetScalingMode(pDisplay, &diplayScalingMode);
        return diplayScalingMode;
    }, py::return_value_policy::move)
        .def("GetVariBright", [](py::object self, IADLXDisplay* pDisplay) {
        IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
        IADLXDisplayVariBrightPtr diplayVariBright;
        disService->GetVariBright(pDisplay, &diplayVariBright);
        return diplayVariBright;
    }, py::return_value_policy::move)
        .def("GetVirtualSuperResolution", [](py::object self, IADLXDisplay* pDisplay) {
        IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
        IADLXDisplayVSRPtr diplayVSR;
        disService->GetVirtualSuperResolution(pDisplay, &diplayVSR);
        return diplayVSR;
    }, py::return_value_policy::move)
        .def("GetDisplayBlanking", [](py::object self, IADLXDisplay* pDisplay) {
        IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
        IADLXDisplayBlankingPtr diplayBlanking;
        IADLXDisplayServices1Ptr disService1(disService);
        if (disService1)
        {
            disService1->GetDisplayBlanking(pDisplay, &diplayBlanking);
        }
        return diplayBlanking;
    }, py::return_value_policy::move)
        // IADLXDisplayServices2
        .def("GetDisplayConnectivityExperience", [](py::object self, IADLXDisplay* pDisplay) {
        IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
        IADLXDisplayServices2Ptr disService2(disService);
        IADLXDisplayConnectivityExperiencePtr displayConnectivityExperience;
        if (disService2)
        {
            disService2->GetDisplayConnectivityExperience(pDisplay, &displayConnectivityExperience);
        }
        return displayConnectivityExperience;
    }, py::return_value_policy::move)
        // IADLXDisplayServices3
        .def("GetDynamicRefreshRateControl", [](py::object self, IADLXDisplay* pDisplay) {
        IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
        IADLXDisplayServices3Ptr disService3(disService);
        IADLXDisplayDynamicRefreshRateControlPtr displayDRRC;
        if (disService3)
        {
            disService3->GetDynamicRefreshRateControl(pDisplay, &displayDRRC);
        }
        return displayDRRC;
    }, py::return_value_policy::move)
        .def("GetFreeSyncColorAccuracy", [](py::object self, IADLXDisplay* pDisplay) {
        IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
        IADLXDisplayServices3Ptr disService3(disService);
        IADLXDisplayFreeSyncColorAccuracyPtr displayFSCA;
        if (disService3)
        {
            disService3->GetFreeSyncColorAccuracy(pDisplay, &displayFSCA);
        }
        return displayFSCA;
    }, py::return_value_policy::move)
    .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
        IADLXDisplayServicesPtr ppInterface = nullptr;
        disService->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
    }, py::return_value_policy::move)
    // Custom methods
        .def("GetDisplaysListRaw", [](py::object self) {
        IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
        IADLXDisplayListPtr displayList = nullptr;
        disService->GetDisplays(&displayList);
        return displayList;
    }, py::return_value_policy::move);

    // Callback for 3DLUTChangedListenerCallback
    py::class_<PyDisplay3DLUTChangedListenerCallback>(m, "PyDisplay3DLUTChangedListenerCallback")
        .def(py::init<>())
        .def_readwrite("call", &PyDisplay3DLUTChangedListenerCallback::m_call);

    // Display change handler
    py::class_<IADLXDisplayChangedHandling, IADLXInterface, PyDisplayChangeHandler, IADLXInterfacePtr_T<IADLXDisplayChangedHandling>>(m, "IADLXDisplayChangedHandling")
        .def(py::init<>())
        .def("AddDisplayListEventListener", [](py::object self, PyDisplayListChangedListenerCallback* call) {
            IADLXDisplayChangedHandling *handler = self.cast<IADLXDisplayChangedHandling*>();
            return handler->AddDisplayListEventListener(call);
        })
        .def("RemoveDisplayListEventListener", [](py::object self, PyDisplayListChangedListenerCallback* call) {
            IADLXDisplayChangedHandling *handler = self.cast<IADLXDisplayChangedHandling*>();
            return handler->RemoveDisplayListEventListener(call);
        })
        .def("AddDisplay3DLUTEventListener", [](py::object self, PyDisplay3DLUTChangedListenerCallback* call) {
            IADLXDisplayChangedHandling* handler = self.cast<IADLXDisplayChangedHandling*>();
            return handler->AddDisplay3DLUTEventListener(call);
        })
        .def("RemoveDisplay3DLUTEventListener", [](py::object self, PyDisplay3DLUTChangedListenerCallback* call) {
            IADLXDisplayChangedHandling* handler = self.cast<IADLXDisplayChangedHandling*>();
            return handler->RemoveDisplay3DLUTEventListener(call);
        })
        .def("AddDisplayGamutEventListener", [](py::object self, PyDisplayGamutChangedListenerCallback* call) {
            IADLXDisplayChangedHandling* handler = self.cast<IADLXDisplayChangedHandling*>();
            return handler->AddDisplayGamutEventListener(call);
        })
        .def("RemoveDisplayGamutEventListener", [](py::object self, PyDisplayGamutChangedListenerCallback* call) {
            IADLXDisplayChangedHandling* handler = self.cast<IADLXDisplayChangedHandling*>();
            return handler->RemoveDisplayGamutEventListener(call);
        })
        .def("AddDisplayGammaEventListener", [](py::object self, PyDisplayGammaChangedListenerCallback* call) {
        IADLXDisplayChangedHandling* handler = self.cast<IADLXDisplayChangedHandling*>();
        return handler->AddDisplayGammaEventListener(call);
        })
        .def("RemoveDisplayGammaEventListener", [](py::object self, PyDisplayGammaChangedListenerCallback* call) {
        IADLXDisplayChangedHandling* handler = self.cast<IADLXDisplayChangedHandling*>();
        return handler->RemoveDisplayGammaEventListener(call);
        })
        .def("AddDisplaySettingsEventListener", [](py::object self, PyDisplaySettingsChangedListenerCallback* call) {
        IADLXDisplayChangedHandling* handler = self.cast<IADLXDisplayChangedHandling*>();
        return handler->AddDisplaySettingsEventListener(call);
        })
        .def("RemoveDisplaySettingsEventListener", [](py::object self, PyDisplaySettingsChangedListenerCallback* call) {
        IADLXDisplayChangedHandling* handler = self.cast<IADLXDisplayChangedHandling*>();
        return handler->RemoveDisplaySettingsEventListener(call);
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXDisplayChangedHandling* handler = self.cast<IADLXDisplayChangedHandling*>();
        IADLXDisplayChangedHandlingPtr ppInterface = nullptr;
        handler->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


    // Callback for displaylist
    py::class_<PyDisplayListChangedListenerCallback>(m, "PyDisplayListChangedListenerCallback")
        .def(py::init<>())
        .def_readwrite("call", &PyDisplayListChangedListenerCallback::m_call);

        // Callback for DisplayGamutChangedListener
    py::class_<PyDisplayGamutChangedListenerCallback>(m, "PyDisplayGamutChangedListenerCallback")
        .def(py::init<>())
        .def_readwrite("call", &PyDisplayGamutChangedListenerCallback::m_call);


    // Callback for DisplayGammaChangedListener
    py::class_<PyDisplayGammaChangedListenerCallback>(m, "PyDisplayGammaChangedListenerCallback")
        .def(py::init<>())
        .def_readwrite("call", &PyDisplayGammaChangedListenerCallback::m_call);


    // Callback for DisplaySettingsChangedListener
    py::class_<PyDisplaySettingsChangedListenerCallback>(m, "PyDisplaySettingsChangedListenerCallback")
        .def(py::init<>())
        .def_readwrite("call", &PyDisplaySettingsChangedListenerCallback::m_call);

    // Display
        py::class_<IADLXDisplay, IADLXInterface, PyDisplay, IADLXInterfacePtr_T<IADLXDisplay>>(m, "IADLXDisplay")
        .def(py::init<>())
        .def("Name", [](py::object self) {
        IADLXDisplay* display = self.cast<IADLXDisplay*>();
        const char* name = nullptr;
        display->Name(&name);
        return py::str(local_to_utf8(name));
        })
        .def("DisplayType", [](py::object self) -> std::variant<ADLX_DISPLAY_TYPE, py::none> {
        IADLXDisplay* display = self.cast<IADLXDisplay*>();
        ADLX_DISPLAY_TYPE type;
        ADLX_RESULT ret = display->DisplayType(&type);
        if (ADLX_SUCCEEDED(ret))
            return type;
        return py::none();
        })
        .def("ConnectorType", [](py::object self) -> std::variant<ADLX_DISPLAY_CONNECTOR_TYPE, py::none> {
        IADLXDisplay* display = self.cast<IADLXDisplay*>();
        ADLX_DISPLAY_CONNECTOR_TYPE type;
        ADLX_RESULT ret = display->ConnectorType(&type);
        if (ADLX_SUCCEEDED(ret))
            return type;
        return py::none();
        })
        .def("ManufacturerID", [](py::object self) -> std::variant<adlx_uint, py::none> {
        IADLXDisplay* display = self.cast<IADLXDisplay*>();
        adlx_uint id;
        ADLX_RESULT ret = display->ManufacturerID(&id);
        if (ADLX_SUCCEEDED(ret))
            return id;
        return py::none();
        })
        .def("EDID", [](py::object self) {
        IADLXDisplay* display = self.cast<IADLXDisplay*>();
        const char* str = nullptr;
        display->EDID(&str);
        return str ? std::string(str) : std::string();
        })
        .def("NativeResolution", [](py::object self) {
        IADLXDisplay* display = self.cast<IADLXDisplay*>();
        adlx_int h, v;
        display->NativeResolution(&h, &v);
        return std::tuple<adlx_int, adlx_int>(h, v);
        })
        .def("RefreshRate", [](py::object self) -> std::variant<adlx_double, py::none> {
        IADLXDisplay* display = self.cast<IADLXDisplay*>();
        adlx_double value;
        ADLX_RESULT ret = display->RefreshRate(&value);
        if (ADLX_SUCCEEDED(ret))
            return value;
        return py::none();
        })
        .def("PixelClock", [](py::object self) -> std::variant<adlx_uint, py::none> {
        IADLXDisplay* display = self.cast<IADLXDisplay*>();
        adlx_uint value;
        ADLX_RESULT ret = display->PixelClock(&value);
        if (ADLX_SUCCEEDED(ret))
            return value;
        return py::none();
        })
        .def("ScanType", [](py::object self) -> std::variant<ADLX_DISPLAY_SCAN_TYPE, py::none> {
        IADLXDisplay* display = self.cast<IADLXDisplay*>();
        ADLX_DISPLAY_SCAN_TYPE type;
        ADLX_RESULT ret = display->ScanType(&type);
        if (ADLX_SUCCEEDED(ret))
            return type;
        return py::none();
        })
        .def("GetGPU", [](py::object self) {
        IADLXDisplay* display = self.cast<IADLXDisplay*>();
        IADLXGPUPtr xgpu = nullptr;
        display->GetGPU(&xgpu);
        return xgpu;
        }, py::return_value_policy::move)
        .def("UniqueId", [](py::object self) -> std::variant<adlx_size, py::none> {
        IADLXDisplay* display = self.cast<IADLXDisplay*>();
        adlx_size id;
        ADLX_RESULT ret = display->UniqueId(&id);
        if (ADLX_SUCCEEDED(ret))
            return id;
        return py::none();
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXDisplayPtr display = self.cast<IADLXDisplay*>();
        IADLXDisplayPtr ppInterface = nullptr;
        display->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


        //ADLX_CustomResolution
        py::class_<ADLX_CustomResolution>(m, "ADLX_CustomResolution")
        .def(py::init<>())
        .def_readwrite("resWidth", &ADLX_CustomResolution::resWidth)
        .def_readwrite("resHeight", &ADLX_CustomResolution::resHeight)
        .def_readwrite("refreshRate", &ADLX_CustomResolution::refreshRate)
        .def_readwrite("presentation", &ADLX_CustomResolution::presentation)
        .def_readwrite("timingStandard", &ADLX_CustomResolution::timingStandard)
        .def_readwrite("GPixelClock", &ADLX_CustomResolution::GPixelClock)
        .def_readwrite("detailedTiming", &ADLX_CustomResolution::detailedTiming);

        py::class_<ADLX_TimingInfo >(m, "ADLX_TimingInfo")
        .def(py::init<>())
        .def_readwrite("timingFlags", &ADLX_TimingInfo::timingFlags)
        .def_readwrite("hTotal", &ADLX_TimingInfo::hTotal)
        .def_readwrite("vTotal", &ADLX_TimingInfo::vTotal)

        .def_readwrite("hDisplay", &ADLX_TimingInfo::hDisplay)
        .def_readwrite("vDisplay", &ADLX_TimingInfo::vDisplay)

        .def_readwrite("hFrontPorch", &ADLX_TimingInfo::hFrontPorch)
        .def_readwrite("vFrontPorch", &ADLX_TimingInfo::vFrontPorch)

        .def_readwrite("hSyncWidth", &ADLX_TimingInfo::hSyncWidth)
        .def_readwrite("vSyncWidth", &ADLX_TimingInfo::vSyncWidth)

        .def_readwrite("hPolarity", &ADLX_TimingInfo::hPolarity)
        .def_readwrite("vPolarity", &ADLX_TimingInfo::vPolarity);


        // DisplayResolution
        py::class_<IADLXDisplayResolution, IADLXInterface, PyDisplayResolution, IADLXInterfacePtr_T<IADLXDisplayResolution>>(m, "IADLXDisplayResolution")
        .def("GetValue", [](py::object self) -> std::variant<ADLX_CustomResolution, py::none> {
        IADLXDisplayResolutionPtr displayResolution = self.cast<IADLXDisplayResolution*>();
        ADLX_CustomResolution customResolution;
        ADLX_RESULT ret = displayResolution->GetValue(&customResolution);
        if (ADLX_SUCCEEDED(ret))
            return customResolution;
        return py::none();
        })
        .def("SetValue", [](py::object self, ADLX_CustomResolution customResolution){
        IADLXDisplayResolutionPtr displayResolution = self.cast<IADLXDisplayResolution*>();
        ADLX_RESULT retSetValue = displayResolution->SetValue(customResolution);
        return retSetValue;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXDisplayResolutionPtr displayResolution = self.cast<IADLXDisplayResolution*>();
        IADLXDisplayResolutionPtr ppInterface = nullptr;
        displayResolution->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


        // Display3DLUT
        py::class_<IADLXDisplay3DLUT, IADLXInterface, PyDisplay3DLUT, IADLXInterfacePtr_T<IADLXDisplay3DLUT>>(m, "IADLXDisplay3DLUT")
        //.def(py::init<>())
        .def("ClearUser3DLUT", [](py::object self) {
        IADLXDisplay3DLUT* display3DLut = self.cast<IADLXDisplay3DLUT*>();
        ADLX_RESULT retClearUser3DLut = display3DLut->ClearUser3DLUT();
        return retClearUser3DLut;
        })
        .def("GetAllUser3DLUT", [](py::object self) {
        IADLXDisplay3DLUT* display3DLut = self.cast<IADLXDisplay3DLUT*>();
        ADLX_3DLUT_TRANSFER_FUNCTION transferFunction;
        ADLX_3DLUT_COLORSPACE colorSpace;
        adlx_int pointsNumber;
        ADLX_3DLUT_Data data;
        display3DLut->GetAllUser3DLUT(&transferFunction, &colorSpace, &pointsNumber, &data);
                    
        adlx_uint16 red = data.data->red;
        adlx_uint16 green = data.data->green;
        adlx_uint16 blue = data.data->blue;

        py::dict data_py;
        
        data_py["red"] = red;
        data_py["green"] = green;
        data_py["blue"] = blue;

        py::dict dict;

        dict["transferFunction"] = transferFunction;
        dict["colorSpace"] = colorSpace;
        dict["pointsNumber"] = pointsNumber;
        dict["data"] = data_py;

        return dict;
        })
        .def("GetHDRUser3DLUT", [](py::object self) {
        IADLXDisplay3DLUT* display3DLut = self.cast<IADLXDisplay3DLUT*>();
        ADLX_3DLUT_TRANSFER_FUNCTION transferFunction;
        ADLX_3DLUT_COLORSPACE colorSpace;
        adlx_int pointsNumber;
        ADLX_3DLUT_Data data;
        display3DLut->GetHDRUser3DLUT(&transferFunction, &colorSpace, &pointsNumber, &data);
        adlx_uint16 red = data.data->red;
        adlx_uint16 green = data.data->green;
        adlx_uint16 blue = data.data->blue;

        py::dict data_py;

        data_py["red"] = red;
        data_py["green"] = green;
        data_py["blue"] = blue;

        py::dict dict;

        dict["transferFunction"] = transferFunction;
        dict["colorSpace"] = colorSpace;
        dict["pointsNumber"] = pointsNumber;
        dict["data"] = data_py;

        return dict;
        })
        .def("GetSCEDynamicContrast", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXDisplay3DLUT* display3DLut = self.cast<IADLXDisplay3DLUT*>();
        adlx_int contrast;
        ADLX_RESULT ret = display3DLut->GetSCEDynamicContrast(&contrast);
        if (ADLX_SUCCEEDED(ret))
            return contrast;
        return py::none();
        })
        .def("GetSCEDynamicContrastRange", [](py::object self) {
        IADLXDisplay3DLUT* display3DLut = self.cast<IADLXDisplay3DLUT*>();
        ADLX_IntRange range;
        display3DLut->GetSCEDynamicContrastRange(&range);
        py::dict dict;
        dict["maxValue"] = range.maxValue;
        dict["minValue"] = range.minValue;
        dict["step"] = range.step;
        return dict;
        })
        .def("GetSDRUser3DLUT", [](py::object self) {
        IADLXDisplay3DLUT* display3DLut = self.cast<IADLXDisplay3DLUT*>();
        ADLX_3DLUT_TRANSFER_FUNCTION transferFunction;
        ADLX_3DLUT_COLORSPACE colorSpace;
        adlx_int pointsNumber;
        ADLX_3DLUT_Data data;
        display3DLut->GetSDRUser3DLUT(&transferFunction, &colorSpace, &pointsNumber, &data);
        adlx_uint16 red = data.data->red;
        adlx_uint16 green = data.data->green;
        adlx_uint16 blue = data.data->blue;

        py::dict data_py;

        data_py["red"] = red;
        data_py["green"] = green;
        data_py["blue"] = blue;

        py::dict dict;

        dict["transferFunction"] = transferFunction;
        dict["colorSpace"] = colorSpace;
        dict["pointsNumber"] = pointsNumber;
        dict["data"] = data_py;

        return dict;
        })
        .def("GetUser3DLUTIndex", [](py::object self, adlx_int lutSize, const ADLX_UINT16_RGB* rgbCoordinate) -> std::variant<adlx_int, py::none> {
        IADLXDisplay3DLUT* display3DLut = self.cast<IADLXDisplay3DLUT*>();
        adlx_int index;
        ADLX_RESULT ret = display3DLut->GetUser3DLUTIndex(lutSize, rgbCoordinate, &index);
        if (ADLX_SUCCEEDED(ret))
            return index;
        return py::none();
        })
        .def("IsCurrentSCEDisabled", [](py::object self) {
        IADLXDisplay3DLUT* display3DLut = self.cast<IADLXDisplay3DLUT*>();
        adlx_bool sceDisabled = false;
        display3DLut->IsCurrentSCEDisabled(&sceDisabled);
        return sceDisabled;
        })
        .def("IsCurrentSCEDynamicContrast", [](py::object self) {
        IADLXDisplay3DLUT* display3DLut = self.cast<IADLXDisplay3DLUT*>();
        adlx_bool dynamicContrast = false;
        display3DLut->IsCurrentSCEDynamicContrast(&dynamicContrast);
        return dynamicContrast;
        })
        .def("IsCurrentSCEVividGaming", [](py::object self) {
        IADLXDisplay3DLUT* display3DLut = self.cast<IADLXDisplay3DLUT*>();
        adlx_bool vividGaming = false;
        display3DLut->IsCurrentSCEVividGaming(&vividGaming);
        return vividGaming;
        })
        .def("IsSupportedSCE", [](py::object self) {
        IADLXDisplay3DLUT* display3DLut = self.cast<IADLXDisplay3DLUT*>();
        adlx_bool supported = false;
        display3DLut->IsSupportedSCE(&supported);
        return supported;
        })
        .def("IsSupportedSCEDynamicContrast", [](py::object self) {
        IADLXDisplay3DLUT* display3DLut = self.cast<IADLXDisplay3DLUT*>();
        adlx_bool supported = false;
        display3DLut->IsSupportedSCEDynamicContrast(&supported);
        return supported;
        })
        .def("IsSupportedSCEVividGaming", [](py::object self) {
        IADLXDisplay3DLUT* display3DLut = self.cast<IADLXDisplay3DLUT*>();
        adlx_bool supported = false;
        display3DLut->IsSupportedSCEVividGaming(&supported);
        return supported;
        })
        .def("IsSupportedUser3DLUT", [](py::object self) {
        IADLXDisplay3DLUT* display3DLut = self.cast<IADLXDisplay3DLUT*>();
        adlx_bool supported = false;
        display3DLut->IsSupportedUser3DLUT(&supported);
        return supported;
        })
        .def("SetAllUser3DLUT", [](py::object self, ADLX_3DLUT_TRANSFER_FUNCTION transferFunction, ADLX_3DLUT_COLORSPACE colorSpace, adlx_int pointsNumber, pybind11::dict py_dict) {
        IADLXDisplay3DLUT* display3DLut = self.cast<IADLXDisplay3DLUT*>();
        ADLX_3DLUT_Data data;

        for (auto item : py_dict)
        {	
            std::string py_key = pybind11::str(item.first);
            std::string py_value = pybind11::str(item.second);

            if (py_key == "red")
            {
                std::istringstream ss(py_value);
                ss >> data.data->red;
            }

            if (py_key == "green")
            {
                std::istringstream ss(py_value);
                ss >> data.data->green;
            }

            if (py_key == "blue")
            {
                std::istringstream ss(py_value);
                ss >> data.data->blue;
            }
        }		
        
        ADLX_RESULT retSetAllUser3DLUT = display3DLut->SetAllUser3DLUT(transferFunction, colorSpace, pointsNumber, &data);
        return retSetAllUser3DLUT;
        })
        .def("SetHDRUser3DLUT", [](py::object self, ADLX_3DLUT_TRANSFER_FUNCTION transferFunction, ADLX_3DLUT_COLORSPACE colorSpace, adlx_int pointsNumber, pybind11::dict py_dict) {
        IADLXDisplay3DLUT* display3DLut = self.cast<IADLXDisplay3DLUT*>();
        ADLX_3DLUT_Data data;

        for (auto item : py_dict)
        {
            std::string py_key = pybind11::str(item.first);
            std::string py_value = pybind11::str(item.second);

            if (py_key == "red")
            {
                std::istringstream ss(py_value);
                ss >> data.data->red;
            }

            if (py_key == "green")
            {
                std::istringstream ss(py_value);
                ss >> data.data->green;
            }

            if (py_key == "blue")
            {
                std::istringstream ss(py_value);
                ss >> data.data->blue;
            }
        }
        ADLX_RESULT retSetHDRUser3DLUT = display3DLut->SetHDRUser3DLUT(transferFunction, colorSpace, pointsNumber, &data);
        return retSetHDRUser3DLUT;
        })
        .def("SetSCEDisabled", [](py::object self) {
        IADLXDisplay3DLUT* display3DLut = self.cast<IADLXDisplay3DLUT*>();
        ADLX_RESULT retSetSCEDisabled = display3DLut->SetSCEDisabled();
        return retSetSCEDisabled;
        })
        .def("SetSCEDynamicContrast", [](py::object self, adlx_int contrast) {
        IADLXDisplay3DLUT* display3DLut = self.cast<IADLXDisplay3DLUT*>();
        ADLX_RESULT retSetSCEDynamicContrast = display3DLut->SetSCEDynamicContrast(contrast);
        return retSetSCEDynamicContrast;
        })
        .def("SetSCEVividGaming", [](py::object self) {
        IADLXDisplay3DLUT* display3DLut = self.cast<IADLXDisplay3DLUT*>();
        ADLX_RESULT retSetSCEVividGaming = display3DLut->SetSCEVividGaming();
        return retSetSCEVividGaming;
        })
        .def("SetSDRUser3DLUT", [](py::object self, ADLX_3DLUT_TRANSFER_FUNCTION transferFunction, ADLX_3DLUT_COLORSPACE colorSpace, adlx_int pointsNumber, pybind11::dict py_dict) {
        IADLXDisplay3DLUT* display3DLut = self.cast<IADLXDisplay3DLUT*>();
        ADLX_3DLUT_Data data;

        for (auto item : py_dict)
        {
            std::string py_key = pybind11::str(item.first);
            std::string py_value = pybind11::str(item.second);

            if (py_key == "red")
            {
                std::istringstream ss(py_value);
                ss >> data.data->red;
            }

            if (py_key == "green")
            {
                std::istringstream ss(py_value);
                ss >> data.data->green;
            }

            if (py_key == "blue")
            {
                std::istringstream ss(py_value);
                ss >> data.data->blue;
            }
        }
        ADLX_RESULT retSetSDRUser3DLUT = display3DLut->SetSDRUser3DLUT(transferFunction, colorSpace, pointsNumber, &data);
        return retSetSDRUser3DLUT;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXDisplay3DLUTPtr display3DLut = self.cast<IADLXDisplay3DLUT*>();
        IADLXDisplay3DLUTPtr ppInterface = nullptr;
        display3DLut->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


        // DisplayColorDepth
        py::class_<IADLXDisplayColorDepth, IADLXInterface, PyDisplayColorDepth, IADLXInterfacePtr_T<IADLXDisplayColorDepth>>(m, "IADLXDisplayColorDepth")
        //.def(py::init<>())
        .def("GetValue", [](py::object self) -> std::variant<ADLX_COLOR_DEPTH, py::none> {
        IADLXDisplayColorDepthPtr displayColorDepth = self.cast<IADLXDisplayColorDepth*>();
        ADLX_COLOR_DEPTH currentColorDepth;
        ADLX_RESULT ret = displayColorDepth->GetValue(&currentColorDepth);
        if (ADLX_SUCCEEDED(ret))
            return currentColorDepth;
        return py::none();
        })
        .def("IsSupported", [](py::object self) {
        IADLXDisplayColorDepthPtr displayColorDepth = self.cast<IADLXDisplayColorDepth*>();
        adlx_bool supported = false;
        displayColorDepth->IsSupported(&supported);
        return supported;
        })
        .def("IsSupported", [](py::object self) {
        IADLXDisplayColorDepthPtr displayColorDepth = self.cast<IADLXDisplayColorDepth*>();
        adlx_bool supported = false;
        displayColorDepth->IsSupported(&supported);
        return supported;
        })
        .def("IsSupportedBPC_6", [](py::object self) {
        IADLXDisplayColorDepthPtr displayColorDepth = self.cast<IADLXDisplayColorDepth*>();
        adlx_bool supported = false;
        displayColorDepth->IsSupportedBPC_6(&supported);
        return supported;
        })
        .def("IsSupportedBPC_8", [](py::object self) {
        IADLXDisplayColorDepthPtr displayColorDepth = self.cast<IADLXDisplayColorDepth*>();
        adlx_bool supported = false;
        displayColorDepth->IsSupportedBPC_8(&supported);
        return supported;
        })
        .def("IsSupportedBPC_10", [](py::object self) {
        IADLXDisplayColorDepthPtr displayColorDepth = self.cast<IADLXDisplayColorDepth*>();
        adlx_bool supported = false;
        displayColorDepth->IsSupportedBPC_10(&supported);
        return supported;
        })
        .def("IsSupportedBPC_12", [](py::object self) {
        IADLXDisplayColorDepthPtr displayColorDepth = self.cast<IADLXDisplayColorDepth*>();
        adlx_bool supported = false;
        displayColorDepth->IsSupportedBPC_12(&supported);
        return supported;
        })
        .def("IsSupportedBPC_14", [](py::object self) {
        IADLXDisplayColorDepthPtr displayColorDepth = self.cast<IADLXDisplayColorDepth*>();
        adlx_bool supported = false;
        displayColorDepth->IsSupportedBPC_14(&supported);
        return supported;
        })
        .def("IsSupportedBPC_16", [](py::object self) {
        IADLXDisplayColorDepthPtr displayColorDepth = self.cast<IADLXDisplayColorDepth*>();
        adlx_bool supported = false;
        displayColorDepth->IsSupportedBPC_16(&supported);
        return supported;
        })
        .def("IsSupportedColorDepth", [](py::object self, ADLX_COLOR_DEPTH colorDepth) {
        IADLXDisplayColorDepthPtr displayColorDepth = self.cast<IADLXDisplayColorDepth*>();
        adlx_bool supported = false;
        displayColorDepth->IsSupportedColorDepth(colorDepth, &supported);
        return supported;
        })
        .def("SetValue", [](py::object self, ADLX_COLOR_DEPTH colorDepth) {
        IADLXDisplayColorDepthPtr displayColorDepth = self.cast<IADLXDisplayColorDepth*>();
        ADLX_RESULT retSetValue = displayColorDepth->SetValue(colorDepth);
        return retSetValue;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXDisplayColorDepthPtr displayColorDepth = self.cast<IADLXDisplayColorDepth*>();
        IADLXDisplayColorDepthPtr ppInterface = nullptr;
        displayColorDepth->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


        // IADLXDisplayCustomColor
        py::class_<IADLXDisplayCustomColor, IADLXInterface, PyDisplayCustomColor, IADLXInterfacePtr_T<IADLXDisplayCustomColor>>(m, "IADLXDisplayCustomColor")
        //.def(py::init<>())
        .def("GetBrightness", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXDisplayCustomColorPtr displayCustomColor = self.cast<IADLXDisplayCustomColor*>();
        adlx_int currentBrightness;
        ADLX_RESULT ret = displayCustomColor->GetBrightness(&currentBrightness);
        if (ADLX_SUCCEEDED(ret))
            return currentBrightness;
        return py::none();
        })
        .def("GetBrightnessRange", [](py::object self) {
        IADLXDisplayCustomColorPtr displayCustomColor = self.cast<IADLXDisplayCustomColor*>();
        ADLX_IntRange range;
        displayCustomColor->GetBrightnessRange(&range);
        return range;
        })
        .def("GetContrast", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXDisplayCustomColorPtr displayCustomColor = self.cast<IADLXDisplayCustomColor*>();
        adlx_int currentContrast;
        ADLX_RESULT ret = displayCustomColor->GetContrast(&currentContrast);
        if (ADLX_SUCCEEDED(ret))
            return currentContrast;
        return py::none();
        })
        .def("GetContrastRange", [](py::object self) {
        IADLXDisplayCustomColorPtr displayCustomColor = self.cast<IADLXDisplayCustomColor*>();
        ADLX_IntRange range;
        displayCustomColor->GetContrastRange(&range);
        return range;
        })
        .def("GetHue", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXDisplayCustomColorPtr displayCustomColor = self.cast<IADLXDisplayCustomColor*>();
        adlx_int currentHue;
        ADLX_RESULT ret = displayCustomColor->GetHue(&currentHue);
        if (ADLX_SUCCEEDED(ret))
            return currentHue;
        return py::none();
        })
        .def("GetHueRange", [](py::object self) {
        IADLXDisplayCustomColorPtr displayCustomColor = self.cast<IADLXDisplayCustomColor*>();
        ADLX_IntRange range;
        displayCustomColor->GetHueRange(&range);
        return range;
        })
        .def("GetSaturation", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXDisplayCustomColorPtr displayCustomColor = self.cast<IADLXDisplayCustomColor*>();
        adlx_int currentSaturation;
        ADLX_RESULT ret = displayCustomColor->GetSaturation(&currentSaturation);
        if (ADLX_SUCCEEDED(ret))
            return currentSaturation;
        return py::none();
        })
        .def("GetSaturationRange", [](py::object self) {
        IADLXDisplayCustomColorPtr displayCustomColor = self.cast<IADLXDisplayCustomColor*>();
        ADLX_IntRange range;
        displayCustomColor->GetSaturationRange(&range);
        return range;
        })
        .def("GetTemperature", [](py::object self) -> std::variant<adlx_int, py::none> {
        IADLXDisplayCustomColorPtr displayCustomColor = self.cast<IADLXDisplayCustomColor*>();
        adlx_int currentTemperature;
        ADLX_RESULT ret = displayCustomColor->GetTemperature(&currentTemperature);
        if (ADLX_SUCCEEDED(ret))
            return currentTemperature;
        return py::none();
        })
        .def("GetTemperatureRange", [](py::object self) {
        IADLXDisplayCustomColorPtr displayCustomColor = self.cast<IADLXDisplayCustomColor*>();
        ADLX_IntRange range;
        displayCustomColor->GetTemperatureRange(&range);
        return range;
        })
        .def("IsBrightnessSupported", [](py::object self) {
        IADLXDisplayCustomColorPtr displayCustomColor = self.cast<IADLXDisplayCustomColor*>();
        adlx_bool supported = false;
        displayCustomColor->IsBrightnessSupported(&supported);
        return supported;
        })
        .def("IsContrastSupported", [](py::object self) {
        IADLXDisplayCustomColorPtr displayCustomColor = self.cast<IADLXDisplayCustomColor*>();
        adlx_bool supported = false;
        displayCustomColor->IsContrastSupported(&supported);
        return supported;
        })
        .def("IsHueSupported", [](py::object self) {
        IADLXDisplayCustomColorPtr displayCustomColor = self.cast<IADLXDisplayCustomColor*>();
        adlx_bool supported = false;
        displayCustomColor->IsHueSupported(&supported);
        return supported;
        })
        .def("IsSaturationSupported", [](py::object self) {
        IADLXDisplayCustomColorPtr displayCustomColor = self.cast<IADLXDisplayCustomColor*>();
        adlx_bool supported = false;
        displayCustomColor->IsSaturationSupported(&supported);
        return supported;
        })
        .def("IsTemperatureSupported", [](py::object self) {
        IADLXDisplayCustomColorPtr displayCustomColor = self.cast<IADLXDisplayCustomColor*>();
        adlx_bool supported = false;
        displayCustomColor->IsTemperatureSupported(&supported);
        return supported;
        })
        .def("SetBrightness" , [](py::object self, adlx_int brightness) {
        IADLXDisplayCustomColorPtr displayCustomColor = self.cast<IADLXDisplayCustomColor*>();
        ADLX_RESULT retSetBrightness = displayCustomColor->SetBrightness(brightness);
        return retSetBrightness;
        })
        .def("SetContrast" , [](py::object self, adlx_int contrast) {
        IADLXDisplayCustomColorPtr displayCustomColor = self.cast<IADLXDisplayCustomColor*>();
        ADLX_RESULT retSetContrast = displayCustomColor->SetContrast(contrast);
        return retSetContrast;
        })
        .def("SetHue" , [](py::object self, adlx_int hue) {
        IADLXDisplayCustomColorPtr displayCustomColor = self.cast<IADLXDisplayCustomColor*>();
        ADLX_RESULT retSetHue = displayCustomColor->SetHue(hue);
        return retSetHue;
        })
        .def("SetSaturation" , [](py::object self, adlx_int saturation) {
        IADLXDisplayCustomColorPtr displayCustomColor = self.cast<IADLXDisplayCustomColor*>();
        ADLX_RESULT retSetSaturation = displayCustomColor->SetSaturation(saturation);
        return retSetSaturation;
        })
        .def("SetTemperature" , [](py::object self, adlx_int temperature) {
        IADLXDisplayCustomColorPtr displayCustomColor = self.cast<IADLXDisplayCustomColor*>();
        ADLX_RESULT retSetTemperature = displayCustomColor->SetTemperature(temperature);
        return retSetTemperature;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXDisplayCustomColorPtr displayCustomColor = self.cast<IADLXDisplayCustomColor*>();
        IADLXDisplayCustomColorPtr ppInterface = nullptr;
        displayCustomColor->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


        // IADLXDisplayCustomResolution
        py::class_<IADLXDisplayCustomResolution, IADLXInterface, PyDisplayCustomResolution, IADLXInterfacePtr_T<IADLXDisplayCustomResolution>>(m, "IADLXDisplayCustomResolution")
        //.def(py::init<>())
        .def("CreateNewResolution", [](py::object self, IADLXDisplayResolution* pResolution) {
        IADLXDisplayCustomResolutionPtr displayCustomRes = self.cast<IADLXDisplayCustomResolution*>();
        ADLX_RESULT retCreateResolution = displayCustomRes->CreateNewResolution(pResolution);
        return retCreateResolution;
        }, py::return_value_policy::move)
        .def("IsSupported", [](py::object self) {
        IADLXDisplayCustomResolutionPtr displayCustomRes = self.cast<IADLXDisplayCustomResolution*>();
        adlx_bool supported = false;
        displayCustomRes->IsSupported(&supported);
        return supported;
        })
        .def("GetCurrentAppliedResolution", [](py::object self) {
        IADLXDisplayCustomResolutionPtr displayCustomRes = self.cast<IADLXDisplayCustomResolution*>();
        IADLXDisplayResolutionPtr pResolution;
        displayCustomRes->GetCurrentAppliedResolution(&pResolution);
        return pResolution;
        })
        .def("GetResolutionList", [](py::object self) {
        IADLXDisplayCustomResolutionPtr displayCustomRes = self.cast<IADLXDisplayCustomResolution*>();
        IADLXDisplayResolutionListPtr resolutionList;
        displayCustomRes->GetResolutionList(&resolutionList);
        std::vector<IADLXDisplayResolutionPtr> list;
        for (adlx_uint s = resolutionList->Begin(); s != resolutionList->End(); s++) {
            IADLXDisplayResolutionPtr item;
            resolutionList->At(s, &item);
            list.emplace_back(std::move(item));
        }
        return list;
        })
        .def("DeleteResolution", [](py::object self, IADLXDisplayResolution* pResolution) {
        IADLXDisplayCustomResolutionPtr displayCustomRes = self.cast<IADLXDisplayCustomResolution*>();
        ADLX_RESULT retDeleteResolution = displayCustomRes->DeleteResolution(pResolution);
        return retDeleteResolution;
        }, py::return_value_policy::move)
        // Custom methods
        .def("GetResolutionListRaw", [](py::object self) {
        IADLXDisplayCustomResolutionPtr displayCustomRes = self.cast<IADLXDisplayCustomResolution*>();
        IADLXDisplayResolutionListPtr resolutionList;
        displayCustomRes->GetResolutionList(&resolutionList);
        return resolutionList;
        }, py::return_value_policy::move);

        // Resolution List
        py::class_<IADLXDisplayResolutionList, IADLXList, PyDisplayResolutionList, IADLXInterfacePtr_T<IADLXDisplayResolutionList>>(m, "IADLXDisplayResolutionList")
            //.def(py::init<>())
        .def("Add_Back", [](py::object self, IADLXDisplayResolution* pItem) {
        IADLXDisplayResolutionListPtr resolutionList = self.cast<IADLXDisplayResolutionList*>();
        ADLX_RESULT retresolutionList = resolutionList->Add_Back(pItem);
        return retresolutionList;
        })
        .def("At", [](py::object self, const adlx_uint location) {
        IADLXDisplayResolutionListPtr resolutionList = self.cast<IADLXDisplayResolutionList*>();
        IADLXDisplayResolutionPtr ppItem;
        resolutionList->At(location, &ppItem);
        return ppItem;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXDisplayResolutionListPtr resolutionList = self.cast<IADLXDisplayResolutionList*>();
        IADLXDisplayResolutionListPtr ppInterface = nullptr;
        resolutionList->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);
            


        // IADLXDisplayFreeSync
        py::class_<IADLXDisplayFreeSync, IADLXInterface, PyDisplayFreeSync, IADLXInterfacePtr_T<IADLXDisplayFreeSync>>(m, "IADLXDisplayFreeSync")
        //.def(py::init<>())
        .def("IsEnabled", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXDisplayFreeSync* displayFreeSync = self.cast<IADLXDisplayFreeSync*>();
        adlx_bool enabled;
        ADLX_RESULT ret = displayFreeSync->IsEnabled(&enabled);
        if (ADLX_SUCCEEDED(ret))
            return enabled;
        return py::none();
        })
        .def("IsSupported", [](py::object self) {
        IADLXDisplayFreeSync* displayFreeSync = self.cast<IADLXDisplayFreeSync*>();
        adlx_bool supported = false;
        displayFreeSync->IsSupported(&supported);
        return supported;
        })
        .def("SetEnabled", [](py::object self, adlx_bool enable) {
        IADLXDisplayFreeSync* displayFreeSync = self.cast<IADLXDisplayFreeSync*>();
        ADLX_RESULT retSetEnable = displayFreeSync->SetEnabled(enable);
        return retSetEnable;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXDisplayFreeSync* displayFreeSync = self.cast<IADLXDisplayFreeSync*>();
        IADLXDisplayFreeSyncPtr ppInterface = nullptr;
        displayFreeSync->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


        // IADLXDisplayGPUScaling
        py::class_<IADLXDisplayGPUScaling, IADLXInterface, PyDisplayGPUScaling, IADLXInterfacePtr_T<IADLXDisplayGPUScaling>>(m,"IADLXDisplayGPUScaling")
        //.def(py::init<>())
        .def("IsSupported", [](py::object self) {
        IADLXDisplayGPUScalingPtr displayGPUScaling = self.cast<IADLXDisplayGPUScaling*>();
        adlx_bool supported = false;
        displayGPUScaling->IsSupported(&supported);
        return supported;
        })
        .def("IsEnabled", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXDisplayGPUScalingPtr displayGPUScaling = self.cast<IADLXDisplayGPUScaling*>();
        adlx_bool enabled;
        ADLX_RESULT ret = displayGPUScaling->IsEnabled(&enabled);
        if (ADLX_SUCCEEDED(ret))
            return enabled;
        return py::none();
        })
        .def("SetEnabled", [](py::object self, adlx_bool enable) {
        IADLXDisplayGPUScalingPtr displayGPUScaling = self.cast<IADLXDisplayGPUScaling*>();
        ADLX_RESULT retSetEnable = displayGPUScaling->SetEnabled(enable);
        return retSetEnable;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXDisplayGPUScalingPtr displayGPUScaling = self.cast<IADLXDisplayGPUScaling*>();
        IADLXDisplayGPUScalingPtr ppInterface = nullptr;
        displayGPUScaling->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


        // IADLXDisplayGamma
        py::class_<IADLXDisplayGamma, IADLXInterface, PyDisplayGamma, IADLXInterfacePtr_T<IADLXDisplayGamma>>(m, "IADLXDisplayGamma")
        //.def(py::init<>())
        .def("GetGammaCoefficient", [](py::object self) {
        IADLXDisplayGamma* displayGamma = self.cast<IADLXDisplayGamma*>();
        ADLX_RegammaCoeff coeff;
        displayGamma->GetGammaCoefficient(&coeff);
        return coeff;
        })
        .def("GetGammaRamp", [](py::object self) {
        IADLXDisplayGamma* displayGamma = self.cast<IADLXDisplayGamma*>();
        ADLX_GammaRamp lut;
        displayGamma->GetGammaRamp(&lut);
        
        // Convert array to vector, on Python side it will be List of integers
        std::vector<adlx_uint16> pylist;
        
        for (int i=0; i < 256 * 3; i++) 
        { 
            pylist.emplace_back(std::move(lut.gamma[i]));
        }

        return pylist;
        })
        .def("IsCurrentDeGammaRamp", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXDisplayGamma* displayGamma = self.cast<IADLXDisplayGamma*>();
        adlx_bool isDeGammaRamp;
        ADLX_RESULT ret = displayGamma->IsCurrentDeGammaRamp(&isDeGammaRamp);
        if (ADLX_SUCCEEDED(ret))
            return isDeGammaRamp;
        return py::none();
        })
        .def("IsCurrentReGamma36", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXDisplayGamma* displayGamma = self.cast<IADLXDisplayGamma*>();
        adlx_bool isCurrentReGamma36;
        ADLX_RESULT ret = displayGamma->IsCurrentDeGammaRamp(&isCurrentReGamma36);
        if (ADLX_SUCCEEDED(ret))
            return isCurrentReGamma36;
        return py::none();
        })
        .def("IsCurrentReGammaBT709", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXDisplayGamma* displayGamma = self.cast<IADLXDisplayGamma*>();
        adlx_bool isCurrentReGammaBT709;
        ADLX_RESULT ret = displayGamma->IsCurrentReGammaBT709(&isCurrentReGammaBT709);
        if (ADLX_SUCCEEDED(ret))
            return isCurrentReGammaBT709;
        return py::none();
        })
        .def("IsCurrentReGammaPQ", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXDisplayGamma* displayGamma = self.cast<IADLXDisplayGamma*>();
        adlx_bool isCurrentReGammaPQ;
        ADLX_RESULT ret = displayGamma->IsCurrentReGammaPQ(&isCurrentReGammaPQ);
        if (ADLX_SUCCEEDED(ret))
            return isCurrentReGammaPQ;
        return py::none();
        })
        .def("IsCurrentReGammaPQ2084Interim", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXDisplayGamma* displayGamma = self.cast<IADLXDisplayGamma*>();
        adlx_bool isCurrentReGammaPQ2084Interim;
        ADLX_RESULT ret = displayGamma->IsCurrentReGammaPQ2084Interim(&isCurrentReGammaPQ2084Interim);
        if (ADLX_SUCCEEDED(ret))
            return isCurrentReGammaPQ2084Interim;
        return py::none();
        })
        .def("IsCurrentReGammaRamp", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXDisplayGamma* displayGamma = self.cast<IADLXDisplayGamma*>();
        adlx_bool isReGammaRamp;
        ADLX_RESULT ret = displayGamma->IsCurrentReGammaRamp(&isReGammaRamp);
        if (ADLX_SUCCEEDED(ret))
            return isReGammaRamp;
        return py::none();
        })
        .def("IsCurrentReGammaSRGB", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXDisplayGamma* displayGamma = self.cast<IADLXDisplayGamma*>();
        adlx_bool isCurrentReGammaSRGB;
        ADLX_RESULT ret = displayGamma->IsCurrentReGammaSRGB(&isCurrentReGammaSRGB);
        if (ADLX_SUCCEEDED(ret))
            return isCurrentReGammaSRGB;
        return py::none();
        })
        .def("IsCurrentRegammaCoefficient", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXDisplayGamma* displayGamma = self.cast<IADLXDisplayGamma*>();
        adlx_bool isRegammaCoeff;
        ADLX_RESULT ret = displayGamma->IsCurrentRegammaCoefficient(&isRegammaCoeff);
        if (ADLX_SUCCEEDED(ret))
            return isRegammaCoeff;
        return py::none();
        })
        .def("IsSupportedReGamma36", [](py::object self) {
        IADLXDisplayGamma* displayGamma = self.cast<IADLXDisplayGamma*>();
        adlx_bool isSupportedReGamma36 = false;
        displayGamma->IsSupportedReGamma36(&isSupportedReGamma36);
        return isSupportedReGamma36;
        })
        .def("IsSupportedReGammaBT709", [](py::object self) {
        IADLXDisplayGamma* displayGamma = self.cast<IADLXDisplayGamma*>();
        adlx_bool isSupportedReGammaBT709 = false;
        displayGamma->IsSupportedReGammaBT709(&isSupportedReGammaBT709);
        return isSupportedReGammaBT709;
        })
        .def("IsSupportedReGammaPQ", [](py::object self) {
        IADLXDisplayGamma* displayGamma = self.cast<IADLXDisplayGamma*>();
        adlx_bool isSupportedReGammaPQ = false;
        displayGamma->IsSupportedReGammaPQ(&isSupportedReGammaPQ);
        return isSupportedReGammaPQ;
        })
        .def("IsSupportedReGammaPQ2084Interim", [](py::object self) {
        IADLXDisplayGamma* displayGamma = self.cast<IADLXDisplayGamma*>();
        adlx_bool isSupportedReGammaPQ2084Interim = false;
        displayGamma->IsSupportedReGammaPQ2084Interim(&isSupportedReGammaPQ2084Interim);
        return isSupportedReGammaPQ2084Interim;
        })
        .def("IsSupportedReGammaSRGB", [](py::object self) {
        IADLXDisplayGamma* displayGamma = self.cast<IADLXDisplayGamma*>();
        adlx_bool isSupportedRegammaSRGB = false;
        displayGamma->IsSupportedReGammaSRGB(&isSupportedRegammaSRGB);
        return isSupportedRegammaSRGB;
        })
        .def("ResetGammaRamp", [](py::object self) {
        IADLXDisplayGamma* displayGamma = self.cast<IADLXDisplayGamma*>();
        ADLX_RESULT  reset_gamma_ramp = displayGamma->ResetGammaRamp();
        return reset_gamma_ramp;
        })
        .def("SetDeGammaRampMemory", [](py::object self, std::vector<adlx_uint16> pylist) {
        IADLXDisplayGamma* displayGamma = self.cast<IADLXDisplayGamma*>();
        ADLX_GammaRamp gammaRamp;
        for (unsigned int i = 0; i < 256 * 3; i++)
        {
            gammaRamp.gamma[i] = pylist[i];
        }
        ADLX_RESULT api_call = displayGamma->SetDeGammaRamp(gammaRamp);
        return api_call;
        })
        .def("SetDeGammaRampFile", [](py::object self, const char* path) {
        IADLXDisplayGamma* displayGamma = self.cast<IADLXDisplayGamma*>();
        ADLX_RESULT api_call = displayGamma->SetDeGammaRamp(path);
        return api_call;
        })		
        .def("SetReGammaRampMemory", [](py::object self, std::vector<adlx_uint16> pylist) {
        IADLXDisplayGamma* displayGamma = self.cast<IADLXDisplayGamma*>();
        ADLX_GammaRamp gammaRamp;
        for (unsigned int i = 0; i < 256 * 3; i++)
        {
        gammaRamp.gamma[i] = pylist[i];
        }
        ADLX_RESULT api_call = displayGamma->SetReGammaRamp(gammaRamp);
        return api_call;
        })
        .def("SetReGammaRampFile", [](py::object self, const char* path) {
        IADLXDisplayGamma* displayGamma = self.cast<IADLXDisplayGamma*>();
        ADLX_RESULT api_call = displayGamma->SetReGammaRamp(path);
        return api_call;
        })
        .def("SetReGamma36", [](py::object self) {
        IADLXDisplayGamma* displayGamma = self.cast<IADLXDisplayGamma*>();
        ADLX_RESULT  set_regamma_36 = displayGamma->SetReGamma36();
        return set_regamma_36;
        })
        .def("SetReGammaBT709", [](py::object self) {
        IADLXDisplayGamma* displayGamma = self.cast<IADLXDisplayGamma*>();
        ADLX_RESULT  set_regamm_bt709 = displayGamma->SetReGammaBT709();
        return set_regamm_bt709;
        })
        .def("SetReGammaCoefficient", [](py::object self, ADLX_RegammaCoeff coeff) {
        IADLXDisplayGamma* displayGamma = self.cast<IADLXDisplayGamma*>();
        ADLX_RESULT set_regamme_bt709 = displayGamma->SetReGammaCoefficient(coeff);
        return set_regamme_bt709;
        })
        .def("SetReGammaPQ", [](py::object self) {
        IADLXDisplayGamma* displayGamma = self.cast<IADLXDisplayGamma*>();
        ADLX_RESULT  set_regamm_pq = displayGamma->SetReGammaPQ();
        return set_regamm_pq;
        })
        .def("SetReGammaPQ2084Interim", [](py::object self) {
        IADLXDisplayGamma* displayGamma = self.cast<IADLXDisplayGamma*>();
        ADLX_RESULT  set_reggamm_pq2084_interim = displayGamma->SetReGammaPQ2084Interim();
        return set_reggamm_pq2084_interim;
        })
        .def("SetReGammaSRGB", [](py::object self) {
        IADLXDisplayGamma* displayGamma = self.cast<IADLXDisplayGamma*>();
        ADLX_RESULT  set_regamma_srgb = displayGamma->SetReGammaSRGB();
        return set_regamma_srgb;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXDisplayGammaPtr displayGamma = self.cast<IADLXDisplayGamma*>();
        IADLXDisplayGammaPtr ppInterface = nullptr;
        displayGamma->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


        // IADLXDisplayIntegerScaling
        py::class_<IADLXDisplayIntegerScaling, IADLXInterface, PyDisplayIntegerScaling, IADLXInterfacePtr_T<IADLXDisplayIntegerScaling>>(m, "IADLXDisplayIntegerScaling")
        //.def(py::init<>())
        .def("IsEnabled", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXDisplayIntegerScaling* displayIntegerScaling = self.cast<IADLXDisplayIntegerScaling*>();
        adlx_bool enabled;
        ADLX_RESULT result = displayIntegerScaling->IsEnabled(&enabled);
        if (ADLX_SUCCEEDED(result)) {
            return enabled;
        }
        return py::none();
        })
        .def("IsSupported", [](py::object self) {
        IADLXDisplayIntegerScaling* displayIntegerScaling = self.cast<IADLXDisplayIntegerScaling*>();
        adlx_bool supported = false;
        displayIntegerScaling->IsSupported(&supported);
        return supported;
        })
        .def("SetEnabled", [](py::object self, adlx_bool enable) {
        IADLXDisplayIntegerScaling* displayIntegerScaling = self.cast<IADLXDisplayIntegerScaling*>();
        ADLX_RESULT retSetEnable = displayIntegerScaling->SetEnabled(enable);
        return retSetEnable;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXDisplayIntegerScaling* displayIntegerScaling = self.cast<IADLXDisplayIntegerScaling*>();
        IADLXDisplayIntegerScalingPtr ppInterface = nullptr;
        displayIntegerScaling->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


        // IADLXDisplayPixelFormat
        py::class_<IADLXDisplayPixelFormat, IADLXInterface, PyDisplayPixelFormat, IADLXInterfacePtr_T<IADLXDisplayPixelFormat>>(m, "IADLXDisplayPixelFormat")
        //.def(py::init<>())
        .def("GetValue", [](py::object self) {
        IADLXDisplayPixelFormat* displayPixelFormat = self.cast<IADLXDisplayPixelFormat*>();
        ADLX_PIXEL_FORMAT pixelFormat;
        displayPixelFormat->GetValue(&pixelFormat);
        return pixelFormat;
        })
        .def("IsSupported", [](py::object self) {
        IADLXDisplayPixelFormat* displayPixelFormat = self.cast<IADLXDisplayPixelFormat*>();
        adlx_bool supported = false;
        displayPixelFormat->IsSupported(&supported);
        return supported;
        })
        .def("IsSupportedPixelFormat", [](py::object self ,ADLX_PIXEL_FORMAT pixelFormat) {
        IADLXDisplayPixelFormat* displayPixelFormat = self.cast<IADLXDisplayPixelFormat*>();
        adlx_bool supported = false;
        displayPixelFormat->IsSupportedPixelFormat(pixelFormat,&supported);
        return supported;
        })
        .def("IsSupportedRGB444Full", [](py::object self) {
        IADLXDisplayPixelFormat* displayPixelFormat = self.cast<IADLXDisplayPixelFormat*>();
        adlx_bool supported = false;
        displayPixelFormat->IsSupportedRGB444Full(&supported);
        return supported;
        })
        .def("IsSupportedRGB444Limited", [](py::object self) {
        IADLXDisplayPixelFormat* displayPixelFormat = self.cast<IADLXDisplayPixelFormat*>();
        adlx_bool supported = false;
        displayPixelFormat->IsSupportedRGB444Limited(&supported);
        return supported;
        })
        .def("IsSupportedYCbCr420", [](py::object self) {
        IADLXDisplayPixelFormat* displayPixelFormat = self.cast<IADLXDisplayPixelFormat*>();
        adlx_bool supported = false;
        displayPixelFormat->IsSupportedYCbCr420(&supported);
        return supported;
        })
        .def("IsSupportedYCbCr422", [](py::object self) {
        IADLXDisplayPixelFormat* displayPixelFormat = self.cast<IADLXDisplayPixelFormat*>();
        adlx_bool supported = false;
        displayPixelFormat->IsSupportedYCbCr422(&supported);
        return supported;
        })
        .def("IsSupportedYCbCr444", [](py::object self) {
        IADLXDisplayPixelFormat* displayPixelFormat = self.cast<IADLXDisplayPixelFormat*>();
        adlx_bool supported = false;
        displayPixelFormat->IsSupportedYCbCr444(&supported);
        return supported;
        })
        .def("SetValue", [](py::object self , ADLX_PIXEL_FORMAT pixelFormat) {
        IADLXDisplayPixelFormat* displayPixelFormat = self.cast<IADLXDisplayPixelFormat*>();
        ADLX_RESULT set_pixel_format= displayPixelFormat->SetValue(pixelFormat);
        return set_pixel_format;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXDisplayPixelFormat* displayPixelFormat = self.cast<IADLXDisplayPixelFormat*>();
        IADLXDisplayPixelFormatPtr ppInterface = nullptr;
        displayPixelFormat->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


        // IADLXDisplayScalingMode
        py::class_<IADLXDisplayScalingMode, IADLXInterface, PyDisplayScalingMode, IADLXInterfacePtr_T<IADLXDisplayScalingMode>>(m, "IADLXDisplayScalingMode")
        //.def(py::init<>())
        .def("GetMode", [](py::object self) {
        IADLXDisplayScalingMode* displayScalingMode = self.cast<IADLXDisplayScalingMode*>();
        ADLX_SCALE_MODE currentMode;
        displayScalingMode->GetMode(&currentMode);
        return currentMode;
        })
        .def("IsSupported", [](py::object self) {
        IADLXDisplayScalingMode* displayScalingMode = self.cast<IADLXDisplayScalingMode*>();
        adlx_bool supported = false;
        displayScalingMode->IsSupported(&supported);
        return supported;
        })
        .def("SetMode", [](py::object self , ADLX_SCALE_MODE mode) {
        IADLXDisplayScalingMode* displayScalingMode = self.cast<IADLXDisplayScalingMode*>();	
        ADLX_RESULT set_mode = displayScalingMode->SetMode(mode);
        return set_mode;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXDisplayScalingMode* displayScalingMode = self.cast<IADLXDisplayScalingMode*>();
        IADLXDisplayScalingModePtr ppInterface = nullptr;
        displayScalingMode->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


        // IADLXDisplayVariBright
        py::class_<IADLXDisplayVariBright, IADLXInterface, PyDisplayVariBright, IADLXInterfacePtr_T<IADLXDisplayVariBright>>(m, "IADLXDisplayVariBright")
        //.def(py::init<>())
        .def("IsCurrentBalanced", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXDisplayVariBright* displayVariBright = self.cast<IADLXDisplayVariBright*>();
        adlx_bool balanced;
        ADLX_RESULT result = displayVariBright->IsCurrentBalanced(&balanced);
        if (ADLX_SUCCEEDED(result)) {
            return balanced;
        }
        return py::none();
        })
        .def("IsCurrentMaximizeBattery", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXDisplayVariBright* displayVariBright = self.cast<IADLXDisplayVariBright*>();
        adlx_bool maximizeBattery;
        ADLX_RESULT result = displayVariBright->IsCurrentMaximizeBattery(&maximizeBattery);
        if (ADLX_SUCCEEDED(result)) {
            return maximizeBattery;
        }
        return py::none();
        })
        .def("IsCurrentMaximizeBrightness", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXDisplayVariBright* displayVariBright = self.cast<IADLXDisplayVariBright*>();
        adlx_bool maximizeBrightness;
        ADLX_RESULT result = displayVariBright->IsCurrentMaximizeBrightness(&maximizeBrightness);
        if (ADLX_SUCCEEDED(result)) {
            return maximizeBrightness;
        }
        return py::none();
        })
        .def("IsCurrentOptimizeBattery", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXDisplayVariBright* displayVariBright = self.cast<IADLXDisplayVariBright*>();
        adlx_bool optimizeBattery;
        ADLX_RESULT result = displayVariBright->IsCurrentOptimizeBattery(&optimizeBattery);
        if (ADLX_SUCCEEDED(result)) {
            return optimizeBattery;
        }
        return py::none();
        })
        .def("IsCurrentOptimizeBrightness", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXDisplayVariBright* displayVariBright = self.cast<IADLXDisplayVariBright*>();
        adlx_bool optimizeBrightness;
        ADLX_RESULT result = displayVariBright->IsCurrentOptimizeBrightness(&optimizeBrightness);
        if (ADLX_SUCCEEDED(result)) {
            return optimizeBrightness;
        }
        return py::none();
        })
        .def("IsEnabled", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXDisplayVariBright* displayVariBright = self.cast<IADLXDisplayVariBright*>();
        adlx_bool IsEnabled;
        ADLX_RESULT result = displayVariBright->IsEnabled(&IsEnabled);
        if (ADLX_SUCCEEDED(result)) {
            return IsEnabled;
        }
        return py::none();
        })
        .def("IsSupported", [](py::object self) {
        IADLXDisplayVariBright* displayVariBright = self.cast<IADLXDisplayVariBright*>();
        adlx_bool supported = false;
        displayVariBright->IsSupported(&supported);
        return supported;
        })
        .def("SetBalanced", [](py::object self) {
        IADLXDisplayVariBright* displayVariBright = self.cast<IADLXDisplayVariBright*>();
        ADLX_RESULT set_balance = displayVariBright->SetBalanced();
        return set_balance;
        })
        .def("SetEnabled", [](py::object self , adlx_bool enable) {
        IADLXDisplayVariBright* displayVariBright = self.cast<IADLXDisplayVariBright*>();
        ADLX_RESULT set_enabled = displayVariBright->SetEnabled(enable);
        return set_enabled;
        })
        .def("SetMaximizeBattery", [](py::object self) {
        IADLXDisplayVariBright* displayVariBright = self.cast<IADLXDisplayVariBright*>();
        ADLX_RESULT set_maximize_battery =  displayVariBright->SetMaximizeBattery();
        return set_maximize_battery;
        })
        .def("SetMaximizeBrightness", [](py::object self) {
        IADLXDisplayVariBright* displayVariBright = self.cast<IADLXDisplayVariBright*>();
        ADLX_RESULT set_maximize_brigtness = displayVariBright->SetMaximizeBrightness();
        return set_maximize_brigtness;
        })
        .def("SetOptimizeBattery", [](py::object self) {
        IADLXDisplayVariBright* displayVariBright = self.cast<IADLXDisplayVariBright*>();
        ADLX_RESULT set_optimize_battery = displayVariBright->SetOptimizeBattery();
        return set_optimize_battery;
        })
        .def("SetOptimizeBrightness", [](py::object self) {
        IADLXDisplayVariBright* displayVariBright = self.cast<IADLXDisplayVariBright*>();
        ADLX_RESULT set_optimize_brightness = displayVariBright->SetOptimizeBrightness();
        return set_optimize_brightness;
        })
        // IADLXDisplayVariBright1
        .def("IsBacklightAdaptiveSupported", [](py::object self) {
        IADLXDisplayVariBrightPtr displayVariBright = self.cast<IADLXDisplayVariBright*>();
        IADLXDisplayVariBright1Ptr displayVariBright1(displayVariBright);
        if (displayVariBright1)
        {
            adlx_bool supported = false;
            displayVariBright1->IsBacklightAdaptiveSupported(&supported);
            return supported;
        }
        return adlx_bool(false);
        })
        .def("IsBacklightAdaptiveEnabled", [](py::object self) {
        IADLXDisplayVariBrightPtr displayVariBright = self.cast<IADLXDisplayVariBright*>();
        IADLXDisplayVariBright1Ptr displayVariBright1(displayVariBright);
        if (displayVariBright1)
        {
            adlx_bool enabled = false;
            displayVariBright1->IsBacklightAdaptiveEnabled(&enabled);
            return enabled;
        }
        return adlx_bool(false);
        })
        .def("SetBacklightAdaptiveEnabled", [](py::object self, adlx_bool enable) {
        IADLXDisplayVariBrightPtr displayVariBright = self.cast<IADLXDisplayVariBright*>();
        IADLXDisplayVariBright1Ptr displayVariBright1(displayVariBright);
        if (displayVariBright1)
        {
            return displayVariBright1->SetBacklightAdaptiveEnabled(enable);
        }
        return ADLX_RESULT(ADLX_FAIL);
        })
        .def("IsBatteryLifeSupported", [](py::object self) {
        IADLXDisplayVariBrightPtr displayVariBright = self.cast<IADLXDisplayVariBright*>();
        IADLXDisplayVariBright1Ptr displayVariBright1(displayVariBright);
        if (displayVariBright1)
        {
            adlx_bool supported = false;
            displayVariBright1->IsBatteryLifeSupported(&supported);
            return supported;
        }
        return adlx_bool(false);
        })
        .def("IsBatteryLifeEnabled", [](py::object self) {
        IADLXDisplayVariBrightPtr displayVariBright = self.cast<IADLXDisplayVariBright*>();
        IADLXDisplayVariBright1Ptr displayVariBright1(displayVariBright);
        if (displayVariBright1)
        {
            adlx_bool enabled = false;
            displayVariBright1->IsBatteryLifeEnabled(&enabled);
            return enabled;
        }
        return adlx_bool(false);
        })
        .def("SetBatteryLifeEnabled", [](py::object self, adlx_bool enable) {
        IADLXDisplayVariBrightPtr displayVariBright = self.cast<IADLXDisplayVariBright*>();
        IADLXDisplayVariBright1Ptr displayVariBright1(displayVariBright);
        if (displayVariBright1)
        {
            return displayVariBright1->SetBatteryLifeEnabled(enable);
        }
        return ADLX_RESULT(ADLX_FAIL);
        })
        .def("IsWindowsPowerModeSupported", [](py::object self) {
        IADLXDisplayVariBrightPtr displayVariBright = self.cast<IADLXDisplayVariBright*>();
        IADLXDisplayVariBright1Ptr displayVariBright1(displayVariBright);
        if (displayVariBright1)
        {
            adlx_bool supported = false;
            displayVariBright1->IsWindowsPowerModeSupported(&supported);
            return supported;
        }
        return adlx_bool(false);
        })
        .def("IsWindowsPowerModeEnabled", [](py::object self) {
        IADLXDisplayVariBrightPtr displayVariBright = self.cast<IADLXDisplayVariBright*>();
        IADLXDisplayVariBright1Ptr displayVariBright1(displayVariBright);
        if (displayVariBright1)
        {
            adlx_bool enabled = false;
            displayVariBright1->IsWindowsPowerModeEnabled(&enabled);
            return enabled;
        }
        return adlx_bool(false);
        })
        .def("SetWindowsPowerModeEnabled", [](py::object self, adlx_bool enable) {
        IADLXDisplayVariBrightPtr displayVariBright = self.cast<IADLXDisplayVariBright*>();
        IADLXDisplayVariBright1Ptr displayVariBright1(displayVariBright);
        if (displayVariBright1)
        {
            return displayVariBright1->SetWindowsPowerModeEnabled(enable);
        }
        return ADLX_RESULT(ADLX_FAIL);
        })
        .def("IsFullScreenVideoSupported", [](py::object self) {
        IADLXDisplayVariBrightPtr displayVariBright = self.cast<IADLXDisplayVariBright*>();
        IADLXDisplayVariBright1Ptr displayVariBright1(displayVariBright);
        if (displayVariBright1)
        {
            adlx_bool supported = false;
            displayVariBright1->IsFullScreenVideoSupported(&supported);
            return supported;
        }
        return adlx_bool(false);
        })
        .def("IsFullScreenVideoEnabled", [](py::object self) {
        IADLXDisplayVariBrightPtr displayVariBright = self.cast<IADLXDisplayVariBright*>();
        IADLXDisplayVariBright1Ptr displayVariBright1(displayVariBright);
        if (displayVariBright1)
        {
            adlx_bool enabled = false;
            displayVariBright1->IsFullScreenVideoEnabled(&enabled);
            return enabled;
        }
        return adlx_bool(false);
        })
        .def("SetFullScreenVideoEnabled", [](py::object self, adlx_bool enable) {
        IADLXDisplayVariBrightPtr displayVariBright = self.cast<IADLXDisplayVariBright*>();
        IADLXDisplayVariBright1Ptr displayVariBright1(displayVariBright);
        if (displayVariBright1)
        {
            return displayVariBright1->SetFullScreenVideoEnabled(enable);
        }
        return ADLX_RESULT(ADLX_FAIL);
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXDisplayVariBright* displayVariBright = self.cast<IADLXDisplayVariBright*>();
        IADLXDisplayVariBrightPtr ppInterface = nullptr;
        displayVariBright->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);

        // IADLXDisplayVSR
        py::class_<IADLXDisplayVSR, IADLXInterface, PyDisplayVSR, IADLXInterfacePtr_T<IADLXDisplayVSR>>(m, "IADLXDisplayVSR")
        //.def(py::init<>())
        .def("IsEnabled", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXDisplayVSR* displayVSR = self.cast<IADLXDisplayVSR*>();
        adlx_bool enabled;
        ADLX_RESULT result = displayVSR->IsEnabled(&enabled);
        if (ADLX_SUCCEEDED(result)) {
            return enabled;
        }
        return py::none();
        })
        .def("IsSupported", [](py::object self) {
        IADLXDisplayVSR* displayVSR = self.cast<IADLXDisplayVSR*>();
        adlx_bool supported = false;
        displayVSR->IsSupported(&supported);
        return supported;
        })
        .def("SetEnabled", [](py::object self , adlx_bool enable) {
        IADLXDisplayVSR* displayVSR = self.cast<IADLXDisplayVSR*>();
        ADLX_RESULT retSetEnable = displayVSR->SetEnabled(enable);
        return retSetEnable;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXDisplayVSR* displayVSR = self.cast<IADLXDisplayVSR*>();
        IADLXDisplayVSRPtr ppInterface = nullptr;
        displayVSR->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);

        // IADLXDisplayBlanking
        py::class_<IADLXDisplayBlanking, IADLXInterface, PyDisplayBlanking, IADLXInterfacePtr_T<IADLXDisplayBlanking>>(m, "IADLXDisplayBlanking")
            //.def(py::init<>())
            .def("IsSupported", [](py::object self) {
            IADLXDisplayBlanking* displayBlanking = self.cast<IADLXDisplayBlanking*>();
            adlx_bool supported = false;
            displayBlanking->IsSupported(&supported);
            return supported;
                })
            .def("IsCurrentBlanked", [](py::object self) -> std::variant<adlx_bool, py::none> {
            IADLXDisplayBlanking* displayBlanking = self.cast<IADLXDisplayBlanking*>();
            adlx_bool blanked;
            ADLX_RESULT result = displayBlanking->IsCurrentBlanked(&blanked);
            if (ADLX_SUCCEEDED(result)) {
                return blanked;
            }
            return py::none();
                })
            .def("IsCurrentUnblanked", [](py::object self) -> std::variant<adlx_bool, py::none> {
            IADLXDisplayBlanking* displayBlanking = self.cast<IADLXDisplayBlanking*>();
            adlx_bool unBlanked;
            ADLX_RESULT result = displayBlanking->IsCurrentUnblanked(&unBlanked);
            if (ADLX_SUCCEEDED(result)) {
                return unBlanked;
            }
            return py::none();
                })
            .def("SetBlanked", [](py::object self) {
            IADLXDisplayBlanking* displayBlanking = self.cast<IADLXDisplayBlanking*>();
            ADLX_RESULT ret = displayBlanking->SetBlanked();
            return ret;
                })
            .def("SetUnblanked", [](py::object self) {
            IADLXDisplayBlanking* displayBlanking = self.cast<IADLXDisplayBlanking*>();
            ADLX_RESULT ret = displayBlanking->SetUnblanked();
            return ret;
                })
            .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
            IADLXDisplayBlanking* displayBlanking = self.cast<IADLXDisplayBlanking*>();
            IADLXDisplayBlankingPtr ppInterface = nullptr;
            displayBlanking->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
            return ppInterface;
                }, py::return_value_policy::move);

        // IADLXDisplayConnectivityExperience
        py::class_<IADLXDisplayConnectivityExperience, IADLXInterface, PyDisplayConnectivityExperience, IADLXInterfacePtr_T<IADLXDisplayConnectivityExperience>>(m, "IADLXDisplayConnectivityExperience")
            .def("IsSupportedHDMIQualityDetection", [](py::object self) {
            IADLXDisplayConnectivityExperience* ce = self.cast<IADLXDisplayConnectivityExperience*>();
            adlx_bool supported = false;
            ce->IsSupportedHDMIQualityDetection(&supported);
            return supported;
                })
            .def("IsSupportedDPLink", [](py::object self) {
            IADLXDisplayConnectivityExperience* ce = self.cast<IADLXDisplayConnectivityExperience*>();
            adlx_bool supported = false;
            ce->IsSupportedDPLink(&supported);
            return supported;
                })
            .def("IsEnabledHDMIQualityDetection", [](py::object self) {
            IADLXDisplayConnectivityExperience* ce = self.cast<IADLXDisplayConnectivityExperience*>();
            adlx_bool enabled = false;
            ce->IsEnabledHDMIQualityDetection(&enabled);
            return enabled;
                })
            .def("SetEnabledHDMIQualityDetection", [](py::object self, adlx_bool enabled) {
            IADLXDisplayConnectivityExperience* ce = self.cast<IADLXDisplayConnectivityExperience*>();
            return ce->SetEnabledHDMIQualityDetection(enabled);
                })
            .def("GetDPLinkRate", [](py::object self) {
            IADLXDisplayConnectivityExperience* ce = self.cast<IADLXDisplayConnectivityExperience*>();
            ADLX_DP_LINK_RATE linkRate = DP_LINK_RATE_UNKNOWN;
            ce->GetDPLinkRate(&linkRate);
            return linkRate;
                })
            .def("GetNumberOfActiveLanes", [](py::object self) {
            IADLXDisplayConnectivityExperience* ce = self.cast<IADLXDisplayConnectivityExperience*>();
            adlx_uint numActiveLanes = 0;
            ce->GetNumberOfActiveLanes(&numActiveLanes);
            return numActiveLanes;
                })
            .def("GetNumberOfTotalLanes", [](py::object self) {
            IADLXDisplayConnectivityExperience* ce = self.cast<IADLXDisplayConnectivityExperience*>();
            adlx_uint numTotalLanes = 0;
            ce->GetNumberOfTotalLanes(&numTotalLanes);
            return numTotalLanes;
                })
            .def("GetRelativePreEmphasis", [](py::object self) {
            IADLXDisplayConnectivityExperience* ce = self.cast<IADLXDisplayConnectivityExperience*>();
            adlx_int relativePreEmphasis = 0;
            ce->GetRelativePreEmphasis(&relativePreEmphasis);
            return relativePreEmphasis;
                })
            .def("SetRelativePreEmphasis", [](py::object self, adlx_int relativePreEmphasis) {
            IADLXDisplayConnectivityExperience* ce = self.cast<IADLXDisplayConnectivityExperience*>();
            return ce->SetRelativePreEmphasis(relativePreEmphasis);
                })
            .def("GetRelativeVoltageSwing", [](py::object self) {
            IADLXDisplayConnectivityExperience* ce = self.cast<IADLXDisplayConnectivityExperience*>();
            adlx_int relativeVoltageSwing = 0;
            ce->GetRelativeVoltageSwing(&relativeVoltageSwing);
            return relativeVoltageSwing;
                })
            .def("SetRelativeVoltageSwing", [](py::object self, adlx_int relativeVoltageSwing) {
            IADLXDisplayConnectivityExperience* ce = self.cast<IADLXDisplayConnectivityExperience*>();
            return ce->SetRelativeVoltageSwing(relativeVoltageSwing);
                })
            .def("IsEnabledLinkProtection", [](py::object self) {
            IADLXDisplayConnectivityExperience* ce = self.cast<IADLXDisplayConnectivityExperience*>();
            adlx_bool enabled = false;
            ce->IsEnabledLinkProtection(&enabled);
            return enabled;
                })
            .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
            IADLXDisplayConnectivityExperience* ce = self.cast<IADLXDisplayConnectivityExperience*>();
            IADLXDisplayConnectivityExperiencePtr ppInterface = nullptr;
            ce->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
            return ppInterface;
                }, py::return_value_policy::move);

        // IADLXDisplayDynamicRefreshRateControl
        py::class_<IADLXDisplayDynamicRefreshRateControl, IADLXInterface, PyDisplayDynamicRefreshRateControl, IADLXInterfacePtr_T<IADLXDisplayDynamicRefreshRateControl>>(m, "IADLXDisplayDynamicRefreshRateControl")
            .def("IsSupported", [](py::object self) {
            IADLXDisplayDynamicRefreshRateControl* drrc = self.cast<IADLXDisplayDynamicRefreshRateControl*>();
            adlx_bool supported = false;
            drrc->IsSupported(&supported);
            return supported;
                })
            .def("IsEnabled", [](py::object self) {
            IADLXDisplayDynamicRefreshRateControl* drrc = self.cast<IADLXDisplayDynamicRefreshRateControl*>();
            adlx_bool enabled = false;
            drrc->IsEnabled(&enabled);
            return enabled;
                })
            .def("SetEnabled", [](py::object self, adlx_bool enabled) {
            IADLXDisplayDynamicRefreshRateControl* drrc = self.cast<IADLXDisplayDynamicRefreshRateControl*>();
            return drrc->SetEnabled(enabled);
                })
            .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
            IADLXDisplayDynamicRefreshRateControl* drrc = self.cast<IADLXDisplayDynamicRefreshRateControl*>();
            IADLXDisplayDynamicRefreshRateControlPtr ppInterface = nullptr;
            drrc->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
            return ppInterface;
                }, py::return_value_policy::move);

        // IADLXDisplayFreeSyncColorAccuracy
        py::class_<IADLXDisplayFreeSyncColorAccuracy, IADLXInterface, PyDisplayFreeSyncColorAccuracy, IADLXInterfacePtr_T<IADLXDisplayFreeSyncColorAccuracy>>(m, "IADLXDisplayFreeSyncColorAccuracy")
            .def("IsSupported", [](py::object self) {
            IADLXDisplayFreeSyncColorAccuracy* fsca = self.cast<IADLXDisplayFreeSyncColorAccuracy*>();
            adlx_bool supported = false;
            fsca->IsSupported(&supported);
            return supported;
                })
            .def("IsEnabled", [](py::object self) {
            IADLXDisplayFreeSyncColorAccuracy* fsca = self.cast<IADLXDisplayFreeSyncColorAccuracy*>();
            adlx_bool enabled = false;
            fsca->IsEnabled(&enabled);
            return enabled;
                })
            .def("SetEnabled", [](py::object self, adlx_bool enabled) {
            IADLXDisplayFreeSyncColorAccuracy* fsca = self.cast<IADLXDisplayFreeSyncColorAccuracy*>();
            return fsca->SetEnabled(enabled);
                })
            .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
            IADLXDisplayFreeSyncColorAccuracy* fsca = self.cast<IADLXDisplayFreeSyncColorAccuracy*>();
            IADLXDisplayFreeSyncColorAccuracyPtr ppInterface = nullptr;
            fsca->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
            return ppInterface;
                }, py::return_value_policy::move);

    // IADLXDisplay3DLUTChangedEvent
        py::class_<IADLXDisplay3DLUTChangedEvent, IADLXChangedEvent, PyDisplay3DLUTChangedEvent, IADLXInterfacePtr_T<IADLXDisplay3DLUTChangedEvent>>(m, "IADLXDisplay3DLUTChangedEvent")
        //.def(py::init<>())
        .def("GetDisplay", [](py::object self) {
        IADLXDisplay3DLUTChangedEvent* dis_3d_event = self.cast<IADLXDisplay3DLUTChangedEvent*>();
        IADLXDisplayPtr display;
        dis_3d_event->GetDisplay(&display);
        return display;
        }, py::return_value_policy::move)
        .def("IsCustom3DLUTChanged", [](py::object self) {
        IADLXDisplay3DLUTChangedEvent* dis_3d_event = self.cast<IADLXDisplay3DLUTChangedEvent*>();
        adlx_bool is_3d_lut_changed = dis_3d_event->IsCustom3DLUTChanged();
        return is_3d_lut_changed;
        })
        .def("IsSCEChanged", [](py::object self) {
        IADLXDisplay3DLUTChangedEvent* dis_3d_event = self.cast<IADLXDisplay3DLUTChangedEvent*>();
        adlx_bool is_sce_changed = dis_3d_event->IsSCEChanged();
        return is_sce_changed;
        });


        // IADLXDisplayHDCP
        py::class_<IADLXDisplayHDCP, IADLXInterface, PyDisplayHDCP, IADLXInterfacePtr_T<IADLXDisplayHDCP>>(m, "IADLXDisplayHDCP")
        //.def(py::init<>())
        .def("IsEnabled", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXDisplayHDCPPtr display_hdcp = self.cast<IADLXDisplayHDCP*>();
        adlx_bool isEnabled;
        ADLX_RESULT result = display_hdcp->IsEnabled(&isEnabled);
        if (ADLX_SUCCEEDED(result)) {
            return isEnabled;
        }
        return py::none();
        })
        .def("IsSupported", [](py::object self) {
        IADLXDisplayHDCPPtr display_hdcp = self.cast<IADLXDisplayHDCP*>();
        adlx_bool supported = false;
        display_hdcp->IsSupported(&supported);
        return supported;
        })
        .def("SetEnabled", [](py::object self, adlx_bool enable) {
        IADLXDisplayHDCPPtr display_hdcp = self.cast<IADLXDisplayHDCP*>();
        ADLX_RESULT retSetEnable = display_hdcp->SetEnabled(enable);
        return retSetEnable;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXDisplayHDCPPtr display_hdcp = self.cast<IADLXDisplayHDCP*>();
        IADLXDisplayHDCPPtr ppInterface = nullptr;
        display_hdcp->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);

        // IADLXDisplayGamutChangedEvent
        py::class_<IADLXDisplayGamutChangedEvent, IADLXChangedEvent, PyDisplayGamutChangedEvent, IADLXInterfacePtr_T<IADLXDisplayGamutChangedEvent>>(m, "IADLXDisplayGamutChangedEvent")
        //.def(py::init<>())
        .def("GetDisplay", [](py::object self) {
        IADLXDisplayGamutChangedEventPtr gamut_changed_event = self.cast<IADLXDisplayGamutChangedEvent*>();
        IADLXDisplayPtr display;
        gamut_changed_event->GetDisplay(&display);
        return display;
        })
        .def("IsColorSpaceChanged", [](py::object self) {
        IADLXDisplayGamutChangedEventPtr gamut_changed_event = self.cast<IADLXDisplayGamutChangedEvent*>();
        adlx_bool color_space_changed = gamut_changed_event->IsColorSpaceChanged();
        return color_space_changed;
        })
        .def("IsWhitePointChanged", [](py::object self) {
        IADLXDisplayGamutChangedEventPtr gamut_changed_event = self.cast<IADLXDisplayGamutChangedEvent*>();
        adlx_bool white_point_changed = gamut_changed_event->IsWhitePointChanged();
        return white_point_changed;
        });


        // ADLX_RegammaCoeff
        py::class_<ADLX_RegammaCoeff>(m, "ADLX_RegammaCoeff")
        .def(py::init<>())
        .def_readwrite("coefficientA0", &ADLX_RegammaCoeff::coefficientA0)
        .def_readwrite("coefficientA1", &ADLX_RegammaCoeff::coefficientA1)
        .def_readwrite("coefficientA2", &ADLX_RegammaCoeff::coefficientA2)
        .def_readwrite("coefficientA3", &ADLX_RegammaCoeff::coefficientA3)
        .def_readwrite("gamma", &ADLX_RegammaCoeff::gamma);


        // ADLX_GamutColorSpace
        py::class_<ADLX_GamutColorSpace>(m, "ADLX_GamutColorSpace")
        .def(py::init<>())
        .def_readwrite("blue", &ADLX_GamutColorSpace::blue)
        .def_readwrite("green", &ADLX_GamutColorSpace::green)
        .def_readwrite("red", &ADLX_GamutColorSpace::red);


        // ADLX_Point
        py::class_<ADLX_Point>(m, "ADLX_Point")
        .def(py::init<>())
        .def_readwrite("x", &ADLX_Point::x)
        .def_readwrite("y", &ADLX_Point::y);


        // ADLX_RGB
        py::class_<ADLX_RGB>(m, "ADLX_RGB")
        .def(py::init<>())
        .def_readwrite("gamutB", &ADLX_RGB::gamutB)
        .def_readwrite("gamutG", &ADLX_RGB::gamutG)
        .def_readwrite("gamutR", &ADLX_RGB::gamutR);


        // IADLXDisplayGamut
        py::class_<IADLXDisplayGamut, IADLXInterface, PyDisplayGamut, IADLXInterfacePtr_T<IADLXDisplayGamut>>(m, "IADLXDisplayGamut")
        //.def(py::init<>())		
        .def("GetGamutColorSpace", [](py::object self) {
        IADLXDisplayGamutPtr display_gamut = self.cast<IADLXDisplayGamut*>();
        ADLX_GamutColorSpace gamutColorSpace;
        display_gamut->GetGamutColorSpace(&gamutColorSpace);
        return gamutColorSpace;
        })
        .def("GetWhitePoint", [](py::object self) {
        IADLXDisplayGamutPtr display_gamut = self.cast<IADLXDisplayGamut*>();
        ADLX_Point point;
        display_gamut->GetWhitePoint(&point);
        return point;
        })	
        .def("IsCurrent5000kWhitePoint", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXDisplayGamutPtr display_gamut = self.cast<IADLXDisplayGamut*>();
        adlx_bool isSet;
        ADLX_RESULT ret_api = display_gamut->IsCurrent5000kWhitePoint(&isSet);
        if (ADLX_SUCCEEDED(ret_api)) {
            return isSet;
        }
        return py::none();
        })
        .def("IsCurrent6500kWhitePoint", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXDisplayGamutPtr display_gamut = self.cast<IADLXDisplayGamut*>();
        adlx_bool isSet = false;
        ADLX_RESULT ret_api = display_gamut->IsCurrent6500kWhitePoint(&isSet);
        if (ADLX_SUCCEEDED(ret_api)) {
            return isSet;
        }
        return py::none();
        })
        .def("IsCurrent7500kWhitePoint", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXDisplayGamutPtr display_gamut = self.cast<IADLXDisplayGamut*>();
        adlx_bool isSet = false;
        ADLX_RESULT ret_api = display_gamut->IsCurrent7500kWhitePoint(&isSet);
        if (ADLX_SUCCEEDED(ret_api)) {
            return isSet;
        }
        return py::none();
        })
        .def("IsCurrent9300kWhitePoint", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXDisplayGamutPtr display_gamut = self.cast<IADLXDisplayGamut*>();
        adlx_bool isSet = false;
        ADLX_RESULT ret_api = display_gamut->IsCurrent9300kWhitePoint(&isSet);
        if (ADLX_SUCCEEDED(ret_api)) {
            return isSet;
        }
        return py::none();
        })
        .def("IsCurrentAdobeRgbColorSpace", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXDisplayGamutPtr display_gamut = self.cast<IADLXDisplayGamut*>();
        adlx_bool isSet = false;
        ADLX_RESULT ret_api = display_gamut->IsCurrentAdobeRgbColorSpace(&isSet);
        if (ADLX_SUCCEEDED(ret_api)) {
            return isSet;
        }
        return py::none();
        })
        .def("IsCurrentCCIR2020ColorSpace", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXDisplayGamutPtr display_gamut = self.cast<IADLXDisplayGamut*>();
        adlx_bool isSet = false;
        ADLX_RESULT ret_api = display_gamut->IsCurrentCCIR2020ColorSpace(&isSet);
        if (ADLX_SUCCEEDED(ret_api)) {
            return isSet;
        }
        return py::none();
        })
        .def("IsCurrentCCIR601ColorSpace", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXDisplayGamutPtr display_gamut = self.cast<IADLXDisplayGamut*>();
        adlx_bool isSet = false;
        ADLX_RESULT ret_api = display_gamut->IsCurrentCCIR601ColorSpace(&isSet);
        if (ADLX_SUCCEEDED(ret_api)) {
            return isSet;
        }
        return py::none();
        })
        .def("IsCurrentCCIR709ColorSpace", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXDisplayGamutPtr display_gamut = self.cast<IADLXDisplayGamut*>();
        adlx_bool isSet = false;
        ADLX_RESULT ret_api = display_gamut->IsCurrentCCIR709ColorSpace(&isSet);
        if (ADLX_SUCCEEDED(ret_api)) {
            return isSet;
        }
        return py::none();
        })
        .def("IsCurrentCIERgbColorSpace", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXDisplayGamutPtr display_gamut = self.cast<IADLXDisplayGamut*>();
        adlx_bool isSet = false;
        ADLX_RESULT ret_api = display_gamut->IsCurrentCIERgbColorSpace(&isSet);
        if (ADLX_SUCCEEDED(ret_api)) {
            return isSet;
        }
        return py::none();
        })
        .def("IsCurrentCustomColorSpace", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXDisplayGamutPtr display_gamut = self.cast<IADLXDisplayGamut*>();
        adlx_bool isSet = false;
        ADLX_RESULT ret_api = display_gamut->IsCurrentCustomColorSpace(&isSet);
        if (ADLX_SUCCEEDED(ret_api)) {
            return isSet;
        }
        return py::none();
        })
        .def("IsCurrentCustomWhitePoint", [](py::object self) -> std::variant<adlx_bool, py::none> {
        IADLXDisplayGamutPtr display_gamut = self.cast<IADLXDisplayGamut*>();
        adlx_bool isSet = false;
        ADLX_RESULT ret_api = display_gamut->IsCurrentCustomWhitePoint(&isSet);
        if (ADLX_SUCCEEDED(ret_api)) {
            return isSet;
        }
        return py::none();
        })
        .def("IsSupported5000kWhitePoint", [](py::object self) {
        IADLXDisplayGamutPtr display_gamut = self.cast<IADLXDisplayGamut*>();
        adlx_bool supported = false;
        display_gamut->IsSupported5000kWhitePoint(&supported);
        return supported;
        })
        .def("IsSupported6500kWhitePoint", [](py::object self) {
        IADLXDisplayGamutPtr display_gamut = self.cast<IADLXDisplayGamut*>();
        adlx_bool supported = false;
        display_gamut->IsSupported6500kWhitePoint(&supported);
        return supported;
        })
        .def("IsSupported7500kWhitePoint", [](py::object self) {
        IADLXDisplayGamutPtr display_gamut = self.cast<IADLXDisplayGamut*>();
        adlx_bool supported = false;
        display_gamut->IsSupported7500kWhitePoint(&supported);
        return supported;
        })
        .def("IsSupported9300kWhitePoint", [](py::object self) {
        IADLXDisplayGamutPtr display_gamut = self.cast<IADLXDisplayGamut*>();
        adlx_bool supported = false;
        display_gamut->IsSupported9300kWhitePoint(&supported);
        return supported;
        })
        .def("IsSupportedAdobeRgbColorSpace", [](py::object self) {
        IADLXDisplayGamutPtr display_gamut = self.cast<IADLXDisplayGamut*>();
        adlx_bool supported = false;
        display_gamut->IsSupportedAdobeRgbColorSpace(&supported);
        return supported;
        })
        .def("IsSupportedCCIR2020ColorSpace", [](py::object self) {
        IADLXDisplayGamutPtr display_gamut = self.cast<IADLXDisplayGamut*>();
        adlx_bool supported = false;
        display_gamut->IsSupportedCCIR2020ColorSpace(&supported);
        return supported;
        })
        .def("IsSupportedCCIR601ColorSpace", [](py::object self) {
        IADLXDisplayGamutPtr display_gamut = self.cast<IADLXDisplayGamut*>();
        adlx_bool supported = false;
        display_gamut->IsSupportedCCIR601ColorSpace(&supported);
        return supported;
        })
        .def("IsSupportedCCIR709ColorSpace", [](py::object self) {
        IADLXDisplayGamutPtr display_gamut = self.cast<IADLXDisplayGamut*>();
        adlx_bool supported = false;
        display_gamut->IsSupportedCCIR709ColorSpace(&supported);
        return supported;
        })
        .def("IsSupportedCIERgbColorSpace", [](py::object self) {
        IADLXDisplayGamutPtr display_gamut = self.cast<IADLXDisplayGamut*>();
        adlx_bool supported = false;
        display_gamut->IsSupportedCIERgbColorSpace(&supported);
        return supported;
        })
        .def("IsSupportedCustomColorSpace", [](py::object self) {
        IADLXDisplayGamutPtr display_gamut = self.cast<IADLXDisplayGamut*>();
        adlx_bool supported = false;
        display_gamut->IsSupportedCustomColorSpace(&supported);
        return supported;
        })
        .def("IsSupportedCustomWhitePoint", [](py::object self) {
        IADLXDisplayGamutPtr display_gamut = self.cast<IADLXDisplayGamut*>();
        adlx_bool supported;
        display_gamut->IsSupportedCustomWhitePoint(&supported);
        return supported;
        })
        .def("SetGamut1", [](py::object self, ADLX_RGB customWhitePoint, ADLX_GamutColorSpace customGamut) {
        IADLXDisplayGamutPtr display_gamut = self.cast<IADLXDisplayGamut*>();
        ADLX_RESULT ret_api = display_gamut->SetGamut(customWhitePoint, customGamut);
        return ret_api;
        })
        .def("SetGamut2", [](py::object self, ADLX_RGB customWhitePoint, ADLX_GAMUT_SPACE predefinedGamutSpace) {
        IADLXDisplayGamutPtr display_gamut = self.cast<IADLXDisplayGamut*>();
        ADLX_RESULT ret_api = display_gamut->SetGamut(customWhitePoint, predefinedGamutSpace);
        return ret_api;
        })
        .def("SetGamut3", [](py::object self, ADLX_WHITE_POINT predefinedWhitePoint, ADLX_GamutColorSpace customGamut) {
        IADLXDisplayGamutPtr display_gamut = self.cast<IADLXDisplayGamut*>();
        ADLX_RESULT ret_api = display_gamut->SetGamut(predefinedWhitePoint, customGamut);
        return ret_api;
        })
        .def("SetGamut4", [](py::object self, ADLX_WHITE_POINT predefinedWhitePoint, ADLX_GAMUT_SPACE predefinedGamutSpace) {
        IADLXDisplayGamutPtr display_gamut = self.cast<IADLXDisplayGamut*>();
        ADLX_RESULT ret_api = display_gamut->SetGamut(predefinedWhitePoint, predefinedGamutSpace);
        return ret_api;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXDisplayGamutPtr display_gamut = self.cast<IADLXDisplayGamut*>();
        IADLXDisplayGamutPtr ppInterface = nullptr;
        display_gamut->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


        // IADLXDisplayGammaChangedEvent
        py::class_<IADLXDisplayGammaChangedEvent, IADLXChangedEvent, PyDisplayGammaChangedEvent, IADLXInterfacePtr_T<IADLXDisplayGammaChangedEvent>>(m, "IADLXDisplayGammaChangedEvent")
            //.def(py::init<>())
        .def("GetDisplay", [](py::object self) {
        IADLXDisplayGammaChangedEventPtr gamma_changed_event = self.cast<IADLXDisplayGammaChangedEvent*>();
        IADLXDisplayPtr display;
        gamma_changed_event->GetDisplay(&display);
        return display;
        })
        .def("IsDeGammaChanged", [](py::object self) {
        IADLXDisplayGammaChangedEventPtr gamma_changed_event = self.cast<IADLXDisplayGammaChangedEvent*>();
        adlx_bool change_bool = gamma_changed_event->IsDeGammaChanged();
        return change_bool;
        })
        .def("IsGammaCoefficientChanged", [](py::object self) {
        IADLXDisplayGammaChangedEventPtr gamma_changed_event = self.cast<IADLXDisplayGammaChangedEvent*>();
        adlx_bool change_bool = gamma_changed_event->IsGammaCoefficientChanged();
        return change_bool;
        })
        .def("IsGammaRampChanged", [](py::object self) {
            IADLXDisplayGammaChangedEventPtr gamma_changed_event = self.cast<IADLXDisplayGammaChangedEvent*>();
        adlx_bool change_bool = gamma_changed_event->IsGammaRampChanged();
        return change_bool;
        })
        .def("IsReGammaChanged", [](py::object self) {
        IADLXDisplayGammaChangedEventPtr gamma_changed_event = self.cast<IADLXDisplayGammaChangedEvent*>();
        adlx_bool change_bool = gamma_changed_event->IsReGammaChanged();
        return change_bool;
        });


        // IADLXDisplaySettingsChangedEvent
        py::class_<IADLXDisplaySettingsChangedEvent, IADLXChangedEvent, PyDisplaySettingsChangedEvent, IADLXInterfacePtr_T<IADLXDisplaySettingsChangedEvent>>(m, "IADLXDisplaySettingsChangedEvent")
        //.def(py::init<>())
        .def("GetDisplay", [](py::object self) {
        IADLXDisplaySettingsChangedEventPtr display_settings_changed_event = self.cast<IADLXDisplaySettingsChangedEvent*>();
        IADLXDisplayPtr display;
        display_settings_changed_event->GetDisplay(&display);
        return display;
        })
        .def("IsColorDepthChanged", [](py::object self) {
        IADLXDisplaySettingsChangedEventPtr display_settings_changed_event = self.cast<IADLXDisplaySettingsChangedEvent*>();
        adlx_bool change_bool = display_settings_changed_event->IsColorDepthChanged();
        return change_bool;
        })
        .def("IsCustomColorBrightnessChanged", [](py::object self) {
        IADLXDisplaySettingsChangedEventPtr display_settings_changed_event = self.cast<IADLXDisplaySettingsChangedEvent*>();
        adlx_bool change_bool = display_settings_changed_event->IsCustomColorBrightnessChanged();
        return change_bool;
        })
        .def("IsCustomColorContrastChanged", [](py::object self) {
        IADLXDisplaySettingsChangedEventPtr display_settings_changed_event = self.cast<IADLXDisplaySettingsChangedEvent*>();
        adlx_bool change_bool = display_settings_changed_event->IsCustomColorContrastChanged();
        return change_bool;
        })
        .def("IsCustomColorHueChanged", [](py::object self) {
        IADLXDisplaySettingsChangedEventPtr display_settings_changed_event = self.cast<IADLXDisplaySettingsChangedEvent*>();
        adlx_bool change_bool = display_settings_changed_event->IsCustomColorHueChanged();
        return change_bool;
        })
        .def("IsCustomColorSaturationChanged", [](py::object self) {
        IADLXDisplaySettingsChangedEventPtr display_settings_changed_event = self.cast<IADLXDisplaySettingsChangedEvent*>();
        adlx_bool change_bool = display_settings_changed_event->IsCustomColorSaturationChanged();
        return change_bool;
        })
        .def("IsCustomColorTemperatureChanged", [](py::object self) {
        IADLXDisplaySettingsChangedEventPtr display_settings_changed_event = self.cast<IADLXDisplaySettingsChangedEvent*>();
        adlx_bool change_bool = display_settings_changed_event->IsCustomColorTemperatureChanged();
        return change_bool;
        })
        .def("IsCustomResolutionChanged", [](py::object self) {
        IADLXDisplaySettingsChangedEventPtr display_settings_changed_event = self.cast<IADLXDisplaySettingsChangedEvent*>();
        adlx_bool change_bool = display_settings_changed_event->IsCustomResolutionChanged();
        return change_bool;
        })
        .def("IsFreeSyncChanged", [](py::object self) {
        IADLXDisplaySettingsChangedEventPtr display_settings_changed_event = self.cast<IADLXDisplaySettingsChangedEvent*>();
        adlx_bool change_bool = display_settings_changed_event->IsFreeSyncChanged();
        return change_bool;
        })
        .def("IsGPUScalingChanged", [](py::object self) {
        IADLXDisplaySettingsChangedEventPtr display_settings_changed_event = self.cast<IADLXDisplaySettingsChangedEvent*>();
        adlx_bool change_bool = display_settings_changed_event->IsGPUScalingChanged();
        return change_bool;
        })
        .def("IsHDCPChanged", [](py::object self) {
        IADLXDisplaySettingsChangedEventPtr display_settings_changed_event = self.cast<IADLXDisplaySettingsChangedEvent*>();
        adlx_bool change_bool = display_settings_changed_event->IsHDCPChanged();
        return change_bool;
        })
        .def("IsIntegerScalingChanged", [](py::object self) {
        IADLXDisplaySettingsChangedEventPtr display_settings_changed_event = self.cast<IADLXDisplaySettingsChangedEvent*>();
        adlx_bool change_bool = display_settings_changed_event->IsIntegerScalingChanged();
        return change_bool;
        })
        .def("IsPixelFormatChanged", [](py::object self) {
        IADLXDisplaySettingsChangedEventPtr display_settings_changed_event = self.cast<IADLXDisplaySettingsChangedEvent*>();
        adlx_bool change_bool = display_settings_changed_event->IsPixelFormatChanged();
        return change_bool;
        })
        .def("IsScalingModeChanged", [](py::object self) {
        IADLXDisplaySettingsChangedEventPtr display_settings_changed_event = self.cast<IADLXDisplaySettingsChangedEvent*>();
        adlx_bool change_bool = display_settings_changed_event->IsScalingModeChanged();
        return change_bool;
        })
        .def("IsVSRChanged", [](py::object self) {
        IADLXDisplaySettingsChangedEventPtr display_settings_changed_event = self.cast<IADLXDisplaySettingsChangedEvent*>();
        adlx_bool change_bool = display_settings_changed_event->IsVSRChanged();
        return change_bool;
        })
        .def("IsVariBrightChanged", [](py::object self) {
        IADLXDisplaySettingsChangedEventPtr display_settings_changed_event = self.cast<IADLXDisplaySettingsChangedEvent*>();
        adlx_bool change_bool = display_settings_changed_event->IsVariBrightChanged();
        return change_bool;
        })
        .def("IsDisplayBlankingChanged", [](py::object self) {
        IADLXDisplaySettingsChangedEventPtr settingsEvent = self.cast<IADLXDisplaySettingsChangedEvent*>();
        IADLXDisplaySettingsChangedEvent1Ptr settingsEvent1(settingsEvent);
        if (settingsEvent1 == nullptr)
        {
            return false;
        }
        return settingsEvent1->IsDisplayBlankingChanged();
        })
        .def("IsDisplayConnectivityExperienceChanged", [](py::object self) {
        IADLXDisplaySettingsChangedEventPtr settingsEvent = self.cast<IADLXDisplaySettingsChangedEvent*>();
        IADLXDisplaySettingsChangedEvent2Ptr settingsEvent2(settingsEvent);
        if (settingsEvent2 == nullptr)
        {
            return false;
        }
        return settingsEvent2->IsDisplayConnectivityExperienceChanged();
        })
        .def("IsDisplayDynamicRefreshRateControlChanged", [](py::object self) {
        IADLXDisplaySettingsChangedEventPtr settingsEvent = self.cast<IADLXDisplaySettingsChangedEvent*>();
        IADLXDisplaySettingsChangedEvent3Ptr settingsEvent3(settingsEvent);
        if (settingsEvent3 == nullptr)
        {
            return false;
        }
        return settingsEvent3->IsDisplayDynamicRefreshRateControlChanged();
        })
        .def("IsFreeSyncColorAccuracyChanged", [](py::object self) {
        IADLXDisplaySettingsChangedEventPtr settingsEvent = self.cast<IADLXDisplaySettingsChangedEvent*>();
        IADLXDisplaySettingsChangedEvent3Ptr settingsEvent3(settingsEvent);
        if (settingsEvent3 == nullptr)
        {
            return false;
        }
        return settingsEvent3->IsFreeSyncColorAccuracyChanged();
        });
}
