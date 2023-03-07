#pragma once

#include <public.sdk/source/vst/vstaudioeffect.h>
#include <pluginterfaces/vst/ivstparameterchanges.h>

namespace WordCel {
namespace Gate {

using namespace Steinberg;

// processor class. must declare createInstance method to be called on instantiation
class GateProcessor : public Vst::AudioEffect
{
public:
  // constructor
  GateProcessor ();

  // initializer (from IPluginBase)
  tresult PLUGIN_API initialize (FUnknown* context) SMTG_OVERRIDE;

  // IAudioProcessor methods
  tresult PLUGIN_API setBusArrangements (Vst::SpeakerArrangement* inputs,
                                         int32 numIns,
                                         Vst::SpeakerArrangement* outputs,
                                         int32 numOuts) SMTG_OVERRIDE;
  tresult PLUGIN_API canProcessSampleSize (int32 symbolicSampleSize) SMTG_OVERRIDE;
  tresult PLUGIN_API setupProcessing (Vst::ProcessSetup& setup) SMTG_OVERRIDE;
  tresult PLUGIN_API process (Vst::ProcessData& data) SMTG_OVERRIDE;

  // Component methods
  tresult PLUGIN_API setState (IBStream* state) SMTG_OVERRIDE;
  tresult PLUGIN_API getState (IBStream* state) SMTG_OVERRIDE;

  // createInstance method called on instantiation (inline)
  static FUnknown* createInstance (void*) { return (IAudioProcessor*)new GateProcessor (); }

protected:
  // parameter change method
  void doParameterChanges (Vst::IParameterChanges& changes);

  // audio processing method
  template <typename SampleType>
  tresult processAudio (Vst::ProcessData& data);
  tresult (GateProcessor::*processAudioPtr) (Vst::ProcessData& data);

  // bypass
  bool mBypass = false;
    
  // context vars
  double mTempo {120}; // bpm
  double mSampleRate {48000}; // samples per second
  double mBeatUnit {4}; // 4 beats per measure, i.e. quarter-note pulse
  
  // plugin params
  double mSyncRate {0.125}; // default 1/8 note gate sync
  double mGateDepth {0.15};
};

}
}
