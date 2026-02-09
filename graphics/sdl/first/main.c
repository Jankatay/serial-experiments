// As cool as this macro is, I don't like relying on global variables
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>


// Since macro means callbacks, a lot of variables have to be global
static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static bool status = false;


// initialize everything at startup
//----------------------------------------------
SDL_AppResult SDL_AppInit(void**, int, char**) {
  // trust me the identifier makes sense in context of my projecs' file-hirearchy
  SDL_SetAppMetadata("First sdl app", "1.0", "jan.sdl.first");

  // initial SDL3
  status = SDL_Init(SDL_INIT_VIDEO);
  if(!status) {
    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  // set renderer
  SDL_WindowFlags flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS;
  status = SDL_CreateWindowAndRenderer("first", 0, 0, flags, &window, &renderer);
  if(!status) {
    SDL_Log("Couldn't get window/renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  // set expected rendering dimensions
  int width = -1, height = -1; // rule of repair
  status = SDL_GetWindowSize(window, &width, &height);
  status &= (width >= 0) && (height >= 0);
  if(!status) {
    SDL_Log("Dimensions error %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  // success, continue
  return SDL_APP_CONTINUE;
}


// handling the "quit" input
//----------------------------------------------
SDL_AppResult SDL_AppEvent(void*, SDL_Event* event) {
  return (event->type == SDL_EVENT_QUIT) ? SDL_APP_SUCCESS : SDL_APP_CONTINUE;
}


// looping part of the program, reminds me of arduino
//----------------------------------------------
SDL_AppResult SDL_AppIterate(void*) {
  // get time in seconds
  const double now = ((double)SDL_GetTicks())/1000;

  // sane constants for the sin function
  static const int degrees120 = SDL_PI_D*2/3;
  static const int degrees240 = SDL_PI_D*4/3;

  // calculate colors
  const float red = (float)(0.5 + 0.5 * SDL_sin(now)); 
  const float green = (float)(0.5 + 0.5 * SDL_sin(now + degrees120)); 
  const float blue = (float)(0.5 + 0.5 * SDL_sin(now + degrees240));

  // render, clear-screen, and draw
  SDL_SetRenderDrawColorFloat(renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);

  // continue running
  return SDL_APP_CONTINUE;
}


// cleaning up, apparently sdl handles this one pretty well
void SDL_AppQuit(void*, SDL_AppResult) {
}

