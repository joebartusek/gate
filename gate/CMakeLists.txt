set(target ${project})

### add plugin (source files) as library target
smtg_add_vst3plugin(${target}
  src/CIDs.h
  src/version.h
  src/processor.h
  src/controller.h
  src/factory.cpp
  src/processor.cpp
  src/controller.cpp
  resource/gate.uidesc
)

### set plugin resources
smtg_target_add_plugin_resources(${target}
  RESOURCES
    resource/gate.uidesc
)

### link libraries to plugin
target_link_libraries(${target}
  PRIVATE
    sdk_hosting
    vstgui_support
    sdk
)

### allow GUI live editing
target_compile_definitions(${target}
  PUBLIC
    $<$<CONFIG:Debug>:VSTGUI_LIVE_EDITING=1>
)

### configure plugin version (creates projectversion.h header file)
smtg_target_configure_version_file(${target})

### set plugin bundle variables (MacOS specific)
smtg_target_set_bundle(${target}
  BUNDLE_IDENTIFIER
    ${bundle_identifier}
  COMPANY_NAME
    WordCel
)
