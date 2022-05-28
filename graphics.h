#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "la.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 800

typedef struct {
    SDL_Window* win;
    SDL_Renderer* rend;
    int isRunning;
    Matrix* points;
    Matrix* projections;
    float angle;
} State;

State* init(const char* title, int width, int height);
void update(State* state);
void render(State* state);
void handleEvents(State* state);
void quit(State* state);

#endif