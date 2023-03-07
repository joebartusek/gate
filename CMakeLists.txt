cmake_minimum_required(VERSION 3.19)

set(project gate)

project(${project}
  VERSION
    1.0.0
  DESCRIPTION
    "gate idk"
)

include(setup.cmake)

set(bundle_identifier
  "org.wordcel.${project}"
)

smtg_add_subdirectories()
