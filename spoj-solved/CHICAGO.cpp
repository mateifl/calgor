#include <ctime>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

struct edge {
	int head;
	int tail;
	double value;
	double heap_value;
};

typedef edge edge;
typedef vector<vector<edge> > graph;
typedef unsigned int uint;
template<class T> struct greater_edge : binary_function<T, T, bool> {
	bool operator()(const T& x, const T& y) const {
		return x.heap_value < y.heap_value;
	}
};
typedef priority_queue<edge, vector<edge>, greater_edge<edge> > heap;

vector<double> dijkstra(graph g, int source_node) {
	// the heap
	heap nodes_heap;
	vector<bool> v_bool_visited = vector<bool>(g.size());
	v_bool_visited[source_node] = true;

	for (uint i = 0; i < g[source_node].size(); i++) {
		g[source_node][i].heap_value = g[source_node][i].value;
		nodes_heap.push(g[source_node][i]);
	}
	// initialize the map that will store the shortest paths.
	vector<double> m_shortest_path = vector<double>(g.size());
	m_shortest_path[source_node] = 0;
	edge next_edge;
	int i_processed = 1;
	while (i_processed < g.size() && nodes_heap.size() > 0) {
		next_edge = nodes_heap.top();
		nodes_heap.pop();

		if (v_bool_visited[next_edge.head] && v_bool_visited[next_edge.tail])
			continue;

		if (m_shortest_path[next_edge.head] == 0)
			m_shortest_path[next_edge.tail] = next_edge.value;
		else
			m_shortest_path[next_edge.tail] = m_shortest_path[next_edge.head] * next_edge.value / 100.;

		for (uint i = 0; i < g[next_edge.tail].size(); i++) {
			if (!v_bool_visited[g[next_edge.tail][i].tail]) {
				edge e = g[next_edge.tail][i];
				e.heap_value = m_shortest_path[next_edge.tail] * e.value / 100.;
				nodes_heap.push(e);
			}
		}
		// mark node as visited
		v_bool_visited[next_edge.tail] = true;
	}

	return m_shortest_path;
}

int main(int argc, char **argv) {
	FILE *ifile = stdin;
	if (ifile == NULL) {
		printf("ERROR no input file\n");
		return 0;
	}

	int i_nodes, i_edges, i_start, i_end, i_head, i_tail;
	double i_value;
	char pch_line[64];
	char *pch = new char[100];
	while (true)
	{
		fscanf(ifile, "%d %d", &i_nodes, &i_edges);
		if (i_nodes == 0)
			break;
		
/*		pch = strtok(pch_line, " \r\n");
		i_nodes = atoi(pch);
		pch = strtok(NULL, " \r\n");
		i_edges = atoi(pch);*/
		graph g = graph(i_nodes + 1);
		for (int j = 0; j < i_edges; j++){
			fscanf(ifile, "%d %d %lf", &i_head, &i_tail, &i_value);
			edge e, e1;
			e.head = i_head;
			e.tail = i_tail;
			e.value = i_value;
			g[i_head].push_back(e);
			e1.tail = i_head;
			e1.head = i_tail;
			e1.value = i_value;
			g[i_tail].push_back(e1);

		}

		vector<double> v = dijkstra(g, 1);
		printf("%lf percent\n", v[i_nodes]);
	}
	return 0;
}