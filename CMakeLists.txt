cmake_minimum_required(VERSION 3.19)

set(project gate)

project(${project}
  VERSION
    1.0.0
  DESCRIPTION
    "gate idk"
)

# VST3SDK doesn't support xcode 14.3 yet
if(XCODE_VERSION VERSION_GREATER 14.2)
  message([WARNING] " Xcode>14.2 not yet supported by vst3sdk")
endif()

include(setup.cmake)

set(bundle_identifier
  "org.wordcel.${project}"
)

smtg_add_subdirectories()
