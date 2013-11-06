#ifndef _UTIL_H_
#define _UTIL_H_
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


template <class T> void dprint(vector<T> v)
{
    cout << "Size: " << v.size() << endl;
    for(unsigned int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
}

template <class T> T vector_sum(vector<T> v)
{
	T sum = 0;
	vector<T>::iterator it;
	for( it = v.begin(); it != v.end(); it++)
		sum += *it;
	return sum;
}


void print_short_array(short *a, size_t a_length);


#endif
