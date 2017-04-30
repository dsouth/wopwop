#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

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
      gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
      if (gRenderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        success = false;
      } else {
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        success = true;
      }
    }
  }
  return success;
}

void close() {
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  gRenderer = NULL;
  IMG_Quit();
  SDL_Quit();
}

bool loadMedia() {
  bool success = true;
  return success;
}

int main(int argc, char* args[]) {
  if(!init()) {
    printf("Failed to initialize!\n");
  } else {
    if(!loadMedia()) {
      printf("Failed to load media!\n");
    }
  }

  bool quit = false;
  SDL_Event e;


  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }

      SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00,  0x00, 0xFF);
      SDL_RenderClear(gRenderer);

      SDL_Rect fillRect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4,
                           SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
      SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
      SDL_RenderFillRect(gRenderer, &fillRect);

      SDL_Rect outlineRect = {SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6,
                              SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3};
      SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
      SDL_RenderDrawRect(gRenderer, &outlineRect);

      SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
      SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

      SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
      for(int i = 0; i < SCREEN_HEIGHT; i += 4) {
        SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, i);
      }

      SDL_RenderPresent(gRenderer);
    }
  }
  close();
  return 0;
}
       
