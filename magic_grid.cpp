// http://www.spoj.com/problems/AMR11A/

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
typedef unsigned int uint;
struct edge {
	uint head;
	uint tail;
	int value;
};

typedef edge edge;	
typedef vector<vector<edge> > graph;

void print_vector(vector<int> v) {
	for (ulong i = 0; i < v.size(); i++)
		cout << v[i] << " ";
	cout << "----" << endl;
}

/*
int main(int argc, char **argv) {

	ulong l_head, l_tail, l_weight, l_source_node;
	uint l_nodes_number, l_edges_number, ui_testcases, ui_rows, ui_columns;
	int i_edge_value;
	FILE *f = fopen("tc_mg1.txt", "r");
	fscanf(f, "%d", &ui_testcases);
	cout << ui_testcases << endl;
	for (uint t = 0; t < ui_testcases; t++) {
		fscanf(f, "%d %d", &ui_rows, &ui_columns);
		vector< vector<int> > m(ui_rows);
		
		for (uint r = 0; r < ui_rows; r++) {
			cout << r << endl;
			vector<int> row(ui_columns);
			for (uint c = 0; c < ui_columns; c++) {
				fscanf(f, "%d", &i_edge_value);
				row[c] = i_edge_value;
			}
			m[r] = row;
		}
	}
	fclose(f);
	return 0;
}
*/