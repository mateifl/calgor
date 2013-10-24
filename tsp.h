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
#include <utility>
using namespace std;
#pragma once


struct point {
    float x;
    float y;
};

typedef struct point point;
typedef vector<short> vector_short;

float tsp(const vector<point> &vertices_coord);
vector<point> read_data(string filename);

map<pair<short, short>, float> distances( vector<point> coordinates);
float points_distance(const point & p1, const point & p2);

vector< vector_short > subsets(vector_short initial_set, size_t sub_set_size);
void print_set( vector_short s, bool with_newline);
#endif /* TSP_H_ */
