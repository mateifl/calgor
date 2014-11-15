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

int_pair solution(const vector<party> &v_parties, int max_sum, int number_of_parties) {
	vector<vector<int> > memo = vector<vector<int> >(number_of_parties + 1);
	for(int i = 0; i <= number_of_parties; i++)
		memo[i] = vector<int>(max_sum + 1);

	for(int i = 0; i <= max_sum; i++)
		memo[0][i] = 0; 

	int i_temp_val1 = 0, i_temp_val2 = 0;
	
	for (int i = 1; i <= number_of_parties; i++)
	{
		for (int j = 0; j <= max_sum; j++)
		{
			i_temp_val1 = memo[i - 1][j];
			if (j < v_parties[i - 1].cost)
			{
				memo[i][j] = i_temp_val1;
				continue;
			}
			i_temp_val2 = memo[i - 1][j - v_parties[i - 1].cost] + v_parties[i - 1].fun;
			if( i_temp_val1 > i_temp_val2 ) 
				memo[i][j] = i_temp_val1;
			else
				memo[i][j] = i_temp_val2;
		}
	}

	int fun = memo[number_of_parties][max_sum];
	vector<int> parties;
	for (int i = number_of_parties; i > 0; i--)
	{
		for (int j = max_sum; j > 0; j--) {
			if(fun == memo[i][j])
				continue;
			else
			{
				parties.push_back(i - 1);
				fun = memo[i - 1][j - v_parties[i - 1].cost];
			}
		}
	}

	int_pair cost_fun = make_pair(0, memo[number_of_parties][max_sum]);
	return cost_fun;
}

int main(int argc, char** argv) {
	int i_number_of_parties, i_max_sum;
	int i_cost, i_fun;
	while (true)
	{
		scanf("%d %d", &i_max_sum, &i_number_of_parties);
		if(i_max_sum == 0 && i_number_of_parties == 0)
			break;
		vector<party> v_parties;
		for(int i = 0; i < i_number_of_parties; i++)
		{
			party p;
			scanf("%d %d", &p.cost, &p.fun);
			v_parties.push_back(p);
		}

		int_pair sol = solution(v_parties, i_max_sum, i_number_of_parties);
		printf("%d %d\n", sol.first, sol.second);
		scanf("");
	}
	return 0;
}
