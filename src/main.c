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

const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];
texture* gSpriteSheetTexture;

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
  gSpriteSheetTexture = init_texture();
  return success;
}

void close() {
  freeTexture(gSpriteSheetTexture);
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  gRenderer = NULL;
  IMG_Quit();
  SDL_Quit();
}

int loadMedia() {
  int success = 1;
  if(!loadTextureFromFile(gSpriteSheetTexture, gRenderer, "res/foo.png")){
    printf("Failed to load walking animation texture!\n");
    success = 0;
  } else {
    gSpriteClips[0].x = 0;
    gSpriteClips[0].y = 0;
    gSpriteClips[0].w = 64;
    gSpriteClips[0].h = 205;

    gSpriteClips[1].x = 64;
    gSpriteClips[1].y = 0;
    gSpriteClips[1].w = 64;
    gSpriteClips[1].h = 205;

    gSpriteClips[2].x = 128;
    gSpriteClips[2].y = 0;
    gSpriteClips[2].w = 64;
    gSpriteClips[2].h = 205;

    gSpriteClips[3].x = 196;
    gSpriteClips[3].y = 0;
    gSpriteClips[3].w = 64;
    gSpriteClips[3].h = 205;
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
  int frame = 0;
  const int frame_interval = 5;

  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = 1;
      } 
    }        
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
    
    SDL_Rect* currentClip = &gSpriteClips[frame / frame_interval];
    renderTexture(gSpriteSheetTexture, 
                  gRenderer, 
                  (SCREEN_WIDTH - currentClip->w) / 2, 
                  (SCREEN_HEIGHT - currentClip->h) / 2,
                  currentClip);
    SDL_RenderPresent(gRenderer);
    
    frame++;
    if(frame / frame_interval >= WALKING_ANIMATION_FRAMES) {
      frame = 0;
      
    }
  }
  close();
  return 0;
}
       
