#include "canvas.h"

int main(int argc, char* argv[]) {
  vector<Fl_Widget> tools;
  Canvas* c = new Canvas(0, 0, w(), h(), argv[0]);
  return 0;
}
