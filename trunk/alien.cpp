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

sol alien_c(vector<ulong> &v_values, int i_min, int i_middle, int i_max, ulong l_limit){
	cout << i_min << " " << i_middle << " " << i_max << endl;
	ulong z = 0;
	vector<ulong> v_sums;
	for (int i = i_middle - 1; i > i_min - 1; --i) {
		z += v_values[i];
		if (z >= l_limit)
			break;
		v_sums.push_back(z);
	}

	ulong i_max_v = 0, i_min_r = 0, i_max_r = 0, max_j = 0;
	
	for (int i = i_middle - 1; i > i_min - 1; --i) {
		ulong l_sum = v_sums[i - i_middle + 1];
		if (l_sum >= l_limit)
			break;
		max_j = 0;
		for (uint j = i_middle; j <= i_max; j++) {
			l_sum += v_values[j];
			if (l_sum >= l_limit)
				break;
			max_j = j;
		}
		if (l_sum >= i_max_v) {
			i_max_v = l_sum;
			i_min_r = i;
			i_max_r = max_j;
		}
		l_sum = 0;
	}

	sol s;
	s.l_value = i_max_v;
	s.i_min_index = i_min_r;
	s.i_max_index = i_max_r;
	return s;
}

sol alien(vector<ulong> &v_values, uint i_start_idx, uint i_end_idx, ulong l_limit) {
	if( i_start_idx == i_end_idx )
	{
		sol s;
		s.i_min_index = i_start_idx;
		s.i_max_index = i_end_idx;
		s.l_value = v_values[i_start_idx];
		return s;
	}

	uint mid_index = (i_start_idx + i_end_idx) / 2;
	sol sol1 = alien(v_values, i_start_idx, mid_index, l_limit);
	sol sol2 = alien(v_values, mid_index + 1, i_end_idx, l_limit);
	sol sol3 = alien_c(v_values, i_start_idx, mid_index + 1, i_end_idx + 1, l_limit);

	if( sol1.i_max_index - sol1.i_min_index >= sol2.i_max_index - sol2.i_min_index &&  
		sol1.i_max_index - sol1.i_min_index >= sol3.i_max_index - sol3.i_min_index  )
		return sol1;
	else 
	if( sol2.i_max_index - sol2.i_min_index >= sol1.i_max_index - sol1.i_min_index &&  
		sol2.i_max_index - sol2.i_min_index >= sol3.i_max_index - sol3.i_min_index  )
		return sol2;	
	else 
	if( sol3.i_max_index - sol3.i_min_index >= sol1.i_max_index - sol1.i_min_index &&  
		sol3.i_max_index - sol3.i_min_index >= sol2.i_max_index - sol2.i_min_index  )
		return sol3;	


}

int main(int argc, char** argv) {
    uint i_testcases_number, i_length;
    ulong l_max_sum, l_value;
    scanf("%d", &i_testcases_number);

    for (int i = 0; i < i_testcases_number; i++) {

    	scanf("%d %ld", &i_length, &l_max_sum);
    	vector<ulong> v_values = vector<ulong>(i_length);

    	for(uint j = 0; j < i_length; j++)
    	{
    		scanf("%ld", &l_value);
    		v_values[j] = l_value;
    	}
    	sol s = alien(v_values, 0, i_length - 1, l_max_sum);
    	cout << s.l_value << " " << s.i_min_index << " " << s.i_max_index << endl;

    }
	return 0;
}
