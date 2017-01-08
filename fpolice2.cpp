#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <climits>
#include <ctime>
using namespace std;

typedef unsigned long ulong;
typedef unsigned int uint;
typedef vector<vector<ulong> > matrix;
typedef struct result
{
	ulong risk;
	ulong time;
	result() : risk(ULONG_MAX), time(ULONG_MAX) {}
} result;


void print_result(vector<matrix> m) {
	for (int i = 0; i < m.size(); i++) {
		for (int j = 0; j < m[i].size(); j++) {
			for (int k = 0; k < m[i][j].size(); k++) {
				if(m[i][j][k] > 100000000)
				cout << "xx" << " ";
				else 
				cout << m[i][j][k] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
}

void fpolice(matrix &time, matrix &risk, uint ui_max_time, uint ui_locations) {
	ulong ul_init_value = ULONG_MAX - (1000 * 1000);
	matrix m(ui_locations);
	for (uint i = 0; i < ui_locations; i++)
		m[i] = vector<ulong>(ui_max_time + 1, ul_init_value);
	vector<matrix> memo(ui_locations - 1);
	for (uint i = 0; i < ui_locations - 1; i++)
		memo[i] = m;

	//cout << "done init" << endl;
	// initialization done. Memo is now [iterations][locations][max time]
	// At the first iteration, for location 0 (start) the risk is 0.
	for (uint i = 0; i < ui_max_time; i++)
		memo[0][0][i] = 0;
	// Compute the risk to reach every location in one step
	ulong ul_time, ul_risk, ul_time_sum;
	for (uint i = 1; i < ui_locations; i++) {
		ul_time = time[0][i];
		ul_risk = risk[0][i];
		if(ul_time < ui_max_time)
			memo[0][i][ul_time] = ul_risk;

	}

	vector<result> v(ui_max_time + 1); 

	
	//cout << "done first iter" << endl;
	// now the first iteration matrix is complete with the risks for paths made of 1 step.
	for (uint pl = 1; pl < ui_locations - 1; pl++) {
		// The next vector will hold the "best solution" for every location. The "best solution" means 
		// if I have r1.risk > r_best.risk and r1.time > r_best.time for the same location and 
		// the same number of steps in the path, then there is no point in keeping that 
		// solution and compute a path based on it.
		vector<result> v_temp(ui_locations);
		// cout << "pl " << pl << endl;
		// pl represents the lenght of the path - 1
		for (uint head = 1; head < ui_locations; head++)
		{
			// here I must get all the risks less then max value from the previous iteration for location head.
			// The path at the current iteration are build from the path at the previous iteration plus the one
			// added now.	
			ulong v_index = 0;
			for (uint k = 1; k < ui_max_time + 1; k++) {
				// cout << k << endl;
				if (memo[pl - 1][head][k] < ul_init_value) {
					result r;
					r.risk = memo[pl - 1][head][k];
					r.time = k;
					v[v_index] = r;
					v_index += 1;
				}
			}
			// print_vector(v);
			//cout << v_index << endl;
			// cout << head << " " << v.size() << endl;
			// head start the location number. This is the end of the path from the previous iterarion, so it becomes the head 
			// for the current operation. It starts at one as there is no point in going back to the source. 
			for (uint tail = 1; tail < ui_locations; tail++)
			{
				// this is the tail of the edge that will be added. Also start at 1
				if (tail == head)
					continue; 
				// The iter path is build upon the n-1 path that end in i
				ul_time = time[head][tail];
				ul_risk = risk[head][tail];
				for(uint k = 0; k < v_index; k++) {
					ul_time_sum = ul_time + v[k].time;
					if (ul_time_sum > ui_max_time)
						continue;
					if (memo[pl][tail][ul_time_sum] > v[k].risk + ul_risk) {
						if (v_temp[tail].risk > v[k].risk + ul_risk && v_temp[tail].time > ul_time_sum) {
							memo[pl][tail][ul_time_sum] = v[k].risk + ul_risk;
							v_temp[tail].risk = v[k].risk + ul_risk;
							v_temp[tail].time = ul_time_sum;
						}
					}
				}
			}
		}
	}

	result r_final; 
	r_final.risk = ULONG_MAX - (1000 * 1000);
	for(uint pl = 0; pl < ui_locations - 1; pl++) {
		for (uint i = 0; i <= ui_max_time; i++) {
			if (r_final.risk > memo[pl][ui_locations - 1][i])
			{
				r_final.risk = memo[pl][ui_locations - 1][i];
				r_final.time = i;
			}
		}
	}
	if (r_final.risk == (ULONG_MAX - (1000 * 1000)))
		cout << -1 << endl;
	else
		cout << r_final.risk << " " << r_final.time << endl;
	//print_result(memo);
}

int main(int argc, char const *argv[])
{

	int i_testcases, i_stations, i_time;
	scanf("%d", &i_testcases);

	for (int i = 0; i < i_testcases; i++) {
		scanf("%d %d", &i_stations, &i_time);

		vector< vector<ulong> > times(i_stations);
		vector< vector<ulong> > risks(i_stations);
		
		for (int j = 0; j < i_stations; j++) {
			times[j] = vector<ulong>(i_stations);
			risks[j] = vector<ulong>(i_stations);
		}

		for (int j = 0; j < i_stations; j++) 
			for (int k = 0; k < i_stations; k++) 
				scanf("%ld", &times[j][k]);
		
		for (int j = 0; j < i_stations; j++)
			for (int k = 0; k < i_stations; k++)
				scanf("%ld", &risks[j][k]);
		fpolice(times, risks, i_time, i_stations);
	}
	return 0;
}