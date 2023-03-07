set(vst3sdk_SOURCE_DIR /Users/joebartusek/Documents/Code/plugin/sdk/vst3sdk)
set(SDK_ROOT ${vst3sdk_SOURCE_DIR})
set(public_sdk_SOURCE_DIR ${vst3sdk_SOURCE_DIR}/public.sdk)
set(pluginterfaces_SOURCE_DIR ${vst3sdk_SOURCE_DIR}/pluginterfaces)

set(SDK_IDE_LIBS_FOLDER FOLDER "Libraries")

option(SMTG_ADD_VSTGUI "Add VSTGUI Support" ON)
set(VST_SDK BOOL TRUE)

# include vst3sdk cmake modules
list(APPEND CMAKE_MODULE_PATH "${vst3sdk_SOURCE_DIR}/cmake/modules")
include_directories(${vst3sdk_SOURCE_DIR})
include(SMTG_VST3_SDK)

smtg_setup_platform_toolset()
smtg_enable_vstgui_support(VSTGUI_SOURCE_DIR ${vst3sdk_SOURCE_DIR}/vstgui4)
setupCoreAudioSupport()

# Add some base libraries
add_subdirectory(${vst3sdk_SOURCE_DIR}/pluginterfaces ${PROJECT_BINARY_DIR}/vst3sdk/pluginterfaces)
add_subdirectory(${vst3sdk_SOURCE_DIR}/base ${PROJECT_BINARY_DIR}/vst3sdk/base)
add_subdirectory(${vst3sdk_SOURCE_DIR}/public.sdk ${PROJECT_BINARY_DIR}/vst3sdk/public.sdk)
add_subdirectory(${vst3sdk_SOURCE_DIR}/public.sdk/source/vst/interappaudio ${PROJECT_BINARY_DIR}/vst3sdk/interappaudio)

# Add hosting examples subdirectory, includes validator
set(SDK_IDE_HOSTING_EXAMPLES_FOLDER FOLDER "HostingExamples")
add_subdirectory(${vst3sdk_SOURCE_DIR}/public.sdk/samples/vst-hosting ${PROJECT_BINARY_DIR}/vst3sdk/vst-hosting)

# Add utilities subdirectory, includes moduleinfotool
set(SDK_IDE_UTILITIES_FOLDER FOLDER "Utilities")
add_subdirectory(${vst3sdk_SOURCE_DIR}/public.sdk/samples/vst-utilities ${PROJECT_BINARY_DIR}/vst3sdk/vst-utilities)

# Add AuV3 wrapper subdirectory
add_subdirectory(${vst3sdk_SOURCE_DIR}/public.sdk/source/vst/auv3wrapper ${PROJECT_BINARY_DIR}/vst3sdk/auv3wrapper)

smtg_enable_vst3_sdk()
