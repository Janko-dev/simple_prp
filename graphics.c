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

void rotateX(Mat4x4* m, float angle){
    fill_mat4(m, 0);
    m->d[0][0] = 1;
    m->d[1][1] = cos(angle);
    m->d[1][2] = -sin(angle);
    m->d[2][1] = sin(angle);
    m->d[2][2] = cos(angle);
    m->d[3][3] = 1;
}

void rotateY(Mat4x4* m, float angle){
    fill_mat4(m, 0);
    m->d[0][0] = cos(angle);
    m->d[1][1] = 1;
    m->d[2][2] = cos(angle);
    m->d[2][0] = -sin(angle);
    m->d[0][2] = sin(angle);
    m->d[3][3] = 1;
}

void rotateZ(Mat4x4* m, float angle){
    fill_mat4(m, 0);
    m->d[0][0] = cos(angle);
    m->d[1][1] = cos(angle);
    m->d[0][1] = sin(angle);
    m->d[1][0] = -sin(angle);
    m->d[2][2] = 1;
    m->d[3][3] = 1;
}

void update(State* state){

    Vec4 points[VERT_SIZE] = POINTS(1);
    // 3d modeling transformations
    Mat4x4 rotMat;
    rotateX(&rotMat, state->angle);
    for (int i = 0; i < VERT_SIZE; i++) {
        Vec4 v = {.x=0, .y=0, .z=0, .h=0};
        // rotate vector around axis with updated angle
        prod_mat_vec4(&v, rotMat, points[i]);
        // invert vector 
        scale_vec4(&v, -1);
        // translate vector
        add_vec4(&v, (Vec4){.x=0, .y=0, .z=1});
        state->points[i] = v;
    }
    
    // viewing transformations
    Mat4x4 w_trans, R, T_COP;
    
    iden4(&T_COP);
    T_COP.d[0][3] = -state->COP.d[0];
    T_COP.d[1][3] = -state->COP.d[1];
    T_COP.d[2][3] = -state->COP.d[2];

    // u, v, w vectors
    Vec3 u, v, w = {
        .x = state->COP.x, 
        .y = state->COP.y, 
        .z = state->COP.z
    };

    scale_vec3(&w, 1/mag3(state->COP));
    cross_prod3(&u, VUV, w);
    cross_prod3(&v, w, u);

    iden4(&R);
    for (int i = 0; i < 3; i++){
        R.d[0][i] = u.d[i];
        R.d[1][i] = v.d[i];
        R.d[2][i] = w.d[i];
    }
    
    fill_mat4(&w_trans, 0);
    prod_mat4(&w_trans, R, T_COP);

    // Perspective transformations
    float d = distance(state->COP, (Vec3){.x=0, .y=0, .z=0});
    for (int i = 0; i < VERT_SIZE; i++){
        Vec4 v = {.x=0, .y=0, .z=0, .h=0};
        prod_mat_vec4(&v, w_trans, state->points[i]);
        state->points[i] = v;

        Mat4x4 persp_trans;
        iden4(&persp_trans);
        scale_mat4(&persp_trans, -d/state->points[i].z);
        persp_trans.d[3][3] = 1.f;

        v = (Vec4){.x=0, .y=0, .z=0, .h=0};
        prod_mat_vec4(&v, persp_trans, state->points[i]);
        state->points[i] = v;

        scale_vec4(&state->points[i], 100.f);
    }
    state->angle += 0.01;
}

void render(State* state){
    SDL_SetRenderDrawColor(state->rend, 0, 0, 0, 1);
    SDL_RenderClear(state->rend);
    // TODO: make vector out of translation so that camera movement is possible 
    SDL_SetRenderDrawColor(state->rend, 255, 0, 0, 1);
    for (int i = 0; i < 4; i++){
        SDL_RenderDrawLineF(state->rend,
            state->points[i].x + state->VRP.x,
            state->points[i].y + state->VRP.y,
            state->points[(i+1)%4].x + state->VRP.x,
            state->points[(i+1)%4].y + state->VRP.y);
        
        SDL_RenderDrawLineF(state->rend,
            state->points[i+4].x + state->VRP.x,
            state->points[i+4].y + state->VRP.y,
            state->points[((i+1)%4)+4].x + state->VRP.x,
            state->points[((i+1)%4)+4].y + state->VRP.y);

        SDL_RenderDrawLineF(state->rend,
            state->points[i].x + state->VRP.x,
            state->points[i].y + state->VRP.y,
            state->points[i+4].x + state->VRP.x,
            state->points[i+4].y + state->VRP.y);
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
            case SDL_KEYDOWN:{
                switch (e.key.keysym.sym){
                    case SDLK_LEFT: {
                        state->VRP.x--;
                    } break;
                    case SDLK_RIGHT: {
                        state->VRP.x++;
                    } break;
                    case SDLK_UP: {
                        state->COP.x -= 0.01f;
                        state->COP.y -= 0.01f;
                    } break;
                    case SDLK_DOWN: {
                        state->COP.x += 0.01f;
                        state->COP.y += 0.01f;
                    } break;
                    default: break;
                }
                // print_vec3(state->COP);
            } break;
            case SDL_MOUSEMOTION:{
                //printf("X: %d\n", e.motion.x);
                
            } break;
            default: break;
        }
    }
}

void quit(State* state){
    SDL_DestroyRenderer(state->rend);
    SDL_DestroyWindow(state->win);
    SDL_Quit();
}