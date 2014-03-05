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

	for(unsigned int i = 0; i < g.size(); i++)
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

void parse_roads_line(char *source, char* destination, char* mid, graph &g, map<char*, int> locations_map) {
	int i_source_index = locations_map[source];
	int i_destination_index = locations_map[destination];
	char pch_value[10];
	strncpy(pch_value, mid + 2, strlen(mid) - 2);
	if( mid[0] == '<' )
	{
		edge e;
		e.tail = i_destination_index;
		e.value = atoi(pch_value);
		g[i_source_index].push_back(e);
	}
}

int main(int argc, char **argv) {
	int i_locations, i_cars, i_roads;
	char *pch_line = new char[1024 * 8], *pch;
	char source[32], mid[32], end[32];

	while(true) {
		scanf("%d %d %d\n", &i_locations, &i_cars, &i_roads);

		if(i_locations == 0 && i_cars == 0 && i_roads == 0)
			break;

		fgets(pch_line, 8*1024, stdin);

		pch = strtok(pch_line, " ");

		int i = 0;
		map<char*, int> m_locations_map;

		while( (pch = strtok(NULL, " ")) != NULL ){
			m_locations_map.insert(make_pair(pch, i));
			i++;
		}

		graph g = graph(i_locations);

		for(int i = 0; i < i_roads; i++){
			scanf("%s %s %s", source, mid, end);
			parse_roads_line(source, end, mid, g, m_locations_map);
		}
	}

	return 0;
}
