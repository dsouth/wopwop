#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER
typedef struct texture texture;

struct texture {
  SDL_Texture* texture;
  int width;
  int height;
};
#endif

texture* init_texture();
int loadTextureFromFile(texture* t, SDL_Renderer* r, const char* path);
int loadTextureFromRenderedText(texture* t, SDL_Renderer* r, TTF_Font* f, const char* text, SDL_Color textColor);
void setColorTexture(texture* t, Uint8 r, Uint8 g, Uint8 b);
void setBlendModeTexture(texture* t, SDL_BlendMode bleeding);
void setAlphaTexture(texture* t, Uint8 a);
void renderTexture(texture* t, 
                   SDL_Renderer* r, 
                   int x, 
                   int y, 
                   SDL_Rect* clip,
                   double angle,
                   SDL_Point* center,
                   SDL_RendererFlip* flip);
void freeTexture(texture* t);
