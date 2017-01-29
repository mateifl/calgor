// http://www.spoj.com/problems/BIA/

#include <iostream>
#include <cmath>
#include <vector>
#include <cstdio>
#include <stack>
#include <ctime>
#include <cstring>
using namespace std;

typedef unsigned int u_int;

typedef vector< vector<u_int> > graph;

vector<u_int> dfs(graph &g, u_int start_node){
	stack<u_int> node_stack;
    node_stack.push(start_node);
	u_int node;
    vector<short> processed_nodes(g.size());
    vector<u_int> node_numbers;

    u_int node_number = 0;
    while(node_stack.size() > 0){
        node = node_stack.top();
		// mark node as discovered
		processed_nodes[node] = 1;
		// get the neighbours

		bool continue_flag = false;

        for(u_int i = 0; i < g[node].size(); i++) {
			short node_state = processed_nodes[g[node][i]];

			if( node_state == 2 )
				continue;
			else if(node_state == 0)
			{
				processed_nodes[g[node][i]] = 1;
				node_stack.push(g[node][i]);
                node_numbers[g[node][i]] = node_number;
                node_number += 1;
				continue_flag = true;
				break;
			}
		}

		if(continue_flag)
			continue;
		// node processed
		processed_nodes[node] = 2;
		node_stack.pop();
    }
    return node_numbers;
}

int main(int argc, char **argv) {
   	clock_t t0 = clock();
    FILE *f = stdin;
    u_int nodes, edges, head, tail;
    fscanf(f, "%d %d", &nodes, &edges);
    graph g(nodes);
    for (size_t i = 0; i < edges; i++)
    {
        fscanf(f, "%d %d", &head, &tail);
        g[head].push_back(tail);
    }

    return 0;
}