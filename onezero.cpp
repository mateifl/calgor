#include <iostream>
#include <climits>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <string>
#include <ctime>
#include <algorithm>
#include <queue>
#include <functional>
using namespace std;

typedef unsigned long long ullong;
typedef vector<ullong> ll_vector;

ll_vector generate_numbers(ullong ll_limit){
	ll_vector v_numbers = ll_vector(1048575), vector_temp1 = ll_vector(524288), vector_temp2 = ll_vector(524288);

	v_numbers[0] = 1;
	vector_temp1[0] = 1;
	ullong ll_start_number = 1;
	int i_next_index = 1, i_temp_index = 0, i_start_index = 0;
	while(true) {
		i_temp_index = 0;
		for(int i = 0; i < i_next_index - i_start_index; i++)
		{
			vector_temp2[2 * i] = vector_temp1[i] * 10;
			vector_temp2[2 * i + 1] = vector_temp1[i] * 10 + 1;
			i_temp_index += 2;
		}

		copy(vector_temp2.begin(), vector_temp2.begin() + i_temp_index, v_numbers.begin() + i_next_index); 
		copy(vector_temp2.begin(), vector_temp2.begin() + i_temp_index, vector_temp1.begin());
		cout << i_next_index << endl;
		if(vector_temp2[0] > ll_limit || vector_temp2[i_temp_index - 1] >= ll_limit)
			break;
		// copy ll_vector_temp2 to v_numbers
		i_start_index = i_next_index;
		i_next_index += i_temp_index;
	}
	return v_numbers;
}

void find_multiple(int i_number, const ll_vector &v_numbers, const ll_vector &v_longest_numbers) {
	ll_vector::const_iterator it, it_second;
	const ullong MULTIPLIER = 10000000000000000000LL;
	unsigned int i_mod_result1, i_mod_result2, i_mod_result3;
	for(it = v_numbers.begin(); it != v_numbers.end(); it++)
	{
		if( *it % i_number == 0 )
		{
			printf("%lld\n", *it);
			break;
		}

		for(it = v_longest_numbers.begin(); it != v_longest_numbers.end(); it++) {

		}

	}

}


int main(int argc, char** argv) {
	ll_vector v_numbers = generate_numbers(11111111111111111111LL);
/*	ll_vector v_long_numbers = ll_vector(524288);
	copy(v_numbers.begin() + 524287, v_numbers.end(), v_long_numbers.begin());
	int i = 0;
	for(it = v_numbers.begin(); it != v_numbers.end(); it++)
	{
		if(*it > 0)
			i += 1;
	} 

	cout << i << endl;
	int i_testcases;*/
		
	ll_vector::iterator it;
	for( int i = 1; i <= 20000; i++ ){
		for(it = v_numbers.begin(); it != v_numbers.end(); it++)
		{
			if( *it % i == 0 )
			{
				printf("%d %lld\n", i, *it);
				break;
			}
		}
	}

	// scanf("%d", &i_testcases);

	// for(int i = 0; i < i_testcases; i++)
	// {
	// 	scanf("%lld", &i_number);
	// 	for(it = v_numbers.begin(); it != v_numbers.end(); it++)
	// 	{
	// 		if( *it % i_number == 0 )
	// 		{
	// 			printf("%lld\n", *it);
	// 			break;
	// 		}
	// 	}
	// }

	return 0;
}