#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

typedef vector<vector<int> > graph;

vector<vector<char> > read_data(FILE *f) {
	int rows, columns;
	fscanf(f, "%d %d\n", &rows, &columns);
	vector<char> v_line(columns);
	vector<vector<char> > v_res(rows);
	char pch_line[1024];
	for (int i = 0; i < rows; i++)
	{
		fgets(pch_line, 1001, f);
		for (int j = 0; j < columns; j++)
		{
			v_line[j] = pch_line[j];
		}
	}

    return v_res;
}

graph create(vector<vector<char> > m, int rows, int columns ) {
    graph g = vector<vector<int> >(rows * columns);
    for( int i = 0; i < rows; i++ )
    {
        for( int j = 0; j < columns; j++ )
        {
            
        }
    }
    
}


int main(int argc, char** argv) {
    
    return 0;
}

