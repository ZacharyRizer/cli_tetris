// Using SDL and standard IO
#include "SDL.h"
#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_surface.h"
#include "SDL_video.h"
#include <iostream>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Starts up SDL and creates window
bool init();
// Loads media
bool loadMedia();
// Frees media and shuts down SDL
void close();

// the window we'll be rendering to
SDL_Window *gWindow{nullptr};
// the surface contained by the window
SDL_Surface *gScreenSurface{nullptr};
// the image we will load and show on the screen
SDL_Surface *gXOut{nullptr};

bool init() {
  // Initialization flag
  bool success = true;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError()
              << std::endl;
    success = false;
  } else {
    // Create window
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      std::cout << "Window could not be created! SDL_Error: " << SDL_GetError()
                << std::endl;
      success = false;
    } else {
      // Get window surface
      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
  }
  return success;
}

bool loadMedia() {
  // Loading success flag
  bool success = true;

  // Load splash image
  gXOut = SDL_LoadBMP("x.bmp");
  if (gXOut == NULL) {
    std::cout << "Unable to load image x.bmp! SDL Error: " << SDL_GetError()
              << std::endl;
    success = false;
  }
  return success;
}

void close() {
  // Delete surface
  SDL_FreeSurface(gXOut);
  gXOut = NULL;

  // Destroy window
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  // Quit SDL subsystems
  SDL_Quit();
}

int main(int argc, char *args[]) {

  // Start up SDL and create window
  if (!init()) {
    std::cout << "Failed to initialize!\n";
  } else {
    // Load media
    if (!loadMedia()) {
      std::cout << "Failed to load media!\n";
    } else {
      // main loop flag
      bool quit = false;
      // event handler
      SDL_Event e;

      while (!quit) {
        // handle events on queue
        while (SDL_PollEvent(&e) != 0) {
          // user requests quit
          if (e.type == SDL_QUIT) {
            quit = true;
          }
        }
        // Apply the image
        SDL_BlitSurface(gXOut, NULL, gScreenSurface, NULL);
        // update the surface
        SDL_UpdateWindowSurface(gWindow);
      }
    }
  }
  // clean up and close
  close();

  return 0;
}
