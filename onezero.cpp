#include <iostream>
#include <climits>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <ctime>
#include <algorithm>
using namespace std;

typedef unsigned long long ullong;
typedef vector<ullong> ll_vector;
typedef vector<long> vl;
typedef vector<vl> vvl;

ll_vector generate_numbers(ullong ll_limit){
	ll_vector v_nrs = ll_vector(1048575), v_tmp1 = ll_vector(524288), v_temp2 = ll_vector(524288);

	v_nrs[0] = 1;
	v_tmp1[0] = 1;
	ullong ll_start_number = 1;
	int i_next_index = 1, i_temp_index = 0, i_start_index = 0;
	while(true) {
		i_temp_index = 0;
		for(int i = 0; i < i_next_index - i_start_index; i++)
		{
			v_temp2[2 * i] = v_tmp1[i] * 10;
			v_temp2[2 * i + 1] = v_tmp1[i] * 10 + 1;
			i_temp_index += 2;
		}

		copy(v_temp2.begin(), v_temp2.begin() + i_temp_index, v_nrs.begin() + i_next_index); 
		copy(v_temp2.begin(), v_temp2.begin() + i_temp_index, v_tmp1.begin());
		if(v_temp2[0] > ll_limit || v_temp2[i_temp_index - 1] >= ll_limit)
			break;
		i_start_index = i_next_index;
		i_next_index += i_temp_index;
	}

	int j = 0;
	for (int i = 0; i < v_nrs.size(); i++){

		if(v_nrs[i] == 0)
			break;
				j += 1;
	}
	v_nrs.erase(v_nrs.begin() + j, v_nrs.end()); 
	return v_nrs;
}

vl even_indexes(long l) {
	vl v = vl(l);
	for(long i =  0;  i <= l; i++)
		v[i] = 2 * i + 1;
}

int sum_d(ullong n) {
	int sum = 0, r;
	while(n != 0)
    {
      r = n % 10;
      sum = sum + r;
      n = n / 10;
    }
    return sum;
}

vvl indexes(ll_vector &v_nrs, int i) {
	vvl v = vvl(i);
	for(long i = 0; i < v_nrs.size(); i ++)
	{
		long m = sum_d(v_nrs[i]) % i;
		v[m].push_back(i);
	}	
	return v;
}

void solution(const ll_vector &v_nrs, long l_number, vvl idx, vl idx2)
{
	const int digits = 19;
	vl v_modulo = vl(v_nrs.size());
	long l_modulo = 0L;

	for (int i = 0; i < v_nrs.size(); i++)
	{
		l_modulo = v_nrs[i] % l_number;
		if(l_modulo == 0){
			printf("%d\n", v_nrs[i]);
			return;
		}
		else
			v_modulo[i] = l_modulo;
	}

	long l_multiplier = ((100000 % l_number) * (10000000 % l_number) * (10000000 % l_number)) % l_number;
	long l_modulo_i = 0L, l_modulo_j = 0L;
	char pch_number1[digits], pch_number2[digits];

	// cout << l_multiplier << endl;
	for (int i = 0; i < v_nrs.size(); i++){
		l_modulo_i = (v_modulo[i] * l_multiplier) % l_number;
		for (int j = 0; j < v_nrs.size(); j++) {
			l_modulo_j = v_modulo[j];
			l_modulo = (l_modulo_i + l_modulo_j) % l_number;
			if( l_modulo == 0)
			{
				
				sprintf(pch_number1, "%ld", v_nrs[i]);
				sprintf(pch_number2, "%ld", v_nrs[j]);
				int i_zeros = digits - strlen(pch_number2);
				char *pch_zeros = new char[i_zeros];
				memset(pch_zeros, '0', i_zeros);
				//cout << pch_number1 << " " << pch_zeros << " " << pch_number2 << endl;
				printf("%s%s%s\n", pch_number1, pch_zeros, pch_number2);
				delete[] pch_zeros;
				return;
			}
		}

	}

	printf("0\n"); 
}

int main(int argc, char** argv) {
	int i_testcases;
	ll_vector v_nrs = generate_numbers(1111111111111111111LL);
	cout << v_nrs.size() << endl;
	vvl idx3 = indexes(v_nrs, 3);
	vvl idx9 = indexes(v_nrs, 9);
	vl idx2 = even_indexes(v_nrs.size());
	// clock_t t1 = clock();
	// printf("19992 ");
	// solution(v_nrs, 19992);
	// printf("19997 ");
	// solution(v_nrs, 19997);
	// printf("19999 ");
	// solution(v_nrs, 19999);
	// printf("19994 ");
	// solution(v_nrs, 19994);
	// printf("999 ");
	// solution(v_nrs, 999);
	// clock_t t2 = clock();
	// cout << "time: " << (float)(t2 - t1)/CLOCKS_PER_SEC << endl;
	int i_number;
	scanf("%d", &i_testcases);

	for(int i = 0; i < i_testcases; i++)
	{
		scanf("%d", &i_number);
		printf("%d ", i_number);
		if 
		solution(v_nrs, i_number);
	}

	return 0;
}