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
	uint diff;
} sol;

sol alien_c(vector<ulong> &v_values, int i_min, int i_middle, int i_max, ulong l_limit){
	// cout << i_min << " " << i_middle << " " << i_max << endl;
	ulong z = 0;
	vector<ulong> v_sums;
	for (int i = i_middle - 1; i >= i_min; --i) {
		z += v_values[i];
		if (z >= l_limit)
			break;
		v_sums.push_back(z);
	}

	ulong diff = 0, max_j = 0, i_max_v = 0;

	for (int i = 0; i < v_sums.size(); i++) {
		ulong l_sum = v_sums[i];
		if (l_sum >= l_limit)
			break;
		max_j = 0;
		for (uint j = i_middle; j <= i_max; j++) {
			ulong sum_1 = l_sum + v_values[j];
			if (sum_1 >= l_limit)
				break;
			max_j = j;
			l_sum = sum_1;
		}
		// if the first index is 0, we must add 1
		
		ulong diff1 = max_j > 0 ? max_j - i_middle + i + 1 : 0;
		int x = ((i_min == 0) && (i_middle + i + 1) == 0) ? 1 : 0;
		diff1 += 1;
		if (diff1 >= diff) {
			i_max_v = l_sum;
			diff = diff1;
		}
		l_sum = 0;
	}

	sol s;
	s.l_value = i_max_v;
	s.diff = diff;

	return s;
}

sol alien(vector<ulong> &v_values, uint i_start_idx, uint i_end_idx, ulong l_limit) {
	if( i_start_idx == i_end_idx )
	{
		sol s;
		s.diff = 1;
		s.l_value = v_values[i_start_idx];
		return s;
	}

	uint mid_index = (i_start_idx + i_end_idx) / 2;
	sol sol1 = alien(v_values, i_start_idx, mid_index, l_limit);
	sol sol2 = alien(v_values, mid_index + 1, i_end_idx, l_limit);
	sol sol3 = alien_c(v_values, i_start_idx, mid_index + 1, i_end_idx + 1, l_limit);

	if( sol1.diff >= sol2.diff && sol1.diff >= sol3.diff )
		return sol1;
	else 
	if( sol2.diff >= sol1.diff && sol2.diff >= sol3.diff  )
		return sol2;	
	else 
	if( sol3.diff >= sol1.diff && sol3.diff >= sol2.diff  )
		return sol3;	


}

int main(int argc, char** argv) {
	time_t t = clock();

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
    	printf("%d %d\n", s.l_value, s.diff);

    }

	time_t t1 = clock();
	//cout << "time: " << (float)(t1 - t) / CLOCKS_PER_SEC << endl;
	return 0;
}
