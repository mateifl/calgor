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
};

typedef edge edge;
typedef vector<vector<edge> > graph;

typedef unsigned long ulong;

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
			}
		}
	}

	return v_shortest_path;
}

int main(int argc, char **argv) {
		
	return 0;
}