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

texture* gColors;

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
  gColors = init_texture();
  return success;
}

void close() {
  freeTexture(gColors);
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  gRenderer = NULL;
  IMG_Quit();
  SDL_Quit();
}

int loadMedia() {
  int success = 1;
  if(!loadTextureFromFile(gColors, gRenderer, "res/colors.png")){
    printf("Failed to load colors texture!\n");
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
  Uint8 r = 255;
  Uint8 g = 255;
  Uint8 b = 255;

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = 1;
      } else if (e.type == SDL_KEYDOWN) {
        switch(e.key.keysym.sym) {
        case SDLK_q:
          r += 32;
          break;
        case SDLK_w:
          g += 32;
          break;
        case SDLK_e:
          b += 32;
          break;
        case SDLK_a:
          r -= 32;
          break;
        case SDLK_s:
          g -= 32;
          break;
        case SDLK_d:
          b -= 32;
          break;
        }
      }
        
      SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
      SDL_RenderClear(gRenderer);
      setColorTexture(gColors, r, g, b);
      renderTexture(gColors, gRenderer, 0, 0, NULL);
      SDL_RenderPresent(gRenderer);
    }
  }
  close();
  return 0;
}
       
