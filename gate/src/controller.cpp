#include "controller.h"
#include "CIDs.h"

#include <base/source/fstreamer.h>
#include <pluginterfaces/base/ibstream.h>
#include <vstgui/plugin-bindings/vst3editor.h>

namespace WordCel {
namespace Gate {

tresult PLUGIN_API GateController::initialize (FUnknown* context)
{
  tresult result = EditController::initialize (context);
  if (result != kResultOk)
    return result;
  
  // add bypass parameter to controller
  int32 bypassStepCount = 1;
  Vst::ParamValue bypassDefaultVal = 0;
  int32 bypassFlags = Vst::ParameterInfo::kCanAutomate | Vst::ParameterInfo::kIsBypass;
  int bypassTag = kBypassId;
  parameters.addParameter (STR16 ("Bypass"),
                           nullptr,
                           bypassStepCount,
                           bypassDefaultVal,
                           bypassFlags,
                           bypassTag);
  
  // add sync rate parameter to controller
  int32 syncRateStepCount = 1;
  Vst::ParamValue syncRateDefaultVal = 0.125;
  int32 syncRateFlags = Vst::ParameterInfo::kCanAutomate;
  int syncRateTag = kSyncRateId;
  parameters.addParameter(STR16 ("SyncRate"),
                          nullptr,
                          syncRateStepCount,
                          syncRateDefaultVal,
                          syncRateFlags,
                          syncRateTag);
  
  // add gate depth parameter to controller
  int32 gateDepthStepCount = 1;
  Vst::ParamValue gateDepthDefaultVal = 0.15;
  int32 gateDepthFlags = Vst::ParameterInfo::kCanAutomate;
  int gateDepthTag = kGateDepthId;
  parameters.addParameter(STR16 ("GateDepth"),
                          nullptr,
                          gateDepthStepCount,
                          gateDepthDefaultVal,
                          gateDepthFlags,
                          gateDepthTag);
  
  return kResultOk;
}

IPlugView* PLUGIN_API GateController::createView(const char* name)
{
  if (strcmp (name, Vst::ViewType::kEditor) == 0)
  {
    return new VSTGUI::VST3Editor (this, "view", "gate.uidesc");
  }
  return nullptr;
}

tresult PLUGIN_API GateController::setComponentState(IBStream *state)
{
  if (!state)
    return kResultFalse;
  
  IBStreamer streamer (state, kLittleEndian);
  
  // read and set bypass value
  int32 bypassState;
  if (streamer.readInt32 (bypassState) == false)
    return kResultFalse;
  this->setParamNormalized (kBypassId, bypassState ? 1 : 0);

  return kResultOk;
}

}
}
