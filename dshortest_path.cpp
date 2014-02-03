#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <string>
#include <cstdio>
#include <set>
#include <queue>
#include <ctime>
#include <cstring>
using namespace std;

typedef vector< vector<int> > graph;

template <typename T, typename G> void generic_d_shortest_path(G &g, T source_node) {
	map<T, vector<T> > m_paths; // this map will have have the paths from the source node to every node
	map<T, long> m_path_values;
	m_paths.insert( make_pair(T, vector<T>() ) ); 
	m_path_values.insert( make_pair(T, 0) );

	G::iterator it;
	for(it = g.begin(); it != g.end(); it++)
	{

	}

}


int main(int argc, char** argv) {

	return 0;
}