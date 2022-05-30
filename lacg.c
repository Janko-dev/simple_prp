#include <stdio.h>
#include <math.h>
#include "lacg.h"

// Matrix 4x4 functions
void fill_mat4(Mat4x4* m, float val){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            m->d[i][j] = val;
        }
    }
}

void iden4(Mat4x4* m){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            m->d[i][j] = 0;
        }
        m->d[i][i] = 1.f;
    }
}

void scale_mat4(Mat4x4* m, float scalar){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            m->d[i][j] *= scalar;
        }
    }
}

void print_mat4(const Mat4x4 m){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            printf("%9.4f ", m.d[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void prod_mat4(Mat4x4* res, const Mat4x4 A, const Mat4x4 B){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            for (int k = 0; k < 4; k++){
                res->d[i][j] += A.d[i][k] * B.d[k][j]; 
            }
        }
    }
}

// Matrix 3x3
void fill_mat3(Mat3x3* m, float val){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            m->d[i][j] = val;
        }
    }
}

void iden3(Mat3x3* m){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            m->d[i][j] = 0;
        }
        m->d[i][i] = 1.f;
    }
}

void scale_mat3(Mat3x3* m, float scalar){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            m->d[i][j] *= scalar;
        }
    }
}

void print_mat3(const Mat3x3 m){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            printf("%9.4f ", m.d[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void prod_mat3(Mat3x3* res, const Mat3x3 A, const Mat3x3 B){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            for (int k = 0; k < 3; k++){
                res->d[i][j] += A.d[i][k] * B.d[k][j]; 
            }
        }
    }
}

// Vector 4 
void scale_vec4(Vec4* v, float scalar){
    v->x *= scalar;
    v->y *= scalar;
    v->z *= scalar;
    v->h *= scalar;
}

void add_vec4(Vec4* v1, Vec4 v2){
    v1->x += v2.x;
    v1->y += v2.y;
    v1->z += v2.z;
    v1->h += v2.h;
}

void print_vec4(const Vec4 v){
    printf("%9.4f\n%9.4f\n%9.4f\n%9.4f\n", v.x, v.y, v.z, v.h);
}

void prod_mat_vec4(Vec4* res, const Mat4x4 A, const Vec4 B){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            res->d[i] += A.d[i][j] * B.d[j];
        }
    }
}

float mag4(const Vec4 v){
    return sqrt(v.x*v.x + v.y*v.y + v.z*v.z + v.h*v.h);
}

// Vector 3
void scale_vec3(Vec3* v, float scalar){
    v->x *= scalar;
    v->y *= scalar;
    v->z *= scalar;
}

void add_vec3(Vec3* v1, Vec3 v2){
    v1->x += v2.x;
    v1->y += v2.y;
    v1->z += v2.z;
}

void print_vec3(const Vec3 v){
    printf("%9.4f\n%9.4f\n%9.4f\n", v.x, v.y, v.z);
}

void prod_mat_vec3(Vec3* res, const Mat3x3 A, const Vec3 B){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            res->d[i] += A.d[i][j] * B.d[j];
        }
    }
}

void cross_prod3(Vec3* res, const Vec3 A, const Vec3 B){
    res->x = A.y*B.z - A.z*B.y;
    res->y = A.z*B.x - A.x*B.z;
    res->z = A.x*B.y - A.y*B.x;
}

float mag3(Vec3 v){
    return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}