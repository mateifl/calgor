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
};

typedef edge edge;

template<class T> struct greater_edge : binary_function<T, T, bool> {
	bool operator()(const T& x, const T& y) const {
		return x.value > y.value;
	}
};

typedef priority_queue<edge, vector<edge>, greater_edge<edge> > heap;

int dijkstra(char **g, u_int start, u_int dest, u_int rows, u_int columns) {
	int MAX_INT = INT_MAX - 100000;
	u_int nodes = rows * columns;
	vector<u_int> path_values = vector<u_int>(nodes, MAX_INT);
	vector<bool> v_bool_visited = vector<bool>(nodes);
	v_bool_visited[start] = true;
	heap h;

	u_int start_row = start / rows;
	u_int start_column = start - (start / rows);

	if (start_row > 0)
	{
		edge e; 
		e.head = start;
		e.tail = start - columns;
		e.value = atoi(&g[start_row][start_column]);
		h.push(e);

	}

	if (start_row < rows - 1) {

		edge e;
		e.head = start;
		e.tail = start + columns;
		e.value = atoi(&g[start_row][start_column]);
		h.push(e);
	}


	return 0;
}


int main(int argc, char** argv) {
    u_int rows, columns;
    FILE *f = fopen("tc_shop1.in", "r");
    // FILE *f = stdin;
	while(true)
    {
		fscanf(f, "%d %d", &rows, &columns);
		if(rows == 0 && columns == 0)
			break;
        int start = 0, end = 0;
        char **pch = new char*[rows];

        // char buffer[21];
        for (size_t j = 0; j < rows; j++)
        {
            pch[j] = new char[columns + 5];
            fscanf(f, "%s", pch[j]);
			char *s =  strchr(pch, 'S');
			if(s != NULL)
				start = pch[j] - s + 1;
			char *d =  strchr(pch, 'D');
			if(s != NULL)
				end = pch[j] - d + 1;

        }

        //graph g = create(pch, rows, columns);
		delete[] pch;
    }
    return 0;
}