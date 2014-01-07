#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>
#include <queue>
#include <set>
#include <map>
using namespace std;
const char coordinates[] = {'S', 'N', 'E', 'W'}; 
typedef vector<vector<int> > graph;

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

graph create(vector<vector<char> > m, int rows, int columns ) {
    graph g = vector<vector<int> >(rows * columns);
	int k = 0;
    for( int i = 0; i < rows; i++ )
    {
        for( int j = 0; j < columns; j++ )
        {
			if( m[i][j] == coordinates[0] ){
				g[k].push_back(k + columns);
//				g[k + columns].push_back(k);
			}
			if( m[i][j] == coordinates[1] ){
				g[k].push_back(k - columns);
//				g[k - columns].push_back(k);
			}
			if( m[i][j] == coordinates[2] ){
				g[k].push_back(k + 1);
//				g[k + 1].push_back(k);
			}
			if( m[i][j] == coordinates[3] ){
				g[k].push_back(k - 1);
//				g[k - 1].push_back(k);
			}
			k++;
        }
    }
    return g;
}

void bfs( graph &g, int start_node, vector<bool> &discovered) {
	discovered[start_node] = true;
    queue<int> q;
    q.push(start_node);
    int node;
	vector<int> neighbors;
    vector<int>::iterator it;

    while(q.size() > 0){
        node = q.front();
        q.pop();
		discovered[node] = true;
        neighbors = g[node];

        for(it = neighbors.begin(); it != neighbors.end(); it++) {
            if( !discovered[*it]  ) {
				discovered[*it] = true;
                q.push(*it);
            }
        }
    }

}

int main(int argc, char** argv) {
    vector<vector<char> > data = read_data(stdin);
    graph g = create(data, data.size(), data[0].size() );

	vector<bool> discovered = vector<bool>(g.size()); 
	vector<bool>::iterator it;

	int groups = 0;
	for(int i = 0; i < discovered.size(); i++) {
		if( discovered[i] )
			continue;
		//cout << "Start BFS: " << i << endl;
		bfs(g, i, discovered);
		groups++;
	}
	cout << groups << endl;
    return 0;
}