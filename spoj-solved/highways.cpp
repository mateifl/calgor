#include <ctime>
#include <climits>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

struct edge {
	long head;
	long tail;
	long value;
	long heap_value;
};

typedef edge edge;
typedef vector<vector<edge> > graph;
//typedef unsigned int uint;
typedef unsigned long ulong;
template<class T> struct greater_edge : binary_function<T, T, bool> {
	bool operator()(const T& x, const T& y) const {
		return x.heap_value > y.heap_value;
	}
};
typedef priority_queue<edge, vector<edge>, greater_edge<edge> > heap;

vector<ulong> dijkstra(graph g, long source_node) {
	// the heap
	heap nodes_heap;
	vector<bool> v_bool_visited = vector<bool>(g.size());
	v_bool_visited[source_node] = true;

	for (ulong i = 0; i < g[source_node].size(); i++) {
		g[source_node][i].heap_value = g[source_node][i].value;
		nodes_heap.push(g[source_node][i]);
	}
	// initialize the map that will store the shortest paths.
	vector<ulong> m_shortest_path = vector<ulong>(g.size());
	m_shortest_path.assign(g.size(), ULONG_MAX);
	m_shortest_path[source_node] = 0;
	edge next_edge;

	while (nodes_heap.size() > 0) {
		next_edge = nodes_heap.top();
		nodes_heap.pop();

		if (v_bool_visited[next_edge.head] && v_bool_visited[next_edge.tail])
			continue;

		m_shortest_path[next_edge.tail] = m_shortest_path[next_edge.head] + next_edge.value;
		for (ulong i = 0; i < g[next_edge.tail].size(); i++) {
			if (!v_bool_visited[g[next_edge.tail][i].tail]) {
				edge e = g[next_edge.tail][i];
				e.heap_value = m_shortest_path[next_edge.tail] + e.value;
				nodes_heap.push(e);
			}
		}
		v_bool_visited[next_edge.tail] = true;
	}

	return m_shortest_path;
}

int main(int argc, char **argv) {
	ulong  i_testcases, i_nodes, i_edges, i_start, i_end, i_head, i_tail, i_value;
	scanf("%d", &i_testcases);

	for (ulong i = 0; i < i_testcases; i++)
	{
		scanf("%d %d %d %d", &i_nodes, &i_edges, &i_start, &i_end);

		if (i_nodes == 1) {
			printf("0\n");
			continue;
		}
		graph g = graph(i_nodes + 1);
		for (ulong j = 0; j < i_edges; j++){
			scanf("%d %d %d", &i_head, &i_tail, &i_value);
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
		
		vector<ulong> v = dijkstra(g, i_start);
		/*
		for (ulong j = 0; j < v.size(); j++) 
			cout << j << " " << v[j] << endl;
		*/
		if (v[i_end] == ULONG_MAX)
			printf("NONE\n");
		else
			printf("%ld\n", v[i_end]);
	}
	return 0;
}