#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "texture.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int init();
int loadMedia();
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

texture* gFooTexture;
texture* gBackgroundTexture;

int init() {
  int success = 0;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = 0;
  } else {
    gWindow = SDL_CreateWindow("Wop Wop", 
                               SDL_WINDOWPOS_UNDEFINED, 
                               SDL_WINDOWPOS_UNDEFINED, 
                               SCREEN_WIDTH,
                               SCREEN_HEIGHT,
                               SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      success = 0;
    } else {
      gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
      if (gRenderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        success = 0;
      } else {
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        success = 1;
      }
    }
  }
  gFooTexture = init_texture();
  gBackgroundTexture = init_texture();
  return success;
}

void close() {
  freeTexture(gFooTexture);
  freeTexture(gBackgroundTexture);
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  gRenderer = NULL;
  IMG_Quit();
  SDL_Quit();
}

int loadMedia() {
  int success = 1;
  if(!loadTextureFromFile(gFooTexture, gRenderer, "res/foo.png")){
    printf("Failed to load Foo's texture image!\n");
    success = 0;
  }
  if(!loadTextureFromFile(gBackgroundTexture, gRenderer, "res/background.png")) {
    printf("Failed to load background texture image!\n");
    success = 0;
  }
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

  int quit = 0;
  SDL_Event e;

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = 1;
      }

      SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
      SDL_RenderClear(gRenderer);
      renderTexture(gBackgroundTexture, gRenderer, 0, 0);
      renderTexture(gFooTexture, gRenderer, 240, 190);
      SDL_RenderPresent(gRenderer);
    }
  }
  close();
  return 0;
}
       
