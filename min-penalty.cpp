// https://www.hackerrank.com/challenges/beautiful-path

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
	cout << "----" << endl;
}

vector<ulong> bellman_ford(vector<edge> &g, ulong l_nodes_number,  ulong l_source_node) {
	vector<ulong> v_shortest_path = vector<ulong>(l_nodes_number + 1);
	v_shortest_path.assign(v_shortest_path.size(), ULONG_MAX);
	v_shortest_path[l_source_node] = 0;
	
	// print_vector(v_shortest_path);
	for (ulong i = 0; i < l_nodes_number - 1; i++)
	{
		// cout << "===== " << g.size() << endl; 
		for(ulong j = 0; j < g.size(); j++)
		{
			edge e = g[j];
			// cout << e.head << " " << e.tail << endl;
			// cout << v_shortest_path[e.head] << " - " << v_shortest_path[e.tail] << endl; 
			// cout << ((v_shortest_path[e.tail] | e.value) < v_shortest_path[e.head] ) << endl;
			if ((v_shortest_path[e.head] | e.value) < v_shortest_path[e.tail])
				v_shortest_path[e.tail] = v_shortest_path[e.head] | e.value;
			if ((v_shortest_path[e.tail] | e.value) < v_shortest_path[e.head])
				v_shortest_path[e.head] = v_shortest_path[e.tail] | e.value;
			// print_vector(v_shortest_path);
		}
	}

	return v_shortest_path;
}

int main(int argc, char **argv) {

	ulong l_head, l_tail, l_weight, l_source_node, l_dest_node;
	ulong l_nodes_number, l_edges_number;
	// FILE *f = fopen("g12.txt", "r");
	// fscanf(f, "%d %d %ld", &l_nodes_number, &l_edges_number, &l_source_node);
	scanf("%ld %ld", &l_nodes_number, &l_edges_number);
	// cout << "cc" <<  l_nodes_number << " " << l_edges_number << endl;
	
	vector<edge> g(l_edges_number);
	for(int i = 0; i < l_edges_number; i++) {
		// fscanf(f, "%ld %ld %ld", &l_head, &l_tail, &l_weight);
		scanf("%ld %ld %ld", &l_head, &l_tail, &l_weight);
		edge e; 
		e.head = l_head;
		e.tail = l_tail;
		e.value = l_weight;
		// cout << e.head << " " << e.tail << " " << e.value << endl;
		g[i] = e;
	}
	scanf("%ld %ld", &l_source_node, &l_dest_node);
	// exit(0);
	// fclose(f);
	
	// cout << "graph created" << endl;
	vector<ulong> result = bellman_ford(g, l_nodes_number, l_source_node);
    // print_vector(result);
	// cout << "done computing" << l_nodes_number << endl;
    // f = fopen("bfresults.txt", "w");
	cout << result[l_dest_node] << endl;
	// for(ulong i = 0; i < l_nodes_number; i++)
    // {
    //     // cout << i << " " << result[i] << " " << endl;
	// 	printf("%ld %ld\n", i, result[i]);
    // }
    // fclose(f);
	return 0;
}