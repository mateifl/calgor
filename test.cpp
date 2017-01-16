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
   FILE* f = fopen("test.txt", "r");
   char pch[128];
   for(int i = 0; i < 10; i++)
   {
       fgets(pch, 128, f);
       cout << pch << endl;
   }
   fclose(f);

}