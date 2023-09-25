#include <SDL2/SDL_keycode.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <stdlib.h>
#include <time.h>

#include "include/types.h"
#include "include/consts.h"
#include "include/color.h"
#include "include/shapes.h"

Color rand_color() {
    srand(time(NULL));
    Color c = {};
    c.r = rand() % 255;
    c.g = rand() % 255;
    c.b = rand() % 255;
    c.a = rand() % 255;
    return c;
}

f32 rand_z() {
    srand(time(NULL));
    return rand() % 20;
}

i32 rand_length() {
    srand(time(NULL));
    i32 len = (rand() + 50) % 100;
    return len;
}

void clear_array(Cube* arr, i32 len) {
    for (i32 i = 0; i < len; ++i) {
        arr[i] = (Cube){};
    }
}

int main(void) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("SDL Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool quit = false;
    SDL_Event e;
    u32 frameStart, frameTime;
    const u32 frameDelay = 1000/FPS;

    f32 focal_length = 1024;

    i32 cube_count = 0;
    Cube cubes[5000] = {};
    
    while (!quit) {
        frameStart = SDL_GetTicks();
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT: {
                    quit = true;
                    break;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    cubes[cube_count++] = newCube((vec3){e.motion.x, e.motion.y, rand_z()}, rand_length(), rand_color());
                    break;
                }

                case SDL_KEYDOWN: {
                    SDL_KeyCode key = e.key.keysym.sym;

                    if (key == SDLK_UP) {
                        if (focal_length + 5 >= 2000) { focal_length = 1995;}
                        focal_length += 5;
                    } else if (key == SDLK_DOWN) {
                        if (focal_length - 5 <= 0) { focal_length = 5;}
                        focal_length -= 5;
                    } else if (key == SDLK_SPACE) {
                        focal_length = 1024;
                    } else if (key == SDLK_LCTRL) {
                        clear_array(cubes, cube_count);
                    }

                    break;
                } 
            }
        }

        SDL_SetRenderDrawColor(renderer, ColorParam(BACKGROUND_COLOR));
        SDL_RenderClear(renderer);

        // Start Drawing
        for (i32 i = 0; i < 1024 && i < cube_count; ++i) {
            drawCubeWire(renderer, cubes[i], focal_length);
        }

        // End Drawing
        SDL_RenderPresent(renderer);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < frameDelay) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
