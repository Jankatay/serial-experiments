#pragma once 

// standard
#include <vector>
#include <math.h>
using namespace std;

// fltk
#include <FL/Fl.H>
#include <FL/rgb_colors.H>
#include <FL/Fl_Cairo.H>
#include <FL/Fl_Cairo_Window.H>
using namespace Fl;


// Paintable window with simple toolbar at top
class Canvas : public Fl_Cairo_Window {
  public: 
  Canvas(int X, int Y, int W, int H, const char* L) : Fl_Cairo_Window(X, Y, W, H, L) {
    //this->set_draw_cb(cairo_draw); // draw the cairo canvas as necessary
  }
  static void cairo_draw(Fl_Cairo_Window* self, cairo_t* cairo_context);

  // color variables
  Fl_Color color = FL_BLACK; 
  bool drawing = false;
  double width = 10.0;

  // schedule variables
  enum Next_Action {
    Draw_Circle,
    Draw_Line,
    None
  } agenda = None;

  // calculation variables
  int mouseX = 0, mouseY = 0;
  
  private:
  // mouse-event handling
  int handle(int event) override;
  void handle_release(int button);
  void handle_push(int button);
  void handle_move();

  // actual cairo part of drawing, rather than calculations
};
