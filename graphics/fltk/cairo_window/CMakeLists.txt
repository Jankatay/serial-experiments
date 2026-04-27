# init project
cmake_minimum_required(VERSION 4.0)
project(cairo_window)
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

# set files 
add_executable(cairo_window WIN32 MACOSX_BUNDLE main.cpp)
target_link_libraries(cairo_window PRIVATE fltk::fltk fltk::images)
