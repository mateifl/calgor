#ifndef _PPATH_H_
#define _PPATH_H_

#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>
#include <map>
#include <string>
#include <cstdio>
#include <set>
#include <queue>
#include <ctime>
#include <unordered_map>
using namespace std;

typedef map<int, set<int>> graph;

set<int> prime_numbers(int low, int high);
graph create_graph(const set<int> &numbers);

void check_string_in_primes(int prime, int position, char number, 
                           set<int> &neighbors, const set<int> &numbers ); 

int bfs(graph g, int start_node, int end_node);

#endif