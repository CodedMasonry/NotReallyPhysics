#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#define SDL_MAIN_USE_CALLBACKS 1
#include "SDL3/SDL_main.h"


static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

// Startup
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    // Metadata
    SDL_SetAppMetadata("NotReallyPhysics", "0.0", "dev.brockshaffer.notreallyphysics");

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
    int window_width = display->w * 3/4;
    int window_height = display->h * 3/4;


    // Create window & Renderer
    if (!SDL_CreateWindowAndRenderer("Not Really Physics", window_width, window_height, 0, &window, &renderer)){
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

    // Render a box
    SDL_FRect rect;
    int w,h;
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE);
    SDL_GetWindowSizeInPixels(window, &w, &h);
    rect.x = (float)w * 1/4;
    rect.y = (float)h * 1/4;
    rect.w = (float)w * 1/2;
    rect.h = (float)h * 1/2;
    SDL_RenderFillRect(renderer, &rect);

    // Render buffer
    SDL_RenderPresent(renderer);
    return SDL_APP_CONTINUE;
}

// Shutdown
void SDL_AppQuit(void *appstate, SDL_AppResult result) {
// cleanup
}
