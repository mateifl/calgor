#include "bottom.h"
#include "util.h"

// This returns a tree with the 

template <typename T> class  dfs_visitor {
public:
    virtual void visit(T node) = 0;
};

class finishing_times_visitor : public dfs_visitor<int> {
public:
	finishing_times_visitor() {
		mi_finishing_time = 0;
	}

	map<int, int> finish_times(){
		return mm_finishing_times;
	}

    virtual void visit(int node);
private:
    map<int, int> mm_finishing_times;
	int mi_finishing_time;
};

void finishing_times_visitor::visit(int node){
	mm_finishing_times.insert(make_pair(node, mi_finishing_time));
	mi_finishing_time += 1;
}

class dfs_tree_visitor : public dfs_visitor<int> {
public:

	graph tree_graph(){
		return tree;
	}

	virtual void visit(int node){};
private:
	graph tree;
};




template <typename T> void generic_dfs(map<T, vector<T> > g, T start_node, dfs_visitor<T> *visitor) {
	stack<T> node_stack;
    node_stack.push(start_node);
    set<T> visited_nodes;
    visited_nodes.insert(start_node);
    T node;

	vector<T> neighbors;
    vector<T>::iterator it;
	
    while(node_stack.size() > 0){
        node = node_stack.top();
        node_stack.pop();
        neighbors = g[node];
		visitor->visit(node);
        for(it = neighbors.begin(); it != neighbors.end(); it++) {
            if( visited_nodes.find(*it) == visited_nodes.end() ){
                node_stack.push(*it);  
                visited_nodes.insert(*it);
            }
        }
    }
}

graph dfs(graph &g, int start_node) {
    graph dfs_tree;
    stack<int> node_stack;
    node_stack.push(start_node);
    set<int> visited_nodes;
    visited_nodes.insert(start_node);
    int node;

    vector<int> neighbors;
    vector<int>::iterator it;

    while(node_stack.size() > 0){
        node = node_stack.top();
        node_stack.pop();
        neighbors = g[node];

        dfs_tree[node] = vector<int>();
        for(it = neighbors.begin(); it != neighbors.end(); it++) {
            if( visited_nodes.find(*it) == visited_nodes.end() ){
                node_stack.push(*it);  
                dfs_tree[node].push_back(*it);
                visited_nodes.insert(*it);
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

vector<vector<int> > calculate_sccs( graph &g, graph &g_reversed) {
    vector<vector<int> > sccs;



    return sccs;
}

int main() {
	graph g, g_rev;
	FILE *f;
	f = fopen("tc_bottom1.txt", "r");

	read_data(f, g, g_rev);

	// cout << g.size() << " " << g_rev.size() << endl;
    cout << "Data read!" << endl;
    
    print_graph_edges(g_rev);
	finishing_times_visitor *v = new finishing_times_visitor();
	generic_dfs(g_rev, 1, v); 
    cout << "First dfs applied" << endl;
    
	map<int, int> tree = v->finish_times();
	map<int, int>::iterator it;

	for(it = tree.begin(); it != tree.end();  it++)
	{
		cout << it->first << " " << it->second << endl;
	}
    /*
    dfs_tree = dfs(g_rev, 1);
    cout << "Second dfs applied" << endl;
    print_graph_edges(dfs_tree);
    */
    return 0;
}