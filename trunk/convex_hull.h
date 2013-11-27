#ifndef _CONVEX_HULL_
#define _CONVEX_HULL_
#include "main.h"

struct point {
    float x;
    float y;
};

typedef struct point point;

int calculate_convex_hull_perimeter( vector<point> points );


#endif // _CONVEX_HULL_
