# init project
cmake_minimum_required(VERSION 4.0)
project(cairo_window)

# attributes
set(CMAKE_BUILD_TYPE MinSizeRel)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(FLTK_OPTION_CAIRO_WINDOW ON)

# fetch fltk
include(FetchContent)
FetchContent_Declare(FLTK
  GIT_REPOSITORY  https://github.com/fltk/fltk.git
  GIT_TAG         master
  GIT_SHALLOW     TRUE
)

# debug-message
message(STATUS "Installing fltk if doesn't exist already")
FetchContent_MakeAvailable(FLTK)
message(STATUS "Finding/building fltk - Done")

# for each main.cpp
file(GLOB SOURCE_FILES */main.cpp)
foreach(SOURCE_FILE ${SOURCE_FILES})
  # get directory DIR_PATH and name without extension BIN_FILE
  get_filename_component(DIR_PATH ${SOURCE_FILE} DIRECTORY)
  get_filename_component(BIN_FILE ${DIR_PATH} NAME)
  set(BIN_LIB ${BIN_FILE}_library)

  # add BIN_FILE as an executable
  add_executable(${BIN_FILE} WIN32 MACOSX_BUNDLE ${SOURCE_FILE})
  target_link_libraries(${BIN_FILE} PRIVATE ${BIN_LIB}) 
  #target_link_libraries(${BIN_FILE} PUBLIC fltk::fltk)
  # for each file under same folder as BIN_FILE
  message(STATUS "Searching ${DIR_PATH}")
  file(GLOB_RECURSE LIB_FILES ${DIR_PATH}/*.cpp)
  foreach(LIB_FILE ${LIB_FILES})
    # Ensure it's not source and add to source code for custom library
    if(NOT ${LIB_FILE} STREQUAL ${SOURCE_FILE}) 
      message(STATUS "Adding ${LIB_FILE} >> lib${BIN_FILE}")
      list(APPEND LIB_SOURCE ${LIB_FILE})
    endif()
  endforeach(LIB_FILE ${LIB_FILES})

  #link the custom library with the BIN_FILE
  message(STATUS "Source files are ${LIB_SOURCE}")
  add_library(${BIN_LIB} STATIC ${LIB_SOURCE}) 
  target_link_libraries(${BIN_LIB} PUBLIC fltk::fltk) 
endforeach(SOURCE_FILE ${SOURCE_FILES})

