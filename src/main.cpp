#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

bool init();
bool loadMedia();
void close();
SDL_Surface* loadSurface(const char* path);

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* images[1];

bool init() {
  bool success = false;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = false;
  } else {
    gWindow = SDL_CreateWindow("SDL Tutorial", 
                               SDL_WINDOWPOS_UNDEFINED, 
                               SDL_WINDOWPOS_UNDEFINED, 
                               SCREEN_WIDTH,
                               SCREEN_HEIGHT,
                               SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      success = false;
    } else {
      int imgFlags = IMG_INIT_PNG;
      if(!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        success = false;
      } else {
        gScreenSurface = SDL_GetWindowSurface(gWindow);
        success = true;
      }
    }
  }
  return success;
}

void close() {
  for(int i = 0; i < sizeof(images); i++ ){
    SDL_FreeSurface(images[i]);
  }
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  SDL_Quit();
}

SDL_Surface* loadSurface(const char* path) {
  SDL_Surface* optimizedSurface = NULL;
  SDL_Surface* loadedSurface = IMG_Load(path);
  if(loadedSurface == NULL) {
    printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
  } else {
    optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
    if (optimizedSurface == NULL) {
      printf("Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError());
    }
    SDL_FreeSurface(loadedSurface);
  }
  return optimizedSurface;
}

bool loadMediaItem(int s, 
                   const char* path,
                   const char* name) {
  bool success = true;
  images[s] = loadSurface(path);
  if (images[s] == NULL) {
    printf("Failed to load %s image!\n", name);
    success = false;
  }
  return success;
}

bool loadMedia() {
  bool success = true;
  success = loadMediaItem(0, "../res/elements.png", "elements");
  return success;
}

int main(int argc, char* args[]) {
  SDL_Rect stretchRect;
  if(!init()) {
    printf("Failed to initialize!\n");
  } else {
    if(!loadMedia()) {
      printf("Failed to load media!\n");
    } else {
      stretchRect.x = 0;
      stretchRect.y = 0;
      stretchRect.w = SCREEN_WIDTH;
      stretchRect.h = SCREEN_HEIGHT;
      SDL_BlitScaled(images[0],
                      NULL,
                      gScreenSurface,
                      &stretchRect);
      SDL_UpdateWindowSurface(gWindow);
    }
  }

  bool quit = false;
  SDL_Event e;
  SDL_Surface* gCurrentSurface = images[0];

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }

      SDL_BlitScaled(gCurrentSurface,
                     NULL,
                     gScreenSurface,
                     &stretchRect);
      SDL_UpdateWindowSurface(gWindow);

    }
  }
  close();
  return 0;
}
       
