#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <climits>
#include <ctime>
using namespace std;

typedef unsigned long ulong;
typedef unsigned int uint;
typedef vector<vector<ulong> > matrix;
typedef struct result
{
	ulong risk;
	ulong time;

    result(): risk(0), time(0) {
    }
} result;

int main(int argc, char const *argv[])
{
    vector<result> v(10);
    result r;
    cout << r.risk << endl;
    for(int i = 0; i < 10; i++)
        v[i] = r;

    v[5].risk = 6;
    cout << v.size() << endl;
    cout << v[2].risk << endl;     
    return 0;

}