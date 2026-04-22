#include <Simple_window.h>
#include <FL/Fl_Window.H>

class MyWindow : public Simple_window {
  public:
  MyWindow(Point tl, int xx, int yy, const string& title): Simple_window(tl, xx, yy, title) {}
  void attach(Shape &s) {
    s.set_fill_color(s.color());
    Simple_window::attach(s);
  }
};

int main() {
  using namespace Graph_lib;
  Point tl(100, 100);
  MyWindow win(tl, 600, 400, "Canvas");
  Polygon poly;
  poly.add(Point(300, 200));
  poly.add(Point(400, 200));
  poly.add(Point(400, 300));
  poly.add(Point(300, 300));
  poly.set_color(Color::red);
  win.attach(poly);
  win.wait_for_button();
}
