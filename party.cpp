#include <iostream>
#include <functional>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <string>
#include <ctime>
#include <algorithm>
using namespace std;
typedef pair<int, int> int_pair;

typedef struct party {
	int cost;
	int fun;
} party;

party solution(const vector<party> &v_parties, int max_sum, int number_of_parties) {
	vector<vector<party> > memo = vector<vector<party> >(number_of_parties + 1);

	for(int i = 0; i <= number_of_parties; i++)
		memo[i] = vector<party>(max_sum + 1);

	for (int i = 0; i <= max_sum; i++) {
		memo[0][i].fun = 0; 
		memo[0][i].cost = 0;
	}

	int i_temp_val1 = 0, i_temp_val2 = 0;
	
	for (int i = 1; i <= number_of_parties; i++)
	{
		for (int j = 0; j <= max_sum; j++)
		{
			i_temp_val1 = memo[i - 1][j].fun;
			if (j < v_parties[i - 1].cost)
			{
				memo[i][j].fun = i_temp_val1;
				memo[i][j].cost = memo[i - 1][j].cost;
				continue;
			}

			i_temp_val2 = memo[i - 1][j - v_parties[i - 1].cost].fun + v_parties[i - 1].fun;
			
			if (i_temp_val1 > i_temp_val2) {
				memo[i][j].fun = i_temp_val1;
				memo[i][j].cost = memo[i - 1][j].cost;
			}
			else if (i_temp_val1 == i_temp_val2) {
				if (memo[i - 1][j].cost < (memo[i - 1][j - v_parties[i - 1].cost].cost + v_parties[i - 1].cost)) {
					memo[i][j].fun = i_temp_val1;
					memo[i][j].cost = memo[i - 1][j].cost;
				}
				else {
					memo[i][j].fun = i_temp_val2;
					memo[i][j].cost = memo[i - 1][j - v_parties[i - 1].cost].cost + v_parties[i - 1].cost;
				}
			}
			else{
				memo[i][j].fun = i_temp_val2;
				memo[i][j].cost = memo[i - 1][j - v_parties[i - 1].cost].cost + v_parties[i - 1].cost;
			}
		}
	}
	/*
	for (int i = 0; i <= number_of_parties; i++)
	{
		for (int j = 0; j <= max_sum; j++)
			cout << memo[i][j].cost << "|" << memo[i][j].fun << " ";
		cout << endl;
	}
	*/
	return memo[number_of_parties][max_sum];
}

int main(int argc, char** argv) {
	int i_number_of_parties, i_max_sum;
	int i_cost, i_fun;
	while (true)
	{
		scanf("%d %d", &i_max_sum, &i_number_of_parties);
		if(i_max_sum == 0 && i_number_of_parties == 0)
			break;
		vector<party> v_parties = vector<party>(i_number_of_parties);
		for(int i = 0; i < i_number_of_parties; i++)
		{
			party p;
			scanf("%d %d", &p.cost, &p.fun);
			v_parties[i] = p;
		}

		party sol = solution(v_parties, i_max_sum, i_number_of_parties);
		printf("%d %d\n", sol.cost, sol.fun);

	}
	return 0;
}
