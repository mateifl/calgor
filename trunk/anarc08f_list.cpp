#include <ctime>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;

struct edge {
	int head;
	int tail;
	int value;
	int heap_value;
};

typedef map<string, int> string_int_map;
typedef edge edge;
typedef vector<vector<edge> > graph;
typedef unsigned int uint;
template<class T> struct greater_edge: binary_function<T, T, bool> {
	bool operator()(const T& x, const T& y) const {
		return x.heap_value > y.heap_value;
	}
};
typedef priority_queue<edge, vector<edge>, greater_edge<edge> > heap;

vector<int> dijkstra(graph g, int source_node) {

	// the heap
	heap nodes_heap;
	// create a map with not visited nodes
	vector<bool> v_bool_visited = vector<bool>(g.size());
	v_bool_visited[source_node] = true;

	for (uint i = 0; i < g[source_node].size(); i++) {
		g[source_node][i].heap_value = g[source_node][i].value;
		nodes_heap.push(g[source_node][i]);
	}
	// initialize the map that will store the shortest paths.
	vector<int> m_shortest_path = vector<int>(g.size());
	m_shortest_path[source_node] = 0;
	edge next_edge;

	while (nodes_heap.size() > 0) {
		next_edge = nodes_heap.top();
		nodes_heap.pop();

		if (v_bool_visited[next_edge.head] && v_bool_visited[next_edge.tail])
			continue;

		m_shortest_path[next_edge.tail] = m_shortest_path[next_edge.head] + next_edge.value;
		for (uint i = 0; i < g[next_edge.tail].size(); i++) {
			if (!v_bool_visited[g[next_edge.tail][i].tail]) {
				edge e = g[next_edge.tail][i];
				e.heap_value = m_shortest_path[next_edge.tail] + e.value;
				nodes_heap.push(e);
			}
		}
		// mark node as visited
		v_bool_visited[next_edge.tail] = true;
	}

	return m_shortest_path;
}

void parse_roads_line(string &str_source, string &str_destination,
		string &str_mid, graph &g, string_int_map &locations_map) {

    
	int i_source_index = -1, i_destination_index = -1;
	if ( locations_map.find(str_source) == locations_map.end() ) {
		i_source_index = locations_map.size();
		locations_map[str_source] = i_source_index;
	}
	else
		i_source_index = locations_map[str_source];

	if ( locations_map.find(str_destination) == locations_map.end() ) {
		i_destination_index = locations_map.size();
		locations_map[str_destination] = i_destination_index;
	}
	else
		i_destination_index = locations_map[str_destination];

	string str_value = str_mid.substr(2, str_mid.size() - 4);
	if (str_mid[str_mid.size() - 1] == '>') {
		edge e;
		e.head = i_source_index;
		e.tail = i_destination_index;
		e.value = atoi(str_value.c_str());
		g[i_source_index].push_back(e);
	}
	if (str_mid[0] == '<') {
		edge e;
		e.head = i_destination_index;
		e.tail = i_source_index;
		e.value = atoi(str_value.c_str());
		g[i_destination_index].push_back(e);
	}

}
//
//int main(int argc, char **argv) {
//	clock_t t0 = clock();
//	int i_locations, i_cars, i_roads;
//	char *pch_line = new char[1024 * 100], *pch = new char[100];
//	FILE *ifile = stdin;
//	if(ifile == NULL) {
//		printf("ERROR no input file\n");
//		return 0;
//	}
//	int x = 1;
//
//	char town1[16], town2[16], middle[16];
//	while (true) {
//		int rs = fscanf(ifile, "%d %d %d\n", &i_locations, &i_cars, &i_roads);
//		if (i_locations == 0 && i_cars == 0 && i_roads == 0)
//			break;
//
//		if(i_cars == 0){
//			printf("%d. %d\n", x, 0);
//			x++;
//			for(int k = 0; k <= i_roads + 1 ; k++){
//				fgets(pch_line, 100 * 1024, ifile);
//			}
//			continue;
//		}
//		vector<int> v_cars(i_cars);
//		int i = 0;
//		string_int_map m_locations_map;
//
//		char* r = fgets(pch_line, 100 * 1024, ifile);
//		if (r == NULL)
//			break;
//		pch = strtok(pch_line, " \r\n");
//		m_locations_map.insert(make_pair(string(pch), i));
//		v_cars[0] = i;
//		i++;
//		string str_pch;
//		int j = 0;
//		while ((pch = strtok(NULL, " \r\n")) != NULL) {
//			str_pch = pch;
//			int i_location_index;
//
//			if (m_locations_map.find(str_pch) == m_locations_map.end()) {
//				m_locations_map[str_pch] = i;
//				i_location_index = i;
//				i++;
//			}
//			else
//				i_location_index = m_locations_map[str_pch];
//
//			v_cars[j] = i_location_index;
//			j++;
//		}
//
//		graph g = graph(i_locations), g_rev = graph(i_locations);
//
//
//		string str_town1, str_town2, str_middle;
//		for (int i = 0; i < i_roads; i++) {
//			fscanf(ifile, "%s %s %s", town1, middle, town2);
//			str_town1 = town1;
//			str_town2 = town2;
//			str_middle = middle;
//			parse_roads_line(str_town1, str_town2, str_middle, g, m_locations_map);
//			parse_roads_line(str_town2, str_town1, str_middle, g_rev, m_locations_map);
//		}
//
//		vector<int> path_values = dijkstra(g, 0);
//		vector<int> path_values_rev = dijkstra(g_rev, 0);
//		int sum = 0;
//		for (unsigned int ii = 0; ii < v_cars.size(); ii++) {
//			sum += path_values[v_cars[ii]] + path_values_rev[v_cars[ii]];
//		}
//		printf("%d. %d\n", x, sum);
//		x++;
//	}
//
//	clock_t t1 = clock();
////	cout << "time: " << (float)(t1 - t0)/CLOCKS_PER_SEC << endl;
//	return 0;
//}
