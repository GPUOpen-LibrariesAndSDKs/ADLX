// Copyright Advanced Micro Devices, Inc. All rights reserved.
#include <pybind11/pybind11.h>

#include "../../../SDK/Include/IDisplaySettings.h"

namespace py = pybind11;
using namespace adlx;

class PyDisplayConnectivityExperience : public IADLXDisplayConnectivityExperience
{
public:
    using IADLXDisplayConnectivityExperience::IADLXDisplayConnectivityExperience;

    ADLX_RESULT IsSupportedHDMIQualityDetection(adlx_bool* supported) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayConnectivityExperience, IsSupportedHDMIQualityDetection);
    }

    ADLX_RESULT IsSupportedDPLink(adlx_bool* supported) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayConnectivityExperience, IsSupportedDPLink);
    }

    ADLX_RESULT IsEnabledHDMIQualityDetection(adlx_bool* enabled) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayConnectivityExperience, IsEnabledHDMIQualityDetection);
    }

    ADLX_RESULT SetEnabledHDMIQualityDetection(adlx_bool enabled) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayConnectivityExperience, SetEnabledHDMIQualityDetection);
    }

    ADLX_RESULT GetDPLinkRate(ADLX_DP_LINK_RATE* linkRate) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayConnectivityExperience, GetDPLinkRate);
    }

    ADLX_RESULT GetNumberOfActiveLanes(adlx_uint* numActiveLanes) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayConnectivityExperience, GetNumberOfActiveLanes);
    }

    ADLX_RESULT GetNumberOfTotalLanes(adlx_uint* numTotalLanes) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayConnectivityExperience, GetNumberOfTotalLanes);
    }

    ADLX_RESULT GetRelativePreEmphasis(adlx_int* relativePreEmphasis) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayConnectivityExperience, GetRelativePreEmphasis);
    }

    ADLX_RESULT SetRelativePreEmphasis(adlx_int relativePreEmphasis) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayConnectivityExperience, SetRelativePreEmphasis);
    }

    ADLX_RESULT GetRelativeVoltageSwing(adlx_int* relativeVoltageSwing) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayConnectivityExperience, GetRelativeVoltageSwing);
    }

    ADLX_RESULT SetRelativeVoltageSwing(adlx_int relativeVoltageSwing) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayConnectivityExperience, SetRelativeVoltageSwing);
    }

    ADLX_RESULT IsEnabledLinkProtection(adlx_bool* enabled) override {
        PYBIND11_OVERRIDE_PURE(ADLX_RESULT, IADLXDisplayConnectivityExperience, IsEnabledLinkProtection);
    }
};
