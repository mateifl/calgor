#include <iostream>
#include <cmath>
#include <vector>
#include <cstdio>
#include <stack>
#include <ctime>
#include <cstring>
using namespace std;

typedef unsigned int u_int;
typedef struct point
{
    u_int row;
    u_int column;
    char c;
    u_int last_index;
    point(): row(-1), column(-1), last_index(-1) {}
} point;
// typedef vector< vector<u_int> > graph;

vector<char> alliswell(10);

vector<point> get_neighbors(char **g, u_int row, u_int column, u_int rows, u_int columns, u_int last_index) {
    vector<point> result(4);
    if( row > 0 && g[row - 1][column] == alliswell[last_index + 1]) {
        // north
        result[0].row = row - 1;
        result[0].column = column;
        result[0].c = g[row - 1][column];
        result[0].last_index = last_index + 1;
    }

    if( column < (columns - 1) && g[row][column + 1] == alliswell[last_index + 1]) {
        // east
        result[1].row = row;
        result[1].column = column + 1;
        result[1].c = g[row][column + 1];
        result[1].last_index = last_index + 1;
    }

    if( row < (rows - 1) && g[row + 1][column] == alliswell[last_index + 1]) {
        // south
        result[2].row = row + 1;
        result[2].column = column;
        result[2].c = g[row + 1][column];
        result[2].last_index = last_index + 1;
    }


    if( column > 0 && g[row][column - 1] == alliswell[last_index + 1]) {
        // west
        result[3].row = row;
        result[3].column = column - 1;
        result[3].c = g[row][column - 1];
        result[3].last_index = last_index + 1;
    }

    return result;
}

bool dfs(char** g, point &start_node, u_int rows, u_int columns){

    stack<point> node_stack;
    node_stack.push(start_node);
	point node;
    vector< vector <short> > processed_nodes(rows);
    for (size_t i = 0; i < rows; i++) 
        processed_nodes[i] = vector<short>(columns, 0);

	processed_nodes[start_node.row][start_node.column] = 1;
    
    while(node_stack.size() > 0){
        node = node_stack.top();
		// mark node as discovered
		// processed_nodes[node] = 1;
		// get the neighbors
		bool continue_flag = false;
        vector<point> neighbors = get_neighbors(g, node.row, node.column, rows, columns, node.last_index);

        for(u_int i = 0; i < neighbors.size(); i++) {
            if(neighbors[i].last_index == -1)
                continue;
            if(neighbors[i].last_index == 9)
                return true;
            u_int nr = neighbors[i].row, nc = neighbors[i].column;
            short node_state = processed_nodes[nr][nc];

			if( node_state == 2 ) // node and all the neighbors have been processed 
				continue;
			else if(node_state == 0)
			{
				processed_nodes[nr][nc] = 1; // node is entering processing (state = 1) -> discovered
				node_stack.push(neighbors[i]);
				continue_flag = true;
				break;
			}
		}

		if(continue_flag)
			continue;
		// node processed
		processed_nodes[node.row][node.column] = 2;
		node_stack.pop();
    }
    return false;
}

int main(int argc, char** argv) {
    alliswell[0] = 'A';
    alliswell[1] = 'L';
    alliswell[2] = 'L';
    alliswell[3] = 'I';
    alliswell[4] = 'Z';
    alliswell[5] = 'Z';
    alliswell[6] = 'W';
    alliswell[7] = 'E';
    alliswell[8] = 'L';
    alliswell[9] = 'L';

    //FILE *f = stdin;
	FILE *f = fopen("alliswell.in", "r");
    vector<point> points;
    u_int testcases_number, rows, columns;
    fscanf(f, "%d", &testcases_number);
	
    for (size_t i = 0; i < testcases_number; i++)
    {

        fscanf(f, "%d %d", &rows, &columns);
		
		char **table = new char*[rows];
        for (size_t j = 0; j < rows; j++)
        {
            table[j] = new char[columns];
            fscanf(f,"%s", table[j]);
			//cout << table[j] << endl;
            // find 'A'
            for (size_t k = 0; k < columns; k++)
            {
				//cout << table[j][k] << endl;
                if(table[j][k] == 'A')
                {
                    point s;
                    s.row = j;
                    s.column = k;
                    s.c = 'A';
                    s.last_index = 0;
                    points.push_back(s);
                }
            }
        }
		for (size_t k = 0; k < points.size(); k++)
		{
			bool r = dfs(table, points[k], rows, columns);
			if(r)
				cout << "YES" << endl;
		}

        delete[] table;
    }

    return 0;
}