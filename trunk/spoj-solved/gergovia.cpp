#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <string>
#include <ctime>
#include <numeric>
using namespace std;

vector<long> read_data(FILE *f) 
{
	int i_elements;
	fscanf(f, "%d\n", &i_elements);
	vector<long> v(i_elements);

	if(i_elements == 0)
		return v;

	char *line = new char[ 6 * (i_elements + 1)];
	char *pch;
	fgets(line, 6 * i_elements, f);
	pch = strtok(line, " \n");
	int i = 0;
	while( pch != NULL){
		v[i] = atol(pch);
		pch = strtok(NULL, " \n");
		i++;
	}

	return v;
}

long long calculate(vector<long> &v, vector<long> &v2) {
	v2[0] = v[0];
	int i = 0;

	while( i < v.size() - 1){
		v2[i + 1] = v2[i] + v[i + 1];
		i++;
	}

	long long work = 0;
	
	vector<long>::iterator it;

	for(it = v2.begin(); it != v2.end(); it++)
		work += abs(*it);
	
	return work;
}
//
//int main(int argc, char** argv) {
//	vector<long> v, v2;
//	clock_t t = clock();
//	while(1) {
//		v = read_data(stdin);
//		if(v.size() == 0)
//			break;
//
//		v2 = vector<long>(v.size());
//		long long work = calculate(v, v2);
//		printf("%lld\n", work);
//	}
//	clock_t t1 = clock();
//	cout << "Time: " << (float)(t1 - t)/CLOCKS_PER_SEC << endl;
//	return 0;
//}
