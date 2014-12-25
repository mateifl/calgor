#include <ctime>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>

using namespace std;
typedef unsigned long ulong;
typedef unsigned int uint;
typedef struct sol {
	unsigned long l_value;
	uint i_min_index;
	uint i_max_index;
} sol;

sol alien_c(vector<ulong> &v_values, uint i_min, uint i_middle, uint i_max, ulong l_limit){
	ulong z = 0;
	vector<ulong> v_sums;
	for (uint i = i_middle - 1; i > i_min - 1; i--) {
		z += v_values[i];
		if (z >= l_limit)
			break;
		v_sums.push_back(z);
	}

	ulong v, i_max_v, i_min_r, i_max_r, max_j;
	
	for (uint i = i_middle - 1; i > i_min - 1; i--) {
		ulong l_sum = v_sums[i];
		if (l_sum >= l_limit)
			break;
		for (uint j = i_middle; j <= i_max; j++) {
			l_sum += v_values[j];
			if (l_sum >= l_limit)
				break;
			max_j = j;
		}
		if (l_sum >= i_max_v) {
			i_max_v = v;
			i_min_r = i;
			i_max_r = max_j;
		}
		
	}

	sol s;
	return s;
}

sol alien(vector<ulong> values, ulong limit) {



}