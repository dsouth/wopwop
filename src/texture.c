#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "texture.h"

texture* init_texture() {
  texture* c = (texture*)malloc(sizeof(texture));
  c->texture = NULL;
  c->width = 0;
  c->height = 0;
  return c;
}

int loadTextureFromFile(texture* t, SDL_Renderer* renderer, const char* path) {
  freeTexture(t);
  SDL_Texture* newTexture = NULL;
  SDL_Surface* loadedSurface = IMG_Load(path);
  if(loadedSurface == NULL) {
    printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
  } else {
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0x00, 0xFF, 0xFF));
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (newTexture == NULL) {
      printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
    } else {
      t->width = loadedSurface->w;
      t->height = loadedSurface->h;
    }
    SDL_FreeSurface(loadedSurface);
  }
  t->texture = newTexture;
  return t->texture != NULL;
}

void renderTexture(texture* t, SDL_Renderer* renderer, int x, int y, SDL_Rect* clip) {
  SDL_Rect renderQuad = {x, y, t->width, t->height};
  if (clip != NULL) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }
  SDL_RenderCopy(renderer, t->texture, clip, &renderQuad);
}

void freeTexture(texture* t) {
  if (t->texture != NULL) {
    SDL_DestroyTexture(t->texture);
    t->texture = NULL;
    t->width = 0;
    t->height = 0;
  }
}
