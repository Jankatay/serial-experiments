#include "canvas.h"

int Canvas::handle(int event) {
  // init, don't modify the non-mouse events
  int ret = Fl_Cairo_Window::handle(event);
  if(!event_button1()) return ret; 

  // single click 
  if(event == FL_PUSH)

  // dragged
  
  // finish
  return ret;
}
