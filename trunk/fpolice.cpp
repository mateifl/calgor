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

long solution(int i_last_station, int i_steps, int i_time_limit,
			  vector< vector<ulong> > &times, vector< vector<ulong> > &risks, 
			  vector< vector< vector<long> > > &memo) {

	if (memo[i_time_limit][i_last_station][i_steps] > -1)
		return memo[i_time_limit][i_last_station][i_steps];

    if(i_steps == 0 && i_last_station == 0)
        return 0;

    if(i_steps == 0 && i_last_station != 0)
        return INT_MAX;

	int i_no_locations = times.size();
	long r = memo[i_time_limit][i_last_station][i_steps - 1];
	if (r == -1)
		r = solution(i_last_station, i_steps - 1, i_time_limit, times, risks, memo);

    for(int i = 0; i < i_no_locations; i++) {
        if(i == i_last_station)
            continue;

        int s_tl = i_time_limit - times[i][i_last_station];
		if (s_tl < 0)
            continue;

		long r2 = memo[s_tl][i][i_steps - 1];
		if (r2 == -1) {
			r2 = solution(i, i_steps - 1, s_tl, times, risks, memo);
			memo[s_tl][i][i_steps - 1] = r2;
		}

        if (r > r2 + risks[i][i_last_station]) 
            r = r2 + risks[i][i_last_station];
    }

	//printf("%d %d %d\n", i_last_station, i_steps, r);
	memo[i_time_limit][i_last_station][i_steps] = r;
    return r;
}

int main(int argc, char const *argv[])
{
	time_t t = clock();
	int i_testcases, i_stations, i_time;
	scanf("%d", &i_testcases);

	for(int i = 0; i < i_testcases; i++){
		scanf("%d %d", &i_stations, &i_time); 

		vector< vector< vector<long> > > memo(i_time + 1);
		vector<long> v(i_stations);
		v.assign(i_stations, -1);
		for (int j = 0; j < i_time + 1; j++) {
			memo[j] = vector< vector<long> >(i_stations);
			if (j % 50 == 0)
			cout << j << endl;
			for (int k = 0; k < i_stations; k++) {
				memo[j][k] = v;
			}
		}

		vector< vector<ulong> > times(i_stations);
        vector< vector<ulong> > risks(i_stations);

		for(int j = 0; j < i_stations; j++) {
            times[j] = vector<ulong>(i_stations);
            risks[j] = vector<ulong>(i_stations);
        }

		for (int j = 0; j < i_stations; j++) {
			for (int k = 0; k < i_stations; k++) {
				scanf("%ld", &times[j][k]);
			}
		}

		for(int j = 0; j < i_stations; j++)
            for(int k = 0; k < i_stations; k++)
                scanf("%ld", &risks[j][k]);

		time_t t2 = clock();
		cout << "time: " << (float)(t2 - t) / CLOCKS_PER_SEC << endl;
        ulong r = solution(i_stations - 1, i_stations - 1, i_time, times, risks, memo);

		if (r == -1 || r == INT_MAX)
			printf("-1\n");
		else 
			printf("%d %d\n", r, r);

		time_t t1 = clock();
		cout << "time: " << (float)(t1 - t) / CLOCKS_PER_SEC << endl;

	}

    return 0;
}