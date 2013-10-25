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

void print_short_array(short *a, size_t a_length);


template <class T> void add_to_vector2(vector<vector<T> > &result, const vector<T> &initial_set, const char *v_mask, int sub_set_size) {
    vector<T> subset = vector<T>(sub_set_size);
    int j = 0;
    for(int i = 0; i < initial_set.size(); i++)
    {
        if( v_mask[i] == 1 ){
            subset[j]  = initial_set.at(i);
            j++;
        }
    }

    result.push_back(subset);
}

template <class T> vector<vector<T> > subsets2(vector<T> initial_set, int subset_size) 
{
    vector<vector<T> > v_result;
    unsigned short v_set_size = initial_set.size();
    char *v_mask = new char[v_set_size];

    for(unsigned short i = 0; i < v_set_size; i++ )
    {
        if( i < (v_set_size - subset_size))
            v_mask[i] = 0;
        else
            v_mask[i] = 1;
    }

    add_to_vector2(v_result, initial_set, v_mask, subset_size);

    while( next_permutation( v_mask, v_mask + v_set_size ) )
        add_to_vector2(v_result, initial_set, v_mask, subset_size);

    delete[] v_mask;
    return v_result;

    
}


#endif
