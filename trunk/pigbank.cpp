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


int solution( int_pair_vector &coins, int i_last_index, int weight, vector<vector<int>> &memo )
{
	if(weight < 0 || i_last_index < 0)
		return -1;

	if( memo[i_last_index][weight] != -2 )
		return memo[i_last_index][weight];
	
	// get the last coin 
	int_pair last_coin = coins[i_last_index];

	if(i_last_index == 0)
	{
		if(weight % last_coin.second == 0) {
			memo[i_last_index][weight] = (weight / last_coin.second) * last_coin.first;
			return (weight / last_coin.second) * last_coin.first;
		}
		else {
			memo[i_last_index][weight] = -1;
			return -1;
		}
	}

	//int_pair last_coin = coins[coins.size() - 1];
	int i_last_coin = weight / last_coin.second;
	int min_val = 1000000;

	for(int i = 0; i <= i_last_coin; i++)
	{
		int i_sub_problem_result = solution(coins, i_last_index - 1, weight - (i * last_coin.second), memo);
		if(i_sub_problem_result > -1) {
			int x = i_sub_problem_result  + (i * last_coin.first);
            if (x < min_val)
				min_val = x;
		}
	}

	if (min_val == 1000000)
        return -1;

	memo[i_last_index][weight] = min_val;
    return min_val;

}

int  solution2( int_pair_vector &coins, int weight) {
	vector<long> v_memo = vector<long>(weight + 1);
	int i_coins_number = coins.size();
	v_memo[0] = 0;


	for(int i = 1; i < coins[0].second; i++) {
		v_memo[i] = -1;
		if(i == (v_memo.size() - 1))
			break;
	}
	for(int i = 1; i <= weight; i++)
	{
		long l_min_val = 1000000;
		for(int j = 0; j < coins.size(); j++){
			if (i < coins[j].second  || v_memo[i - coins[j].second] == -1)
                continue;
		
			long v = v_memo[i - coins[j].second] + coins[j].first;
            if (l_min_val > v)
                l_min_val = v;
		}
		if( l_min_val == 1000000)
			v_memo[i] = -1;
		else
			v_memo[i] = l_min_val;
	}
	return v_memo[weight];
}

int main(int argc, char* argv[]) {
	clock_t t1, t2; // = clock();
	int i_test_cases, i_first, i_second, i_coins;
	scanf("%d", &i_test_cases);
	t1 = clock();
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

		sort(v_coins.begin(), v_coins.end(), sort_pred());
		vector<vector<int>> memo = vector<vector<int>>(v_coins.size() + 1);
		vector<int> v_temp = vector<int>(weight + 1);

		for(unsigned int j = 0; j < v_temp.size(); j++)
			v_temp[j] = -2;

		for(unsigned int j = 0; j < v_coins.size() + 1; j++)
			memo[j] = v_temp;


		int i_result = solution2(v_coins, weight);
		//t2 = clock();
		printf("%d\n", i_result);
		//cout << "time: " << (float)(t2 - t1)/CLOCKS_PER_SEC << endl;
	}
	t2 = clock();
    cout << "Total time: " << (float)(t2 - t1)/CLOCKS_PER_SEC << endl;
	return 0;
}	