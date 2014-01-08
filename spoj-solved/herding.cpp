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
const char coordinates[] = {'S', 'N', 'E', 'W'}; 
typedef vector<vector<int> > graph;
struct gnode {
	char value;
	int row;
	int column;
};
typedef struct gnode gnode;	


vector<gnode> read_data_nodes(FILE *f, int &rows, int &columns) {
	
	fscanf(f, "%d %d\n", &rows, &columns);
	vector<gnode> v_res(columns * rows);
	gnode graph_node;
	char *pch_line = new char[columns + 3];
	int k = 0;
	for (int i = 0; i < rows; i++)
	{
		fgets(pch_line, columns + 3, f);
		for (int j = 0; j < columns; j++)
		{
			graph_node.value = pch_line[j];
			graph_node.row = i;
			graph_node.column = j;
			v_res[k] = graph_node;
			k++;
		}
	}

	delete[] pch_line;
    return v_res;
}


vector<vector<char> > read_data(FILE *f) {
	int rows, columns;
	fscanf(f, "%d %d\n", &rows, &columns);
	vector<char> v_line(columns);
	vector<vector<char> > v_res(rows);
	char *pch_line = new char[columns + 3];
	for (int i = 0; i < rows; i++)
	{
		fgets(pch_line, columns + 3, f);
		//pch_line[columns] = '\0';
		//cout << pch_line << endl;
		for (int j = 0; j < columns; j++)
			v_line[j] = pch_line[j];
		//delete[] pch_line;
		v_res[i] = v_line;
	}
	delete[] pch_line;
    return v_res;
}

graph create(vector<vector<char> > &m, int rows, int columns ) {
	graph g = graph(rows * columns);
	int k = 0;
    for( int i = 0; i < rows; i++ )
    {
        for( int j = 0; j < columns; j++ )
        {
			if( m[i][j] == coordinates[0] ){
				g[k].push_back(k + columns);
				g[k + columns].push_back(k);
			}
			if( m[i][j] == coordinates[1] ){
				g[k].push_back(k - columns);
				g[k - columns].push_back(k);
			}
			if( m[i][j] == coordinates[2] ){
				g[k].push_back(k + 1);
				g[k + 1].push_back(k);
			}
			if( m[i][j] == coordinates[3] ){
				g[k].push_back(k - 1);
				g[k - 1].push_back(k);
			}
			k++;
        }
    }
    return g;
}

// void bfs( graph &g, int start_node, vector<bool> &discovered) {
// 	discovered[start_node] = true;
//     queue<int> q;
//     q.push(start_node);
//     int node;
// 	vector<int> neighbors;
//     vector<int>::iterator it;

//     while(q.size() > 0){
//         node = q.front();
//         q.pop();
// 		discovered[node] = true;
//         neighbors = g[node];

//         for(it = neighbors.begin(); it != neighbors.end(); it++) {
//             if( !discovered[*it]  ) {
// 				discovered[*it] = true;
//                 q.push(*it);
//             }
//         }
//     }

// }

int* get_neighbors(vector<vector<char> > &data, int node, int row, int column)
{
	int *n = new int[4];
	int rows = node / row; 
	int columns = node - node / row * row;
	memset(n, -1, 4 * sizeof(int));
	cout << rows << " " << columns << endl;
	if( data[rows][columns] == coordinates[1] || 
		(rows > 0 && data[rows - 1][columns] == coordinates[0]) )
		n[0] = node - column;
	if( data[rows][columns] == coordinates[0] || 
		(rows < row && data[rows + 1][columns] == coordinates[1]) )
		n[1] = node + column;
	if( data[rows][columns] == coordinates[2] || 
		(columns < column && data[rows][columns + 1] == coordinates[3]) )
		n[2] = node - 1;
	if( data[rows][columns] == coordinates[3] || 
		(columns > 0 && data[rows][columns - 1] == coordinates[2]) ) 
		n[3] = node + 1;


	return n;

}

void bfs(vector<gnode> &data, int start_node, vector<bool> &discovered, int rows, int columns  ) {
    
	discovered[start_node] = true;
    queue<int> q;
    q.push(start_node);
    int node;

    while(q.size() > 0){
        node = q.front();
        q.pop();
		discovered[node] = true;
		
		if(data[node].row < rows - 1 && !discovered[node + columns]) {
			if( data[node].value == coordinates[0] || // if value is south
				data[node + columns].value == coordinates[1] ) 
				q.push(node + columns);
		}
		
		if(data[node].row > 0 && !discovered[node - columns] ) {
			if( data[node].value == coordinates[1] || // if value is north
				data[node - columns].value == coordinates[0] ) 
				q.push(node - columns);
		}

		if(data[node].column < columns - 1 && !discovered[node + 1]) {
			if( data[node].value == coordinates[2] || // value is east -> 
			    data[node + 1].value == coordinates[3] ) // value for neighbor right is west <-
				q.push(node + 1);
		}

		if (data[node].column > 0 && !discovered[node - 1]) {
			if( data[node].value == coordinates[3] || // value is west <-
				data[node - 1].value == coordinates[2] ) // value for neighbor right is east ->
				q.push(node - 1);
		}
    }    
}

int main(int argc, char** argv) {
/* 	clock_t t1 = clock();
    vector<vector<char> > data = read_data(stdin);
    clock_t t11 = clock();
    cout << "read time: " << (float)(t11 - t1) << endl;
 */
 
	clock_t t1 = clock();
	int rows, columns;
    vector<gnode> data = read_data_nodes(stdin, rows, columns);
    clock_t t2 = clock();
    cout << "read time: " << (float)(t2 - t1) << endl; 

	vector<bool> discovered = vector<bool>(data.size()); 
	vector<bool>::iterator it;

	int groups = 0;
	for(size_t i = 0; i < discovered.size(); i++) {
		if( discovered[i] )
			continue;

		bfs(data, i, discovered, rows, columns);
		groups++;
	}
	cout << groups << endl;
	clock_t t3 = clock();
	cout << "calculation time: " << (float)(t3 - t2) << endl;
	
 
/*     int* n = get_neighbors(data, 0, 3, 4);

    printf("%d %d %d %d\n", n[0], n[1], n[2], n[3] );
    delete[] n;
    n = get_neighbors(data, 5, 3, 4);
    printf("%d %d %d %d\n", n[0], n[1], n[2], n[3] );
 */    
	// graph g = create(data, data.size(), data[0].size() );
    // clock_t t2 = clock();
    // cout << "create g time: " << (float)(t2 - t11) << endl;
	// vector<bool> discovered = vector<bool>(g.size()); 
	// vector<bool>::iterator it;

	// int groups = 0;
	// for(int i = 0; i < discovered.size(); i++) {
	// 	if( discovered[i] )
	// 		continue;
	// 	//cout << "Start BFS: " << i << endl;
	// 	bfs(g, i, discovered);
	// 	groups++;
	// }
	// cout << groups << endl;
	// clock_t t3 = clock();
	// cout << "calculation time: " << (float)(t3 - t2) << endl;
    return 0;
}