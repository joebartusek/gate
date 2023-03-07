#pragma once

#include <vstgui/plugin-bindings/vst3editor.h>
#include <public.sdk/source/vst/vsteditcontroller.h>
#include <pluginterfaces/vst/ivstparameterfunctionname.h>

namespace WordCel {
namespace Gate {

using namespace Steinberg;

class GateController : public Vst::EditController,
                            public VSTGUI::VST3EditorDelegate
{
public:
  // createInstance called on instantiation
  static FUnknown* createInstance (void*)
  {
    return (IEditController*)new GateController ();
  }

  // initialization method (from IPluginBase)
  tresult PLUGIN_API initialize (FUnknown* context) SMTG_OVERRIDE;

  // from EditController
  IPlugView* PLUGIN_API createView (const char* name) SMTG_OVERRIDE;
  tresult PLUGIN_API setComponentState (IBStream* state) SMTG_OVERRIDE;

  // define interfaces or something?
  OBJ_METHODS (GateController, EditController)
  DELEGATE_REFCOUNT (EditController)
};

}
}
