//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

#include "bind_common.h"

void bind_misc(py::module_& m)
{
    // IADLXI2C
        py::class_<IADLXI2C, IADLXInterface, PyI2C, IADLXInterfacePtr_T<IADLXI2C>>(m, "IADLXI2C")
        .def("IsSupported", [](py::object self, ADLX_I2C_LINE line, adlx_int address) {
        IADLXI2CPtr i2cService = self.cast<IADLXI2C*>();
        adlx_bool isSupported = false;
        i2cService->IsSupported(line, address, &isSupported);
        return isSupported;
        })
        .def("Read", [](py::object self, ADLX_I2C_LINE line, adlx_int speed, adlx_int address, adlx_int offset, adlx_int dataSize) {
        std::vector<adlx_byte> data(dataSize, 0);
        IADLXI2CPtr i2cService = self.cast<IADLXI2C*>();
        ADLX_RESULT ret_read = i2cService->Read(line, speed, address, offset, dataSize, data.data());

        std::vector<uint8_t> list(data.begin(), data.end());
        return py::make_tuple(ret_read, list);
        })
        .def("RepeatedStartRead", [](py::object self, ADLX_I2C_LINE line, adlx_int speed, adlx_int address, adlx_int offset, adlx_int dataSize) {
        std::vector<adlx_byte> data(dataSize, 0);
        IADLXI2CPtr i2cService = self.cast<IADLXI2C*>();
        ADLX_RESULT ret_repeated_start_read = i2cService->RepeatedStartRead(line, speed, address, offset, dataSize, data.data());

        std::vector<uint8_t> list(data.begin(), data.end());
        return py::make_tuple(ret_repeated_start_read, list);
        })
        .def("Version", [](py::object self) {
        IADLXI2CPtr i2cService = self.cast<IADLXI2C*>();
        adlx_int major = 0;
        adlx_int minor = 0;
        i2cService->Version(&major, &minor);
        std::string major_str = std::to_string(major);
        std::string minor_str = std::to_string(minor);
        std::string version_for_py = major_str + "." + minor_str;
        return version_for_py;
        })
        .def("Write", [](py::object self, ADLX_I2C_LINE line, adlx_int speed, adlx_int address, adlx_int offset, adlx_int dataSize, py::bytes data) {
        IADLXI2CPtr i2cService = self.cast<IADLXI2C*>();
        std::string buf = data;
        ADLX_RESULT ret_write = i2cService->Write(line, speed, address, offset, dataSize, reinterpret_cast<adlx_byte*>(buf.data()));
        return ret_write;
        })
        .def("QueryInterface", [](py::object self, const wchar_t* interfaceId) {
        IADLXI2CPtr i2cService = self.cast<IADLXI2C*>();
        IADLXI2CPtr ppInterface = nullptr;
        i2cService->QueryInterface(interfaceId, reinterpret_cast<void**>(&ppInterface));
        return ppInterface;
        }, py::return_value_policy::move);

        // IADLMapping
        py::class_<IADLMapping, PyIADLMapping>(m, "IADLMapping")
        //.def(py::init<>())
        .def("ADLIdsFromADLXDesktop", [](py::object self, IADLXDesktop* pDesktop) {
        IADLMapping* adl_mapping = self.cast<IADLMapping*>();
        adlx_int adapterIndex;
        adlx_int VidPnSourceId;
        adlx_int bus;
        adlx_int device;
        adlx_int function;
        adl_mapping->ADLIdsFromADLXDesktop(pDesktop, &adapterIndex, &VidPnSourceId, &bus, &device, &function);

        PyADLIdsFromADLX py_adl_ids_from_adlx;
        py_adl_ids_from_adlx.adapterIndex = adapterIndex;
        py_adl_ids_from_adlx.VidPnSourceId = VidPnSourceId;
        py_adl_ids_from_adlx.bus = bus;
        py_adl_ids_from_adlx.device = device;
        py_adl_ids_from_adlx.function = function;
        return py_adl_ids_from_adlx;
        })
        .def("ADLIdsFromADLXDisplay", [](py::object self, IADLXDisplay* pDisplay) {
        IADLMapping* adl_mapping = self.cast<IADLMapping*>();
        adlx_int adapterIndex;
        adlx_int VidPnSourceId;
        adlx_int bus;
        adlx_int device;
        adlx_int function;
        adl_mapping->ADLIdsFromADLXDisplay(pDisplay, &adapterIndex, &VidPnSourceId, &bus, &device, &function);

        PyADLIdsFromADLX py_adl_ids_from_adlx;
        py_adl_ids_from_adlx.adapterIndex = adapterIndex;
        py_adl_ids_from_adlx.VidPnSourceId = VidPnSourceId;
        py_adl_ids_from_adlx.bus = bus;
        py_adl_ids_from_adlx.device = device;
        py_adl_ids_from_adlx.function = function;
        return py_adl_ids_from_adlx;
        })
        .def("AdlAdapterIndexFromADLXGPU", [](py::object self, IADLXGPU* ppGPU) -> std::variant<adlx_int, py::none> {
        IADLMapping* adl_mapping = self.cast<IADLMapping*>();
        adlx_int adapterIndex = 0;
        ADLX_RESULT ret_api = adl_mapping->AdlAdapterIndexFromADLXGPU(ppGPU, &adapterIndex);
        if (ADLX_SUCCEEDED(ret_api)) {
            return adapterIndex;
        }
        return py::none();
        })
        .def("BdfFromADLXGPU", [](py::object self, IADLXGPU* ppGPU) {
        IADLMapping* adl_mapping = self.cast<IADLMapping*>();
        adlx_int bus;
        adlx_int device;
        adlx_int function;
        adl_mapping->BdfFromADLXGPU(ppGPU, &bus, &device, &function);

        PyBdfFromADLXGPU py_bdf_from_adlx_gpu;
        py_bdf_from_adlx_gpu.bus = bus;
        py_bdf_from_adlx_gpu.device = device;
        py_bdf_from_adlx_gpu.function = function;
        return py_bdf_from_adlx_gpu;
        })
        .def("GetADLXDesktopFromADLIds", [](py::object self, adlx_int adapterIndex, adlx_int VidPnSource, adlx_int bus, adlx_int device, adlx_int function) {
        IADLMapping* adl_mapping = self.cast<IADLMapping*>();
        IADLXDesktopPtr pDesktop = nullptr;
        adl_mapping->GetADLXDesktopFromADLIds(adapterIndex, VidPnSource, bus, device, function, &pDesktop);
        return pDesktop;
        }, py::return_value_policy::move)
        .def("GetADLXDisplayFromADLIds", [](py::object self, adlx_int adapterIndex, adlx_int displayIndex, adlx_int bus, adlx_int device, adlx_int function) {
        IADLMapping* adl_mapping = self.cast<IADLMapping*>();
        IADLXDisplayPtr ppDisplay = nullptr;
        adl_mapping->GetADLXDisplayFromADLIds(adapterIndex, displayIndex, bus, device, function, &ppDisplay);
        return ppDisplay;
        }, py::return_value_policy::move)
        .def("GetADLXGPUFromAdlAdapterIndex", [](py::object self, adlx_int adlAdapterIndex) {
        IADLMapping* adl_mapping = self.cast<IADLMapping*>();
        IADLXGPUPtr ppGPU = nullptr;
        adl_mapping->GetADLXGPUFromAdlAdapterIndex(adlAdapterIndex, &ppGPU);
        return ppGPU;
        }, py::return_value_policy::move)
        .def("GetADLXGPUFromBdf", [](py::object self, adlx_int bus, adlx_int device, adlx_int function) {
        IADLMapping* adl_mapping = self.cast<IADLMapping*>();
        IADLXGPUPtr ppGPU = nullptr;
        adl_mapping->GetADLXGPUFromBdf(bus, device, function, &ppGPU);
        return ppGPU;
        }, py::return_value_policy::move);


        // custom structs/classes
        py::class_<PyADLIdsFromADLX>(m, "PyADLIdsFromADLX")
        .def(py::init<>())
        .def_readwrite("adapterIndex", &PyADLIdsFromADLX::adapterIndex)
        .def_readwrite("VidPnSourceId", &PyADLIdsFromADLX::VidPnSourceId)
        .def_readwrite("bus", &PyADLIdsFromADLX::bus)
        .def_readwrite("device", &PyADLIdsFromADLX::device)
        .def_readwrite("function", &PyADLIdsFromADLX::function);

        py::class_<PyBdfFromADLXGPU>(m, "PyBdfFromADLXGPU")
        .def(py::init<>())
        .def_readwrite("bus", &PyBdfFromADLXGPU::bus)
        .def_readwrite("device", &PyBdfFromADLXGPU::device)
        .def_readwrite("function", &PyBdfFromADLXGPU::function);
}
