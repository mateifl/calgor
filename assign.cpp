#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <numeric>
#include <string>
#include <ctime>

using namespace std;
typedef unsigned long ulong;
typedef vector<ulong> v_ulong;

v_ulong bitmasks(ulong N) {
	v_ulong v_bitmasks;
	for(int i = 0; i <= N; i++)
		v_bitmasks.push_back(1 << i);
	return v_bitmasks;
}

v_ulong decompose(ulong l_first, v_ulong &v_bitmasks){
	v_ulong r;
	for(ulong i = 0; i < v_bitmasks.size(); i++)
		if(l_first & v_bitmasks[i])
			r.push_back(v_bitmasks[i]);

	return r;
}

v_ulong assign(v_ulong &data, int length){

	v_ulong memo((1 << length));
	//cout << memo.size() << endl;

	v_ulong v_bitmasks = bitmasks(length);
	// decompose every set of student options
	vector<v_ulong> v_decompositions = vector<v_ulong>(length);
	for(ulong i = 0; i < length; i++)
		v_decompositions[i] = decompose(data[i], v_bitmasks);

	v_ulong result((1 << length));
	for(ulong i = 0; i < v_decompositions[0].size(); i++) {
		for(ulong j = 0; j < v_decompositions[1].size(); j++) {
			if((v_decompositions[0][i] & v_decompositions[1][j]) == 0) {
				ulong v = v_decompositions[0][i] | v_decompositions[1][j];
				memo[v] += 1;
				result[v] = 1;
			}
		}
	}

	for(ulong i = 2; i < length; i++)
	{
		v_ulong result_temp((1 << length)), memo_temp((1 << length));
		for(ulong j = 0; j < result.size(); j++) {
			if (result[j] == 0)
				continue;
			for (ulong k = 0; k < v_decompositions[i].size(); k++) {
				if ((j & v_decompositions[i][k]) == 0) {
					ulong v = j | v_decompositions[i][k];
					//cout << "v = " << v << endl;
					result_temp[v] = 1;
					memo_temp[v] += memo[j];
 				}
			}
		}
		result = result_temp;
		memo = memo_temp;
	}
	return memo;
}

ulong create_number(ulong *pch_number, ulong length) {
	ulong l_power_2 = 1;
	ulong result = 0;
	for(ulong i = 0; i < length; i++)
	{
		result += l_power_2 * pch_number[i];
		l_power_2 *= 2;
	}
	return result;
}

int main(int argc, char** argv) {

	ulong i_testcases, i_number_students;
	scanf("%d", &i_testcases);
//	cout << "test cases: " << i_testcases << endl;
//	clock_t t1 = clock();
	for(ulong k = 0; k < i_testcases; k++)
	{
		scanf("%d", &i_number_students);
		v_ulong data = v_ulong(i_number_students);

		ulong *pch_number = new ulong[i_number_students];
		//cout << "students: " << i_number_students << endl;
		for(ulong j = 0; j < i_number_students; j++){
			for (ulong i = 0; i < i_number_students; i++)
				scanf("%d", &pch_number[i]);

			ulong number = create_number(pch_number, i_number_students);
			data[j] = number;
		}
		v_ulong r = assign(data, i_number_students);
		printf("%d\n", accumulate(r.begin(), r.end(), 0));
		
	}
	//clock_t t2 = clock();
	//cout << "time: " << (float)(t2 - t1)/CLOCKS_PER_SEC << endl;
	return 0;
}
