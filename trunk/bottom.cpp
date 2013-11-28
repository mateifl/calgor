#include "bottom.h"
#include "util.h"

// This returns a tree with the 

graph dfs(graph &g, int start_node) {
    graph dfs_tree;
    stack<int> node_stack;
    node_stack.push(start_node);

    int node;

    vector<int> neighbors;
    vector<int>::iterator it;

    while(node_stack.size() > 0){
        node = node_stack.top();
        node_stack.pop();
        neighbors = g[node];

        dfs_tree[node] = vector<int>();
        for(it = neighbors.begin(); it != neighbors.end(); it++) {
            if( dfs_tree.find(*it) == dfs_tree.end() ){
                node_stack.push(*it);  
                dfs_tree[node].push_back(*it);
            }
        }
    }

    return dfs_tree;
}

void read_data(FILE *f, graph &g, graph &g_reversed) {

    int i_number_vertices, i_number_of_edges, i_start_vertex, i_end_vertex;
    char pch_line[512 * 100], *pch = new char[16];
    fscanf(f, "%d %d\n", &i_number_vertices, &i_number_of_edges);
    fgets(pch_line, 512 * 100, f);

    pch = strtok(pch_line, " ");
    cout << pch << endl;
    while( pch != NULL ){
        i_start_vertex = atol(pch);
        pch = strtok(NULL, " ");
        if( pch == NULL )
            break;
        i_end_vertex = atol(pch);
//        cout << "Direct: " << i_start_vertex << " " << i_end_vertex << endl;
//        cout << "Reverse: " << i_end_vertex << " " << i_start_vertex << endl;
        g[i_start_vertex].push_back(i_end_vertex);
        g_reversed[i_end_vertex].push_back(i_start_vertex);
        pch = strtok(NULL, " ");
    }

}

vector<graph> calculate_sccs( graph &g) {
    vector<graph> sccs;
    //graph g, g_rev;
    
    // call dfs on reversed edges
    // call dfs on original edges  
    return sccs;
}

int main() {
	graph g, g_rev;
	FILE *f;
	f = fopen("tc_bottom1.txt", "r");

	read_data(f, g, g_rev);
	cout << g.size() << " " << g_rev.size() << endl;
	return 0;
}