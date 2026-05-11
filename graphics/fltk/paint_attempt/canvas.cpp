#include "canvas.h"
#include <iostream>
#include <FL/fl_draw.H>

int Canvas::handle(int event) {
  // init 
  int ret = Fl_Overlay_Window::handle(event);
  agenda = None; // refresh agenda

  // handle
  switch(event) {
  case(FL_DRAG): handle_move(); break;
  case(FL_PUSH): handle_push(event_button()); break;
  case(FL_RELEASE): handle_release(event_button()); break;
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
  State newstate = {
    .prevX = 0,
    .prevY = 0,
    .mouseX = mouseX, 
    .mouseY = mouseY,
    .width = width/2,
    .agenda = Draw_Circle,
  };
  vec.push_back(newstate);
  drawing = true;

  // Go forward with the schedule.
  redraw_overlay();
}

// moved the mouse
void Canvas::handle_move() {
  if(drawing != true) return; // skip if just hovering

  // set a schedule
  mouseX = event_x();
  mouseY = event_y();
  State newstate = {
    .prevX = prevX,
    .prevY = prevY,
    .mouseX = mouseX, 
    .mouseY = mouseY,
    .width = width,
    .agenda = Draw_Line,
  };
  vec.push_back(newstate);

  // go forward with schedule
  redraw_overlay();
}

// draw based on given info
void Canvas::draw_overlay() {
  if(!drawing) return; 
  for(const State& state : vec) {
    Fl_Overlay_Window::draw();
    fl_line_style(FL_SOLID, state.width);
    if(state.agenda == Draw_Circle) fl_circle(state.mouseX, state.mouseY, state.width/2);
    else if(state.agenda == Draw_Line) fl_line(state.prevX, state.prevY, state.mouseX, state.mouseY);
  }
  prevX = mouseX;
  prevY = mouseY;
}

// stop drawing :(
void Canvas::handle_release(int button) {
  if(button != FL_LEFT_MOUSE) return; // not handling other buttons
  drawing = false;
  agenda = Draw_End;
}
