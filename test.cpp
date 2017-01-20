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

void read_ingore_empty_line(FILE *f, char *pch) {
    strcpy(pch, "\0");
    while(strlen(pch) <= 2) 
        fgets(pch, 126, f);
}





int main(int argc, char const *argv[])
{
    // cout << atoi("10\n\0") << endl;
    FILE* f = fopen("tc_blinnet.in", "r");
    char pch[128];
    uint testcases, towns, neighbors, tail, value;
    read_ingore_empty_line(f, pch);
    testcases = atoi(pch);
    cout << testcases << endl;

    for (size_t i = 0; i < testcases; i++)
    {
        read_ingore_empty_line(f, pch);
        towns = atoi(pch);
        cout << "towns: " <<  towns << endl;
        read_ingore_empty_line(f, pch);
        cout << "town: " <<  pch << endl;
        read_ingore_empty_line(f, pch);
        neighbors = atoi(pch);
        for (size_t j = 0; j < neighbors; j++)  {}



    }

    // for (size_t i = 0; i < testcases; i++)
    // {
    //     fgets(pch, 126, f);
    //     towns = atoi(pch);
    //     cout << pch << " " <<  towns << endl;
        
    //     while(!feof(f)) {
    //         fgets(pch, 30, f);
    //         if(strlen(pch) == 2)
    //             break;
    //         cout << "pch = " << pch << " " << strlen(pch) << endl;
    //         fgets(pch, 30, f);
    //         neighbors = atoi(pch);
    //         cout << "neighbors: " << neighbors << endl; 
    //         for (size_t j = 0; j < neighbors; j++)
    //         {
    //             fscanf(f, "%d %d", &tail, &value);
    //             cout << "v: " <<  tail << " " << value << endl;
    //         }
    //         fgets(pch, 30, f);
    //     }
    // }

    fclose(f);

}