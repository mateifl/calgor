#include "bottom.h"
#include "util.h"

#define DBG_PRINT 

// This returns a tree with the 

template <typename T> class  dfs_visitor {
public:
    virtual void visit(vector<T> nodes) = 0;
};

class finishing_times_visitor : public dfs_visitor<int> {
public:
	finishing_times_visitor() {
		mi_finishing_time = 1;
	}

	map<int, int> finish_times(){
		return mm_finishing_times;
	}

    virtual void visit(vector<int> nodes);
private:
    map<int, int> mm_finishing_times;
	int mi_finishing_time;
};

void finishing_times_visitor::visit(vector<int> nodes){
	mm_finishing_times.insert(make_pair(nodes[0], mi_finishing_time));
	mi_finishing_time += 1;
}

class sccs_leader_visitor : public dfs_visitor<int> {
public:

	map<int, int> leaders() { 
		return mm_leaders;
	}
	virtual void visit(vector<int> nodes){
		mm_leaders.insert(make_pair(nodes[0], nodes[1]));
	};
private:
	map<int, int> mm_leaders;
};


template <typename T> void generic_dfs(map<T, vector<T> > g, T start_node, dfs_visitor<T> *visitor) {
	stack<T> node_stack;
    node_stack.push(start_node);
    set<T> processed_nodes;

	T node;

	vector<T> neighbors;
    vector<T>::iterator it;
	vector<T> nodes;

    while(node_stack.size() > 0){
		nodes.clear();
        node = node_stack.top();
        node_stack.pop();

		if( processed_nodes.find( node ) != processed_nodes.end() )
			continue;

		// build and populate the visitor
		nodes.push_back(node);
		nodes.push_back(start_node);
		visitor->visit(nodes);
		// put neighbours in the stack
        neighbors = g[node];
		for(it = neighbors.begin(); it != neighbors.end(); it++)
			if( processed_nodes.find(*it) == processed_nodes.end() ) 
				node_stack.push(*it);
		// node processed
		processed_nodes.insert(node);
    }
}

graph dfs(graph &g, int start_node) {
    graph dfs_tree;
    stack<int> node_stack;
    node_stack.push(start_node);
    set<int> processed_nodes;
    processed_nodes.insert(start_node);
    int node;

    vector<int> neighbors;
    vector<int>::iterator it;

    while(node_stack.size() > 0){
        node = node_stack.top();
        node_stack.pop();
        neighbors = g[node];

        dfs_tree[node] = vector<int>();
        for(it = neighbors.begin(); it != neighbors.end(); it++) {
            if( processed_nodes.find(*it) == processed_nodes.end() ){
                node_stack.push(*it);  
                dfs_tree[node].push_back(*it);
                processed_nodes.insert(*it);
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

map<int, int> calculate_sccs( graph &g, graph &g_reversed) {
	// run dfs on the reversed graph
	finishing_times_visitor *v = new finishing_times_visitor();
	map<int, vector<int> >::iterator it;
	map<int, int> finish_times, tmp_map;
	for(it = g_reversed.begin(); it != g_reversed.end(); it++)
	{
		if( finish_times.find(it->first) == finish_times.end() )
		{
			generic_dfs(g_reversed, it->first, v); 
			tmp_map = v->finish_times();
			finish_times.insert(tmp_map.begin(), tmp_map.end());
		}
		
	}
	delete v;

#ifdef DBG_PRINT
	for( map<int, int>::iterator itd = finish_times.begin(); itd != finish_times.end(); itd++)
		cout << itd->first << " " << itd->second << endl;
#endif

	// run dfs on the initial graph in order of the finishing times

	map<int, int>::iterator it2;
	map<int, int> finish_times_rev; 
	for(it2 = finish_times.begin(); it2 != finish_times.end(); it2++)
		finish_times_rev.insert(make_pair(it2->second, it2->first));

	sccs_leader_visitor *v2 = new sccs_leader_visitor();
	map<int, int> leaders;
	map<int, int>::reverse_iterator rit;
	for(rit = finish_times.rbegin(); rit != finish_times.rend(); ++rit)
	{
		if( leaders.find(rit->second) == leaders.end() )
		{
#ifdef DBG_PRINT
			cout << "Processing node " << rit->second << " with finishing time: " << rit->first << endl;  
#endif
			generic_dfs(g_reversed, rit->second, v2); 
			tmp_map = v2->leaders();
			leaders.insert(tmp_map.begin(), tmp_map.end());
		}

	}
	return leaders;
}

int main() {
	graph g, g_rev;
	FILE *f;
	f = fopen("tc_bottom1.txt", "r");

	read_data(f, g, g_rev);
    cout << "Data read!" << endl;
#ifdef DBG_PRINT
	print_adjacency_list(g_rev);
	cout << endl;
#endif
	finishing_times_visitor *v = new finishing_times_visitor();
	generic_dfs(g, 1, v);
	map<int, int> finish_times = v->finish_times();
//	map<int, int>::iterator it;

//	for(it = finish_times.begin(); it != finish_times.end();  it++)
//		cout << it->first << " " << it->second << endl;

	delete v;
//    print_graph_edges(g_rev);
	
	map<int, int> leaders = calculate_sccs(g, g_rev);
	map<int, int>::iterator it;

	for(it = leaders.begin(); it != leaders.end();  it++)
		cout << it->first << " " << it->second << endl;
	
    return 0;
}