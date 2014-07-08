#include <iostream>
#include <cstdlib>
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

typedef unsigned long long llong;
typedef vector<unsigned long long> ll_vector;

ll_vector generate_numbers(llong ll_limit){
	ll_vector v_numbers = ll_vector(2000000), vector_temp1 = ll_vector(2000000), vector_temp2 = ll_vector(2000000);

	v_numbers[0] = 1;
	vector_temp1[0] = 1;
	llong ll_start_number = 1;
	int i_next_index = 1, i_temp_index = 0, i_start_index = 0;
	while(true) {
		i_temp_index = 0;
		for(int i = 0; i < i_next_index - i_start_index; i++)
		{
			vector_temp2[2 * i] = vector_temp1[i] * 10;
			vector_temp2[2 * i + 1] = vector_temp1[i] * 10 + 1;
			i_temp_index += 2;
		}
		//cout << "copy to v_numbers " << endl;
		copy(vector_temp2.begin(), vector_temp2.begin() + i_temp_index, v_numbers.begin() + i_next_index); 
		//cout << "copy to vector_temp1 " << endl;
		copy(vector_temp2.begin(), vector_temp2.begin() + i_temp_index, vector_temp1.begin());
		// copy ll_vector_temp2 to v_numbers
		if(vector_temp1[0] > ll_limit || vector_temp1.back() > ll_limit)
			break;
		i_start_index = i_next_index;
		i_next_index += i_temp_index;
	}

	return v_numbers;
}

int main(int argc, char** argv) {
	ll_vector v_numbers = generate_numbers(1200000000000000000LL);
	
	ll_vector::iterator it;
	int i_testcases;
	llong i_number;

	for( int i = 1; i <= 20000; i++ ){
		printf("%d ", i);
		for(it = v_numbers.begin(); it != v_numbers.end(); it++)
		{
			if( *it % i == 0 )
			{
				printf("%lld\n", *it);
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