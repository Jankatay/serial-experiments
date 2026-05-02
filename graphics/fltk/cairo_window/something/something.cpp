#include "something.hpp"
using namespace std;
using namespace Fl;

// cairo drawing logic
// ----------------------------------------------------------
void cb_diagonal_line(Fl_Cairo_Window* win, cairo_t* cairo) { 
  frame += accel;
  accel += 0.01;
  cairo_set_line_width(cairo, 5);               
  cairo_set_source_rgb(cairo, Mauve.R/rgbmax, Mauve.G/rgbmax, Mauve.B/rgbmax);   
  const double half_width = win->decorated_w()/2.0;
  const double half_height = win->decorated_h()/2.0;
  cairo_move_to(cairo, half_width, half_height);
  cairo_line_to(cairo, half_width+half_width*cos(frame), half_height+half_height*sin(frame));
  cairo_stroke(cairo);                                      
}

// to repeatedly update the cairo surface on some Fl_Cairo_Window
// ----------------------------------------------------------
void cb_redraw(void* data) {
  Fl_Cairo_Window* self = (Fl_Cairo_Window*)data;
  self->redraw();
  repeat_timeout(timeout, cb_redraw, data);
}
