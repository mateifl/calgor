#ifndef TSP_H_
#define TSP_H_

#include <algorithm>
#include <set>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <map>
#include <string>
using namespace std;
#pragma once


struct point {
    float x;
    float y;
};

typedef struct point point;

set< set<short> > subsets(set<short> initial_set, size_t sub_set_size);
float tsp(vector<point> &vertices_coord);
vector<point> read_data(string filename);
void print_set( set<short> s );
map<pair<short, short>, float> distances( vector<point> coordinates);
float points_distance(const point & p1, const point & p2);

#endif /* TSP_H_ */
