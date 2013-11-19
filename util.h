#ifndef _UTIL_H_
#define _UTIL_H_

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

/* prints the edges of a graph in the form:
1 2
1 3
2 4

The graph must be in an adjancecy list representation: map< T, vector<U> > for example.  */

template <typename T> void print(T i){
    cout << i << " ";
}

template <typename T, typename U> void print_graph_edges(map<T, vector<U> > g) {
    typename map<T, vector<U> >::iterator it;
    typename vector<U>::iterator it_vect;

    for( it = g.begin(); it != g.end(); it++)
    {
    	for(it_vect = it->second.begin(); it_vect != it->second.end(); it_vect++)
    		cout << it->first << " " << *it_vect << endl;
    }

}

#endif