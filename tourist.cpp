/*
 * tourist.cpp
 *
 *  Created on: Dec 24, 2014
 *      Author: matei
 */

#include <iostream>
#include <climits>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <string>
using namespace std;


typedef struct coord {
	int x;
	int y;

} coord;

void setup_initial(vector<string> &v_matrix, vector< vector<long> > &v_memo,
					 int i_width, int i_height) {
	for(int i = 0; i < i_height; i++)
		v_memo[i] = vector<long>(i_width);

	v_memo[0][0] = v_matrix[0][0] == '*' ? 1 : 0;

	for(int i = 1; i < i_width; i++){
		if(v_matrix[0][i] == '#') {
			v_memo[0][i] = -1;
			break;
		}
		if(v_matrix[0][i] == '*')
			v_memo[0][i] = v_memo[0][i - 1] + 1;
		else if(v_matrix[0][i] == '.')
			v_memo[0][i] = v_memo[0][i - 1];
	}

	for(int i = 1; i < i_height; i++){
		if(v_matrix[i][0] == '#') {
			v_memo[i][0] = -1;
			break;
		}

		if(v_matrix[i][0] == '*')
			v_memo[i][0] = v_memo[i - 1][0] + 1;
		else if(v_matrix[i][0] == '.')
			v_memo[i][0] = v_memo[i - 1][0];
	}
}

int tourist(vector<string> &v_matrix, int i_width, int i_height) {
	vector< vector<coord> > v_coord = vector< vector<coord> >(i_height);

	for(int i = 0; i < i_height; i++)
		v_coord[i] = vector<coord>(i_width);

	vector< vector<long> > v_memo = vector< vector<long> >(i_height);

	setup_initial(v_matrix, v_memo, i_width, i_height);

	for(int i = 1; i < i_height; i++) {
		for(int j = 1; j < i_width; j++) {
			if(v_matrix[i][j] == '#') {
				v_memo[i][j] = -1;
				continue;
			}
//			cout << i << " " << j << endl;
			coord s;
			if( v_memo[i][j - 1] > v_memo[i - 1][j]) {
				s.x = j - 1;
				s.y = i;
				v_coord[i][j] = s;
			}
			else {
				s.x = j;
				s.y = i - 1;
				v_coord[i][j] = s;
			}

			cout << "===" << endl;
			if(v_matrix[i][j] == '*'){
				v_memo[i][j] = max(v_memo[i][j - 1], v_memo[i - 1][j]) + 1;

			}
			else if(v_matrix[i][j] == '.')
				v_memo[i][j] = max(v_memo[i][j - 1], v_memo[i - 1][j]);
		}
	}


	int value = v_memo[i_height - 1][i_width - 1];

//	v_memo = vector< vector<long> >(i_width);
//	v_memo[i_height - 1][i_width - 1] = v_matrix[0][0] == '*' ? 1 : 0;
//
//	for(int i = (i_height - 2); i >= 0; i--) {
//		for(int j = (i_width - 2); j >= 0; j--) {
//			if(v_matrix[i][j] == '#')
//				v_memo[i][j] = -1;
//			else if(v_matrix[i][j] == '*')
//				v_memo[i][j] = max(v_memo[i][j + 1], v_memo[i + 1][j]) + 1;
//			else if(v_matrix[i][j] == '.')
//				v_memo[i][j] = max(v_memo[i][j + 1], v_memo[i + 1][j]);
//		}
//	}
//
//	value += v_memo[0][0];
	return value;
}

int main(int argc, char** argv) {

	FILE *ifile = stdin;
	if(ifile == NULL) {
		printf("ERROR no input file\n");
		return 0;
	}

    int i_testcases_number;
    fscanf(ifile, "%d", &i_testcases_number);
    int i_width, i_height;

    for (int i = 0; i < i_testcases_number; i++) {
    	fscanf(ifile, "%d %d", &i_width, &i_height);

    	vector<string> v_matrix(i_height);
    	char *pch = new char[i_width + 1];
    	for(int j = 0; j < i_height; j++)
    	{
    		fscanf(ifile, "%s", pch);
    		string s = pch;
    		v_matrix[j] = s;
    	}

    	int i_val = tourist(v_matrix, i_width, i_height);
    	printf("%d\n", i_val);
	}

	return 0;
}
