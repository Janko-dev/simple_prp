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

// Matrix* getRotationX(float angle){
//     Matrix* rot = create_mat(4, 4);
//     rot->data[0][0] = 1;
//     rot->data[1][1] = cos(angle);
//     rot->data[1][2] = -sin(angle);
//     rot->data[2][1] = sin(angle);
//     rot->data[2][2] = cos(angle);
//     rot->data[3][3] = 1;
//     return rot;
// }

// Matrix* getRotationY(float angle){
//     Matrix* rot = create_mat(4, 4);
//     rot->data[0][0] = cos(angle);
//     rot->data[1][1] = 1;
//     rot->data[2][2] = cos(angle);
//     rot->data[2][0] = -sin(angle);
//     rot->data[0][2] = sin(angle);
//     rot->data[3][3] = 1;
//     return rot;
// }

// Matrix* getRotationZ(float angle){
//     Matrix* rot = create_mat(4, 4);
//     rot->data[0][0] = cos(angle);
//     rot->data[1][1] = cos(angle);
//     rot->data[0][1] = sin(angle);
//     rot->data[1][0] = -sin(angle);
//     rot->data[2][2] = 1;
//     rot->data[3][3] = 1;
//     return rot;
// }

// Matrix* getProjectionMatrix(float w){
//     float d = 2.f;
//     Matrix* rot = create_mat(4, 4);
//     rot->data[0][0] = (d/-w);
//     rot->data[1][1] = (d/-w);
//     rot->data[2][2] = (d/-w);
//     rot->data[3][3] = 1;
//     return rot;
// }

void update(State* state){
    // state->angle+=0.01f;
    // Matrix* rotX = getRotationX(state->angle);
    // Matrix* rotY = getRotationY(state->angle);
    
    // Matrix* rotationMatrix = prod_mat(rotY, rotX);
    // state->projections = prod_mat(rotationMatrix, state->points);
    // free_mat(rotationMatrix);
    // free_mat(rotX);
    // free_mat(rotY);
    // Vector* temp = create_vec(state->projections->m);
    // for (int i = 0; i < state->projections->n; i++){
    //     temp->data[0] = state->projections->data[0][i];
    //     temp->data[1] = state->projections->data[1][i];
    //     temp->data[2] = state->projections->data[2][i];
    //     temp->data[3] = state->projections->data[3][i];
    //     Matrix* projectionMatrix = getProjectionMatrix(temp->data[2]);
    //     Vector* projected = prod_mat_vec(projectionMatrix, temp);
    //     free_mat(projectionMatrix);

    //     state->projections->data[0][i] = projected->data[0];
    //     state->projections->data[1][i] = projected->data[1];
    //     state->projections->data[2][i] = projected->data[2];
    //     state->projections->data[3][i] = projected->data[3];
    //     free_vec(projected);
    // }
    // free_vec(temp);
    
    // Matrix* result = scale_mat(state->projections, 10.f);
    // free_mat(state->projections);
    // state->projections = result;

    Vec4 points[VERT_SIZE] = {
        { .x = 0, .y = 0, .z = 0, .h = 1 },
        { .x = 1, .y = 0, .z = 0, .h = 1 },
        { .x = 1, .y = 1, .z = 0, .h = 1 },
        { .x = 0, .y = 1, .z = 0, .h = 1 },
        { .x = 0, .y = 0, .z = 1, .h = 1 },
        { .x = 1, .y = 0, .z = 1, .h = 1 },
        { .x = 1, .y = 1, .z = 1, .h = 1 },
        { .x = 0, .y = 1, .z = 1, .h = 1 }
    };
    for (int i = 0; i < VERT_SIZE; i++) {
        scale_vec4(&points[i], -1);
        add_vec4(&points[i], (Vec4){.x=0, .y=0, .z=2});
        state->points[i] = points[i];
    }

    // Center of projection (COP) and View up Vector (VUV)
    //state->COP = (Vec3){.x = 4.f, .y = 2.f, .z = 0.f};
    
    // World coordinate transform, Rotation matrix, transform -COP
    Mat4x4 w_trans, R, T_COP;
    iden4(&R);
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

    for (int i = 0; i < 3; i++){
        R.d[0][i] = u.d[i];
        R.d[1][i] = v.d[i];
        R.d[2][i] = w.d[i];
    }
    
    fill_mat4(&w_trans, 0);
    prod_mat4(&w_trans, R, T_COP);

    float d = 2;
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

        scale_vec4(&state->points[i], 200.f);
    }

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