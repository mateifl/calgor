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
		memo[i] = vector<int>();

	for(int i = 0; i < max_sum; i++)
	{
		for(int i = 0; i < max_sum; i++){
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
		vector<pair<int, int>> v_parties;
		for(int i = 0; i < i_number_of_parties; i++)
		{
			scanf("%d %d", &i_cost, &i_fun);
			v_parties.push_back(make_pair(i_cost, i_fun));
		}

		int_pair sol = solution(v_parties);

		printf("%d %d\n", sol.first, sol.second);
	}


	return 0;
}