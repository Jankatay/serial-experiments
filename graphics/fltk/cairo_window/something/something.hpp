#pragma once

#include <iostream>
#include <FL/Fl.H>
#include <FL/math.h>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Cairo_Window.H>
#include <FL/Fl_Cairo.H>
#include <FL/rgb_colors.H>
#include "mainsome.hpp"

// cairo drawing logic
// ----------------------------------------------------------
void cb_diagonal_line(Fl_Cairo_Window* win, cairo_t* cairo);
static double frame = 0;
static double accel = 0.01;
void cb_redraw(void* data);

// to repeatedly update the cairo surface on some Fl_Cairo_Window
// ----------------------------------------------------------
static double timeout = 1/30.0;
