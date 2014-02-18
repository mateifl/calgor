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

map<vector<short>, long> combine(vector<short> &v_first, vector<short> &v_second){
	map<vector<short>, long> r;// = assign(data, length - 1);
	int i_vector_size = v_first.size();

	for(int i = 0; i < i_vector_size; i++)
	{
		if(v_first[i] == 0)
			continue;
		for(int j = 0; j < i_vector_size; j++)
		{
			if(v_second[j] == 1 && i != j)
			{
				vector<short> v = vector<short>(i_vector_size);
				v[i] = 1;
				v[j] = 1;
				long val = r[v];
				r[v] = val + 1;
			}
		}
	}
	return r;
}

map<vector<short>, long> assign(vector<vector<short> > &data, int length){

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