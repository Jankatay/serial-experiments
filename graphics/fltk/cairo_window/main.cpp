#include <cstring>
#include "./something/mainsome.hpp"
#include "./something/something.hpp"

using namespace std;
using namespace Fl;
static bool unpaused = true;

class Shortcut_Window : public Fl_Cairo_Window {
  // override the event handler to pause on space-bar
  int handle(int event) {
    // handle enter
    int ret = Fl_Cairo_Window::handle(event);
    cout << "event happened "<< endl;
    /*if(event_text) {
      cout << "kinda works?" << endl;
      unpaused = !unpaused;
      if(unpaused) add_timeout(timeout, cb_redraw, this);
      else remove_timeout(cb_redraw, this);
    }
    */
    // handle rest
    return ret;
  }
};

// draw a simple window with libcairo support
// ----------------------------------------------------------
int main(int argc, char* argv[]) {
  Fl_Cairo_Window win(512, 360, "Cairo Window");            
  win.color(fl_rgb_color(Surface.R, Surface.G, Surface.B)); 
  win.resizable(&win);
  win.set_draw_cb(cb_diagonal_line);                        
  win.show(argc, argv);                                     

  // experiment with cairo functions
  cairo_t* cc = Fl::cairo_make_current(&win);
  add_timeout(timeout, cb_redraw, &win);
  return Fl::run();
}
