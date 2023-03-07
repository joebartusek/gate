#include <public.sdk/source/main/pluginfactory.h>

#include "CIDs.h"
#include "version.h"
#include "processor.h"
#include "controller.h"

using namespace Steinberg;
using namespace WordCel::Gate;

BEGIN_FACTORY (stringCompanyName, stringCompanyWeb, stringCompanyEmail, PFactoryInfo::kNoFlags)

DEF_CLASS2 (INLINE_UID_FROM_FUID(GateProcessorUID),
	    PClassInfo::kManyInstances,
	    kVstAudioEffectClass,      
	    stringPluginName,
	    0,                          
 	    Vst::PlugType::kFxDynamics,
	    FULL_VERSION_STR,           
	    kVstVersionString,          
	    GateProcessor::createInstance)
	    
DEF_CLASS2 (INLINE_UID_FROM_FUID(GateControllerUID),
	    PClassInfo::kManyInstances,
	    kVstComponentControllerClass,
	    stringPluginName"Controller",
	    0,                           
	    "",                          
	    FULL_VERSION_STR,            
	    kVstVersionString,           
	    GateController::createInstance)

END_FACTORY
