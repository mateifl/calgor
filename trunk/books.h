#ifndef BOOKS_H_
#define BOOKS_H_

#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <fstream>
#include <cstring>

using namespace std;
bool check_partitions(const vector<long long> &numbers, const long long max_partition, const int partition_number);
long long max_partition_bs(const vector<long long> &numbers, int partition_number);
long long max_partition(vector<long long> numbers, int end_index, int partition_number, map<pair<int, int>, long long> &subproblems);
void process(string filename);
void process_bs(string filename);
#endif