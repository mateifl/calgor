#include <ctime>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;

struct edge {
	// int head;
	int tail;
	int val;
};

typedef edge edge;
typedef vector< vector<edge> > graph;
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
		//if (i_node_index % 10 == 0)
		//	printf("%d %d\n", i_node_index, nodes_heap.size());
	}

	return v_mst;
}

int main(int argc, char **argv) {
	clock_t t0 = clock();
	uint i_cities, i_neighbors, i_test_cases;
    uint i_head, i_tail, i_value;
	FILE *ifile = stdin;
	fscanf(ifile, "%d", &i_test_cases);
    char buffer[128];

	for(uint i = 0; i < i_test_cases; i++)
	{
		fscanf(ifile, "%d", &i_cities);
        graph g = graph(i_cities);
        uint i = 0;
        while(true) {
            fgets(buffer, 128, ifile);
            if( buffer ){
                break;
            }     

            fscanf(ifile, "%d", &i_neighbors);  
            for (size_t j = 0; j < i_neighbors; j++)
            {
                fscanf(ifile, "%d %d", &i_tail, &i_value);
                egde e; 
                e.head = i;
                e.tail = i_tail;
                e.val = i_value;
                g[i].push_back(e);
                egde e1;
                e1.head = i_tail;
                e1.tail = i;
                e1.val = i_value;
                g[i_tail].push_back(e1);
            }
            
            i += 1;   
        }
        
		vector<edge> mst = prim(g, 1);
		int val_mst = 0;
		
		for (int k = 0; k < mst.size(); k++) {
			val_mst += mst[k].val;

		}
		
		//cout << "val = " << val_mst << endl;
		printf("%d\n", val_mst);
	}
	//clock_t t1 = clock();
	//cout << "time: " << (float)(t1 - t0) / CLOCKS_PER_SEC << endl;
	return 0;
}