#ifndef _BOTTOM_H_
#define _BOTTOM_H_

#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <string>
#include <cstdio>
#include <set>
#include <stack>
#include <ctime>
#include <cstring>
using namespace std;

typedef map<int, vector<int> > graph;

graph dfs(graph &g, int start_node);
void read_data(FILE *f, graph &g, graph &g_reversed);


#endif