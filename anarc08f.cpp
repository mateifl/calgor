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

void update_heap(heap &nodes_heap, graph g, char* source_node, map<char *, int> &m_not_visited, int i_path_value) {
	vector<edge> v = g[source_node];
	vector<edge>::iterator it;
	for(it = v.begin(); it != v.end(); it++)
	{
		if( m_not_visited.find( it->tail ) == m_not_visited.end() )
			continue;
		else if ( m_not_visited[it->tail] > i_path_value + it->value)
		{
			nodes_heap.push( make_pair(i_path_value + it->value, it->tail));
			m_not_visited[it->tail] = i_path_value + it->value;
		}
	}
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

	while(nodes_heap.size() > 0){
		pair<int, char*> node = nodes_heap.top();
		if( m_not_visited.find( node.second ) == m_not_visited.end() )
			continue;
		m_shortest_path[node.second] = node.first;
		update_heap(nodes_heap, g, source_node, m_not_visited, node.first);
		m_not_visited.erase(node.second);
	}
	return m_shortest_path;
}


int main(int argc, char** argv) {
	char pch_line[1024], *pch;
	string s;
	while(true) {
		fgets(pch_line, 1024, stdin);
		if( pch_line == NULL)
			break;
		pch = strtok(pch_line, " ");
		cout << pch << endl;
		while(pch != NULL)
		{
			pch = strtok(NULL, " ");
			cout << pch << endl;
		}
	}
	return 0;
}
