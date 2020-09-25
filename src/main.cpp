// Using SDL and standard IO
#include "SDL.h"
#include "SDL_image.h"
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
SDL_Surface *gStretchedSurface = NULL;

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

  // Load stretching surface
  gStretchedSurface = loadSurface("stretch.bmp");
  if (gStretchedSurface == NULL) {
    printf("Failed to load stretching image!\n");
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
  // The final optimized image
  SDL_Surface *optimizedSurface{nullptr};

  // Load image at specified path
  SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
  if (loadedSurface == NULL) {
    std::cout << "Unable to load image " << path.c_str()
              << "! SDL Error: " << SDL_GetError() << std::endl;
  } else {
    // Convert surface to screen format
    optimizedSurface =
        SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
    if (optimizedSurface == NULL) {
      std::cout << "Unable to optimize image " << path.c_str()
                << "! SDL Error: " << SDL_GetError() << std::endl;
    }
    // Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
  }
  return optimizedSurface;
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
      // while application is running
      while (!quit) {
        // handle events on queue
        while (SDL_PollEvent(&e) != 0) {
          // user requests quit
          if (e.type == SDL_QUIT) {
            quit = true;
          }
        }
        // apply the image stretched
        SDL_Rect stretchRect;
        stretchRect.x = 0;
        stretchRect.y = 0;
        stretchRect.w = SCREEN_WIDTH;
        stretchRect.h = SCREEN_HEIGHT;
        SDL_BlitScaled(gStretchedSurface, NULL, gScreenSurface, &stretchRect);
        // update the surface
        SDL_UpdateWindowSurface(gWindow);
      }
    }
  }
  // clean up and close
  close();

  return 0;
}
