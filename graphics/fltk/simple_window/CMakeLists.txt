# init
cmake_minimum_required(VERSION 4.0)
project(simple_window)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# fetch
include(FetchContent)
FetchContent_Declare(FLTK
  GIT_REPOSITORY  https://github.com/fltk/fltk.git
  GIT_TAG         master
  GIT_SHALLOW     TRUE
)

# build
message(STATUS "Will auto-build fltk if not installed already, may take a bit first time.")
FetchContent_MakeAvailable(FLTK)
message(STATUS "Finding/building fltk - done")

# setup 
add_executable(simple_window WIN32 MACOSX_BUNDLE main.cpp)
target_link_libraries(simple_window PRIVATE fltk::fltk)
