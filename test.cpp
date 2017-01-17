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
   while(!feof(f))
   {
       fgets(pch, 128, f);
       if(strcmp(pch, "\n") == 0)
        cout << "Found EOL" << endl;
       cout << "|" << pch << "|"  << strlen(pch) << endl;
   }
   fclose(f);

}