# init
cmake_minimum_required(VERSION 4.0)
project(simple_window)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# fetch fltk
set(FLTK_SKIP_IMAGES OFF)
include(FetchContent)
FetchContent_Declare(FLTK
  GIT_REPOSITORY  https://github.com/fltk/fltk.git
  GIT_TAG         master
  GIT_SHALLOW     TRUE
)

# build fltk
message(STATUS "Will auto-build fltk if not installed already, may take a bit first time.")
FetchContent_MakeAvailable(FLTK)
message(STATUS "Finding/building fltk - done")

# for each file in root ending with .cpp
file(GLOB SOURCE_FILES *.cpp)
foreach(FILE ${SOURCE_FILES})
  get_filename_component(EXECUTABLE ${FILE} NAME_WE)        # filter file-extension
  add_executable(${EXECUTABLE} WIN32 MACOSX_BUNDLE ${FILE}) # compile
  target_link_libraries(${EXECUTABLE} PRIVATE Window)        # link
  target_include_directories(${EXECUTABLE} PRIVATE libgraph) # include
endforeach(FILE ${SOURCE_FILES})

# link graph library - credits to Bjarne Stroustrup for it in their book "C++ Programming and Principles second edition"
add_library(Window STATIC libgraph/Graph.cpp libgraph/GUI.cpp libgraph/Window.cpp)
target_link_libraries(Window PUBLIC fltk::fltk fltk::images)

