#include "canvas.h"
#include <iostream>

int Canvas::handle(int event) {
  // init 
  int ret = Fl_Cairo_Window::handle(event);
  agenda = None; // refresh agenda

  // handle
  switch(event) {
  case(FL_PUSH): handle_push(event_button()); break;
  case(FL_RELEASE): handle_release(event_button()); break;
  case(FL_ENTER): handle_move(); break;
  default: agenda = None; break;
  }
  
  // finish
  return ret;
}

void Canvas::handle_push(int button) {
  if(button != FL_LEFT_MOUSE) return; // ignore click.

  // set a schedule
  mouseX = event_x();
  mouseY = event_y();
  agenda = Draw_Circle;
  drawing = true;

  // debug
  cerr << "Clicked Mouse" << endl; 

  // Go forward with the schedule.
  redraw(); 
}

// moved the mouse
void Canvas::handle_move() {
  if(drawing != true) return; // skip if just hovering

  // set a schedule
  mouseX = event_x();
  mouseY = event_y();
  agenda = Draw_Line;

  // debug
  cerr << "Moved mouse" << endl;

  // go forward with schedule
  redraw();
}

// stop drawing :(
void Canvas::handle_release(int button) {
  if(button != FL_LEFT_MOUSE) return; // not handling other buttons
  drawing = false; 
  agenda = None;
}

// actual cairo part of drawing, rather than calculations
void Canvas::cairo_draw(Fl_Cairo_Window* self, cairo_t* cairo_context) {
  Canvas* canvas = (Canvas*)self;
  if((!canvas) || !(canvas->drawing)) return; // nothing to do
  cairo_set_line_width(cairo_context, canvas->width);
  // mouse-click
  if(canvas->agenda == Canvas::Draw_Circle) {
    cerr<< "Drawing to " << canvas->mouseX << ',' << canvas->mouseY << ',' << canvas->width << endl;
    cairo_line_to(cairo_context, canvas->decorated_w()/2.0, canvas->decorated_h()/2.0);
    cairo_move_to(cairo_context, canvas->decorated_w(), canvas->decorated_h());
    //cairo_arc(cairo_context, canvas->mouseX, canvas->mouseY, canvas->width/2.0, 0, 0.25*M_PI);
    //cairo_move_to(cairo_context, canvas->mouseX, canvas->mouseY); // for lines
  }

  // mouse-movement
  if(canvas->agenda == Canvas::Draw_Line) {
    cairo_line_to(cairo_context, canvas->mouseX, canvas->mouseY);
    cairo_move_to(cairo_context, canvas->mouseX, canvas->mouseY);
  }

  cairo_stroke(cairo_context);
}
