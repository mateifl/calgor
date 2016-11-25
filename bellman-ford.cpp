#include <ctime>
#include <climits>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

typedef unsigned long ulong;

struct edge {
	ulong head;
	ulong tail;
	ulong value;
};

typedef edge edge;
typedef vector<vector<edge> > graph;

void print_vector(vector<ulong> v) {
	for (ulong i = 0; i < v.size(); i++)
		cout << v[i] << " ";
	cout << endl;
}

vector<ulong> bellman_ford(vector<edge> &g, ulong l_nodes_number,  ulong l_source_node) {
	vector<ulong> v_shortest_path = vector<ulong>(l_nodes_number);
	v_shortest_path.assign(v_shortest_path.size(), ULONG_MAX);
	v_shortest_path[l_source_node] = 0;

	for (ulong i = 0; i < l_nodes_number - 1; i++)
	{
		for(ulong j = 0; j < g.size(); j++)
		{
			edge e = g[j];
			// cout << e.head << " " << e.tail << endl;
			if (v_shortest_path[e.head] + e.value < v_shortest_path[e.tail])
				v_shortest_path[e.tail] = v_shortest_path[e.head] + e.value;
			if (v_shortest_path[e.tail] + e.value < v_shortest_path[e.head])
				v_shortest_path[e.head] = v_shortest_path[e.tail] + e.value;
			print_vector(v_shortest_path);
		}
		
	}

	return v_shortest_path;
}


vector<ulong> bellman_ford(graph &g, long source_node) {
	vector<ulong> v_shortest_path = vector<ulong>(g.size());
	long l_iterations = g.size() - 1;
	
	for (long i = 0; i < l_iterations; i++)
	{
		for (long j = 0; j <= l_iterations; j++)
		{
			vector<edge> v_edges = g[j];
			for (long k = 0; k < v_edges.size(); k++) {
				edge e = v_edges[k];
				if (v_shortest_path[e.head] + e.value < v_shortest_path[e.tail])
					v_shortest_path[e.tail] = v_shortest_path[e.head] + e.value;
				if (v_shortest_path[e.tail] + e.value < v_shortest_path[e.head])
					v_shortest_path[e.head] = v_shortest_path[e.tail] + e.value;
					
			}
		}
	}

	return v_shortest_path;
}

int main(int argc, char **argv) {

	ulong l_head, l_tail, l_weight, l_source_node;
	int l_nodes_number, l_edges_number;
	
	scanf("%d %d %ld", &l_nodes_number, &l_edges_number, &l_source_node);
	cout << l_nodes_number << " " << l_edges_number << endl;
	
	vector<edge> g(l_edges_number);
	for(int i = 0; i < l_edges_number; i++) {
		scanf("%ld %ld %ld", &l_head, &l_tail, &l_weight);
		edge e; 
		e.head = l_head;
		e.tail = l_tail;
		e.value = l_weight;
		// cout << e.head << " " << e.tail << " " << e.value << endl;
		g[i] = e;
	}
	
	// cout << "graph created" << endl;
	vector<ulong> result = bellman_ford(g, l_nodes_number, 1);
	cout << l_nodes_number << " " << l_edges_number << endl;

	for(int i = 0; i < l_nodes_number; i++)
		cout << result[i] << endl;

	return 0;
}