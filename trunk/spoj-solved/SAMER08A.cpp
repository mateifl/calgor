#include <climits>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <ctime>
using namespace std;
typedef unsigned long ulong;
struct edge {
	ulong head;
	ulong tail;
	ulong value;
};

typedef edge edge;

typedef vector<vector<ulong> > graph;
//typedef unsigned int uint;

template<class T> struct greater_edge : binary_function<T, T, bool> {
	bool operator()(const T& x, const T& y) const {
		return x.value > y.value;
	}
};
typedef priority_queue<edge, vector<edge>, greater_edge<edge> > heap;

vector<ulong> dijkstra(graph &g, long source_node, graph &g_edges) {
	// the heap
	heap nodes_heap;
	vector<bool> v_bool_visited = vector<bool>(g.size());
	v_bool_visited[source_node] = true;

	for (ulong i = 0; i < g_edges[source_node].size(); i++) {
		edge e;
		e.value = g[source_node][g_edges[source_node][i]];
		if (e.value == ULONG_MAX)
			continue;
		e.tail = g_edges[source_node][i];
		e.head = source_node;
		nodes_heap.push(e);
	}

	vector<ulong> m_shortest_path = vector<ulong>(g.size());
	m_shortest_path.assign(g.size(), ULONG_MAX);
	m_shortest_path[source_node] = 0;
	//m_shortest_path[source_node].l_predecesor = 0;
	edge next_edge;

	long visited_nodes = 1;
	while (visited_nodes < g.size() && !nodes_heap.empty()) {
		next_edge = nodes_heap.top();
		nodes_heap.pop();

		if (v_bool_visited[next_edge.tail] || next_edge.value == ULONG_MAX)
			continue;

		m_shortest_path[next_edge.tail] = next_edge.value;

		for (ulong i = 0; i < g_edges[next_edge.tail].size(); i++) {
			ulong i_ne_tail = g_edges[next_edge.tail][i];
			if (!v_bool_visited[i_ne_tail] && g[next_edge.tail][i_ne_tail] < ULONG_MAX) {
				edge e;
				e.head = next_edge.tail;
				e.tail = i_ne_tail;
				e.value = m_shortest_path[next_edge.tail] + g[next_edge.tail][i_ne_tail];
				nodes_heap.push(e);
			}
		}
		v_bool_visited[next_edge.tail] = true;
		visited_nodes += 1;
	}

	return m_shortest_path;
}

int main(int argc, char **argv) {
	time_t t = clock();
	ulong  i_nodes, i_edges, i_start, i_end, i_head, i_tail, i_value;

	while (true) {
		scanf("%d %d", &i_nodes, &i_edges);

		if (i_nodes == 0 && i_edges == 0)
			break;

		scanf("%d %d", &i_start, &i_end);
		//cout << i_nodes << " " << i_edges << " " << endl;
		graph g = graph(i_nodes), gr = graph(i_nodes), g_edges(i_nodes), gr_edges(i_nodes);

		for (ulong j = 0; j < i_nodes; j++)
		{
			g[j] = vector<ulong>(i_nodes);
			g[j].assign(i_nodes, ULONG_MAX);
			gr[j] = vector<ulong>(i_nodes);
			gr[j].assign(i_nodes, ULONG_MAX);
		}

		for (ulong j = 0; j < i_edges; j++){
			scanf("%d %d %d", &i_head, &i_tail, &i_value);
			g[i_head][i_tail] = i_value;
			g_edges[i_head].push_back(i_tail);
			gr[i_tail][i_head] = i_value;
			gr_edges[i_tail].push_back(i_head);
		}

		clock_t t0 = clock();
		//cout << "time: " << (float)(t0 - t) / CLOCKS_PER_SEC << endl;
		vector<ulong> v = dijkstra(g, i_start, g_edges);
		
		if (v[i_end] == ULONG_MAX){
			printf("-1\n");
			continue;
		}
		
		vector<ulong> v2 = dijkstra(gr, i_end, gr_edges);

		for (ulong i = 0; i < i_nodes; i++) {
			for (ulong j = 0; j < i_nodes; j++) {
				if (i == j) continue;
				if (v[i] + g[i][j] + v2[j] == v[i_end] && g[i][j] < ULONG_MAX) {
					//cout << "Remove " << i << " " << j << " - " << g[i][j] <<  endl;
					g[i][j] = ULONG_MAX;
				}
			}
		}

		v = dijkstra(g, i_start, g_edges);
		if (v[i_end] == ULONG_MAX)
			printf("-1\n");
		else
			printf("%d\n", v[i_end]);
	}

	clock_t t1 = clock();
	//cout << "time: " << (float)(t1 - t)/CLOCKS_PER_SEC << endl;

	return 0;
}




