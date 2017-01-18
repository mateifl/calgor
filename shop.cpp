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

struct edge {
	u_int head;
	u_int tail;
	u_int value;
	u_int heap_value;
};

typedef edge edge;
typedef vector< vector<edge> > graph;

graph create(char **pch, u_int rows, u_int columns) {
    graph g(rows * columns);

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
			if (pch[i][j] == 'X')
				continue;

			if(i < (rows - 1)) {
				edge e;
				char v = pch[i + 1][j];
				e.head = i * columns + j;
				e.tail = (i + 1) * columns + j;
				e.value = atoi(&v);
				g[i * columns + j].push_back(e);
				e.head = (i + 1) * columns + j;
				e.tail = i * columns + j;
				g[(i + 1) * columns + j].push_back(e);
			}

			if (i > 0) {
				edge e;
				char v = pch[i - 1][j];
				e.head = i * columns + j;
				e.tail = (i - 1) * columns + j;
				e.value = atoi(&v);
				g[e.head].push_back(e);
				e.head = (i - 1) * columns + j;
				e.tail = i * columns + j;
				g[e.head].push_back(e);
			}

			if (j < (columns - 1)) {
				edge e;
				char v = pch[i][j + 1];
				e.head = i * columns + j;
				e.tail = i * columns + j + 1;
				e.value = atoi(&v);
				g[e.head].push_back(e);
				e.head = i * columns + j + 1;
				e.tail = i * columns + j;
				g[e.head].push_back(e);
			}

			if (j > 0) {
				edge e;
				char v = pch[i][j - 1];
				e.head = i * columns + j;
				e.tail = (i - 1) * columns + j;
				e.value = atoi(&v);
				g[e.head].push_back(e);
				e.head = (i - 1) * columns + j;
				e.tail = i * columns + j;
				g[e.head].push_back(e);
			}
		}
    }
    return g;
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


		delete[] pch;
    }
    return 0;
}