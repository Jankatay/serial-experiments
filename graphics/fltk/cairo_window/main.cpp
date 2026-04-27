#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Cairo_Window.H>
#include <FL/Fl_Cairo.H>
#include <FL/rgb_colors.H>

using namespace Fl;


// my favorite colorscheme https://catppuccin.com/palette/
// ----------------------------------------------------------
typedef struct {uchar R, G, B;} RGB;  // for personal use
RGB Surface{49, 50, 68};              // for window
RGB Mauve{203, 166, 247};             // for line


// window dimensions
// ----------------------------------------------------------
const static struct {int width, height;} Dim = {.width = 512, .height = 360};


// cairo drawing logic
// ----------------------------------------------------------
static void cb_diagonal_line(Fl_Cairo_Window* win, cairo_t* cairo) { 
  cairo_set_line_width(cairo, 10);                          // line thickness
  cairo_set_source_rgb(cairo, Mauve.R/255.0, Mauve.G/255.0, Mauve.B/255.0);   // cool purple line
  cairo_move_to(cairo, 10, 10);                             // move cursor to (10,10)
  cairo_line_to(cairo, Dim.width-10, Dim.height-10);        // draw just short of other corner
  cairo_stroke(cairo);                                      // paint the line just drawn
}


// draw a simple window with libcairo support
// ----------------------------------------------------------
int main(int argc, char* argv[]) {
  Fl_Cairo_Window win(512, 360, "Cairo Window");            // init window
  win.color(fl_rgb_color(Surface.R, Surface.G, Surface.B)); // set window color
  win.set_draw_cb(cb_diagonal_line);                        // draw a diagonal line
  win.show(argc, argv);                                     // show the window
  return Fl::run();                                         // run until exit
}

