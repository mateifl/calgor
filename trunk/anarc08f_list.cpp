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
	int tail;
	int value;
};

typedef edge edge;
typedef vector<vector<edge> > graph;
typedef priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > heap;

void update_heap(heap &nodes_heap, graph &g, int source_node, int path_value, vector<int> &v_not_visited) {
	vector<edge> edges = g[source_node];
	vector<edge>::iterator it;
	for(it = edges.begin(); it != edges.end(); it++)
	{
		if( v_not_visited[it->tail] > path_value + it->value )
		{
			nodes_heap.push(make_pair(path_value + it->value, it->tail));
			v_not_visited[it->tail] = path_value + it->value;
		}
	}
}

map<int, int> dijkstra(graph g, int source_node) {
	int MAX_INT = 63356;
	// build the heap
	heap nodes_heap;
	// create a map with not visited nodes
	vector<int> v_not_visited;

	for( int i = 0; i < g.size(); i++)
	{
		if( i != source_node ){
			nodes_heap.push(make_pair(MAX_INT, i));
			v_not_visited[i] = MAX_INT;
		}
	}

	v_not_visited[source_node] = false;
	// initialize the map that will store the shortest paths.

	map<int, int> m_shortest_path;
	m_shortest_path.insert(make_pair(source_node, 0));
	pair<int, int> node;
	while( nodes_heap.size() > 0) {
		node = nodes_heap.top();
		nodes_heap.pop();

		if( node.second == MAX_INT )
			break;
		else if( v_not_visited[node.first] < 0 )
			continue;
		else {
			m_shortest_path.insert(make_pair( node.first, node.second ));
			update_heap(nodes_heap, g, node.first, node.second, v_not_visited);
			v_not_visited[node.first] = false;
		}

		// mark node as visited
		v_not_visited[node.first] = -1;
	}

	return m_shortest_path;
}
