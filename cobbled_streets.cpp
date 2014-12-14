#include <ctime>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;

struct edge {
	int head;
	int tail;
	int val;
	//int heap_value;
};

typedef map<string, int> string_int_map;
typedef edge edge;
typedef vector<vector<edge> > graph;
typedef unsigned int uint;
template<class T> struct greater_edge: binary_function<T, T, bool> {
	bool operator()(const T& x, const T& y) const {
		return x.val > y.val;
	}
};
typedef priority_queue<edge, vector<edge>, greater_edge<edge> > heap;

vector<edge> prim(graph &g, int i_source_node) {
	// the heap
	heap nodes_heap;
	vector<bool> v_bool_visited = vector<bool>(g.size());
	v_bool_visited[i_source_node] = true;

	for (uint i = 0; i < g[i_source_node].size(); i++) {
		nodes_heap.push(g[i_source_node][i]);
	}
	// initialize the vector that will store the MST.
	vector<edge> v_mst;
	
	edge next_edge;
	uint i_node_index = 1;

	while ( i_node_index < g.size() - 1) {
		next_edge = nodes_heap.top();
		nodes_heap.pop();

		// check if the tail is already visited (avoid cycles)
		if (v_bool_visited[next_edge.head] && v_bool_visited[next_edge.tail])
			continue;
		
		// put the edge in the MST.
		v_mst.push_back(next_edge);

		// add the neighbouring edges in the heap
		for (uint i = 0; i < g[next_edge.tail].size(); i++) {
			if (!v_bool_visited[g[next_edge.tail][i].tail]) {
				edge e = g[next_edge.tail][i];
				nodes_heap.push(e);
			}
		}

		// mark node as visited
		v_bool_visited[next_edge.tail] = true;
		i_node_index += 1;
	}

	return v_mst;
}


int main(int argc, char **argv) {
	clock_t t0 = clock();
	int i_buildings, i_streets, i_test_cases, i_price;

	FILE *ifile = stdin;
	if(ifile == NULL) {
		printf("ERROR no input file\n");
		return 0;
	}
	scanf("%d", &i_test_cases);

	for(uint i = 0; i < i_test_cases; i++)
	{
		scanf("%d", &i_price);
		scanf("%d", &i_buildings);
		scanf("%d", &i_streets);
		graph g = graph(i_buildings + 1);
		for(uint j = 0; j < i_streets; j++)
		{
			int i_head, i_tail, i_value;
			scanf("%d %d %d", &i_head, &i_tail, &i_value);
		//	cout << i_head << " " << i_tail << " " << i_value << endl;
			edge e, e1;
			e.head = i_head;
			e.tail = i_tail;
			e.val = i_value;
			g[i_head].push_back(e);
			
			e1.head = i_tail;
			e1.tail = i_head;
			e1.val = i_value;
			g[i_tail].push_back(e1);
		//	cout << i_head << " " << i_tail << " " << i_value << endl;
		}
		/*
		for(uint j = 1; j < g.size(); j++) {
			for(int k = 0; k < g[j].size(); k++) {
				cout << g[j][k].head << " " << g[j][k].tail << endl; 
			}
		}
		*/
		vector<edge> mst = prim(g, 1);
		int val_mst = 0;
		for (int k = 0; k < mst.size(); k++) {
			val_mst += mst[k].val;
			if (mst[k].head < mst[k].tail)
				cout << mst[k].head << " " << mst[k].tail << " " << mst[k].val << endl;
			else
				cout << mst[k].tail << " " << mst[k].head << " " << mst[k].val << endl;
		}
		cout << "val = " << val_mst << endl;
	}

	return 0;
}