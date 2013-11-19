#include "bottom.h"
#include "util.h"


int main(int argc, char** argv) {

	graph g;
	//vector<int> v1, v2, v3;
	
	g[1].push_back(2);
	g[1].push_back(3);
	g[2].push_back(3);
	g[2].push_back(4);
	g[3].push_back(5);
	g[3].push_back(6);
	g[5].push_back(6);
	graph g2 = dfs(g, 1);

	print_graph_edges(g2);

    return 0;
}