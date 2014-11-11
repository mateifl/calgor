#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <cmath>
#include <string>
#include <ctime>
#include <map>
using namespace std;

void solution(const string &str_message, const int i_rows, const int i_columns) {
	vector<vector<char> > v_matrix = vector<vector<char> >(i_rows);
	for(int i = 0; i < i_rows; i++){
		v_matrix[i] = vector<char>(i_columns);
		for(int j = 0; j < i_columns; j++)
		{
			v_matrix[i][j] = str_message.at(i * i_rows + j);
		}
	}
	bool reverse_column = false, reverse_row = false;
	// decypher the matrix in sequnce of chars 
	
	int rows = i_rows, columns = i_columns;
	string str_decrypt_message = str_message.substr(0, i_rows - 1);

	cout << str_decrypt_message << endl;
}

//
//int main(int argc, char** argv) {
//	int i_testcases, i_rows, i_columns;
//	char pch_line[401];
//	scanf("%d\n", &i_testcases);
//
//
//	for(int k = 0; k < i_testcases; k++)
//	{
//		scanf("%d %d %s", &i_rows, &i_columns, pch_line);
//		int i = strlen(pch_line);
//		if( pch_line[i - 1] == '\n')
//			pch_line[i - 1] = '\0';
//		else
//			pch_line[i] = '\0';
//		string s1 = pch_line;
//		solution(s1, i_rows, i_columns);
//	}
//	return 0;
//}
