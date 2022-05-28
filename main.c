#include "graphics.h"

int main(int argc, char **argv){

    (void)argc;
    (void)argv;

    State* graphics = init("Computer Graphics", WIDTH, HEIGHT);

    float data[4][8] = {
        {0, 1, 1, 0, 0, 1, 1, 0},
        {0, 0, 1, 1, 0, 0, 1, 1},
        {0, 0, 0, 0, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1}
    };
    graphics->points = create_mat(4, 8);
    graphics->projections = create_mat(4, 8);
    for (int i = 0; i < graphics->points->m; i++){
        for (int j = 0; j < graphics->points->n; j++){
            graphics->points->data[i][j] = data[i][j] - 0.5f;
        }   
    }
    graphics->angle = 0.0f;

    while(graphics->isRunning){
        handleEvents(graphics);
        update(graphics);
        render(graphics);
        SDL_Delay(1000/60);
    }
    quit(graphics);

    return 0;
}