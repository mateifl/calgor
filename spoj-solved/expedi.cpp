#include <iostream>
#include <cmath>
#include <vector>
#include <cstdio>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

typedef unsigned int u_int;

typedef struct point{
	u_int distance;
	u_int fuel;
} point;

template<class T> struct greater_fuel : binary_function<T, T, bool> {
	bool operator()(const T& x, const T& y) const {
		return x.fuel < y.fuel;
	}
};

bool greaterThen(const point &p1, const point &p2) {
	return p1.distance > p2.distance;
}

typedef priority_queue<point, vector<point>, greater_fuel<point> > heap;

int solution(vector<point> &v_locations) {

	// sort the locations
	point current_location = v_locations[v_locations.size() - 2]; 
	sort(v_locations.begin(), v_locations.end(), greaterThen);
	u_int i = 0;
	for (size_t j = 0; j < v_locations.size(); j++)
	{
		i += 1;
		if( current_location.distance == v_locations[j].distance)
		{
			current_location = v_locations[j];
			break;
		}
	}

	heap h;
	vector<point> v_solution;
	u_int fuel = current_location.fuel;
	while(true) {
		while(fuel > 0) {
			u_int distance = v_locations[i - 1].distance - v_locations[i].distance;
			if(fuel >= distance) 
				fuel -= distance;
			else
				break;
			if(i == (v_locations.size() - 1))
				return v_solution.size();
			h.push(v_locations[i]);
			i += 1;
		}
		if(h.size() == 0)
			return -1;
		// get the location with the most fuel and add it to the solution
		point p = h.top();
		h.pop();
		fuel += p.fuel;
		v_solution.push_back(p);
	}
	return -1;
}


// void test() {
// 	heap h;

// 	point p;
// 	p.distance = 10;
// 	p.fuel = 8;
// 	h.push(p);
// 	p.distance = 15;
// 	p.fuel = 20;
// 	h.push(p);
// 	p.distance = 8;
// 	p.fuel = 3;
// 	h.push(p);
// 	p.distance = 7;
// 	p.fuel = 15;
// 	h.push(p);
// 	p = h.top();
// 	cout << p.fuel << endl; 
// }

int main(int argc, char** argv) {
	// test();
	// FILE *f = fopen("tc_expedi2.in", "r");
	FILE *f = stdin;
	u_int i_testcases, i_distance, i_fuel, i_locations_number;
	fscanf(f, "%d", &i_testcases);
	point p;
	for (int i = 0; i < i_testcases; i++)
	{
		fscanf(f, "%d", &i_locations_number);
		vector<point> v_locations = vector<point>(i_locations_number + 2);
		// last location is (0, 0)
		for (int j = 0; j < i_locations_number + 1; j++) {
			fscanf(f, "%d %d", &i_distance, &i_fuel);
			p.distance = i_distance;
			p.fuel = i_fuel;
			v_locations[j] = p;
		}
		p.distance = 0;
		p.fuel = 0;
		v_locations[v_locations.size() - 1] = p;
		cout << solution(v_locations) << endl;
	}
	return 0;
}
