#include "bottom.h"
#include "util.h"

//#define DBG_PRINT 

/* Parameters:
	g - graph in adjacency list representation
	start_node - start node for DFS
	processed_node - map with the status of every node: 0 - not visited, 1 - visited (node visited but not every neighbour), 
	2 - processed (the node and everyone of it's negihbours have been visited).
	visitor - object used to gather data related to the DFS.
*/
template <typename T> void generic_dfs(map<T, vector<T> > g, T start_node, map<T, short> &processed_nodes, dfs_visitor<T> *visitor) {
	stack<T> node_stack;
    node_stack.push(start_node);
	T node;

	vector<T> neighbors;
    typename vector<T>::iterator it;
	vector<T> nodes;

    while(node_stack.size() > 0){
		nodes.clear();
        node = node_stack.top();
//		if(processed_nodes[node] == 2)
//			continue;
#ifdef DBG_PRINT
		cout << "Proc. node " << node << endl;
#endif
		// mark node as discovered
		processed_nodes[node] = 1;
		// get the neighbours
        neighbors = g[node];
		bool continue_flag = false;

		for(it = neighbors.begin(); it != neighbors.end(); it++) {
			short node_state = processed_nodes[*it];

			if( node_state == 2 )
				continue;
			else if(node_state == 0)
			{
				processed_nodes[*it] = 1;
				node_stack.push(*it);
				continue_flag = true;
				break;
			}
		}

		if(continue_flag)
			continue;
		// node processed
		processed_nodes[node] = 2;
		node_stack.pop();
		nodes.push_back(node);
		nodes.push_back(start_node);
		visitor->visit(nodes);
    }
}

void read_edge_by_line(FILE *f, graph &g, graph &g_reversed) {
	int i_number_vertices, i_number_of_edges, i_start_vertex, i_end_vertex;
	char pch_line[128], *pch;// = new char[16];
	fscanf(f, "%d %d\n", &i_number_vertices, &i_number_of_edges);
	for(int i = 0; i < i_number_of_edges; i++)
	{
		fgets(pch_line, 128, f);
		pch = strtok(pch_line, " ");
		i_start_vertex = atol(pch);
        pch = strtok(NULL, " \n");
        i_end_vertex = atol(pch);
        g[i_start_vertex].push_back(i_end_vertex);
        g_reversed[i_end_vertex].push_back(i_start_vertex);
	}
}

void read_data(FILE *f, graph &g, graph &g_reversed) {

    int i_number_vertices, i_number_of_edges, i_start_vertex, i_end_vertex;
    char pch_line[512 * 100], *pch = new char[16];
    fscanf(f, "%d %d\n", &i_number_vertices, &i_number_of_edges);
    fgets(pch_line, 512 * 100, f);

    pch = strtok(pch_line, " ");
    while( pch != NULL ){
        i_start_vertex = atol(pch);
        pch = strtok(NULL, " ");
        if( pch == NULL )
            break;
        i_end_vertex = atol(pch);
        g[i_start_vertex].push_back(i_end_vertex);
        g_reversed[i_end_vertex].push_back(i_start_vertex);
        pch = strtok(NULL, " ");
    }
}

/*
map<int, int> calculate_sccs( graph &g, graph &g_reversed) {
	// run dfs on the reversed graph
	finishing_times_visitor<int> *v = new finishing_times_visitor<int>();
	map<int, vector<int> >::iterator it;
	map<int, short> processed_nodes;
	for(it = g_reversed.begin(); it != g_reversed.end(); it++)
	{
		if(processed_nodes[it->first] == 2)
			continue;
		generic_dfs(g_reversed, it->first, processed_nodes, v);
		
	}
	vector<int> finishing_times = v->finish_times();

	delete v;

#ifdef DBG_PRINT
	vector<int>::iterator itv;
	cout << "Finishing times calculated" << endl;
	for_each(finishing_times.begin(), finishing_times.end(), print<int>);
	cout << endl;
#endif

	// run dfs on the initial graph in order of the finishing times

	sccs_leader_visitor<int> *v2 = new sccs_leader_visitor<int>();
	vector<int>::reverse_iterator rit;
	processed_nodes.clear();
	for(rit = finishing_times.rbegin(); rit != finishing_times.rend(); ++rit){
		if(processed_nodes[*rit] == 2)
			continue;

		generic_dfs(g, *rit, processed_nodes, v2);
	}
	map<int, int> leaders = v2->leaders();
	delete v2;

	return leaders;
}
*/

int main() {
	graph g, g_rev;
	FILE *f;
	f = fopen("edges5000_1_res_70.txt", "r");
	read_edge_by_line(f, g, g_rev);

#ifdef DBG_PRINT
	cout << "Reversed graph:" << endl;
	print_adjacency_list(g_rev);
	cout << endl;
#endif
/*	
	map<int, vector<int> >::iterator it_map;
	vector<int>::iterator it_vect;
	finishing_times_visitor<int> *v = new finishing_times_visitor<int>();
	map<int, short> processed_nodes;
	generic_dfs(g_rev, 1, processed_nodes, v);
	vector<int> finish_times = v->finish_times();
	delete v;
*/
//    print_graph_edges(g_rev);
	clock_t t1 = clock();
	map<int, int> leaders = calculate_sccs(g, g_rev);
    
	map<int, int>::iterator it;
    map<int, vector<int> > sccs_groups;

	for(it = leaders.begin(); it != leaders.end();  it++) 
        sccs_groups[it->second].push_back(it->first);
    
    clock_t t2 = clock();
    cout << sccs_groups.size() << endl;

    cout << (float)(t2 - t1)/CLOCKS_PER_SEC << endl;

    return 0;
}