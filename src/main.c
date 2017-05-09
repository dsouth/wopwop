#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "texture.h"
#include "button.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int JOYSTICK_DEAD_ZONE = 8000;

int init();

int loadMedia();

void close();

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
texture *gArrowTexture = NULL;

SDL_Joystick *gGameController = NULL;

int init() {
    int success = 0;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
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

                if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
                    printf("Warning: Linear texture filtering not enabled!\n");
                }
                if (SDL_NumJoysticks() < 1) {
                    printf("Warning: No joysticks connected!\n");
                } else {
                    gGameController = SDL_JoystickOpen(0);
                    if (gGameController == NULL) {
                        printf("Warning: unable to open game controller! SDL Error%s\n", SDL_GetError());
                    }
                }
            }
        }
    }
    gArrowTexture = init_texture();
    return success;
}

void close() {
    freeTexture(gArrowTexture);
    SDL_JoystickClose(gGameController);
    gGameController = NULL;
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
    if (!loadTextureFromFile(gArrowTexture, gRenderer, "res/arrow.png")) {
        printf("Failed to load arrow sprite texture!\n");
        success = 0;
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
    Sint16 xDir = 0;
    Sint16 yDir = 0;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_JOYAXISMOTION) {
                if (e.jaxis.which == 0) {
                    if (e.jaxis.axis == 0) {
                        if (e.jaxis.value < -JOYSTICK_DEAD_ZONE ||
                            e.jaxis.value > JOYSTICK_DEAD_ZONE) {
                            xDir = e.jaxis.value;
                        }
                    } else if (e.jaxis.axis == 1) {
                        if (e.jaxis.value < -JOYSTICK_DEAD_ZONE ||
                            e.jaxis.value > JOYSTICK_DEAD_ZONE) {
                            yDir = e.jaxis.value;
                        }
                    }
                }
            }
        }
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        double joystickAngle = atan2((double) yDir, (double) xDir) * (180.0 / M_PI);
        if (xDir == 0 && yDir == 0) {
            joystickAngle = 0;
        }

        renderTexture(gArrowTexture,
                      gRenderer,
                      (SCREEN_HEIGHT - gArrowTexture->height) / 2,
                      (SCREEN_WIDTH - gArrowTexture->width) / 2,
                      NULL,
                      joystickAngle,
                      NULL,
                      NULL);
        SDL_RenderPresent(gRenderer);
    }
    close();
    return 0;
}
       
