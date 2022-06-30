#ifndef LA_COMP_GRAPHICS_H
#define LA_COMP_GRAPHICS_H

// x y z
// r g b
// d[3]
typedef union{
    struct {
        union {
            float x;
            float r;
        };
        union {
            float y;
            float g;
        };
        union {
            float z;
            float b;
        };
    };
    float d[3];
} Vec3;

// x y z h
// r g b a
// d[4]
typedef union{
    struct {
        union {
            float x;
            float r;
        };
        union {
            float y;
            float g;
        };
        union {
            float z;
            float b;
        };
        union {
            float h;
            float a;
        };
    };
    float d[4];
} Vec4;

typedef struct{
    float d[3][3];
} Mat3x3;

typedef struct{
    float d[4][4];
} Mat4x4;

#define POINTS(v) {\
        { .x = -v, .y = -v, .z = -v, .h = v },\
        { .x = v, .y = -v, .z = -v, .h = v },\
        { .x = v, .y = v, .z = -v, .h = v },\
        { .x = -v, .y = v, .z = -v, .h = v },\
        { .x = -v, .y = -v, .z =  v, .h = v },\
        { .x = v, .y = -v, .z =  v, .h = v },\
        { .x = v, .y = v, .z =  v, .h = v },\
        { .x = -v, .y = v, .z =  v, .h = v }\
    }\

// Matrix 4x4
void fill_mat4(Mat4x4* m, float val);
void iden4(Mat4x4* m);
void scale_mat4(Mat4x4* m, float scalar);
void print_mat4(const Mat4x4 m);
void prod_mat4(Mat4x4* res, const Mat4x4 A, const Mat4x4 B);

// Matrix 3x3
void fill_mat3(Mat3x3* m, float val);
void iden3(Mat3x3* m);
void scale_mat3(Mat3x3* m, float scalar);
void print_mat3(const Mat3x3 m);
void prod_mat3(Mat3x3* res, const Mat3x3 A, const Mat3x3 B);

// Vector 4 
void scale_vec4(Vec4* v, float scalar);
void add_vec4(Vec4* v1, Vec4 v2);
void print_vec4(const Vec4 v);
void prod_mat_vec4(Vec4* res, const Mat4x4 A, const Vec4 B);
float mag4(const Vec4 v);

// Vector 3
void scale_vec3(Vec3* v, float scalar);
void add_vec3(Vec3* v1, Vec3 v2);
void print_vec3(const Vec3 v);
void prod_mat_vec3(Vec3* res, const Mat3x3 A, const Vec3 B);
void cross_prod3(Vec3* res, const Vec3 A, const Vec3 B);
float mag3(const Vec3 v);
float distance(const Vec3 a, const Vec3 b);

#endif // LA_COMP_GRAPHICS_H