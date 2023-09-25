#include "include/shapes.h"
#include "include/types.h"
#include <SDL2/SDL_render.h>

// Circle Stuff
Circle newCircle(vec2 center, u32 radius, Color color) {
    return (Circle){.center = center, .radius = radius, .color = color}; 
}

void drawFillCircle(SDL_Renderer* renderer, Circle circle) {
    SDL_SetRenderDrawColor(renderer, ColorParam(circle.color));
    i32 radius = (i32)circle.radius;
    for (i32 y = -radius; y <= radius; ++y) {
        for (i32 x = -radius; x <= radius; ++x) {
            if (x * x + y * y <= radius * radius) {
                SDL_RenderDrawPoint(renderer, circle.center.x + x, circle.center.y + y);
            }
        }
    }
}

void drawCircleAtPoint(SDL_Renderer* renderer, vec2 point, u32 radius, Color color) {
    Circle c = newCircle(point, radius, color);
    drawFillCircle(renderer, c);
}

//  Rectangle Stuff
Rect newRect(vec2 topLeft, i32 width, i32 height, Color color) {
    return (Rect){.topLeft = topLeft, .width = width, .height = height, .color = color}; 
}

void drawFillRect(SDL_Renderer* renderer, Rect rect) {
    SDL_SetRenderDrawColor(renderer, ColorParam(rect.color));
    for (i32 y = rect.topLeft.y; y < rect.topLeft.y + rect.height; ++y) {
        for (i32 x = rect.topLeft.x; x < rect.topLeft.x + rect.width; ++x) {
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}

// Cube Stuff
Cube newCube(vec3 closeTopLeft, i32 length, Color color) {
    Cube c = {};
    c.closeTopLeft = closeTopLeft;
    c.length = length;
    c.color = color;

    // Calculate other vertices based on closeTopLeft
    c.vertices[0] = c.closeTopLeft;
    c.vertices[1] = (vec3){c.closeTopLeft.x + c.length, c.closeTopLeft.y, c.closeTopLeft.z};
    c.vertices[2] = (vec3){c.closeTopLeft.x + c.length, c.closeTopLeft.  y + c.length, c.closeTopLeft.z};
    c.vertices[3] = (vec3){c.closeTopLeft.x, c.closeTopLeft.  y + c.length, c.closeTopLeft.z};
    c.vertices[4] = (vec3){c.closeTopLeft.x, c.closeTopLeft.y, c.closeTopLeft.z + c.length};
    c.vertices[5] = (vec3){c.closeTopLeft.x + c.length, c.closeTopLeft.y, c.closeTopLeft.z + c.length};
    c.vertices[6] = (vec3){c.closeTopLeft.x + c.length, c.closeTopLeft.  y + c.length, c.closeTopLeft.z + c.length};
    c.vertices[7] = (vec3){c.closeTopLeft.x, c.closeTopLeft.  y + c.length, c.closeTopLeft.z + c.length};
    return c;
}

void drawCubeVertices(SDL_Renderer* renderer, Cube cube, f32 focal_length) {
    SDL_SetRenderDrawColor(renderer, ColorParam(cube.color));
    for (i32 i = 0; i < 8; ++i) {
        // Orthographic projection: Scale x and y coordinates, keep z coordinate as is
        vec2 projected = project_vec3(cube.vertices[i], focal_length);
        SDL_RenderDrawPoint(renderer, projected.x, projected.y);
    }
}

void drawCubeWire(SDL_Renderer* renderer, Cube cube, f32 focal_length) {
    SDL_SetRenderDrawColor(renderer, ColorParam(cube.color));

    // Define the edges of the cube (pairs of vertices)
    i32 edges[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        {0, 4}, {1, 5}, {2, 6}, {3, 7}
    };

    // Project and draw each edge with depth adjustment
    for (i32 i = 0; i < 12; ++i) {
        vec2 projected_a = project_vec3(cube.vertices[edges[i][0]], focal_length);
        vec2 projected_b = project_vec3(cube.vertices[edges[i][1]], focal_length);

        SDL_RenderDrawLine(renderer, projected_a.x, projected_a.y, projected_b.x, projected_b.y);
    }
}
