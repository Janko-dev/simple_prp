#include "graphics.h"

State* init(const char* title, int width, int height){
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0){
        fprintf(stderr, "Unable to init subsystems: %s\n", SDL_GetError());
        exit(1);
    }

    State* s = (State*)malloc(sizeof(State));
    s->win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (s->win == NULL){
        fprintf(stderr, "Unable to create window: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    s->rend = SDL_CreateRenderer(s->win, -1, 0);
    if (s->rend == NULL){
        fprintf(stderr, "Unable to create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(s->win);
        SDL_Quit();
        exit(1);
    }

    s->isRunning = 1;
    return s;
}

Matrix* getRotationX(float angle){
    Matrix* rot = create_mat(4, 4);
    rot->data[0][0] = 1;
    rot->data[1][1] = cos(angle);
    rot->data[1][2] = -sin(angle);
    rot->data[2][1] = sin(angle);
    rot->data[2][2] = cos(angle);
    rot->data[3][3] = 1;
    return rot;
}

Matrix* getRotationY(float angle){
    Matrix* rot = create_mat(4, 4);
    rot->data[0][0] = cos(angle);
    rot->data[1][1] = 1;
    rot->data[2][2] = cos(angle);
    rot->data[2][0] = -sin(angle);
    rot->data[0][2] = sin(angle);
    rot->data[3][3] = 1;
    return rot;
}

Matrix* getRotationZ(float angle){
    Matrix* rot = create_mat(4, 4);
    rot->data[0][0] = cos(angle);
    rot->data[1][1] = cos(angle);
    rot->data[0][1] = sin(angle);
    rot->data[1][0] = -sin(angle);
    rot->data[2][2] = 1;
    rot->data[3][3] = 1;
    return rot;
}

Matrix* getProjectionMatrix(float w){
    float d = 2.f;
    Matrix* rot = create_mat(4, 4);
    rot->data[0][0] = (d/-w);
    rot->data[1][1] = (d/-w);
    rot->data[2][2] = (d/-w);
    rot->data[3][3] = 1;
    return rot;
}

void update(State* state){
    state->angle+=0.01f;
    Matrix* rotX = getRotationX(state->angle);
    Matrix* rotY = getRotationY(state->angle);
    
    Matrix* rotationMatrix = prod_mat(rotY, rotX);
    state->projections = prod_mat(rotationMatrix, state->points);
    free_mat(rotationMatrix);
    free_mat(rotX);
    free_mat(rotY);
    Vector* temp = create_vec(state->projections->m);
    for (int i = 0; i < state->projections->n; i++){
        temp->data[0] = state->projections->data[0][i];
        temp->data[1] = state->projections->data[1][i];
        temp->data[2] = state->projections->data[2][i];
        temp->data[3] = state->projections->data[3][i];
        Matrix* projectionMatrix = getProjectionMatrix(temp->data[2]);
        Vector* projected = prod_mat_vec(projectionMatrix, temp);
        free_mat(projectionMatrix);

        state->projections->data[0][i] = projected->data[0];
        state->projections->data[1][i] = projected->data[1];
        state->projections->data[2][i] = projected->data[2];
        state->projections->data[3][i] = projected->data[3];
        free_vec(projected);
    }
    free_vec(temp);
    
    Matrix* result = scale_mat(state->projections, 10.f);
    free_mat(state->projections);
    state->projections = result;
}

void render(State* state){
    SDL_SetRenderDrawColor(state->rend, 0, 0, 0, 1);
    SDL_RenderClear(state->rend);

    SDL_SetRenderDrawColor(state->rend, 255, 0, 0, 1);
    for (int i = 0; i < state->projections->n/2; i++){
        SDL_RenderDrawLineF(state->rend,
            state->projections->data[0][i] + WIDTH/2,
            state->projections->data[1][i] + HEIGHT/2,
            state->projections->data[0][(i+1)%4] + WIDTH/2,
            state->projections->data[1][(i+1)%4] + HEIGHT/2);
        
        SDL_RenderDrawLineF(state->rend,
            state->projections->data[0][i+4] + WIDTH/2,
            state->projections->data[1][i+4] + HEIGHT/2,
            state->projections->data[0][((i+1)%4)+4] + WIDTH/2,
            state->projections->data[1][((i+1)%4)+4] + HEIGHT/2);

        SDL_RenderDrawLineF(state->rend,
            state->projections->data[0][i] + WIDTH/2,
            state->projections->data[1][i] + HEIGHT/2,
            state->projections->data[0][i+4] + WIDTH/2,
            state->projections->data[1][i+4] + HEIGHT/2);
    }

    SDL_RenderPresent(state->rend);
}

void handleEvents(State* state){
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        switch(e.type){
            case SDL_QUIT:
                state->isRunning = 0;
                break;
            default: break;
        }
    }
}

void quit(State* state){
    free_mat(state->projections);
    free_mat(state->points);
    SDL_DestroyRenderer(state->rend);
    SDL_DestroyWindow(state->win);
    SDL_Quit();
}