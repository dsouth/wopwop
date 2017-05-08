#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <math.h>

#include "texture.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int init();
int loadMedia();
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

TTF_Font *gFont = NULL;
texture* gTextTexture;

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

        int imgFlags = IMG_INIT_PNG;
        if(!(IMG_Init(imgFlags) &imgFlags)) {
          printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
          success = 0;
        }

        if(TTF_Init() == -1) {
          printf("SDL_ttf could not initialize! SDL_tff Error: %s\n", TTF_GetError());
          success = 0;
        }
      }
    }
  }
  gTextTexture = init_texture();
  return success;
}

void close() {
  freeTexture(gTextTexture);
  TTF_CloseFont(gFont);
  gFont = NULL;
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  gRenderer = NULL;
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

int loadMedia() {
  int success = 1;
  gFont = TTF_OpenFont("res/lazy.ttf", 28);
  if (gFont == NULL) {
    printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
    success = 0;
  } else {
    SDL_Color textColor = {0, 0, 0};
    if(!loadTextureFromRenderedText(gTextTexture, gRenderer, gFont, "The quick brown fox jumps over the lazy dog", textColor)) {
      printf("Failed to render text texture!\n");
      success = 0;
    }
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
      } 
    }      
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
    
    renderTexture(gTextTexture, 
                  gRenderer,
                  (SCREEN_WIDTH - gTextTexture->width) / 2,
                  (SCREEN_HEIGHT - gTextTexture->height) / 2,
                  NULL, 
                  degrees,
                  NULL, 
                  flipType);                  

    SDL_RenderPresent(gRenderer);
  }
  close();
  return 0;
}
       
