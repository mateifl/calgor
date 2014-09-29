#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <string>
#include <cstdio>
#include <set>
#include <stack>
#include <ctime>
#include <cstring>
using namespace std;

typedef struct point{
	int distance;
	int fuel;
} point;

int solution(vector<point> &v_locations) {
	int start_location_index = 0, next_location_index, current_location_index;
	int i_stops = 0;
	int fuel = v_locations[0].fuel;
	for (int i = 0; i < v_locations.size(); i++)
	{
		if (v_locations[i].distance - v_locations.back().distance <= fuel)
		{
			i_stops += 1;
			return i_stops;
		}
		if (v_locations[next_location_index].distance > 0 && v_locations[i].distance != v_locations[next_location_index].distance)
			continue;

		vector<point>::iterator it;
		for (it = v_locations.begin() + current_location_index; it != v_locations.end(); it++)
		{

		}
	}



	
	return i_stops;
}
//
//int main(int argc, char** argv) {
//	int i_testcases, i_distance, i_fuel, i_locations_number;
//	scanf("%d", &i_testcases);
//	point p;
//	for (int i = 0; i < i_testcases; i++)
//	{
//		scanf("%d", &i_locations_number);
//		vector<point> v_locations = vector<point>(i_locations_number);
//		for (int j = 0; j < i_locations_number; j++) {
//			scanf("%d %d", &i_distance, &i_fuel);
//			p.distance = i_distance;
//			p.fuel = i_fuel;
//			v_locations[j] = p;
//			solution(v_locations);
//		}
//
//	}
//	return 0;
//}
