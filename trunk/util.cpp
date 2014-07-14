#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;

void print_short_array(short *a, size_t a_length) {
    for(unsigned int i = 0; i < a_length; i++)
        cout << a[i] << " " ;
    cout << endl;
}



int main(int argc, char const *argv[])
{
    // char pch_number[10];
    // sprintf(pch_number, "%d", 11111);
    // cout << pch_number << " " << strlen(pch_number) << endl;


    char pch_number[10];
    memset(pch_number, '0', 10);
    cout << pch_number << endl;
      
    return 0;
}