#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <queue>
#include <functional>
using namespace std;

struct edge {
	long tail;
	long value;
};

typedef map<string, long> string_int_map;
typedef edge edge;
typedef vector<vector<edge> > graph;
// first -> edge value, second - edge id.
typedef priority_queue<pair<long, long>, vector<pair<long, long> >, greater<pair<long, long> > > heap;

void update_heap(heap &nodes_heap, graph &g, long source_node, long path_value, vector<long> &v_not_visited) {
	vector<edge> edges = g[source_node];
	vector<edge>::iterator it;
	for(it = edges.begin(); it != edges.end(); it++)
	{
		if( v_not_visited[it->tail] > path_value + it->value )
		{
			nodes_heap.push(make_pair(path_value + it->value, it->tail));
			v_not_visited[it->tail] = path_value + it->value;
		}
	}
}

map<long, long> dijkstra(graph g, long source_node) {
	long MAX_INT = 1000000;
	// build the heap
	heap nodes_heap;
	// create a map with not visited nodes
	vector<long> v_not_visited(g.size());

	for(unsigned long i = 0; i < g.size(); i++)
	{
		if( i != source_node ){
			nodes_heap.push(make_pair(MAX_INT, i));
			v_not_visited[i] = MAX_INT;
		}
	}
	nodes_heap.push(make_pair(0, source_node));
	v_not_visited[source_node] = 0;
	// initialize the map that will store the shortest paths.

	map<long, long> m_shortest_path;
	m_shortest_path.insert(make_pair(source_node, 0));
	pair<long, long> node;
	while( nodes_heap.size() > 0) {
		node = nodes_heap.top();
		nodes_heap.pop();

		if( node.first == MAX_INT )
			break;
		else if( v_not_visited[node.second] < 0 )
			continue;
		else {
			m_shortest_path.insert(make_pair( node.second, node.first ));
			update_heap(nodes_heap, g, node.second, node.first, v_not_visited);
			v_not_visited[node.second] = -1;
		}

		// mark node as visited
		v_not_visited[node.second] = -1;
	}

	return m_shortest_path;
}

void parse_roads_line(char *pch_source, char* pch_destination, char* mid, graph &g, string_int_map &locations_map) {
	
	string str_source = string(pch_source), str_destination = string(pch_destination);
	long i_source_index = locations_map[str_source];
	if( i_source_index == 0)
	{
		i_source_index = locations_map.size();
		locations_map[str_source] = i_source_index;
	}

	long i_destination_index = locations_map[str_destination];

	if( i_destination_index == 0)
	{
		i_destination_index = locations_map.size();
		locations_map[str_destination] = i_destination_index;
	}

	//cout << i_source_index << " " << i_destination_index << endl;
	char pch_value[10];
	strncpy(pch_value, mid + 2, strlen(mid) - 2);
	if( mid[strlen(mid) - 1] == '>' )
	{
		edge e;
		e.tail = i_destination_index;
		e.value = atoi(pch_value);
		g[i_source_index].push_back(e);
	}
	if( mid[0] == '<' )
	{
		edge e;
		e.tail = i_source_index;
		e.value = atoi(pch_value);
		g[i_destination_index].push_back(e);
	}

}

void parse_roads_line(string &str_source, string &str_destination, string &str_mid, graph &g, string_int_map &locations_map) {

	long i_source_index = locations_map[str_source];
	if( i_source_index == 0)
	{
		i_source_index = locations_map.size();
		locations_map[str_source] = i_source_index;
	}

	long i_destination_index = locations_map[str_destination];

	if( i_destination_index == 0)
	{
		i_destination_index = locations_map.size();
		locations_map[str_destination] = i_destination_index;
	}

	string str_value = str_mid.substr(2, str_mid.size() - 4);
	if( str_mid[str_mid.size() - 1] == '>' )
	{
		edge e;
		e.tail = i_destination_index;
		e.value = atoi(str_value.c_str());
		g[i_source_index].push_back(e);
	}
	if( str_mid[0] == '<' )
	{
		edge e;
		e.tail = i_source_index;
		e.value = atoi(str_value.c_str());
		g[i_destination_index].push_back(e);
	}

}


int main(int argc, char **argv) {
//	clock_t t0 = clock();
	long i_locations, i_cars, i_roads;
	char *pch_line = new char[1024 * 200], *pch = new char[100];
	char *source = new char[100], *mid = new char[100], *end = new char[100]; 
	long x = 1;
	while(true) {
		int rs = scanf("%d %d %d\n", &i_locations, &i_cars, &i_roads);
		if(rs < 3)
			break;
		//cout << rs << endl;
//		cout << i_locations << " " << i_cars << " " << i_roads << endl;
		if(i_locations == 0 && i_cars == 0 && i_roads == 0)
			break;
/*		if(i_cars == 0)
		{
			printf("%d. %d\n", x, 0);
			x++;
			continue;
		}*/
		vector<int> v_cars(i_cars + 3);
		int i = 1;
		string_int_map m_locations_map;

		char* r = fgets(pch_line, 200*1024, stdin);
		if(r == NULL)
			break;
		pch = strtok(pch_line, "\n ");
		m_locations_map.insert(make_pair(string(pch), i));
		v_cars[0] = i;
		i++;
		string str_pch;
		int j = 1;
		while( (pch = strtok(NULL, "\n ")) != NULL ){
			str_pch = pch;
			int i_location_index = m_locations_map[str_pch];
			if( i_location_index == 0 )
			{
				m_locations_map[str_pch] = i;
				i_location_index = i;
				i++;
			}
			v_cars[j] = i_location_index;
			j++;
		}

		graph g = graph(i_locations + 1), g_rev = graph(i_locations + 1);

		string source, mid, end;
		for(long i = 0; i < i_roads; i++){
			r = fgets(pch_line, 200*1024, stdin);
			if(r == NULL)
				break;
			string line = pch_line;
			line.erase(line.size() - 1);
			source = line.substr(0, line.find_first_of(" "));
			mid = line.substr(line.find_first_of(" ") + 1, line.find_last_of(" ") - line.find_first_of(" ")  - 1);
			mid = mid.erase(0, mid.find_first_not_of(" "));
			mid = mid.erase(mid.find_last_not_of(" ") + 1 );
			end = line.substr(line.find_last_of(" ") + 1);
			parse_roads_line(source, end, mid, g, m_locations_map);
			parse_roads_line(end, source, mid, g_rev, m_locations_map);
		}

		map<long, long> path_values = dijkstra(g, 1);
		map<long, long> path_values_rev = dijkstra(g_rev, 1);
		int sum = 0;
		for(unsigned long ii = 1; ii < v_cars.size(); ii++ )
		{
			sum += path_values[v_cars[ii]] + path_values_rev[v_cars[ii]];
		}
		printf("%d. %d\n", x, sum);
		x++;
	}

//	clock_t t1 = clock();
//	cout << "time: " << (float)(t1 - t0)/CLOCKS_PER_SEC << endl;
	return 0;
}
