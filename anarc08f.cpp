#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <cmath>
#include <string>
#include <ctime>
#include <algorithm>
#include <map>
using namespace std;
struct edge {
	//char *head;
	char *tail;
	int value;
};

typedef edge edge;
typedef map<char *, vector<edge> > graph;

bool comp( pair<int, char*> first, pair<int, char*> second)
{
	return first.first < second.first;
}

map<char *, int> dijkstra(graph g, char* source_node) {
	vector<pair<int, char*> > nodes_heap;
	graph::iterator it;
	for( it = g.begin(); it != g.end(); it++)
	{
		if( strcmp(it->first, source_node) )
			nodes_heap.push_back(make_pair(UINT_MAX, it->first));
	}

	make_heap(nodes_heap.begin(), nodes_heap.end(), comp);

	map<char *, int> m_shortest_path;
	m_shortest_path.insert( make_pair(source_node , 0) );
	return m_shortest_path;
}


int main(int argc, char** argv) {

	return 0;
}