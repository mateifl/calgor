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
#include <functional>
using namespace std;

typedef vector<pair<int, int> > places_vector;
typedef set<pair<int, int> > set_vector;
typedef priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > heap;

int solution(places_vector &places) {
	// reverse the places vector
	heap locations_heap;
	for(int i = 0; i < places.size(); i++)
	{
		locations_heap.push(make_pair(places[i].second, places[i].first));

	}

	pair<int, int> node = locations_heap.top();
	locations_heap.pop();

	pair<int, int> start_location = make_pair(node.second, node.first);

	if(start_location.first - places[0].first < places[0].second)
	{
	}



	return 0;
}

int main(int argc, char** argv) {
	return 0;
}
