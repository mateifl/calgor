#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <functional>
using namespace std;

typedef struct number{
	long n[4];
	int digit_sum;

} number;
typedef vector<long> vlong;

vlong generate_numbers(){
	vlong v_nrs = vlong(1023), v_tmp1 = vlong(512), vtmp2 = vlong(512);
	v_nrs[0] = 1;
	v_tmp1[0] = 1;
	long limit = 1111111111;
	int i_next_index = 1, i_temp_index = 0, i_start_index = 0;
	while(true) {
		i_temp_index = 0;
		for(int i = 0; i < i_next_index - i_start_index; i++)
		{
			vtmp2[2 * i] = v_tmp1[i] * 10;
			vtmp2[2 * i + 1] = v_tmp1[i] * 10 + 1;
			i_temp_index += 2;
		}

		copy(vtmp2.begin(), vtmp2.begin() + i_temp_index, v_nrs.begin() + i_next_index); 
		copy(vtmp2.begin(), vtmp2.begin() + i_temp_index, v_tmp1.begin());
		if(vtmp2[0] >= limit || vtmp2[i_temp_index - 1] >= limit)
			break;
		i_start_index = i_next_index;
		i_next_index += i_temp_index;
	}
	return v_nrs;
}

