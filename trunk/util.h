#ifndef _UTIL_H_
#define _UTIL_H_

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

/* prints the edges o a greaph in the form:
1 2
1 3
2 4

The graph must be in an adjancecy list representation: map< T, vector<U> > for example.  */

template <typename T> void print(T i){
    cout << i << " ";
}

template <typename T, typename U> void print_graph_edges(map<T, vector<U> > g) {
    T::iterator it;
    
    for( it = g.begin(); it != g.end(); it++)
    {
        for_each( it->begin(); it->end(); print );
    }

}

#endif