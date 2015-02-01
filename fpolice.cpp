#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <climits>
using namespace std;

typedef unsigned long ulong;

typedef struct result
{
    int risk;
    int time;
} result;

result solution(int i_last_station, int i_steps, int i_time_limit,
              vector< vector<ulong> > &times, vector< vector<ulong> > &risks) {

    result r;
    int i_no_locations = times.size();
    if(i_steps == 0 && i_last_station == 0){
        r.risk = 0;
        r.time = 0;
        return r;
    }

    if(i_steps == 0 && i_last_station != 0){
        r.risk = UINT_MAX;
        r.time = 0;
        return r;
    }

    r = solution(i_last_station, i_steps - 1, i_time_limit, times, risks);

    for(int i = 0; i < i_no_locations; i++) {
        if(i == i_last_station)
            continue;

        int s_tl = i_time_limit - times[i][i_last_station];
        if(s_tl < 0)
            continue;

        result r2 = solution(i, i_steps - 1, s_tl, times, risks);

        if (r.risk > r2.risk + risks[i][i_last_station]) {
            r.risk = r2.risk + risks[i][i_last_station];
            r.time = r2.time + times[i][i_last_station];
        }
    }

	printf("%d %d (%d %d)\n", i_last_station, i_steps, r.risk, r.time);

    return r;
}

int main(int argc, char const *argv[])
{
	int i_testcases, i_stations, i_time;
	scanf("%d", &i_testcases);

	for(int i = 0; i < i_testcases; i++){
		scanf("%d %d", &i_stations, &i_time); 

		vector< vector<ulong> > times(i_stations);
        vector< vector<ulong> > risks(i_stations);
		for(int j = 0; j < i_stations; j++) {
            times[j] = vector<ulong>(i_stations);
            risks[j] = vector<ulong>(i_stations);
        }

        for(int j = 0; j < i_stations; j++)
            for(int k = 0; k < i_stations; k++)
                scanf("%ld", &times[j][k]);

        for(int j = 0; j < i_stations; j++)
            for(int k = 0; k < i_stations; k++)
                scanf("%ld", &risks[j][k]);
        result r = solution(i_stations - 1, i_stations - 1, i_time, times, risks);
        printf("%d %d\n", r.risk, r.time);
	}
    return 0;
}