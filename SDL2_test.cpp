// Using SDL and standard IO
#include "SDL.h"
#include "SDL_error.h"
#include "SDL_events.h"
#include "SDL_surface.h"
#include "SDL_video.h"
#include <iostream>
#include <string>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// key press surfaces constants
enum KeyPressSurfaces {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL
};

// Starts up SDL and creates window
bool init();
// Loads media
bool loadMedia();
// Frees media and shuts down SDL
void close();
// Loads individual image
SDL_Surface *loadSurface(std::string path);
// the window we'll be rendering to

SDL_Window *gWindow{nullptr};
// the surface contained by the window
SDL_Surface *gScreenSurface{nullptr};
// the images that correspond to a keypress
SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
// current displayed image
SDL_Surface *gCurrentSurface{nullptr};

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

  // Load default surface
  gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("press.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
    printf("Failed to load default image!\n");
    success = false;
  }

  // Load up surface
  gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("up.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
    printf("Failed to load up image!\n");
    success = false;
  }

  // Load down surface
  gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("down.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
    printf("Failed to load down image!\n");
    success = false;
  }

  // Load left surface
  gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("left.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
    printf("Failed to load left image!\n");
    success = false;
  }

  // Load right surface
  gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("right.bmp");
  if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
    printf("Failed to load right image!\n");
    success = false;
  }

  return success;
}

void close() {
  // Deallocate surfaces
  for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++) {
    SDL_FreeSurface(gKeyPressSurfaces[i]);
    gKeyPressSurfaces[i] = NULL;
  }

  // Destroy window
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  // Quit SDL subsystems
  SDL_Quit();
}

SDL_Surface *loadSurface(std::string path) {
  // Load image at specified path
  SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
  if (loadedSurface == NULL) {
    std::cout << "Unable to load image " << path.c_str()
              << "! SDL Error: " << SDL_GetError() << std::endl;
  }
  return loadedSurface;
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
      // Set default current surface
      gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

      // while application is running
      while (!quit) {
        // handle events on queue
        while (SDL_PollEvent(&e) != 0) {
          // user requests quit
          if (e.type == SDL_QUIT) {
            quit = true;
          }
          // User presses a key
          else if (e.type == SDL_KEYDOWN) {
            // select surfaces based on key press
            switch (e.key.keysym.sym) {
            case SDLK_UP:
              gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
              break;
            case SDLK_DOWN:
              gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
              break;
            case SDLK_LEFT:
              gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
              break;
            case SDLK_RIGHT:
              gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
              break;
            default:
              gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
              break;
            }
          }
        }
        // Apply the image
        SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
        // update the surface
        SDL_UpdateWindowSurface(gWindow);
      }
    }
  }
  // clean up and close
  close();

  return 0;
}
