// custom
#include <Simple_window.h>
#include <Graph.h>

// namespaces
using namespace Graph_lib;

// make a window with almost nothing in it
int main() {
  Point topleft{0, 0};
  Simple_window window(topleft, 1024, 720, "Blank Window");
  window.next_button.hide();
  window.wait_for_button();
}
