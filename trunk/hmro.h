#ifndef HMRO_H
#define	HMRO_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
#include <cstdio>
#include <cstring>
using namespace std;

typedef map<string, string> string_map;

string_map read_pairs(FILE *f, int size_first, int size_second); 

#endif	/* HMRO_H */