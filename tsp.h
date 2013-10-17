#ifndef TSP_H_
#define TSP_H_

#include <algorithm>
#include <set>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <map>
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


#endif /* TSP_H_ */
