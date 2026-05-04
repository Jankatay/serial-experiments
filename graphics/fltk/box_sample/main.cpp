#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include "../cairo_window/something/mainsome.hpp"
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include <cmath>

using namespace Fl;

struct Vec2 {double X; double Y;}; // just keeping it simple
class draw_box : public Fl_Box {
  public:
  draw_box(int X, int Y, int W, int H, const char* L = ""): Fl_Box(X, Y, W, H, L) {}
  private:
  double frame;
  constexpr static double rate = 100; // set manually for the rate of rotation
  void draw() override {
    fl_color(FL_RED); // must be set BEFORE fl_line_style due to windows
    fl_line_style(FL_SOLID, 4); // very big, solid line 

    Vec2 midpoint = { // origin and half-length
      .X = (Fl_Box::w()-Fl_Box::x())/2.0, 
      .Y = (Fl_Box::h()-Fl_Box::y())/2.0
    };

    Vec2 edge = { // distance from origin to side
      .X = midpoint.X + midpoint.X*cos(frame),
      .Y = midpoint.Y + midpoint.Y*sin(frame)
    };

    // finish
    fl_line(midpoint.X, midpoint.Y, edge.X, edge.Y);
    Fl_Box::draw();

    // increment rotation
    frame += 2*M_PI/rate;
    if(frame >= 2*M_PI) frame = 0;
  }
};

int main(int argc, char* argv[]) {
  Fl_Window* win = new Fl_Window(Fl::w()/2, Fl::h()/2);
  win->resizable(win);
    draw_box* first = new draw_box(0, 0, win->w()/2.0, win->h());
    draw_box* second = new draw_box(win->w()/2.0, 0, win->w()/2.0, win->h());
  win->show(argc, argv);

  // repeatedly refresh instead of Fl::run()
  // also good practice for macos https://www.fltk.org/doc-1.5/classFl.html#a7a3b1236b41800d24267288c564b187a
  while(!program_should_quit()) { 
    win->redraw();
    Fl::wait(1e20);
  }
  return Fl::run();
}
