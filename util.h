#ifndef _UTIL_H_
#define _UTIL_H_

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;

/* 
prints the edges of a graph in the form:
1 2
1 3	
2 4
The graph must be in an adjancecy list representation: map< T, vector<U> > for example.  
*/

template <typename T, typename U> void print_graph_edges(map<T, vector<U> > &g) {
    typename map<T, vector<U> >::iterator it;
    typename vector<U>::iterator it_vect;

    for( it = g.begin(); it != g.end(); it++)
    {
    	for(it_vect = it->second.begin(); it_vect != it->second.end(); it_vect++)
    		cout << it->first << " " << *it_vect << endl;
    }
}

template <typename T, typename G> void print_adjacency_list(G &g) {
    typename G::iterator it;

    for( it = g.begin(); it != g.end(); it++)
    {
        cout << it->first << ": "; 
    	//for_each(it->second.begin(); it->second.end(); print<T>);
        cout << endl;
    }
}
#endif