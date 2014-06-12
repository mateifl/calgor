#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <cmath>
#include <string>
#include <ctime>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <functional>
using namespace std;

typedef vector<pair<int, int> > places_vector;
typedef set<pair<int, int> > set_vector;
typedef map<pair<int, int>, int> map_pair_key;
typedef priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > heap;

int solution(places_vector &places) {
	// reverse the places vector
	heap locations_heap;
	map_pair_key index_map;

	set<pair<int, int> > places_set; 
	for(int i = 0; i < places.size(); i++){
		locations_heap.push(make_pair(places[i].second, places[i].first));
		index_map.insert( make_pair(places[i], i) );
		places_set.insert(places[i]);
	}

	pair<int, int> node = locations_heap.top();
	locations_heap.pop();

	pair<int, int> start_location = make_pair(node.second, node.first);

	if(start_location.first - places[0].first < start_location.second)
	{
		locations_heap.push(make_pair(start_location.second, start_location.first));
		start_location = places[0];
	}

	if(places.back().first - start_location.first < start_location.second)
	{
		locations_heap.push(make_pair(start_location.second, start_location.first));
		start_location = places.back();
	}

	int i_time = 0;
	pair<int, int> next_location_heap, next_location;
	while(places_set.size() > 0){
		// get the next (min) deadline place from the heap
		next_location_heap = locations_heap.top();
		locations_heap.pop();
		next_location = make_pair(next_location_heap.second, next_location_heap.first);
		if( places_set.find(next_location) == places_set.end() ) 
			continue;

		// get the locations indexes from the location map
		int i_start_point_index = index_map[start_location];
        int i_next_node_index = index_map[next_location];

		i_time += abs( places[i_start_point_index].second - places[i_next_node_index].second );

		if(i_time > places[i_next_node_index].second)
			return -1;

		if(i_start_point_index < i_next_node_index)
		{
			for(int i = i_start_point_index; i <= i_next_node_index; i++)
				places_set.erase(places[i]);
		}
		else
		{
			for(int i = i_next_node_index; i <= i_start_point_index; i++)
				places_set.erase(places[i]);
		}
		start_location = next_location;
	}

	return i_time;
}

int main(int argc, char** argv) {
	int i_testcases, i_location_number, i_first, i_second;
	scanf("%d", &i_testcases);

	for(int i = 0; i < i_testcases; i++)
	{
		scanf("%d", &i_location_number);
		places_vector v = places_vector(i_location_number);
		for(int j = 0; j < i_location_number; j++)
		{
			scanf("%d %d", &i_first, &i_second);
			//cout << i_first << " " << i_second << endl;
			v[j] = make_pair(i_first, i_second);
		}
		cout << solution(v) << endl;
	}
	return 0;
}
