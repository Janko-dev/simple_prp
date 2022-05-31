#include "graphics.h"

int main(int argc, char **argv){

    (void)argc; (void)argv;

    State* graphics = init("Computer Graphics", WIDTH, HEIGHT);

    // Vec4 points[VERT_SIZE] = {
    //     { .x = 0, .y = 0, .z = 0, .h = 1 },
    //     { .x = 1, .y = 0, .z = 0, .h = 1 },
    //     { .x = 1, .y = 1, .z = 0, .h = 1 },
    //     { .x = 0, .y = 1, .z = 0, .h = 1 },
    //     { .x = 0, .y = 0, .z = 1, .h = 1 },
    //     { .x = 1, .y = 0, .z = 1, .h = 1 },
    //     { .x = 1, .y = 1, .z = 1, .h = 1 },
    //     { .x = 0, .y = 1, .z = 1, .h = 1 }
    // };
    // for (int i = 0; i < VERT_SIZE; i++) {
    //     scale_vec4(&points[i], -1);
    //     add_vec4(&points[i], (Vec4){.x=0, .y=0, .z=2});
    //     graphics->points[i] = points[i];
    // }
    // graphics->angle = 0.0f;

    // // Center of projection (COP) and View up Vector (VUV)
    // graphics->COP = (Vec3){.x = 4.f, .y = 2.f, .z = 0.f};
    // Vec3 VUV = {.x = 0,   .y = 0,   .z = 1.f};
    
    // // World coordinate transform, Rotation matrix, transform -COP
    // Mat4x4 w_trans, R, T_COP;
    // iden4(&R);
    // iden4(&T_COP);
    // T_COP.d[0][3] = -graphics->COP.d[0];
    // T_COP.d[1][3] = -graphics->COP.d[1];
    // T_COP.d[2][3] = -graphics->COP.d[2];

    // // u, v, w vectors
    // Vec3 u, v, w = {.x = graphics->COP.x, .y = graphics->COP.y, .z = graphics->COP.z};
    // scale_vec3(&w, 1/mag3(graphics->COPCOP));
    // cross_prod3(&u, VUV, w);
    // cross_prod3(&v, w, u);

    // for (int i = 0; i < 3; i++){
    //     R.d[0][i] = u.d[i];
    //     R.d[1][i] = v.d[i];
    //     R.d[2][i] = w.d[i];
    // }
    
    // fill_mat4(&w_trans, 0);
    // prod_mat4(&w_trans, R, T_COP);

    // float d = 2;
    // for (int i = 0; i < VERT_SIZE; i++){
    //     Vec4 v = {.x=0, .y=0, .z=0, .h=0};
    //     prod_mat_vec4(&v, w_trans, graphics->points[i]);
    //     graphics->points[i] = v;

    //     Mat4x4 persp_trans;
    //     iden4(&persp_trans);
    //     scale_mat4(&persp_trans, -d/graphics->points[i].z);
    //     persp_trans.d[3][3] = 1.f;
    //     v = (Vec4){.x=0, .y=0, .z=0, .h=0};
    //     prod_mat_vec4(&v, persp_trans, graphics->points[i]);
    //     graphics->points[i] = v;

    //     scale_vec4(&graphics->points[i], 200.f);
    // }

    // for (int i = 0; i < VERT_SIZE; i++){
    //     for (int j = 0; j < 4; j++){
    //         printf("%9.4f ", graphics->points[i].d[j]);
    //     }
    //     printf("\n");
    // }

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