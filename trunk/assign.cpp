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

vector<long> bitmasks() {
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

map<long, long> assign(vector<vector<short> > &data, int length){

	if(length == 2){
		return combine(data[0], data[1]);
	}

	map<vector<short>, long> r = assign(data, length - 1);
	cout << r.size() << endl;
	map<vector<short>, long> r2;
	map<vector<short>, long>::iterator it;
	vector<short>::iterator it_vect;
	for( it = r.begin(); it != r.end(); it++)
	{
		for(unsigned int i = 0; i < data.size(); i++ )
		{
			if(data[length - 1][i] == 1 && it->first[i] == 0)
			{
				vector<short> v = it->first;
				v[i] = 1;
				long val = r2[v];
				r2[v] = val + it->second;
			}
		}
	}
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
		map<vector<short>, long> res = assign(data, data.size());
		//cout << endl;
	}
	clock_t t2 = clock();

	cout << " time: " << (float)(t2 - t1)/CLOCKS_PER_SEC << endl;
	return 0;
}