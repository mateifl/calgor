// http://www.spoj.com/problems/SHOP/

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <queue>
#include <ctime>
#include <set>
using namespace std;
typedef unsigned int u_int;
typedef vector< vector<int> > graph;


graph create(char **pch, u_int rows, u_int columns, vector<u_int> &edges) {
    graph g(rows * columns);

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            if(pch[i][j] == '.')
            {
                if(i == 0 || j == 0 || i == (rows - 1) || j == (columns - 1))
                    edges.push_back(i * columns + j);
                
                if(j > 0 && pch[i][j - 1] == '.')
                    g[i * columns + j].push_back(i * columns + j - 1);
                if(j < (columns - 1) && pch[i][j + 1] == '.') 
                    g[i * columns + j].push_back(i * columns + j + 1);
                if(i > 0 && pch[i - 1][j] == '.') 
                    g[i * columns + j].push_back((i - 1) * columns + j);
                if(i < (rows - 1) && pch[i + 1][j] == '.') 
                    g[i * columns + j].push_back((i + 1) * columns + j);
            }    
        }
    }
    return g;
}

bool bfs(graph g, u_int start_node, u_int end_node) {
	vector<bool> discovered(g.size());
	discovered[start_node] = true;
	queue<int> q;
	q.push(start_node);
	int node;

	while (q.size() > 0) {
		node = q.front();
		if (node == end_node)
			return true;
		q.pop();
		discovered[node] = true;

		for (u_int i = 0; i < g[node].size(); i++) {
			if( !discovered[g[node][i]] )
				q.push(g[node][i]);
		}
	}
	return false;
}


int main(int argc, char** argv) {
    u_int rows, columns, testcases;
    // FILE *f = fopen("tc_makemaze1.in", "r");
    FILE *f = stdin;
    fscanf(f, "%d", &testcases);
    for (size_t i = 0; i < testcases; i++)
    {
        vector<int> entry_points;
        fscanf(f, "%d %d", &rows, &columns);
        char **pch = new char*[rows];

        // char buffer[21];
        for (size_t j = 0; j < rows; j++)
        {
            pch[j] = new char[columns + 5];
            fscanf(f, "%s", pch[j]);
        }

        vector<u_int> edges;
        graph g = create(pch, rows, columns, edges);
		if (edges.size() != 2) {
			printf("invalid\n");
			continue;
		}
		bool result = bfs(g, edges[0], edges[1]);
		if(result)
			printf("valid\n");
		else
			printf("invalid\n");
		delete[] pch;
    }
    return 0;
}