set(target ${project})
set(target_auv3 ${project}_auv3)

### configure audio unit (wrapped) target
set(gate_auv3_app_sources
  "src/ViewController.m"
  "src/ViewController.h"
  "src/AppDelegate.m"
  "src/AppDelegate.h"
  "audiounitconfig.h"
)

set(gate_auv3_app_ui_resources
  "resource/Base.lproj/Main.storyboard"
  "resource/gate.icns"
)

include(SMTG_AddVST3AuV3)
smtg_add_auv3_app(${target_auv3}
  "macOS"
  "Gate AUv3"
  "${bundle_identifier}.auv3"
  "audiounitconfig.h"
  "gate.entitlements"
  "${gate_auv3_app_sources}"
  "${gate_auv3_app_ui_resources}"
  "AppInfo.plist"
  "ExtensionInfo.plist"
  ${target}
)
