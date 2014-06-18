#include <cstring>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;
typedef vector<pair<int, int> > int_pair_vector; 
typedef pair<int, int> int_pair;

struct sort_pred {
    bool operator()(const std::pair<int,int> &left, const std::pair<int,int> &right) {
        return left.second < right.second;
    }
};

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
		for(unsigned int j = 0; j < coins.size(); j++){
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

		sort(v_coins.begin(), v_coins.end(), sort_pred());

		int i_result = solution2(v_coins, weight);

		if (i_result > 0)
			printf("The minimum amount of money in the piggy-bank is %d.\n", i_result);
		else
			printf("This is impossible.\n");
	}

	return 0;
}	