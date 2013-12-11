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


void read_edge_by_line(FILE *f, graph2 &g, graph2 &g_reversed) {
	int i_number_vertices, i_number_of_edges, j;
	char pch_line[128], *pch;// = new char[16];
	fscanf(f, "%d %d\n", &i_number_vertices, &i_number_of_edges);
    vector<int> data(2 * i_number_of_edges);

	for(int i = 0; i < 2 * i_number_of_edges; i += 2)
	{
		fgets(pch_line, 128, f);
		pch = strtok(pch_line, " ");
		j = atol(pch);
        data[i] = j;
        pch = strtok(NULL, " \n");
        j = atol(pch);
        data[i + 1] = j;
	}

    int size_vector = *max_element( data.begin(), data.end() );
    g = graph2(size_vector + 1);
    g_reversed = graph2(size_vector + 1);
    for(int i = 0; i < 2 * i_number_of_edges; i += 2) {
        if( g[data[i]] == NULL )
            g[data[i]] = new vector<int>();
        g[data[i]]->push_back(data[i + 1]);
        if( g_reversed[data[i + 1]] == NULL )
            g_reversed[data[i + 1]] = new vector<int>();
        g_reversed[data[i + 1]]->push_back(data[i]);
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

int main(int argc, char** argv) {
	graph2 g, g_rev;
	FILE *f;
	clock_t t1 = clock();
	f = fopen("edges5000_1_res_70.txt", "r");
	read_edge_by_line(f, g, g_rev);
    clock_t t2 = clock();
    cout << "Read time: " << (float)(t2 - t1)/CLOCKS_PER_SEC << endl;
	map<int, int> leaders = calculate_sccs<graph2, int>(g, g_rev);
    
	map<int, int>::iterator it;
    map<int, vector<int> > sccs_groups;
    clock_t t3 = clock();
    cout << "sccs time: " << (float)(t3 - t2)/CLOCKS_PER_SEC << endl;
	for(it = leaders.begin(); it != leaders.end();  it++) 
        sccs_groups[it->second].push_back(it->first);
    
    clock_t t4 = clock();
    cout << "Read time: " << (float)(t4 - t3)/CLOCKS_PER_SEC << endl;
    cout << sccs_groups.size() << endl;
    return 0;
}