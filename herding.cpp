#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;
char coordinates[] = {'S', 'N', 'E', 'W'}; 
typedef vector<vector<int> > graph;

vector<vector<char> > read_data(FILE *f) {
	int rows, columns;
	fscanf(f, "%d %d\n", &rows, &columns);
	vector<char> v_line(columns);
	vector<vector<char> > v_res(rows);
	char *pch_line = new char[columns + 1];
	for (int i = 0; i <= rows; i++)
	{
		fgets(pch_line, columns + 1, f);
		pch_line[columns] = '\0';
		cout << pch_line << endl;
		for (int j = 0; j < columns; j++)
			v_line[j] = pch_line[j];
		v_res[i] = v_line;
	}

    return v_res;
}

graph create(vector<vector<char> > m, int rows, int columns ) {
    graph g = vector<vector<int> >(rows * columns);
	int k = 0;
    for( int i = 0; i < rows; i++ )
    {
        for( int j = 0; j < columns; j++ )
        {
			if( m[i][j] == coordinates[0] )
				g[k].push_back( k + columns);
			else if( m[i][j] == coordinates[1] )
				g[k].push_back( k - columns);
			if( m[i][j] == coordinates[0] )
				g[k].push_back( k + 1);
			if( m[i][j] == coordinates[0] )
				g[k].push_back( k - 1);
			k++;
        }
    }
    
}


int main(int argc, char** argv) {
    vector<vector<char> > data = read_data(stdin);
    cout << data.size() << " " << data[0].size() << endl;
    graph g = create(data, data.size(), data[0].size() );
    return 0;
}

