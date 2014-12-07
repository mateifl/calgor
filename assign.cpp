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

vector<long> decompose(long l_first, vector<long> &v_bitmasks){
	vector<long> r;
	for(int i = 0; i < v_bitmasks.size(); i++)
	{
		if(l_first & v_bitmasks[i])
			r.push_back(v_bitmasks[i]);
	}
	return r;
}

vector<long> assign(vector<long> &data, int length){
	vector<long> v_bitmasks = bitmasks(length);
	// decompose every set of student options
	vector< vector<long> > v_decompositions = vector< vector<long> >(length);
	for(unsigned int i = 0; i < length; i++)
		v_decompositions[i] = decompose(data[i], v_bitmasks);

	// 
	vector<long> result;
	for(unsigned int i = 0; i < v_decompositions[0].size(); i++) {
		for(unsigned int j = 0; j < v_decompositions[1].size(); j++) {
			//cout << ((v_decompositions[0][i] & v_decompositions[1][j]) == 0) << endl;
			if((v_decompositions[0][i] & v_decompositions[1][j]) == 0) {
				result.push_back(v_decompositions[0][i] | v_decompositions[1][j]);
			}
		}
	}

	for(unsigned int i = 2; i < length; i++)
	{
		cout << result.size() << endl;
		vector<long> result_temp;
		for(unsigned int j = 0; j < result.size(); j++) {
			for(unsigned int k = 0; k < v_decompositions[i].size(); k++) {
				if( (result[j] & v_decompositions[i][k]) == 0 )
					result_temp.push_back( result[j] | v_decompositions[i][k] );
			}
		}
		result = result_temp;
	}
	return result;
}

long create_number(char *pch_data, int length) {
	long l_power_2 = 1;
	long result = 0;
	for(unsigned int i = 0; i < length; i++)
	{
		result += l_power_2 * (pch_data[i] - 48);
		l_power_2 *= 2;
	}
	return result;
}

int main(int argc, char** argv) {

	int i_testcases, i_number_students;
	scanf("%d\n", &i_testcases);
	cout << "test cases: " << i_testcases << endl;
	clock_t t1 = clock();
	for(int k = 0; k < i_testcases; k++)
	{
		scanf("%d\n", &i_number_students);
		vector<long> data = vector<long>(i_number_students);
		char *pch_data = new char[2 * i_number_students];
		char *pch_number = new char[i_number_students + 1];
		for(int j = 0; j < i_number_students; j++){

			fgets(pch_data, 2 * i_number_students + 2, stdin);
			for(int i = 0; i < 2 * i_number_students; i+=2)
				pch_number[i/2] = pch_data[i];
			pch_number[i_number_students] = '\0';
			long number = create_number(pch_number, i_number_students);
			data[j] = number;
		}
		//delete pch_data;
		//delete pch_number;
		vector<long> r = assign(data, i_number_students);
		cout << r.size() << endl;
	}
	clock_t t2 = clock();

	cout << "time: " << (float)(t2 - t1)/CLOCKS_PER_SEC << endl;
	return 0;
}
