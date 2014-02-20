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

vector<long> bitmasks(int N) {
	vector<long> v_bitmasks;
	for(int i = 0; i <= N; i++)
		v_bitmasks.push_back(1 << i);
	return v_bitmasks;
}


map<long, long> combine(long l_first, long l_second, vector<long> v_bitmasks){
	map<long, long> r;

	for(int i = 0; i < v_bitmasks.size(); i++)
	{
		
	}
	return r;
}

map<long, long> assign(vector<long> &data, int length){

	if(length == 2){
		return combine(data[0], data[1]);
	}

	map<long, long> r2;
	return r2;
}


int main(int argc, char** argv) {

	int i_testcases, i_number_students;
	scanf("%d\n", &i_testcases);
	cout << "testcases " << i_testcases << endl;
	clock_t t1 = clock();
	for( int k = 0; k < i_testcases; k++ )
	{
		scanf("%d\n", &i_number_students);
		vector<vector<short> > data = vector<vector<short> >(i_number_students);
		char *pch_data = new char[2 * i_number_students];

		for(int j = 0; j < i_number_students; j++){
			vector<short> numbers = vector<short>(i_number_students);
			fgets(pch_data, 2 * i_number_students + 2, stdin);
			for(int i = 0; i < 2 * i_number_students; i+=2)
				numbers[i/2] = pch_data[i] - 48;
			data[j] = numbers;
		}

		//cout << endl;
	}
	clock_t t2 = clock();

	cout << " time: " << (float)(t2 - t1)/CLOCKS_PER_SEC << endl;
	return 0;
}