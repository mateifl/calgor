#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <queue>
#include <ctime>
#include <set>
#include <map>
using namespace std;

typedef unsigned int u_int;

typedef struct result {
	u_int sheep;
	u_int wolves;
	bool opened;
} result;

// This bfs must return the number of sheep, wolves and the processed nodes
result bfs(char **data, u_int start_node, vector<bool> &discovered, int rows, int columns  ) {
	discovered[start_node] = true;
    queue<int> q;
    q.push(start_node);
    int node;
	result r;
	r.sheep = 0;
	r.wolves = 0;
	r.opened = false;

	while (q.size() > 0) {
		node = q.front();
		q.pop();
		//discovered[node] = true;

		u_int node_row = node / columns;
		u_int node_column = node - (node_row * columns);
		//cout << "bfs: " << node << " " << node_row << " " << node_column << endl;
		// if it is a fence, skip the node 
		if (data[node_row][node_column] == '#')
			continue;
		if (data[node_row][node_column] == 'k')
			r.sheep += 1;
		if (data[node_row][node_column] == 'v')
			r.wolves += 1;

		if (node_row == rows - 1 || node_row == 0 || node_column == columns - 1 || node_column == 0)
			r.opened = true;

		// compute the neighbours
		if (node_row < rows - 1 && !discovered[node + columns] && data[node_row + 1][node_column] != '#') {
			q.push(node + columns);
			discovered[node + columns] = true;
		}
		if (node_row > 0 && !discovered[node - columns] && data[node_row - 1][node_column] != '#') {
			q.push(node - columns);
			discovered[node - columns] = true;
		}
		if( node_column < columns - 1 && !discovered[node + 1] && data[node_row][node_column + 1] != '#'){
			q.push(node + 1);
			discovered[node + 1] = true;
		}
		if (node_column > 0 && !discovered[node - 1] && data[node_row][node_column - 1] != '#') {
			q.push(node - 1);
			discovered[node - 1] = true;
		}
    }    

	return r;
}

int main(int argc, char** argv) {
    FILE *f = stdin;
	//FILE *f = fopen("koze.in", "r");
    u_int rows, columns;
    fscanf(f, "%d %d", &rows, &columns);
    
    char **table = new char*[rows];

    for (size_t j = 0; j < rows; j++)
    {
        table[j] = new char[columns];
        fscanf(f,"%s", table[j]);
        
    }
    // create a set to keep track of graph partitions
	u_int sheep = 0, wolves = 0;
    vector<bool> discovered_nodes(rows * columns);
	for (size_t i = 0; i < discovered_nodes.size(); i++)
	{
		u_int row = i / columns;
		u_int column = i - (row * columns);

		if( discovered_nodes[i] || table[row][column] == '#' )
			continue;
		result r = bfs(table, i, discovered_nodes, rows, columns);
		//cout << "r: " << r.sheep << " " << r.wolves << " " << (r.opened ? "true" : "false") << endl;	
		if( r.opened ){
			sheep += r.sheep;
			wolves += r.wolves;
		}
		else{
			if( r.sheep > r.wolves )
				sheep += r.sheep;
			else
				wolves += r.wolves;
		}
		
	}
	cout << sheep << " " << wolves << endl;
    delete[] table;
    return 0;
}