//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------

#pragma once

#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>

#include "PyDep.h"

#include "../../../SDK/Include/ADLXDefines.h"
#include "CustomStructures.h"

#include <string>
#include <locale>
#include <codecvt>

#ifdef _WIN32
#include <windows.h>
#include <system_error>
#include <stdexcept>

// Convert from local encoding to UTF-8 using Windows APIs
inline std::string local_to_utf8(const std::string& local_str) {
    if (local_str.empty()) return {};

    // Step 1: Convert from local encoding to wide string (UTF-16)
    int wide_size = MultiByteToWideChar(
        CP_ACP,            // Source is current ANSI code page (local encoding)
        MB_ERR_INVALID_CHARS,
        local_str.c_str(),
        static_cast<int>(local_str.size()),
        nullptr,
        0
    );

    if (wide_size == 0) {
        std::cerr << "Failed to get size for wide string conversion (MultiByteToWideChar)" << std::endl;
        return local_str;
    }

    std::wstring wide_str(wide_size, L'\0');
    if (MultiByteToWideChar(
        CP_ACP,
        MB_ERR_INVALID_CHARS,
        local_str.c_str(),
        static_cast<int>(local_str.size()),
        &wide_str[0],
        wide_size
    ) == 0) {
        std::cerr << "Failed to convert to wide string (MultiByteToWideChar)" << std::endl;
        return local_str;
    }

    // Step 2: Convert from wide string (UTF-16) to UTF-8
    int utf8_size = WideCharToMultiByte(
        CP_UTF8,           // Target is UTF-8
        0,
        wide_str.c_str(),
        static_cast<int>(wide_str.size()),
        nullptr,
        0,
        nullptr,
        nullptr
    );

    if (utf8_size == 0) {
        std::cerr << "Failed to get size for UTF-8 conversion (WideCharToMultiByte)" << std::endl;
        return local_str;
    }

    std::string utf8_str(utf8_size, '\0');
    if (WideCharToMultiByte(
        CP_UTF8,
        0,
        wide_str.c_str(),
        static_cast<int>(wide_str.size()),
        &utf8_str[0],
        utf8_size,
        nullptr,
        nullptr
    ) == 0) {
        std::cerr << "Failed to convert to UTF-8 (WideCharToMultiByte)" << std::endl;
        return local_str;
    }

    return utf8_str;
}
#else
inline std::string local_to_utf8(const std::string& local_str) {
    // For non-Windows platforms, we assume the input is already in UTF-8
    // or handle it as needed. This is a placeholder implementation.
    return local_str; // No conversion needed for UTF-8
}
#endif

// Convert from wide string to UTF-8
inline std::string wlocal_to_utf8(const std::wstring& local_str) {
#ifdef _WIN32
    if (local_str.empty()) return {};
    // Step 1: Convert from wide string (UTF-16) to UTF-8
    int utf8_size = WideCharToMultiByte(
        CP_UTF8,           // Target is UTF-8
        0,
        local_str.c_str(),
        static_cast<int>(local_str.size()),
        nullptr,
        0,
        nullptr,
        nullptr
    );
    if (utf8_size == 0) {
        std::cerr << "Failed to get size for UTF-8 conversion (WideCharToMultiByte)" << std::endl;
        return {};
    }
    std::string utf8_str(utf8_size, '\0');
    if (WideCharToMultiByte(
        CP_UTF8,
        0,
        local_str.c_str(),
        static_cast<int>(local_str.size()),
        &utf8_str[0],
        utf8_size,
        nullptr,
        nullptr
    ) == 0) {
        std::cerr << "Failed to convert to UTF-8 (WideCharToMultiByte)" << std::endl;
        return {};
    }
    return utf8_str;
#else
    // For non-Windows platforms, convert wstring to UTF-8 using codecvt
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(local_str);
#endif
}

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

//-----------------------------------------------------------------------------
// Function declarations for each binding module
// Each bind_*.cpp file implements one of these functions
//-----------------------------------------------------------------------------

void bind_enums(py::module_& m);
void bind_core(py::module_& m);
void bind_desktop(py::module_& m);
void bind_display(py::module_& m);
void bind_tuning(py::module_& m);
void bind_3d_settings(py::module_& m);
void bind_gpu(py::module_& m);
void bind_performance(py::module_& m);
void bind_misc(py::module_& m);
void bind_power_tuning(py::module_& m);
void bind_multimedia(py::module_& m);
