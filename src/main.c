#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "texture.h"
#include "button.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int init();

int loadMedia();

void close();

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

SDL_Rect gSpriteClips[BUTTON_SPRITE_MOUSE_TOTAL];
texture *gButtonSpriteSheetTexture;
button *gButtons[BUTTON_TOTAL];

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
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = 0;
                }

                if (TTF_Init() == -1) {
                    printf("SDL_ttf could not initialize! SDL_tff Error: %s\n", TTF_GetError());
                    success = 0;
                }
            }
        }
    }
    gButtonSpriteSheetTexture = init_texture();
    for (int i = 0; i < BUTTON_TOTAL; i++) {
        gButtons[i] = init_button();
    }
    return success;
}

void close() {
    for (int i = 0; i < BUTTON_TOTAL; i++) {
        freeButton(gButtons[i]);
    }
    freeTexture(gButtonSpriteSheetTexture);
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

    if (!loadTextureFromFile(gButtonSpriteSheetTexture, gRenderer, "res/button.png")) {
        printf("Failed to load button sprite texture!\n");
        success = 0;
    } else {
        for (int i = 0; i < BUTTON_SPRITE_MOUSE_TOTAL; i++) {
            gSpriteClips[i].x = 0;
            gSpriteClips[i].y = i * BUTTON_HEIGHT;
            gSpriteClips[i].w = BUTTON_WIDTH;
            gSpriteClips[i].h = BUTTON_HEIGHT;
        }

        setButtonPosition(gButtons[0], 0, 0);
        setButtonPosition(gButtons[1], SCREEN_WIDTH - BUTTON_WIDTH, 0);
        setButtonPosition(gButtons[2], 0, SCREEN_HEIGHT - BUTTON_HEIGHT);
        setButtonPosition(gButtons[3], SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT);
    }

    return success;
}

int main(int argc, char *args[]) {
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        if (!loadMedia()) {
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
            for (int i = 0; i < BUTTON_TOTAL; i++) {
                handleEvent(gButtons[i], &e);
            }
        }
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        for (int i = 0; i < BUTTON_TOTAL; i++) {
            renderButton(gButtons[i], gRenderer, gButtonSpriteSheetTexture, gSpriteClips);
        }
        SDL_RenderPresent(gRenderer);
    }
    close();
    return 0;
}
       
