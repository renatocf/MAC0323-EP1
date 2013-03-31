#ifndef H_POINT_DEFINED
#define H_POINT_DEFINED

typedef struct Point {
    float x;
    float y;
} point;

float distance(point,point);
point r_point();
void set_seed(int);

#endif
