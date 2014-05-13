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

int_pair solution(vector<pair<int, int>> v_parties, int max_sum, int number_of_parties) {
	int_pair cost_fun;
	vector<vector<int>> memo = vector<vector<int>>(max_sum);
	for(int i = 0; i < max_sum; i++)
		memo[i] = vector<int>(number_of_parties);

	for(int i = 0; i < max_sum; i++)
	{
		memo[i][0] = 0; 
	}

	int i_temp_val1 = 0, i_temp_val2 = 0;
	for(int i = 0; i < max_sum; i++)
	{
		for(int j = 0; j < number_of_parties; j++){
			i_temp_val1 = memo[i][j - 1];
			i_temp_val2 = memo[i - 1][j - 1] + v_parties[j].first;
			if( i_temp_val1 > i_temp_val2 ) 
				memo[i][j] = i_temp_val1;
			else
				memo[i][j] = i_temp_val2;
		}
	}

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
		vector<pair<int, int>> v_parties;
		for(int i = 0; i < i_number_of_parties; i++)
		{
			scanf("%d %d", &i_cost, &i_fun);
			v_parties.push_back(make_pair(i_cost, i_fun));
		}

		int_pair sol = solution(v_parties, i_max_sum, i_number_of_parties);

		printf("%d %d\n", sol.first, sol.second);
		
	}


	return 0;
}