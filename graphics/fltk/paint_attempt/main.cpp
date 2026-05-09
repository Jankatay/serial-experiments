#include "canvas.h"

int main(int argc, char* argv[]) {
  Canvas* canvas = new Canvas(0, 0, w()/2, h()/2, "Paint Attempt");
  canvas->set_draw_cb(Canvas::cairo_draw);
  canvas->show(argc, argv);
  return Fl::run();
}
