#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "lacg.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 800

#define VERT_SIZE 8
#define VUV (Vec3){.x = 0, .y = 0, .z = 1.f}

typedef struct {
    SDL_Window* win;
    SDL_Renderer* rend;
    int isRunning;
    Vec4 points[8];
    Vec4 projections[8];
    Vec3 COP;
    Vec3 VRP;
    float angle;
} State;

State* init(const char* title, int width, int height);
void update(State* state);
void render(State* state);
void handleEvents(State* state);
void quit(State* state);

#endif