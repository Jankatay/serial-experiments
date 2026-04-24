#include <string>
#include <Simple_window.h>
#include <Window.h>

// namespaces
using namespace Graph_lib;
using namespace std;

// to draw a heart shape over x
// credits for equation to https://www.desmos.com/calculator/mwnkbqxc09
// -----------------------------------------------------------------------
double heart(double x){ return pow(x, 2.0/3.0) + pow((5-x*x),0.5) * sin(10*M_PI*x); }


// show a collage of graphs
// -----------------------------------------------------------------------
int main() {
  // init
  Point topleft(100, 100); Point len(512, 360);
  Simple_window window(topleft, len.x, len.y, "Simple Graph");

  // axes 
  constexpr int off = 30; Point origin{off, len.y-off}; // offset to NOT make it at very edge of the screen
  Axis xAxis(Axis::x, origin, len.x-off, 10, "x axis"); 
  Axis yAxis(Axis::y, origin, len.y-off*2, 10, "y axis"); // undo the origin's offset and make label visible
  window.attach(xAxis);
  window.attach(yAxis);

  // show
  window.set_label("Canvas 1. Basic");
  window.wait_for_button();

  // customize
  xAxis.set_color(Color::red); yAxis.set_color(Color::red); 
  xAxis.label.set_color(Color::dark_magenta); yAxis.label.set_color(Color::dark_magenta); 
  window.set_label("Canvas 2. Colors");
  window.wait_for_button();
  
  // draw a red heart
  Function sineLeft(heart, 0, 2.5, Point(300, 200), 100, 50, 50);
  Function sineRight(heart, 0, 2.5, Point(300, 200), 100, -50, 50);
  sineLeft.set_color(Color::red); sineRight.set_color(Color::red);
  window.attach(sineLeft); window.attach(sineRight);
  window.set_label("Canvas 3. Functions");
  // with blue axis this time!
  xAxis.set_color(Color::dark_blue); yAxis.set_color(Color::dark_blue);
  xAxis.label.set_color(Color::dark_magenta); yAxis.label.set_color(Color::dark_magenta);
  window.wait_for_button();
}
