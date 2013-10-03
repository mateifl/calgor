#include "convex_hull.h"

bool compare(point first_point, point second_point);
int distance(point first_point, point second_point);

int calculate_convex_hull_perimeter( vector<point> points ){
    int perimeter_convex_hull;
    sort(points.begin(), points.end(), compare);

    vector<point>::iterator it;
    vector<point> conv_hull_up, conv_hull_down;

    for(it = points.begin(); it < points.end(); it++ )
    {
        if( conv_hull_up.size() > 1 ) {
            conv_hull_up.erase( conv_hull_up.end() );
        }
        conv_hull_up.push_back(*it);
    }

    return perimeter_convex_hull;
}


int distance(point first_point, point second_point) {
    return sqrt( pow((first_point.x - second_point.x), 2) + pow((first_point.y - second_point.y), 2) );
}


short movement(point first, point second, point third) {
    short result;

    return result;
}


bool compare(point first_point, point second_point) {
    if( first_point.x != second_point.x )
        return first_point.x < second_point.x;
    else
        return first_point.x < second_point.y;
}
