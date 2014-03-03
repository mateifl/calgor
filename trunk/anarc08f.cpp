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
#include <queue>
#include <functional>
using namespace std;

struct edge {
	char *tail;
	int value;
};

typedef edge edge;
typedef map<char *, vector<edge> > graph;
typedef priority_queue<pair<int, char*>, vector<pair<int, char*> >, greater<pair<int, char*> > > heap;

void update_heap(heap nodes_heap, graph g, char* source_node, map<char *, int> m_not_visited) {


}

map<char *, int> dijkstra(graph g, char* source_node) {
	int MAX_INT = 63356  ;
	// build the heap
	heap nodes_heap;
	// create a map with not visited nodes

	map<char *, int> m_not_visited;
	graph::iterator it;
	for( it = g.begin(); it != g.end(); it++)
	{
		if( strcmp(it->first, source_node) ){
			nodes_heap.push(make_pair(MAX_INT, it->first));
			m_not_visited.insert(make_pair(it->first, MAX_INT));
		}
	}

	m_not_visited.insert(make_pair(source_node, 0));
	// initialize the map that will store the shortest paths.

	map<char *, int> m_shortest_path;
	m_shortest_path.insert( make_pair(source_node , 0) );




	return m_shortest_path;
}


int main(int argc, char** argv) {

	priority_queue<pair<int, const char*>, vector<pair<int, const char*> >, greater<pair<int, const char*> > > heap;
	heap.push(make_pair(5, "Test1"));
	heap.push(make_pair(2, "Test2"));
	heap.push(make_pair(3, "Test3"));
	heap.push(make_pair(4, "Test4"));

	cout << heap.top().second << endl;
	heap.pop();
	cout << heap.top().second << endl;
	heap.pop();
	cout << heap.top().second << endl;
	heap.pop();
	cout << heap.top().second << endl;

	return 0;
}
