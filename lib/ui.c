#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_pixels.h>
#include <emu.h>
#include <ui.h>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

void ui_init() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer("test window", SCREEN_WIDTH, SCREEN_HEIGHT, 0,
                              &window, &renderer);
}

void ui_handle_events() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
      get_emu_context()->die = true;
    }
  }
}

void ui_update() {
  const double ticks = (double)SDL_GetTicks() / 1000;

  float red = (float)(.5 + .5 * SDL_sin(.75 * ticks));
  float green = (float)(.5 + .5 * SDL_sin(.75 * (ticks + SDL_PI_D * 2 / 3)));
  float blue = (float)(.5 + .5 * SDL_sin(.75 * (ticks + SDL_PI_D * 4 / 3)));

  SDL_SetRenderDrawColorFloat(renderer, red, green, blue,
                              SDL_ALPHA_OPAQUE_FLOAT);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
}
