#include <cstring>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;
typedef vector<pair<int, int>> int_pair_vector; 
typedef pair<int, int> int_pair;

struct sort_pred {
    bool operator()(const std::pair<int,int> &left, const std::pair<int,int> &right) {
        return left.second < right.second;
    }
};


int solution( int_pair_vector &coins , int weight, vector<vector<int>> &memo )
{
	if(weight < 0 || coins.size() == 0)
		return -1;

	if( memo[coins.size()][weight] != -1 )
		return memo[coins.size()][weight];

	if(coins.size() == 1)
	{
		if(weight % coins[0].second == 0) {
			memo[coins.size()][weight] = -1;
			return (weight / coins[0].second) * coins[0].first;
		}
		else {
			memo[coins.size()][weight] = -1;
			return -1;
		}
	}

	int_pair last_coin = coins[coins.size() - 1];
	int i_last_coin = weight / last_coin.second;
	int min_val = 1000000;
	int_pair_vector v = int_pair_vector(coins.size() - 1);
	int_pair_vector::iterator it;
	v.assign(coins.begin(), coins.end() - 1);

	for( int i = 0; i <= i_last_coin; i++)
	{
		int i_sub_problem_result = solution(v, weight - (i * last_coin.second), memo);
		if(i_sub_problem_result > -1) {
			int x = i_sub_problem_result  + (i * last_coin.first);
            if (x < min_val)
				min_val = x;
		}
	}

	if (min_val == 1000000)
        return -1;

	memo[coins.size()][weight] = min_val;
    return min_val;

}

int main(int argc, char* argv[]) {
	clock_t t1 = clock();
	int i_test_cases, i_first, i_second, i_coins;
	scanf("%d", &i_test_cases);

	for(int i = 0; i < i_test_cases; i++)
	{
		scanf("%d %d", &i_first, &i_second);
		int weight = i_second - i_first;
		scanf("%d", &i_coins);
		int_pair_vector v_coins = int_pair_vector(i_coins);
		for(int j = 0; j < i_coins; j++) {
			scanf("%d %d", &i_first, &i_second);
			v_coins[j] = make_pair(i_first, i_second);

		}

		//sort(v_coins.begin(), v_coins.end(), sort_pred());
		vector<vector<int>> memo = vector<vector<int>>(v_coins.size() + 1);
		vector<int> v_temp = vector<int>(weight + 1);

		for(unsigned int j = 0; j < v_temp.size(); j++)
			v_temp[j] = -1;

		for(unsigned int j = 0; j < v_coins.size() + 1; j++)
			memo[j] = v_temp;


		int i_result = solution(v_coins, weight, memo);
		printf("%d\n", i_result);
	}
	clock_t t2 = clock();
    cout << "time: " << (float)(t2 - t1)/CLOCKS_PER_SEC << endl;
	return 0;
}