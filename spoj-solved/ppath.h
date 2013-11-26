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

typedef unordered_map<int, set<int>> graph;
typedef unordered_map<int, unordered_map<int, short>> graph2;

set<int> prime_numbers(int low, int high);
unordered_map<int, short> prime_numbers2(int low, int high);

graph create_graph(const set<int> &numbers);
graph2 create_graph(const unordered_map<int, short> &numbers);

void check_string_in_primes(int prime, int position, char number, 
                           unordered_map<int, short> &neighbors, const unordered_map<int, short> &numbers); 

void check_string_in_primes(int prime, int position, char number, 
                           set<int> &neighbors, const set<int> &numbers ); 

int bfs( graph &g, int start_node, int end_node);
int bfs2(graph2 g, int start_node, int end_node);
#endif