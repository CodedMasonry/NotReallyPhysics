#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <cmath>
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
  SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE);

  // Render wall lines
  int wall_horizontal_lines = std::round(window_height / 16) + 1;
  int wall_vertical_lines = std::round(window_width / 16) + 1;
  int wall_horizontal_spacing = window_height / (wall_horizontal_lines - 1);
  int wall_vertical_spacing = window_width / (wall_vertical_lines - 1);
  int h_offset = 0;
  int v_offset = 0;

  for (int i = 0; i < wall_horizontal_lines; i++) {
    SDL_RenderLine(renderer, 0, h_offset, window_width, h_offset);
    h_offset += wall_horizontal_spacing;
  }
  for (int i = 0; i < wall_vertical_lines; i++) {
    SDL_RenderLine(renderer, v_offset, 0, v_offset, window_height);
    v_offset += wall_vertical_spacing;
  }
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
                                   window_height, 0, &window, &renderer)) {
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
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);

  RenderBackground();

  // Render buffer
  SDL_RenderPresent(renderer);
  return SDL_APP_CONTINUE;
}

// Shutdown
void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  // cleanup
}
