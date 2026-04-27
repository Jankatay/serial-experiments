#include <FL/Fl.H>
#include <FL/math.h>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Cairo_Window.H>
#include <FL/Fl_Cairo.H>
#include <FL/rgb_colors.H>

using namespace Fl;


// my favorite colorscheme https://catppuccin.com/palette/
// ----------------------------------------------------------
struct RGB {uchar R, G, B;};        // for personal use
constexpr RGB Surface{49, 50, 68};  // for window
constexpr RGB Mauve{203, 166, 247}; // for line

// window dimensions
// ----------------------------------------------------------
const static struct {int width, height;} Dim = {.width = 512, .height = 360};


// cairo drawing logic
// ----------------------------------------------------------
static void cb_diagonal_line(Fl_Cairo_Window* win, cairo_t* cairo) { 
  cairo_set_line_width(cairo, sqrt(10*10*2));               // fit the corner space of 10 perfectly
  constexpr double r_ratio = Mauve.R/255.0;                 // mauve red if from 1 to 0
  constexpr double g_ratio = Mauve.G/255.0;                 // mauve green if from 1 to 0
  constexpr double b_ratio = Mauve.B/255.0;                 // mauve blue if from 1 to 0
  cairo_set_source_rgb(cairo, r_ratio, g_ratio, b_ratio);   // set cairo color as ratio instead
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

