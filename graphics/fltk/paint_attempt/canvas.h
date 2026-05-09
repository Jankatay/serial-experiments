#pragma once 
//TODO: look more into embedded windows

// standard
#include <vector>
using namespace std;

// fltk
#include <FL/Fl.H>
#include <FL/Fl_Cairo.H>
#include <FL/Fl_Cairo_Window.H>
using namespace Fl;


// Paintable window with simple toolbar at top
class Canvas :  Fl_Cairo_Window {
  public: 
  // functions  
  Canvas(int X, int Y, int W, int H, const char* L) : Fl_Cairo_Window(X, Y, W, H, L) {}
  
  private:
  // functions
  int handle(int event) override;
  void add_tool(Fl_Widget* widget);
  void remove_tool(size_t index);

  // variables
  vector<Fl_Widget*> tools(); // pen, brush, line, etc.
};
