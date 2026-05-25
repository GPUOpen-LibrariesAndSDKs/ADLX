//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

#include "bind_common.h"

void bind_desktop(py::module_& m)
{
    // DesktopService
    py::class_<IADLXDesktopServices, IADLXInterface, PyDesktopServices, IADLXInterfacePtr_T<IADLXDesktopServices>>(m, "IADLXDesktopServices")
    //.def(py::init<>())
    .def("GetDesktopChangedHandling", [](py::object self) {
    IADLXDesktopServices *desktopServices = self.cast<IADLXDesktopServices*>();
    IADLXDesktopChangedHandlingPtr ppDesktopChangedHandling;
    desktopServices->GetDesktopChangedHandling(&ppDesktopChangedHandling);
    return ppDesktopChangedHandling;
    }, py::return_value_policy::move)
    .def("GetDesktops", [](py::object self) {
    IADLXDesktopServices *desktopServices = self.cast<IADLXDesktopServices*>();
    IADLXDesktopListPtr desktopList;
    desktopServices->GetDesktops(&desktopList);
    std::vector<IADLXDesktopPtr> list;
    for (adlx_uint s = desktopList->Begin(); s != desktopList->End(); s++) {
        IADLXDesktopPtr item;
        desktopList->At(s, &item);
        list.emplace_back(std::move(item));
    }
    return list;
    }, py::return_value_policy::move)
    .def("GetNumberOfDesktops", [](py::object self) -> std::variant<adlx_uint, py::none> {
    IADLXDesktopServices *desktopServices = self.cast<IADLXDesktopServices*>();
    adlx_uint numDesktops;
    ADLX_RESULT ret = desktopServices->GetNumberOfDesktops(&numDesktops);
    if (ADLX_SUCCEEDED(ret))
        return numDesktops;
    return py::none();
    })
    .def("GetSimpleEyefinity", [](py::object self) {
    IADLXDesktopServices *desktopServices = self.cast<IADLXDesktopServices*>();
    IADLXSimpleEyefinityPtr simpleEyefinity;
    desktopServices->GetSimpleEyefinity(&simpleEyefinity);
    return simpleEyefinity;
    }, py::return_value_policy::move)
    .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
    IADLXDesktopServicesPtr desktopServices = self.cast<IADLXDesktopServices*>();
    IADLXDesktopServicesPtr ppInterface = nullptr;
    desktopServices->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
    return ppInterface;
    }, py::return_value_policy::move);

    // Callback for DesktopListChangedListener
    py::class_<IADLXDesktopListChangedListener, PyDesktopListChangedListenerCallback>(m, "PyDesktopListChangedListenerCallback")
        .def(py::init<>());

    // DesktopList
        py::class_<IADLXDesktopList, IADLXList, PyDesktopList, IADLXInterfacePtr_T<IADLXDesktopList>>(m, "IADLXDesktopList")
        //.def(py::init<>())
        .def("Add_Back", [](py::object self, IADLXDesktop* pItem) {
        IADLXDesktopListPtr desktopList = self.cast<IADLXDesktopList*>();
        ADLX_RESULT retDesktopList = desktopList->Add_Back(pItem);
        return retDesktopList;
        })
        .def("At", [](py::object self, const adlx_uint location) {
        IADLXDesktopListPtr desktopList = self.cast<IADLXDesktopList*>();
        IADLXDesktopPtr ppItem;
        desktopList->At(location, &ppItem);
        return ppItem;
        });


        // DisplayList
        py::class_<IADLXDisplayList, IADLXList, PyDisplayList, IADLXInterfacePtr_T<IADLXDisplayList>>(m, "IADLXDisplayList")
        //.def(py::init<>())
        .def("Add_Back", [](py::object self, IADLXDisplay* pItem) {
        IADLXDisplayListPtr displayList = self.cast<IADLXDisplayList*>();
        ADLX_RESULT retDisplayList = displayList->Add_Back(pItem);
        return retDisplayList;
        })
        .def("At", [](py::object self, const adlx_uint location) {
        IADLXDisplayListPtr displayList = self.cast<IADLXDisplayList*>();
        IADLXDisplayPtr ppItem;
        displayList->At(location, &ppItem);
        return ppItem;
        });

        // Desktop
        py::class_<IADLXDesktop, PyDesktop, IADLXInterfacePtr_T<IADLXDesktop>>(m, "IADLXDesktop")
        //.def(py::init<>())
        .def("GetDisplays", [](py::object self) {
        IADLXDesktopPtr desktopPtr = self.cast<IADLXDesktop*>();
        IADLXDisplayListPtr displayList;
        desktopPtr->GetDisplays(&displayList);
        std::vector<IADLXDisplayPtr> list;
        for (adlx_uint s = displayList->Begin(); s != displayList->End(); s++) {
            IADLXDisplayPtr item;
            displayList->At(s, &item);
            list.emplace_back(std::move(item));
        }
        return list;
        })
        .def("GetNumberOfDisplays", [](py::object self) -> std::variant<adlx_uint, py::none> {
        IADLXDesktopPtr desktopPtr = self.cast<IADLXDesktop*>();
        adlx_uint numDisplays;
        ADLX_RESULT ret = desktopPtr->GetNumberOfDisplays(&numDisplays);
        if (ADLX_SUCCEEDED(ret))
            return numDisplays;
        return py::none();
        })
        .def("Orientation", [](py::object self) -> std::variant<ADLX_ORIENTATION, py::none> {
        IADLXDesktopPtr desktopPtr = self.cast<IADLXDesktop*>();
        ADLX_ORIENTATION orientation;
        ADLX_RESULT ret = desktopPtr->Orientation(&orientation);
        if (ADLX_SUCCEEDED(ret))
            return orientation;
        return py::none();
        })
        .def("Size", [](py::object self) {
        IADLXDesktopPtr desktopPtr = self.cast<IADLXDesktop*>();
        adlx_int width;
        adlx_int height;
        py::dict dict;
        desktopPtr->Size(&width, &height);
        dict["width"] = width;
        dict["height"] = height;
        return dict;
        })
        .def("TopLeft", [](py::object self) {
        IADLXDesktopPtr desktopPtr = self.cast<IADLXDesktop*>();
        ADLX_Point locationTopLeft;
        py::dict dict;
        desktopPtr->TopLeft(&locationTopLeft);
        dict["x"] = locationTopLeft.x;
        dict["y"] = locationTopLeft.y;
        return dict;
        })
        .def("Type", [](py::object self) -> std::variant<ADLX_DESKTOP_TYPE, py::none> {
        IADLXDesktopPtr desktopPtr = self.cast<IADLXDesktop*>();
        ADLX_DESKTOP_TYPE desktopType;
        ADLX_RESULT ret = desktopPtr->Type(&desktopType);
        if (ADLX_SUCCEEDED(ret))
            return desktopType;
        return py::none();
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXDesktopPtr desktopPtr = self.cast<IADLXDesktop*>();
        IADLXDesktopPtr ppInterface = nullptr;
        desktopPtr->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


        // SimpleEyefinity
        py::class_<IADLXSimpleEyefinity, IADLXInterface, PySimpleEyefinity, IADLXInterfacePtr_T<IADLXSimpleEyefinity>>(m, "IADLXSimpleEyefinity")
        //.def(py::init<>())
        .def("Create", [](py::object self) {
        IADLXSimpleEyefinityPtr simpleEyefinityDesktop = self.cast<IADLXSimpleEyefinity*>();
        IADLXEyefinityDesktopPtr ppEyefinityDesktop;
        simpleEyefinityDesktop->Create(&ppEyefinityDesktop);
        return ppEyefinityDesktop;
        }, py::return_value_policy::move)
        .def("Destroy", [](py::object self, IADLXEyefinityDesktop* pDesktop) {
        IADLXSimpleEyefinityPtr simpleEyefinityDesktop = self.cast<IADLXSimpleEyefinity*>();
        ADLX_RESULT retDestroy = simpleEyefinityDesktop->Destroy(pDesktop);
        return retDestroy;
        })
        .def("DestroyAll", [](py::object self) {
        IADLXSimpleEyefinityPtr simpleEyefinityDesktop = self.cast<IADLXSimpleEyefinity*>();
        ADLX_RESULT retDestroyAll = simpleEyefinityDesktop->DestroyAll();
        return retDestroyAll;
        })
        .def("IsSupported", [](py::object self) {
        IADLXSimpleEyefinityPtr simpleEyefinityDesktop = self.cast<IADLXSimpleEyefinity*>();
        adlx_bool supported = false;
        simpleEyefinityDesktop->IsSupported(&supported);
        return supported;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXSimpleEyefinityPtr simpleEyefinityDesktop = self.cast<IADLXSimpleEyefinity*>();
        IADLXSimpleEyefinityPtr ppInterface = nullptr;
        simpleEyefinityDesktop->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);


        // EyefinityDesktop
        py::class_<IADLXEyefinityDesktop, IADLXInterface, PyEyefinityDesktop, IADLXInterfacePtr_T<IADLXEyefinityDesktop>>(m, "IADLXEyefinityDesktop")
        //.def(py::init<>())
        .def("DisplayOrientation", [](py::object self, adlx_uint row, adlx_uint col) -> std::variant<ADLX_ORIENTATION, py::none> {
        IADLXEyefinityDesktopPtr eyefinityDesktop = self.cast<IADLXEyefinityDesktop*>();
        ADLX_ORIENTATION displayOrientation;
        ADLX_RESULT ret = eyefinityDesktop->DisplayOrientation(row, col, &displayOrientation);
        if (ADLX_SUCCEEDED(ret))
            return displayOrientation;
        return py::none();
        })
        .def("DisplaySize", [](py::object self, adlx_uint row, adlx_uint col) {
        IADLXEyefinityDesktopPtr eyefinityDesktop = self.cast<IADLXEyefinityDesktop*>();
        adlx_int displayWidth;
        adlx_int displayHeight;
        eyefinityDesktop->DisplaySize(row, col, &displayWidth, &displayHeight);
        return std::tuple<adlx_int, adlx_int>(displayWidth, displayHeight);
        })
        .def("DisplayTopLeft", [](py::object self, adlx_uint row, adlx_uint col) {
        IADLXEyefinityDesktopPtr eyefinityDesktop = self.cast<IADLXEyefinityDesktop*>();
        ADLX_Point displayLocationTopLeft;
        eyefinityDesktop->DisplayTopLeft(row, col, &displayLocationTopLeft);
        py::dict dict;
        dict["x"] = displayLocationTopLeft.x;
        dict["y"] = displayLocationTopLeft.y;
        return dict;
        })
        .def("GetDisplay", [](py::object self, adlx_uint row, adlx_uint col) {
        IADLXEyefinityDesktopPtr eyefinityDesktop = self.cast<IADLXEyefinityDesktop*>();
        IADLXDisplayPtr ppDisplay;
        eyefinityDesktop->GetDisplay(row, col, &ppDisplay);
        return ppDisplay;
        })
        .def("GridSize", [](py::object self) {
        IADLXEyefinityDesktopPtr eyefinityDesktop = self.cast<IADLXEyefinityDesktop*>();
        adlx_uint rows, cols;
        eyefinityDesktop->GridSize(&rows, &cols);
        py::dict dict;
        dict["rows"] = rows;
        dict["col"] = cols;
        return dict;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXEyefinityDesktopPtr eyefinityDesktop = self.cast<IADLXEyefinityDesktop*>();
        IADLXEyefinityDesktopPtr ppInterface = nullptr;
        eyefinityDesktop->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);

    // IADLXDesktopChangedHandling
        py::class_<IADLXDesktopChangedHandling, IADLXInterface, PyDesktopChangedHandling, IADLXInterfacePtr_T<IADLXDesktopChangedHandling>>(m, "IADLXDesktopChangedHandling")
        //.def(py::init<>())
        .def("AddDesktopListEventListener", [](py::object self, IADLXDesktopListChangedListener* pDesktopListChangedListener) {
        IADLXDesktopChangedHandlingPtr ppDesktopChangedHandling = self.cast< IADLXDesktopChangedHandling*>();;
        ADLX_RESULT ret_add_desktop_listener = ppDesktopChangedHandling->AddDesktopListEventListener(pDesktopListChangedListener);
        return ret_add_desktop_listener;
        })
        .def("RemoveDesktopListEventListener", [](py::object self, IADLXDesktopListChangedListener* pDesktopListChangedListener) {
        IADLXDesktopChangedHandlingPtr ppDesktopChangedHandling = self.cast< IADLXDesktopChangedHandling*>();;
        ADLX_RESULT ret_remove_desktop_listener = ppDesktopChangedHandling->RemoveDesktopListEventListener(pDesktopListChangedListener);
        return ret_remove_desktop_listener;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXDesktopChangedHandlingPtr ppDesktopChangedHandling = self.cast< IADLXDesktopChangedHandling*>();;
        IADLXDesktopChangedHandlingPtr ppInterface = nullptr;
        ppDesktopChangedHandling->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);
}
