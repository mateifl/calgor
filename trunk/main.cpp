#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <cmath>
#include <string>
#include <ctime>
#include <algorithm>
#include <map>
#include <queue>
#include <functional>
using namespace std;

int main(int argc, char** argv) {
	vector<int> v;

	for(int i = 0; i < 10; i++)
		v.push_back(i);

	cout << v.back() << endl;

    return 0;
}