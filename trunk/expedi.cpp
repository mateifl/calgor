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

void solution(vector<point> &v_locations) {
	point start_location = v_locations[0];
	int i_stops = 0;

}

int main(int argc, char** argv) {
	int i_testcases, i_distance, i_fuel, i_locations_number;
	scanf("%d", &i_testcases);
	point p;
	for (int i = 0; i < i_testcases; i++)
	{
		scanf("%d", &i_locations_number);
		vector<point> v_locations = vector<point>(i_locations_number);
		for (int j = 0; j < i_locations_number; j++) {
			scanf("%d %d", &i_distance, &i_fuel);
			p.distance = i_distance;
			p.fuel = i_fuel;
			v_locations[j] = p;
		}

	}
	return 0;
}