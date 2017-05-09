#include <SDL2/SDL.h>
#include "button.h"

button *init_button() {
    button *b = (button *) malloc(sizeof(button));
    b->position.x = 0;
    b->position.y = 0;
    b->sprite = BUTTON_SPRITE_MOUSE_OUT;
    return b;
}

void freeButton(button *b) {
    free(b);
}

void setButtonPosition(button *b, int x, int y) {
    b->position.x = x;
    b->position.y = y;
}

void handleEvent(button *b, SDL_Event *e) {
    if (e->type == SDL_MOUSEMOTION ||
        e->type == SDL_MOUSEBUTTONDOWN ||
        e->type == SDL_MOUSEBUTTONUP) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        int inside = 1;
        if (x < b->position.x) {
            inside = 0;
        } else if (x > b->position.x + 300) {
            inside = 0;
        }
        if (y < b->position.y) {
            inside = 0;
        } else if (y > b->position.y + 200) {
            inside = 0;
        }

        if (!inside) {
            b->sprite = BUTTON_SPRITE_MOUSE_OUT;
        } else {
            switch (e->type) {
                case SDL_MOUSEMOTION:
                    b->sprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    b->sprite = BUTTON_SPRITE_MOUSE_DOWN;
                    break;
                case SDL_MOUSEBUTTONUP:
                    b->sprite = BUTTON_SPRITE_MOUSE_UP;
                    break;
            }
        }
    }
}

void renderButton(button *b, SDL_Renderer *r, texture *t, SDL_Rect clip[]) {
    renderTexture(t, r, b->position.x, b->position.y, &(clip[b->sprite]), 0.0, NULL, SDL_FLIP_NONE);
}


  
