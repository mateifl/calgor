#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <numeric>
using namespace std;

long solution(vector<int> &numbers, int i_start_index, int i_sum_end, map<pair<int, long>, long> &memo) {

    long v = memo[make_pair(i_start_index, i_sum_end)];
    if( v > 0 )
        return v;

    if(i_start_index == numbers.size())
        return 0;

    long res = 0;
    for(unsigned int i = 1; i < numbers.size() - i_start_index; i++)
    {
        long group_sum = accumulate(numbers.begin() + i_start_index, numbers.begin() + i_start_index + i, 0L);
        if(group_sum < i_sum_end)
            continue;

        long s1 = accumulate(numbers.begin() + i_start_index, numbers.begin() + i_start_index + i, 0L);
        long s2 = accumulate(numbers.begin() + i_start_index + i, numbers.end(), 0L);
        if( s1 <= s2 )
            res += solution(numbers, i_start_index + i, group_sum, memo) + 1;
    }

    if(res > 0)
        memo[make_pair(i_start_index, i_sum_end)] = res;
    return res;
}
//
//int main(int argc, char** argv) {
//    char *pch = new char[27];
//    int i = 1;
//	clock_t t1 = clock();
//
//    while(1)
//    {
//        scanf("%s", pch);
//        if (strncmp(pch, "bye", 3) == 0)
//            break;
//
//        vector<int> numbers = vector<int>(strlen(pch));
//        for(unsigned int j = 0; j < numbers.size(); j++)
//			numbers[j] = pch[j] - '0';
//
//        map< pair<int, long>, long> memo;
//		long s = solution(numbers, 0, 0, memo) + 1;
//
//        printf("%d. %d\n", i, s);
//        i += 1;
//    }
//	clock_t t2 = clock();
////	cout << "time: " << (float)(t2 - t1) / CLOCKS_PER_SEC << endl;
////	cout << "CLOCKS_PER_SEC: " << CLOCKS_PER_SEC << endl;
//    return 0;
//}
