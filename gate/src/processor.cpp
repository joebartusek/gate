#include "processor.h"
#include "CIDs.h"

#include <iostream>
#include <public.sdk/source/vst/vstaudioprocessoralgo.h>
#include <base/source/fstreamer.h>
#include <pluginterfaces/base/ibstream.h>
#include <pluginterfaces/vst/ivstparameterchanges.h>
#include <pluginterfaces/vst/ivstprocesscontext.h>

namespace WordCel {
namespace Gate {

using namespace Steinberg::Vst;
using namespace std;

// constructor
GateProcessor::GateProcessor ()
{
  // register controller class associated with processor
  setControllerClass (GateControllerUID);
  
  // require tempo and time signature from host
  processContextRequirements.needTempo ();

  // init (set pointer to audio processing function; take float/32bit data type by default)
  processAudioPtr = &GateProcessor::processAudio<float>;
}

// intializer
tresult PLUGIN_API GateProcessor::initialize (FUnknown* context)
{
  // initialize parent
  tresult result = AudioEffect::initialize (context);
  if (result != kResultTrue)
    return kResultFalse;

  // add input and output buses (stereo->stereo)
  addAudioInput (STR16 ("AudioInput"), SpeakerArr::kStereo);
  addAudioOutput (STR16 ("AudioOutput"), SpeakerArr::kStereo);

  return kResultTrue;
}

// IAudioProcessor::setBusArrangments() implementation supporting only stereo->stereo
tresult PLUGIN_API GateProcessor::setBusArrangements (SpeakerArrangement* inputs,
                                                      int32 numIns,
                                                      SpeakerArrangement* outputs,
                                                      int32 numOuts)
{
  // support only one input bus and one output bus, with in and out having same number of channels
  if (numIns == 1 && numOuts == 1 && inputs[0] == outputs[0])
  {
    return AudioEffect::setBusArrangements (inputs, numIns, outputs, numOuts);
  }
  return kResultFalse;
}

// promise that 32- and 64-bit processing are both supported
tresult PLUGIN_API GateProcessor::canProcessSampleSize (int32 symbolicSampleSize)
{
  return (symbolicSampleSize == kSample32 ||
	  symbolicSampleSize == kSample64) ?
    kResultTrue :
    kResultFalse;
}

// AudioEffect setupProcessing() override to handle data types
tresult PLUGIN_API GateProcessor::setupProcessing (ProcessSetup& setup)
{
  if (setup.symbolicSampleSize == kSample64)
    processAudioPtr = &GateProcessor::processAudio<double>;
  else
    processAudioPtr = &GateProcessor::processAudio<float>;

  // call parent method
  return AudioEffect::setupProcessing (setup);
}

// Gate processAudio()
template <typename SampleType>
tresult GateProcessor::processAudio (ProcessData& data)
{
  SpeakerArrangement arr;
  getBusArrangement (kOutput, 0, arr);
  auto numChannels = SpeakerArr::getChannelCount (arr);
  
  auto** currentInputBuffers = (SampleType**)getChannelBuffersPointer (processSetup, data.inputs[0]);
  auto** currentOutputBuffers = (SampleType**)getChannelBuffersPointer (processSetup, data.outputs[0]);

  SampleType tmp;
  
  if (mBypass)
  {
    // bypass behavior: copy input to output
    for (int32 channel = 0; channel < numChannels; channel++)
    {
      SampleType* input = currentInputBuffers[channel];
      SampleType* output = currentOutputBuffers[channel];
      for (int32 n = 0; n < data.numSamples; n++)
      {
        tmp = input[n];
        output[n] = tmp;
      }
    }
  }
  else
  {
    // plugin behavior: apply volume gate
    
    // get playhead location if provided by host
    long projectTimeSamples = 0;
    if (data.processContext != NULL)
    {
      projectTimeSamples = data.processContext->projectTimeSamples;
    }
    
    for (int32 channel = 0; channel < numChannels; channel++)
    {
      SampleType* input = currentInputBuffers[channel];
      SampleType* output = currentOutputBuffers[channel];
      for (int32 n = 0; n < data.numSamples; n++)
      {
        tmp = input[n];
        
        // compute playhead segment
	// tempo is always quarter notes per second, regardless of time signature
        double samplesPerSegment = mSampleRate * mSyncRate * (1/mTempo) * 60 * 4;
        long segment = (projectTimeSamples + n) / samplesPerSegment;
        
        bool isGated = segment % 2 != 0;
	
        if (isGated)
        {
          // apply volume reduction
          tmp *= mGateDepth;
        }
	
        output[n] = tmp;
      }
    }
  }

  return kResultOk;
}

// Perform parameter changes
void GateProcessor::doParameterChanges (IParameterChanges& changes)
{
  auto numParamsChanged = changes.getParameterCount ();
  for (int32 index = 0; index < numParamsChanged; index++)
  {
    if (auto queue = changes.getParameterData (index))
    {
      ParamValue value;
      int32 sampleOffset;
      auto numPoints = queue->getPointCount ();
      switch (queue->getParameterId ())
      {
        case kBypassId:
        {
          if (queue->getPoint (numPoints - 1, sampleOffset, value) == kResultTrue)
          {
            mBypass = value > 0.5 ? true : false;
          }
          break;
        }
        case kSyncRateId:
        {
          if (queue->getPoint (numPoints - 1, sampleOffset, value) == kResultTrue)
          {
            mSyncRate = value;
          }
          break;
        }
        case kGateDepthId:
        {
          if (queue->getPoint (numPoints - 1, sampleOffset, value) == kResultTrue)
          {
            mGateDepth = value;
          }
          break;
        }
      }
    }
  }
}

// IAudioProcessor process()
tresult PLUGIN_API GateProcessor::process (ProcessData& data)
{
  // process context variable changes, if any
  if (data.processContext && data.processContext->state)
    {
      if (data.processContext->sampleRate != mSampleRate)
      {
        mSampleRate = data.processContext->sampleRate;
      }
      if (ProcessContext::kTempoValid) {
	if (data.processContext->tempo != mTempo)
        {
          mTempo = data.processContext->tempo;
        }
      }
    }
  
  // process plugin parameter changes, if any
  if (data.inputParameterChanges)
  {
    doParameterChanges (*data.inputParameterChanges);
  }
  
  if (data.numInputs == 0 || data.numOutputs == 0 || data.numSamples == 0)
  {
    // nothing to do
    return kResultOk;
  }
  
  // call appropriately typed protected audio processing function
  return (this->*processAudioPtr) (data);
}

// Component setState(), called when project (or preset) is loaded
tresult PLUGIN_API GateProcessor::setState(IBStream *state)
{
  if (!state)
    return kResultFalse;
  
  IBStreamer streamer (state, kLittleEndian);
  
  int32 savedBypass = 0;
  if (streamer.readInt32 (savedBypass) == false)
    return kResultFalse;

  mBypass = savedBypass > 0;
  
  double savedSyncRate = 0;
  if (streamer.readDouble(savedSyncRate) == false)
    return kResultFalse;
  
  mSyncRate = savedSyncRate;
  
  double savedGateDepth = 0;
  if (streamer.readDouble(savedGateDepth) == false)
    return kResultFalse;
  
  mGateDepth = savedGateDepth;
  
  return kResultOk;
}

// Component getState(), called when saving project (or preset)
tresult PLUGIN_API GateProcessor::getState(IBStream *state)
{
  IBStreamer streamer (state, kLittleEndian);
  
  streamer.writeInt32 (mBypass ? 1 : 0);
  streamer.writeDouble (mSyncRate);
  streamer.writeDouble (mGateDepth);
  
  return kResultOk;
}

}
}
