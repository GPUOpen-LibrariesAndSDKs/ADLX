//
// Copyright (c) 2021 - 2024 Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

// Include pybind11 depends
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>

// Include SDK depends
#include "../../../../SDK/ADLXHelper/Windows/Cpp/ADLXHelper.h"
#include "../../../../SDK/Include/IDisplays.h"

namespace py = pybind11;
using namespace adlx;

// Always needed for custom holder types
PYBIND11_DECLARE_HOLDER_TYPE(T, IADLXInterfacePtr_T<T>, true);

// Only needed if the type's `.get()` goes by another name
namespace pybind11 {
	namespace detail {
		template <typename T>
		struct holder_helper<IADLXInterfacePtr_T<T>> { // <-- specialization
			static const T *get(const IADLXInterfacePtr_T<T> &p) { return p.GetPtr(); }
		};
	}
}

class PySystem : public IADLXSystem
{
public:
	using IADLXSystem::IADLXSystem;

	ADLX_RESULT  HybridGraphicsType(ADLX_HG_TYPE* hgType)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			HybridGraphicsType
		);
	}

	ADLX_RESULT  GetGPUs(IADLXGPUList** ppGPUs)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			GetGPUs
		);
	}

	ADLX_RESULT  QueryInterface(const wchar_t* interfaceId, void** ppInterface)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			QueryInterface
		);
	}

	ADLX_RESULT  GetDisplaysServices(IADLXDisplayServices** ppDispServices)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			GetDisplaysServices
		);
	}

	ADLX_RESULT  GetDesktopsServices(IADLXDesktopServices** ppDeskServices)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			GetDesktopsServices
		);
	}

	ADLX_RESULT  GetGPUsChangedHandling(IADLXGPUsChangedHandling** ppGPUsChangedHandling)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			GetGPUsChangedHandling
		);
	}

	ADLX_RESULT  EnableLog(ADLX_LOG_DESTINATION mode, ADLX_LOG_SEVERITY severity, IADLXLog* pLogger, const wchar_t* fileName)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			EnableLog
		);
	}

	ADLX_RESULT  Get3DSettingsServices(IADLX3DSettingsServices** pp3DSettingsServices)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			Get3DSettingsServices
		);
	}

	ADLX_RESULT  GetGPUTuningServices(IADLXGPUTuningServices** ppGPUTuningServices)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			GetGPUTuningServices
		);
	}

	ADLX_RESULT  GetPerformanceMonitoringServices(IADLXPerformanceMonitoringServices** ppPerformanceMonitoringServices)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			GetPerformanceMonitoringServices
		);
	}

	ADLX_RESULT  TotalSystemRAM(adlx_uint* ramMB)override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			TotalSystemRAM
		);
	}

	ADLX_RESULT  GetI2C(IADLXGPU *pGPU, IADLXI2C **ppI2C) override {
		PYBIND11_OVERRIDE_PURE(
			ADLX_RESULT,
			IADLXSystem,
			GetI2C
		);
	}
};

class PyDisplayService : public IADLXDisplayServices
{
public:
	using IADLXDisplayServices::IADLXDisplayServices;

	adlx_long  Acquire() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Acquire);
	}

	adlx_long  Release() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Release);
	}

	ADLX_RESULT  QueryInterface(const wchar_t* interfaceId, void** ppInterface) {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXInterface, QueryInterface);
	}

	ADLX_RESULT GetNumberOfDisplays(adlx_uint* numDisplays) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetNumberOfDisplays);
	}

	ADLX_RESULT GetDisplays(IADLXDisplayList** ppDisplay) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetDisplays);
	}

	ADLX_RESULT Get3DLUT(IADLXDisplay* pDisplay, IADLXDisplay3DLUT** ppDisp3DLUT) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, Get3DLUT);
	}

	ADLX_RESULT GetGamut(IADLXDisplay* pDisplay, IADLXDisplayGamut** ppDispGamut) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetGamut);
	}

	ADLX_RESULT GetGamma(IADLXDisplay* pDisplay, IADLXDisplayGamma** ppDispGamma) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetGamma);
	}

	ADLX_RESULT GetDisplayChangedHandling(IADLXDisplayChangedHandling** ppDisplayChangeHandling) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetDisplayChangedHandling);
	}

	ADLX_RESULT  GetFreeSync(IADLXDisplay* pDisplay, IADLXDisplayFreeSync** ppFreeSync) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetFreeSync);
	}

	ADLX_RESULT  GetVirtualSuperResolution(IADLXDisplay* pDisplay, IADLXDisplayVSR** ppVSR) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetVirtualSuperResolution);
	}

	ADLX_RESULT  GetGPUScaling(IADLXDisplay* pDisplay, IADLXDisplayGPUScaling** ppGPUScaling) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetGPUScaling);
	}

	ADLX_RESULT  GetScalingMode(IADLXDisplay* pDisplay, IADLXDisplayScalingMode** ppScalingMode) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetScalingMode);
	}

	ADLX_RESULT  GetIntegerScaling(IADLXDisplay* pDisplay, IADLXDisplayIntegerScaling** ppIntegerScaling) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetIntegerScaling);
	}

	ADLX_RESULT  GetColorDepth(IADLXDisplay* pDisplay, IADLXDisplayColorDepth** ppColorDepth) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetColorDepth);
	}

	ADLX_RESULT  GetPixelFormat(IADLXDisplay* pDisplay, IADLXDisplayPixelFormat** ppPixelFormat) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetPixelFormat);
	}

	ADLX_RESULT  GetCustomColor(IADLXDisplay* pDisplay, IADLXDisplayCustomColor** ppCustomColor) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetCustomColor);
	}

	ADLX_RESULT  GetHDCP(IADLXDisplay* pDisplay, IADLXDisplayHDCP** ppHDCP) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetHDCP);
	}

	ADLX_RESULT  GetCustomResolution(IADLXDisplay* pDisplay, IADLXDisplayCustomResolution** ppCustomResolution) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetCustomResolution);
	}

    ADLX_RESULT  GetVariBright(IADLXDisplay* pDisplay, IADLXDisplayVariBright** ppVariBright) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayServices, GetVariBright);
    }
};

class PyDisplay : public IADLXDisplay
{
public:
	using IADLXDisplay::IADLXDisplay;

	adlx_long  Acquire() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Acquire);
	}

	adlx_long  Release() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Release);
	}

	ADLX_RESULT  QueryInterface(const wchar_t* interfaceId, void** ppInterface) {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXInterface, QueryInterface);
	}

	ADLX_RESULT ManufacturerID(adlx_uint* manufacturerID) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, ManufacturerID);
	}

	ADLX_RESULT DisplayType(ADLX_DISPLAY_TYPE* displayType) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, DisplayType);
	}

	ADLX_RESULT ConnectorType(ADLX_DISPLAY_CONNECTOR_TYPE* connectType) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, ConnectorType);
	}

	ADLX_RESULT Name(const char** displayName) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, Name);
	}

	ADLX_RESULT EDID(const char** edid) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, EDID);
	}

	ADLX_RESULT NativeResolution(adlx_int* maxHResolution, adlx_int* maxVResolution) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, NativeResolution);
	}

	ADLX_RESULT RefreshRate(adlx_double* refreshRate) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, RefreshRate);
	}

	ADLX_RESULT PixelClock(adlx_uint* pixelClock) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, PixelClock);
	}

	ADLX_RESULT ScanType(ADLX_DISPLAY_SCAN_TYPE* scanType) const override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, ScanType);
	}

	ADLX_RESULT GetGPU(IADLXGPU** ppGPU) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, GetGPU);
	}

    ADLX_RESULT UniqueId(adlx_size* uniqueId) {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplay, UniqueId);
    }
};

class PyDisplayChangeHandler : public IADLXDisplayChangedHandling
{
public:
	using IADLXDisplayChangedHandling::IADLXDisplayChangedHandling;

	adlx_long  Acquire() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Acquire);
	}

	adlx_long  Release() override {
		PYBIND11_OVERRIDE_PURE(adlx_long, IADLXInterface, Release);
	}

	ADLX_RESULT  QueryInterface(const wchar_t* interfaceId, void** ppInterface) {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXInterface, QueryInterface);
	}

	ADLX_RESULT AddDisplayListEventListener(IADLXDisplayListChangedListener *pDisplayListChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayChangedHandling, AddDisplayListEventListener);
	}

	ADLX_RESULT RemoveDisplayListEventListener(IADLXDisplayListChangedListener *pDisplayListChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayChangedHandling, RemoveDisplayListEventListener);
	}

	ADLX_RESULT AddDisplayGamutEventListener(IADLXDisplayGamutChangedListener *pDisplayGamutChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayChangedHandling, AddDisplayGamutEventListener);
	}

	ADLX_RESULT RemoveDisplayGamutEventListener(IADLXDisplayGamutChangedListener *pDisplayGamutChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayChangedHandling, RemoveDisplayGamutEventListener);
	}

	ADLX_RESULT AddDisplayGammaEventListener(IADLXDisplayGammaChangedListener *pDisplayGammaChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayChangedHandling, AddDisplayGammaEventListener);
	}

	ADLX_RESULT RemoveDisplayGammaEventListener(IADLXDisplayGammaChangedListener *pDisplayGammaChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayChangedHandling, RemoveDisplayGammaEventListener);
	}

	ADLX_RESULT AddDisplay3DLUTEventListener(IADLXDisplay3DLUTChangedListener *pDisplay3DLUTChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayChangedHandling, AddDisplay3DLUTEventListener);
	}

	ADLX_RESULT RemoveDisplay3DLUTEventListener(IADLXDisplay3DLUTChangedListener *pDisplay3DLUTChangedListener) override {
		PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayChangedHandling, RemoveDisplay3DLUTEventListener);
	}

    ADLX_RESULT AddDisplaySettingsEventListener(IADLXDisplaySettingsChangedListener* pDisplaySettingsChangedListener) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayChangedHandling, AddDisplaySettingsEventListener);
    }

    ADLX_RESULT RemoveDisplaySettingsEventListener(IADLXDisplaySettingsChangedListener* pDisplaySettingsChangedListener) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayChangedHandling, RemoveDisplaySettingsEventListener);
    }
};

// Callback
class DisplayListCallBack : public IADLXDisplayListChangedListener
{
public:

	adlx_bool OnDisplayListChanged(IADLXDisplayList *pNewDisplay) override {
		std::vector<IADLXDisplayPtr> list;
		for (adlx_uint s = pNewDisplay->Begin(); s != pNewDisplay->End(); s++) {
			IADLXDisplayPtr item;
			pNewDisplay->At(s, &item);
			list.emplace_back(item);
		}
		if (m_call) {
			return m_call(list);
		}
		return true;
	}

	std::function<bool(std::vector<IADLXDisplayPtr>)> m_call;
};

PYBIND11_MODULE(ADLXPybind, m) {

	m.doc() = "ADLX python binding for display & displayListChangedEvent";

	// Define the objects that get exposed to python
	// ADLX_RESULT
	py::enum_<ADLX_RESULT>(m, "ADLX_RESULT")
		.value("ADLX_OK", ADLX_RESULT::ADLX_OK)
		.value("ADLX_ALREADY_ENABLED", ADLX_RESULT::ADLX_ALREADY_ENABLED)
		.value("ADLX_ALREADY_INITIALIZED", ADLX_RESULT::ADLX_ALREADY_INITIALIZED)
		.value("ADLX_FAIL", ADLX_RESULT::ADLX_FAIL)
		.value("ADLX_INVALID_ARGS", ADLX_RESULT::ADLX_INVALID_ARGS)
		.value("ADLX_BAD_VER", ADLX_RESULT::ADLX_BAD_VER)
		.value("ADLX_UNKNOWN_INTERFACE", ADLX_RESULT::ADLX_UNKNOWN_INTERFACE)
		.value("ADLX_TERMINATED", ADLX_RESULT::ADLX_TERMINATED)
		.value("ADLX_ADL_INIT_ERROR", ADLX_RESULT::ADLX_ADL_INIT_ERROR)
		.value("ADLX_NOT_FOUND", ADLX_RESULT::ADLX_NOT_FOUND)
		.value("ADLX_INVALID_OBJECT", ADLX_RESULT::ADLX_INVALID_OBJECT)
		.value("ADLX_ORPHAN_OBJECTS", ADLX_RESULT::ADLX_ORPHAN_OBJECTS)
		.value("ADLX_NOT_SUPPORTED", ADLX_RESULT::ADLX_NOT_SUPPORTED)
		.export_values();

	// ADLX_DISPLAY_TYPE
	py::enum_<ADLX_DISPLAY_TYPE>(m, "ADLX_DISPLAY_TYPE")
		.value("DISPLAY_TYPE_UNKOWN", ADLX_DISPLAY_TYPE::DISPLAY_TYPE_UNKOWN)
		.value("DISPLAY_TYPE_MONITOR", ADLX_DISPLAY_TYPE::DISPLAY_TYPE_MONITOR)
		.value("DISPLAY_TYPE_TELEVISION", ADLX_DISPLAY_TYPE::DISPLAY_TYPE_TELEVISION)
		.value("DISPLAY_TYPE_LCD_PANEL", ADLX_DISPLAY_TYPE::DISPLAY_TYPE_LCD_PANEL)
		.value("DISPLAY_TYPE_DIGITAL_FLAT_PANEL", ADLX_DISPLAY_TYPE::DISPLAY_TYPE_DIGITAL_FLAT_PANEL)
		.value("DISPLAY_TYPE_COMPONENT_VIDEO", ADLX_DISPLAY_TYPE::DISPLAY_TYPE_COMPONENT_VIDEO)
		.value("DISPLAY_TYPE_PROJECTOR", ADLX_DISPLAY_TYPE::DISPLAY_TYPE_PROJECTOR)
		.export_values();

	// ADLX_DISPLAY_CONNECTOR_TYPE
	py::enum_<ADLX_DISPLAY_CONNECTOR_TYPE>(m, "ADLX_DISPLAY_CONNECTOR_TYPE")
		.value("DISPLAY_CONTYPE_UNKNOWN", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_UNKNOWN)
		.value("DISPLAY_CONTYPE_VGA", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_VGA)
		.value("DISPLAY_CONTYPE_DVI_D", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_DVI_D)
		.value("DISPLAY_CONTYPE_DVI_I", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_DVI_I)
		.value("DISPLAY_CONTYPE_CVDONGLE_NTSC", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_CVDONGLE_NTSC)
		.value("DISPLAY_CONTYPE_CVDONGLE_JPN", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_CVDONGLE_JPN)
		.value("DISPLAY_CONTYPE_CVDONGLE_NONI2C_JPN", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_CVDONGLE_NONI2C_JPN)
		.value("DISPLAY_CONTYPE_CVDONGLE_NONI2C_NTSC", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_CVDONGLE_NONI2C_NTSC)
		.value("DISPLAY_CONTYPE_HDMI_TYPE_A", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_HDMI_TYPE_A)
		.value("DISPLAY_CONTYPE_HDMI_TYPE_B", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_HDMI_TYPE_B)
		.value("DISPLAY_CONTYPE_SVIDEO", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_SVIDEO)
		.value("DISPLAY_CONTYPE_COMPOSITE", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_COMPOSITE)
		.value("DISPLAY_CONTYPE_RCA_3COMPONENT", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_RCA_3COMPONENT)
		.value("DISPLAY_CONTYPE_DISPLAYPORT", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_DISPLAYPORT)
		.value("DISPLAY_CONTYPE_EDP", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_EDP)
		.value("DISPLAY_CONTYPE_WIRELESSDISPLAY", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_WIRELESSDISPLAY)
		.value("DISPLAY_CONTYPE_USB_TYPE_C", ADLX_DISPLAY_CONNECTOR_TYPE::DISPLAY_CONTYPE_USB_TYPE_C)
		.export_values();

	// ADLX_DISPLAY_SCAN_TYPE
	py::enum_<ADLX_DISPLAY_SCAN_TYPE>(m, "ADLX_DISPLAY_SCAN_TYPE")
		.value("PROGRESSIVE", ADLX_DISPLAY_SCAN_TYPE::PROGRESSIVE)
		.value("INTERLACED", ADLX_DISPLAY_SCAN_TYPE::INTERLACED)
		.export_values();

	// ADLX_helper
	py::class_<ADLXHelper>(m, "ADLXHelper")
		.def(py::init<>())
		.def("InitializeWithCallerAdl", &ADLXHelper::InitializeWithCallerAdl)
		.def("Initialize", &ADLXHelper::Initialize)
		.def("InitializeWithIncompatibleDriver", &ADLXHelper::InitializeWithIncompatibleDriver)
		.def("Terminate", &ADLXHelper::Terminate)
		.def("QueryVersion", &ADLXHelper::QueryVersion)
		.def("GetSystemServices", &ADLXHelper::GetSystemServices, py::return_value_policy::reference)
		.def("GetAdlMapping", &ADLXHelper::GetAdlMapping);

	// System
	py::class_<IADLXSystem, PySystem>(m, "IADLXSystem")
		.def(py::init<>())
		.def("GetDisplaysServices", [](py::object self) {
		IADLXSystem *sys = self.cast<IADLXSystem*>();
		IADLXDisplayServicesPtr displayService = nullptr;
		sys->GetDisplaysServices(&displayService);
		return displayService;
	}, py::return_value_policy::move);

	// displayService
	py::class_<IADLXDisplayServices, PyDisplayService, IADLXInterfacePtr_T<IADLXDisplayServices>>(m, "IADLXDisplayServices")
		.def(py::init<>())
		.def("GetNumberOfDisplays", [](py::object self) {
		IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
		adlx_uint num;
		disService->GetNumberOfDisplays(&num);
		return num;
	})
		.def("GetDisplays", [](py::object self) {
		IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
		IADLXDisplayListPtr displayList = nullptr;
		disService->GetDisplays(&displayList);
		std::vector<IADLXDisplayPtr> list;
		for (adlx_uint s = displayList->Begin(); s != displayList->End(); s++) {
			IADLXDisplayPtr item;
			displayList->At(s, &item);
			list.emplace_back(std::move(item));
		}
		return list;
	}, py::return_value_policy::move)
		.def("GetDisplayChangedHandling", [](py::object self) {
		IADLXDisplayServices* disService = self.cast<IADLXDisplayServices*>();
		IADLXDisplayChangedHandlingPtr handler = nullptr;
		disService->GetDisplayChangedHandling(&handler);
		return handler;
	}, py::return_value_policy::move);

	// Display
	py::class_<IADLXDisplay, PyDisplay, IADLXInterfacePtr_T<IADLXDisplay>>(m, "IADLXDisplay")
		.def(py::init<>())
		.def("name", [](py::object self) {
		IADLXDisplay *display = self.cast<IADLXDisplay*>();
		const char *name = nullptr;
		display->Name(&name);
		return py::str(name);
	})
		.def("type", [](py::object self) {
		IADLXDisplay *display = self.cast<IADLXDisplay*>();
		ADLX_DISPLAY_TYPE type;
		display->DisplayType(&type);
		return type;
	})
		.def("connectType", [](py::object self) {
		IADLXDisplay *display = self.cast<IADLXDisplay*>();
		ADLX_DISPLAY_CONNECTOR_TYPE type;
		display->ConnectorType(&type);
		return type;
	})
		.def("ManufacturerID", [](py::object self) {
		IADLXDisplay *display = self.cast<IADLXDisplay*>();
		adlx_uint id;
		display->ManufacturerID(&id);
		return id;
	})
		.def("EDID", [](py::object self) {
		IADLXDisplay *display = self.cast<IADLXDisplay*>();
		const char* str = nullptr;
		display->EDID(&str);
		return std::string(str);
	})
		.def("resolution", [](py::object self) {
		IADLXDisplay *display = self.cast<IADLXDisplay*>();
		adlx_int h, v;
		display->NativeResolution(&h, &v);
		return std::tuple<adlx_int, adlx_int>(h,v);
	})
		.def("RefreshRate", [](py::object self) {
		IADLXDisplay *display = self.cast<IADLXDisplay*>();
		adlx_double value;
		display->RefreshRate(&value);
		return value;
	})
		.def("PixelClock", [](py::object self) {
		IADLXDisplay *display = self.cast<IADLXDisplay*>();
		adlx_uint value;
		display->PixelClock(&value);
		return value;
	})
		.def("ScanType", [](py::object self) {
		IADLXDisplay *display = self.cast<IADLXDisplay*>();
		ADLX_DISPLAY_SCAN_TYPE type;
		display->ScanType(&type);
		return type;
	})
        .def("UniqueId", [](py::object self) {
        IADLXDisplay *display = self.cast<IADLXDisplay*>();
        adlx_size id;
        display->UniqueId(&id);
        return id;
    });

	// Display change handler
	py::class_<IADLXDisplayChangedHandling, PyDisplayChangeHandler, IADLXInterfacePtr_T<IADLXDisplayChangedHandling>>(m, "IADLXDisplayChangedHandling")
		.def(py::init<>())
		.def("AddDisplayListEventListener", [](py::object self, DisplayListCallBack* call) {
			IADLXDisplayChangedHandling *handler = self.cast<IADLXDisplayChangedHandling*>();
			return handler->AddDisplayListEventListener(call);
		})
		.def("RemoveDisplayListEventListener", [](py::object self, DisplayListCallBack* call) {
			IADLXDisplayChangedHandling *handler = self.cast<IADLXDisplayChangedHandling*>();
			return handler->RemoveDisplayListEventListener(call);
		});

	// Callback for displaylist
	py::class_<DisplayListCallBack>(m, "DisplayListCallBack")
		.def(py::init<>())
		.def_readwrite("call", &DisplayListCallBack::m_call);
}