#pragma once

#include <pluginterfaces/base/funknown.h>
#include <pluginterfaces/vst/vsttypes.h>

namespace WordCel {
namespace Gate {

// IDs for real-time processor (RT) and controller (GUI), for each of Debug/Release targets
#ifndef NDEBUG
static const ::Steinberg::FUID GateProcessorUID(0x3ae1dfcd, 0xa76d9a7c, 0x46651350, 0xd2213295);
static const ::Steinberg::FUID GateControllerUID(0xcd6ea0ce, 0x3b3f57e1, 0x89e8ee1e, 0xedbfa0aa);
#else
static const ::Steinberg::FUID GateProcessorUID(0x051db945, 0x0a2fa604, 0x270d772f, 0x8450a284);
static const ::Steinberg::FUID GateControllerUID(0x426a48dc, 0x5a60271d, 0x63aa0db8, 0x81b06a63);
#endif

// IDs for parameters
enum EGateParamID : Steinberg::Vst::ParamID
{
  // bypass
  kBypassId = 1000,
    
  // plugin params
  kSyncRateId = 1001,
  kGateDepthId = 1002,
};

}
}
