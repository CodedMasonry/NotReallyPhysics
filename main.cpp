#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <cstddef>
#define SDL_MAIN_USE_CALLBACKS 1
#include "SDL3/SDL_main.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static int window_width, window_height;

/*
 * Rendering Functions
 */

// Render the background
void RenderBackground() {
  // Divide screen into segments 32 pixels wide, and we only want every other to
  // be a secondary color
  int rect_width = 128;
  int num_rects = (window_width / rect_width / 2) + 1;
  SDL_FRect rects[num_rects];

  int offset = 0;
  for (int i = 0; i < num_rects; i++) {
    rects[i].x = offset;
    rects[i].y = 0;
    rects[i].w = rect_width;
    rects[i].h = window_height;

    offset += (rect_width * 2);
  }

  SDL_SetRenderDrawColor(renderer, 50, 50, 50, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRects(renderer, rects, num_rects);
}

/*
 * Main App Functions
 */

// Startup
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
  // Metadata
  SDL_SetAppMetadata("NotReallyPhysics", "0.0",
                     "dev.brockshaffer.notreallyphysics");

  // SDL Init
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Couldn't innitialize SDL: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  // Get dimensions for new window
  SDL_DisplayID displayID = SDL_GetPrimaryDisplay();
  if (!displayID) {
    SDL_Log("No display found");
    return SDL_APP_FAILURE;
  }
  auto display = SDL_GetDesktopDisplayMode(displayID);
  if (!display) {
    SDL_Log("SDL_GetCurrentDisplayMode Error: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  window_width = display->w * (3.0 / 4.0);
  window_height = display->h * (3.0 / 4.0);

  // Create window & Renderer
  if (!SDL_CreateWindowAndRenderer("Not Really Physics", window_width,
                                   window_height, SDL_WINDOW_RESIZABLE, &window,
                                   &renderer)) {
    SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  return SDL_APP_CONTINUE;
}

// Event handler
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS;
  }

  return SDL_APP_CONTINUE;
}

// Render frame
SDL_AppResult SDL_AppIterate(void *appstate) {
  // Clear screen
  SDL_SetRenderDrawColor(renderer, 40, 40, 40, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);

  // Update window dimensions in case they changed
  SDL_GetWindowSizeInPixels(window, &window_width, &window_height);

  RenderBackground();

  // Render buffer
  SDL_RenderPresent(renderer);
  return SDL_APP_CONTINUE;
}

// Shutdown
void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  // cleanup
}
