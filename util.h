#ifndef _UTIL_H_
#define _UTIL_H_
#include <iostream>
#include <vector>
using namespace std;


template <class T> void dprint(vector<T> v)
{
    cout << "Size: " << v.size() << endl;
    for(unsigned int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
}

void print_short_array(short *a, size_t a_length);

#endif
