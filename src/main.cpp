#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum KeyPressSurfaces {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL
};

bool init();
bool loadMedia();
void close();
SDL_Surface* loadSurface(const char* path);

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

bool init() {
  bool success = false;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  } else {
    gWindow = SDL_CreateWindow("SDL Tutorial", 
                               SDL_WINDOWPOS_UNDEFINED, 
                               SDL_WINDOWPOS_UNDEFINED, 
                               SCREEN_WIDTH,
                               SCREEN_HEIGHT,
                               SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    } else {
      gScreenSurface = SDL_GetWindowSurface(gWindow);
      success = true;
    }
  }
  return success;
}

void close() {
  SDL_FreeSurface(gHelloWorld);
  gHelloWorld = NULL;
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  SDL_Quit();
}

SDL_Surface* loadSurface(const char* path) {
  SDL_Surface* optimizedSurface = NULL;
  SDL_Surface* loadedSurface = SDL_LoadBMP(path);
  if(loadedSurface == NULL) {
    printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
  } else {
    optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, (Uint32)NULL);
    if (optimizedSurface == NULL) {
      printf("Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError());
    }
    SDL_FreeSurface(loadedSurface);
  }
  return optimizedSurface;
}

bool loadMediaItem(KeyPressSurfaces s, 
                   const char* path,
                   const char* name) {
  bool success = true;
  gKeyPressSurfaces[s] = loadSurface(path);
  if (gKeyPressSurfaces[s] == NULL) {
    printf("Failed to load %s image!\n", name);
    success = false;
  }
  return success;
}

bool loadMedia() {
  bool success = true;
  success = loadMediaItem(KEY_PRESS_SURFACE_DEFAULT, "../res/press.bmp", "default") && success;
  success = loadMediaItem(KEY_PRESS_SURFACE_UP, "../res/up.bmp", "up") && success;
  success = loadMediaItem(KEY_PRESS_SURFACE_DOWN, "../res/down.bmp", "down") && success;
  success = loadMediaItem(KEY_PRESS_SURFACE_LEFT, "../res/left.bmp", "left") && success;
  success = loadMediaItem(KEY_PRESS_SURFACE_RIGHT, "../res/right.bmp", "right") && success;
  return success;
}

int main(int argc, char* args[]) {
  if(!init()) {
    printf("Failed to initialize!\n");
  } else {
    if(!loadMedia()) {
      printf("Failed to load media!\n");
    } else {
      SDL_BlitSurface(gHelloWorld,
                      NULL,
                      gScreenSurface,
                      NULL);
      SDL_UpdateWindowSurface(gWindow);
    }
  }

  bool quit = false;
  SDL_Event e;
  SDL_Surface* gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      } else if (e.type == SDL_KEYDOWN) {
        switch(e.key.keysym.sym) {
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

      SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
      SDL_UpdateWindowSurface(gWindow);

    }
  }
  close();
  return 0;
}
       
