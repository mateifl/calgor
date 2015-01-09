#include <iostream>
#include <functional>
#include <cstdio>
#include <climits>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <map>
using namespace std;

typedef unsigned long ulong;

ulong solution(vector<ulong> v_trees, ulong l_wood_q, ulong l_max_height) {
	ulong l_min_height = 0, l_medium_height, l_sum = 0, l_diff = ULONG_MAX;
	l_medium_height = (l_min_height + l_max_height) / 2;
	vector<ulong> v_temp = vector<ulong>(v_trees.size());
	
	while (true) {
		l_sum = 0;
		for (ulong i = 0; i < v_trees.size(); i++)
		{
			if (v_trees[i] > l_medium_height)
				l_sum += (v_trees[i] - l_medium_height);
			else
				break;
		}
		if (l_sum < l_wood_q)
		{
			// 
			l_max_height = l_medium_height;
			l_medium_height = (l_min_height + l_max_height) / 2;
		}
		else if (l_sum > l_wood_q)
		{
			if (l_sum - l_wood_q < l_diff)
				l_diff = l_sum - l_wood_q;
			else
				break;
			l_min_height = l_medium_height;
			l_medium_height = (l_min_height + l_max_height) / 2;
		}
		else {
			return l_medium_height;
		}
	}
	return l_medium_height;
}


int main(int argc, char** argv) {
	
	//cout << ULONG_MAX << endl;
	ulong l_tree_number, l_wood_q, l_height, l_height1, l_max_height;
	scanf("%ld %ld", &l_tree_number, &l_wood_q);
	
	vector<ulong> v_trees = vector<ulong>(l_tree_number);
	l_max_height = 0;
	for (ulong i = 0; i < l_tree_number/2; i+=2)
	{
		scanf("%ld %ld", &l_height, &l_height1);
		if (l_height > l_max_height)
			l_max_height = l_height;

		v_trees[2*i] = l_height;
		if (l_height1 > l_max_height)
			l_max_height = l_height1;

		v_trees[2*i + 1] = l_height1;


	}
	clock_t t0 = clock();
	//sort(v_trees.begin(), v_trees.end(), greater<ulong>());
	ulong r = solution(v_trees, l_wood_q, l_max_height);

	printf("%ld", r);
	clock_t t1 = clock();
	cout << "time: " << (float)(t1 - t0)/CLOCKS_PER_SEC << endl;
	return 0;
}