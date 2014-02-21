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

vector<long> decompose(long l_first, vector<long> v_bitmasks){
	vector<long> r;
	for(int i = 0; i < v_bitmasks.size(); i++)
	{
		if(l_first & v_bitmasks[i])
			r.push_back(v_bitmasks[i]);
	}
	return r;
}

map<long, long> assign(vector<long> &data, int length){
	vector<long> v_bitmasks = bitmasks(data.size()), v_next;

	map<long, long> r, r_temp;
	for(int i = 0; i < data.size(); i++)
	{
		if(data[0] & v_bitmasks[i])
			r.insert(make_pair(v_bitmasks[i], 1L));
	}
	
	map<long, long>::iterator map_iterator;
	for(int i = 1; i < data.size(); i++)
	{
		v_next = decompose(data[i], v_bitmasks);
		for (int j = 0; j < data.size(); j++)
		{
			for(map_iterator = r.begin(); map_iterator != r.end(); map_iterator++ )
			{
				if( (v_next[i] & map_iterator->first) == 0)
				{
					long a = r_temp[v_next[i] | map_iterator->first] + r[map_iterator->first];
					if(a != 0)
						r_temp.insert(make_pair(v_next[i] | map_iterator->first, a));
				}
			}
		}
		r = r_temp;
	}

	return r;
}

int main(int argc, char** argv) {

	int i_testcases, i_number_students;
	scanf("%d\n", &i_testcases);
	cout << "testcases " << i_testcases << endl;
	clock_t t1 = clock();
	for(int k = 0; k < i_testcases; k++)
	{
		scanf("%d\n", &i_number_students);
		vector<long> data = vector<long>(i_number_students);
		char *pch_data = new char[2 * i_number_students];
		char *pch_number = new char[i_number_students];
		for(int j = 0; j < i_number_students; j++){
			
			fgets(pch_data, 2 * i_number_students + 2, stdin);
			for(int i = 0; i < 2 * i_number_students; i+=2)
				pch_number[i/2] = pch_data[i];
			long number = strtol(pch_number, NULL, 2);
			data[j] = number;
		}

		//cout << endl;
	}
	clock_t t2 = clock();

	cout << " time: " << (float)(t2 - t1)/CLOCKS_PER_SEC << endl;
	return 0;
}