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
		index_map.insert(places[i], i);
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
	pair<int, int> next_location;
	while(places_set.size() > 0){
		next_location = locations_heap.top();
		locations_heap.pop();
		if( places_set.find(next_location) == places_set.end() ) 
			continue;


	}

	return 0;
}

int main(int argc, char** argv) {
	return 0;
}
