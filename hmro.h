#ifndef HMRO_H
#define	HMRO_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <cstdio>
#include <ctime>
#include <cstring>
using namespace std;

typedef map<string, string> string_map;
string_map new_centers(string_map &centers);
string_map read_pairs(FILE *f, int size_first, int size_second); 
vector<string> read_items(FILE *f, int item_size); 

#endif	/* HMRO_H */

