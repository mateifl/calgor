#include <ctime>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
using namespace std;


typedef struct result {
	long l_ending_in_1;
	long l_ending_in_0; 
} result;

typedef vector<result> r_vector;
typedef vector<r_vector> r_matrix;

void solution(int i_number_of_bits, int i_sum) {

	r_matrix solution_matrix = r_matrix(i_sum);
	for(int i = 0; i < i_sum; i++)
	{
		r_vector v = r_vector(i_number_of_bits);
		solution_matrix[i] = v;
	}

	for(int i = 0; i < i_sum; i++)
	{
		for(int j = 0; j < i_number_of_bits; j++) {
			//solution_matrix[i][j].l_ending_in_0 = ; 
			//solution_matrix[i][j].l_ending_in_1 = ;
		}
	}


	printf("%d\n", solution_matrix[i_sum][i_number_of_bits].l_ending_in_0 + solution_matrix[i_sum][i_number_of_bits].l_ending_in_1);
}

