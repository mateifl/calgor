#include "bottom.h"
#include "util.h"

#define DBG_PRINT 

template <typename T> class  dfs_visitor {
public:
    virtual void visit(vector<T> nodes) = 0;
};

class finishing_times_visitor : public dfs_visitor<int> {
public:
	vector<int> finish_times(){
		return mv_finishing_times;
	}

    virtual void visit(vector<int> nodes) {
		mv_finishing_times.push_back(nodes[0]);
	}
private:
    vector<int> mv_finishing_times;
};

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
    vector<T>::iterator it;
	vector<T> nodes;

    while(node_stack.size() > 0){
		nodes.clear();
        node = node_stack.top();
		cout << "Proc. node " << node << endl;
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

/*
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
*/

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
	map<int, short> processed_nodes;
	for(it = g_reversed.begin(); it != g_reversed.end(); it++)
	{
		generic_dfs(g_reversed, it->first, processed_nodes, v);
		
	}
	vector<int> finishing_times = v->finish_times();

	delete v;

#ifdef DBG_PRINT
#endif

	// run dfs on the initial graph in order of the finishing times

	sccs_leader_visitor *v2 = new sccs_leader_visitor();
	vector<int>::reverse_iterator rit;
	processed_nodes.clear();
	for(rit = finishing_times.rbegin(); rit != finishing_times.rend(); ++rit)
		generic_dfs(g_reversed, *rit, processed_nodes, v2);

	map<int, int> leaders = v2->leaders();
	delete v2;

	return leaders;
}

int main() {
	graph g, g_rev;
	FILE *f;
	f = fopen("etest.txt", "r");

	read_edge_by_line(f, g, g_rev);

#ifdef DBG_PRINT
	cout << "Reversed graph:" << endl;
	print_adjacency_list(g_rev);
	cout << endl;
#endif

	map<int, vector<int> >::iterator it_map;
	vector<int>::iterator it_vect;
	map<int, short> processed_nodes;
	for(it_map = g_rev.begin(); it_map != g_rev.end(); it_map++)
	{
		for(it_vect = it_map->second.begin(); it_vect != it_map->second.end(); it_vect++)
			processed_nodes[*it_vect] = 0;
	}

	finishing_times_visitor *v = new finishing_times_visitor();
	generic_dfs(g, 13, processed_nodes, v);
	vector<int> finish_times = v->finish_times();


	for(it_vect = finish_times.begin(); it_vect != finish_times.end();  it_vect++)
		cout << *it_vect << " " << endl;

	delete v;
//    print_graph_edges(g_rev);
	/*
	map<int, int> leaders = calculate_sccs(g, g_rev);
	map<int, int>::iterator it;

	for(it = leaders.begin(); it != leaders.end();  it++)
		cout << it->first << " " << it->second << endl;
	*/
    return 0;
}