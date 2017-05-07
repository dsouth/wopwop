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

texture* gArrowTexture;

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
      gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      if (gRenderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        success = 0;
      } else {
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        success = 1;
      }
    }
  }
  gArrowTexture = init_texture();
  return success;
}

void close() {
  freeTexture(gArrowTexture);
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  gRenderer = NULL;
  IMG_Quit();
  SDL_Quit();
}

int loadMedia() {
  int success = 1;
  if(!loadTextureFromFile(gArrowTexture, gRenderer, "res/arrow.png")){
    printf("Failed to load arrow texture!\n");
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
  double degrees = 0;
  SDL_RendererFlip flipType = SDL_FLIP_NONE;

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = 1;
      } else if (e.type == SDL_KEYDOWN) {
        switch(e.key.keysym.sym) {
        case SDLK_a:
          degrees -= 60;
          break;
        case SDLK_d:
          degrees += 60;
          break;
        case SDLK_q:
          flipType = SDL_FLIP_HORIZONTAL;
          break;
        case SDLK_w:
          flipType = SDL_FLIP_NONE;
          break;
        case SDLK_e:
          flipType = SDL_FLIP_VERTICAL;
          break;
        }
      }  
    }      
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
    
    renderTexture(gArrowTexture, 
                  gRenderer, 
                  (SCREEN_WIDTH - gArrowTexture->width) / 2,
                  (SCREEN_HEIGHT - gArrowTexture->height) / 2,
                  NULL, 
                  degrees,
                  NULL, 
                  flipType);
    SDL_RenderPresent(gRenderer);
  }
  close();
  return 0;
}
       
