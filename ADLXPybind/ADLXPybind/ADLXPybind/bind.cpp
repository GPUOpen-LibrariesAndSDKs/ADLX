//
// Copyright Advanced Micro Devices, Inc. All rights reserved.
//
//-------------------------------------------------------------------------------------------------
#include "bind_common.h"

PYBIND11_MODULE(ADLX, m) {
    m.doc() = "ADLX python binding for all interfaces";

    // Register all ADLX enumerations
    bind_enums(m);
    bind_core(m);
    bind_desktop(m);
    bind_display(m);
    bind_tuning(m);
    bind_gpu(m);
    bind_3d_settings(m);
    bind_performance(m);
    bind_misc(m);
    bind_power_tuning(m);
    bind_multimedia(m);
}