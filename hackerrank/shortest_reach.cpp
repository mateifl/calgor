// https://www.hackerrank.com/challenges/dijkstrashortreach

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
typedef vector<vector<ulong> > graph;

vector<ulong> bfs(graph g, ulong source_node) {
	vector<bool> v_bool_visited = vector<bool>(g.size() + 1, false);
	vector<bool> v_added = vector<bool>(g.size() + 1, false);
	v_bool_visited[source_node] = true;
    vector<ulong> m_shortest_path = vector<ulong>(g.size() + 1, ULONG_MAX);
	m_shortest_path[source_node] = 0;
    queue<int> q;

	for (ulong i = 0; i < g[source_node].size(); i++) {
		q.push(g[source_node][i]);
		v_added[g[source_node][i]] = true;
		m_shortest_path[g[source_node][i]] = 1;
	}

	while (q.size() > 0) {
		// cout << m_shortest_path[source_node] << endl;
		ulong node = q.front();
		q.pop();
        cout << "Processing node: " << node << endl;

        vector<ulong> v_neighbors = g[node];
        for(ulong i = 0; i < v_neighbors.size(); i++)
        {
            if(!v_bool_visited[v_neighbors[i]] && !v_added[v_neighbors[i]]) {
				cout << "Adding to queue: " << v_neighbors[i] << endl;
                q.push(v_neighbors[i]);
				v_added[v_neighbors[i]] = true;
                if(m_shortest_path[v_neighbors[i]] == ULONG_MAX)
                    m_shortest_path[v_neighbors[i]] = m_shortest_path[node] + 1;
            }
        }
        v_bool_visited[node] = true;
    }
	return m_shortest_path;
}

int main(int argc, char **argv) {
	FILE *ifile = stdin;
    //FILE *ifile = fopen("hackerrank/shortest_reach_tc2.txt", "r");

	if (ifile == NULL) {
		printf("ERROR no input file\n");
		return 0;
	}

    ulong i_nodes, i_edges, i_start, i_end, i_head, i_tail, ul_testcases;

    fscanf(ifile, "%ld", &ul_testcases);
	for(ulong k = 0; k < ul_testcases; k++)
	{
		fscanf(ifile, "%ld %ld", &i_nodes, &i_edges);
		graph g = graph(i_nodes + 1);

        vector<vector<ulong> > edges = vector<vector<ulong> >(i_nodes + 1, vector<ulong>(i_nodes + 1, 0));
        // time_t t = clock();
        for (int j = 0; j < i_edges; j++){
			fscanf(ifile, "%ld %ld", &i_head, &i_tail);
            edges[i_head][i_tail] = 1;
            edges[i_tail][i_head] = 1;
        }
        // time_t t1 = clock();
        for (int j = 0; j <= i_nodes; j++){
            for (int k1 = 0; k1 <= i_nodes; k1++){
                if(edges[j][k1] > 0)
                {
                    g[j].push_back(k1);
                }
            }
        }
        // time_t t2 = clock();
        // cout << (float)(t1 - t)/CLOCKS_PER_SEC << " " << (float)(t2 - t1)/CLOCKS_PER_SEC << endl;
        fscanf(ifile, "%ld", &i_start);
		cout << "Source node: " << i_start << endl;
		vector<ulong> v = bfs(g, i_start);
        // cout << v[i_start] << endl;
		for(ulong i = 1; i <= i_nodes; i++)
        {
            // if(i == i_start)
                // continue;
            if(v[i] == ULONG_MAX)
                cout << -1 << " ";
            else
                cout << v[i] << " ";
        }
        cout << endl;
	}
	return 0;
}
