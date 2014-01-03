#include "convex_hull.h"

bool compare(point first_point, point second_point) {
    if( first_point.x != second_point.x )
        return first_point.x < second_point.x;
    else
        return first_point.x < second_point.y;
}

