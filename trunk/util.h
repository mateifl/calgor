// *** ADDED BY HEADER FIXUP ***
#include <iostream>
#include <vector>
// *** END ***
#ifndef _UTIL_H_
#define _UTIL_H_

#include "main.h"

template <class T> void dprint(vector<T> v)
{
    cout << "Size: " << v.size() << endl;
    for(unsigned int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
}

#endif
