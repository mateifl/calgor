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

typedef struct result
{
    public:
    int risk;
    int time;
    result() { risk = -1; time = -1; }
} result;

result solution(int i_last_station, int i_steps, int i_time_limit,
				vector< vector<ulong> > &times, vector< vector<ulong> > &risks,
				vector<result> &temp_r, int time_s, int risk_s, result memo[][101][101]) {

	if (memo[i_time_limit][i_last_station][i_steps].risk > -1)
		return memo[i_time_limit][i_last_station][i_steps];

	if(temp_r[i_last_station].risk == -1 && temp_r[i_last_station].time == -1 && 
	   time_s > 0 && risk_s > 0)
	{
		temp_r[i_last_station].risk = risk_s;
		temp_r[i_last_station].time = time_s; 
	}

    result r;
    int i_no_locations = times.size();
    if(i_steps == 0 && i_last_station == 0){
        r.risk = 0;
        r.time = 0;
        return r;
    }

    if(i_steps == 0 && i_last_station != 0){
        r.risk = INT_MAX;
        r.time = 0;
        return r;
    }

	r = memo[i_time_limit][i_last_station][i_steps - 1];
	if (r.risk == -1)
		r = solution(i_last_station, i_steps - 1, i_time_limit, times, risks, temp_r, time_s, risk_s, memo);

    for(int i = 0; i < i_no_locations; i++) {
        if(i == i_last_station)
            continue;

        int s_tl = i_time_limit - times[i][i_last_station];
		if (s_tl < 0) {
			//cout << "TL exceeded! " << i_last_station << " " << i_steps << endl;
            continue;
		}

		if( temp_r[i].risk > 0 && temp_r[i].time > 0 && 
			(time_s + times[i][i_last_station]) > temp_r[i].time && 
			(risk_s + risks[i][i_last_station]) > temp_r[i].risk)
			continue;

		result r2 = memo[s_tl][i][i_steps - 1];
		if (r2.risk == -1) {
			r2 = solution(i, i_steps - 1, s_tl, times, risks, temp_r, 
				time_s + times[i][i_last_station], risk_s + risks[i][i_last_station], memo);
			memo[s_tl][i][i_steps - 1] = r2;
		}

        if (r.risk > r2.risk + risks[i][i_last_station]) {
            r.risk = r2.risk + risks[i][i_last_station];
            r.time = r2.time + times[i][i_last_station];
        }
    }

	//printf("%d %d (%d %d)\n", i_last_station, i_steps, r.risk, r.time);
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

		vector< vector<ulong> > times(i_stations);
        vector< vector<ulong> > risks(i_stations);
		//result memo[251][101][101];
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

		vector<result> temp_r(i_stations);
		result memo[251][101][101];
		time_t t2 = clock();
        result r = solution(i_stations - 1, i_stations - 1, i_time, times, risks, temp_r, 0, 0, memo);

		if (r.risk == -1 || r.risk == INT_MAX)
			printf("-1\n");
		else 
			printf("%d %d\n", r.risk, r.time);

		time_t t1 = clock();
		cout << "time: " << (float)(t1 - t) / CLOCKS_PER_SEC << endl;
		cout << "time: " << (float)(t2 - t) / CLOCKS_PER_SEC << endl;
	}

    return 0;
}