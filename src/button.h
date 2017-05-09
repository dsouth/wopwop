#include <SDL2/SDL.h>
#include "texture.h"

static const int BUTTON_TOTAL = 4;
static const int BUTTON_WIDTH = 300;
static const int BUTTON_HEIGHT = 200;

enum buttonSprite {
  BUTTON_SPRITE_MOUSE_OUT = 0,
  BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
  BUTTON_SPRITE_MOUSE_DOWN = 2,
  BUTTON_SPRITE_MOUSE_UP = 3,
  BUTTON_SPRITE_MOUSE_TOTAL = 4
};

typedef struct button button;

struct button {
  SDL_Point position;
  enum buttonSprite sprite;
};

button* init_button();
void setButtonPosition(button* b, int x, int y);
void handleEvent(button* b, SDL_Event* e);
void renderButton(button* b, SDL_Renderer* r, texture* t, SDL_Rect clip[]);
void freeButton(button* b);

