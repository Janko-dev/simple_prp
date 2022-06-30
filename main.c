#include "graphics.h"

int main(int argc, char **argv){

    (void)argc; (void)argv;

    State* graphics = init("Computer Graphics", WIDTH, HEIGHT);

    graphics->VRP = (Vec3){.x=WIDTH/2, .y=HEIGHT/2, .z=0};
    graphics->COP = (Vec3){.x=4, .y=2, .z=0};

    while(graphics->isRunning){
        handleEvents(graphics);
        update(graphics);
        render(graphics);
        SDL_Delay(1000/60);
    }

    quit(graphics);

    return 0;
}