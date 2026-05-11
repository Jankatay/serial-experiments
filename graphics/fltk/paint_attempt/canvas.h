#pragma once 

// standard
#include <vector>
#include <math.h>
using namespace std;

// fltk
#include <FL/Fl.H>
#include <FL/rgb_colors.H>
#include <FL/Fl_Overlay_Window.H>
using namespace Fl;


// Paintable window with simple toolbar at top
class Canvas : public Fl_Overlay_Window {
  public: 
  Canvas(int X, int Y, int W, int H, const char* L) : Fl_Overlay_Window(X, Y, W, H, L) {}
  void draw_overlay() FL_OVERRIDE;

  // color variables
  Fl_Color color = FL_BLACK; 
  bool drawing = false;

  // schedule variables

  private:
  // mouse-event handling
  int handle(int event) FL_OVERRIDE;
  void handle_release(int button);
  void handle_push(int button);
  void handle_move();

  // calculation variables
  int prevX, prevY;
  int mouseX, mouseY;
  int width = 10.0;
  enum Next_Action {
    Draw_Circle,
    Draw_Line,
    Draw_End,
    None
  } agenda;

  // draw everything from scratch one by one each time
  struct State {
    int prevX;
    int prevY;
    int mouseX;
    int mouseY;
    int width;
    Next_Action agenda;
  };
  vector<State> vec = vector<State>();
};
