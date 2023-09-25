#ifndef __SHAPES_H
#define __SHAPES_H

#include <SDL2/SDL.h>

#include "./color.h"
#include "./types.h"

typedef struct {
    vec2 center; 
    u32 radius;
    Color color;
} Circle;

Circle newCircle(vec2 center, u32 radius, Color color);
void drawFillCircle(SDL_Renderer* renderer, Circle circle);
void drawCircleAtPoint(SDL_Renderer* renderer, vec2 point, u32 radius, Color color);

typedef struct {
    vec2 topLeft;
    i32 width, height;
    Color color;
} Rect;

Rect newRect(vec2 topLeft, i32 width, i32 height, Color color);
void drawFillRect(SDL_Renderer* renderer, Rect rect);

typedef struct {
    vec3 closeTopLeft;
    vec3 vertices[8];
    i32 length;
    Color color;
} Cube;

Cube newCube(vec3 closeTopLeft, i32 length, Color color);
void drawCubeVertices(SDL_Renderer* renderer, Cube cube, f32 focal_length);
void drawCubeWire(SDL_Renderer* renderer, Cube cube, f32 focal_length);

#endif  //__SHAPES_H
