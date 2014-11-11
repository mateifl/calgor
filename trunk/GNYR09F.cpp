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

void print(r_matrix &rm) {
	for (int i = 0; i < rm.size(); i++) {
		for (int j = 0; j < rm[0].size(); j++) {
			cout << "(" << rm[i][j].l_ending_in_0 << "," << rm[i][j].l_ending_in_1 << ") ";
		}
		cout << endl;
	}

}

void solution(int i_number_of_bits, int i_sum) {

	r_matrix solution_matrix = r_matrix(i_number_of_bits + 1);
	for(int i = 0; i <= i_number_of_bits; i++)
	{
		r_vector v = r_vector(i_sum + 1);
		solution_matrix[i] = v;
	}

	solution_matrix[1][0].l_ending_in_0 = 1;
	solution_matrix[1][0].l_ending_in_1 = 1;

	solution_matrix[2][0].l_ending_in_0 = 2;
	solution_matrix[2][0].l_ending_in_1 = 1;

	for (int i = 3; i <= i_number_of_bits; i++)
	{
		solution_matrix[i][0].l_ending_in_0 = solution_matrix[i - 1][0].l_ending_in_0 + solution_matrix[i - 1][0].l_ending_in_1;
		solution_matrix[i][0].l_ending_in_1 = solution_matrix[i - 1][0].l_ending_in_0;
	}

	//print(solution_matrix);

	for (int i = 2; i <= i_number_of_bits; i++)
	{
		for(int j = 1; j <= i_sum; j++) {
			//cout << solution_matrix[i - 1][j].l_ending_in_0 << " " << solution_matrix[i - 1][j].l_ending_in_1 << endl;
			solution_matrix[i][j].l_ending_in_0 = solution_matrix[i - 1][j].l_ending_in_0 + solution_matrix[i - 1][j].l_ending_in_1;
			solution_matrix[i][j].l_ending_in_1 = solution_matrix[i - 1][j].l_ending_in_0 + solution_matrix[i - 1][j - 1].l_ending_in_1;
		}
	}

	//print(solution_matrix);
	printf("%d\n", solution_matrix[i_number_of_bits][i_sum].l_ending_in_0 + solution_matrix[i_number_of_bits][i_sum].l_ending_in_1);
}

int main(int argc, char** argv) {

	solution(5, 2);
	solution(20, 8);
	solution(30, 17);
	solution(40, 24);
	return 0;
}