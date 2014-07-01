#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <numeric>
#include <algorithm>
using namespace std;

typedef vector<long> l_vector;

bool check_partitions(const l_vector &frecv, const long max_partition, const int partition_number) {
    int p_number = 0, i_position = 1;
    int len = frecv.size() - 1;
    long long tmp_sum = 0;
    
    while( len > 0 )
    {
        tmp_sum += frecv[len] * i_position;
        
        //cout << tmp_sum << " " << tmp_sum + numbers[len - 1] << endl;
        if( (tmp_sum + frecv[len - 1]) > max_partition )
        {
            // increase the partition number by one if max_partition value 
            // was reached
            p_number += 1;
            tmp_sum = 0;
            i_position = 1;
        }
        len--;
    }
    
    p_number += 1;
    return p_number <= partition_number;
}


long max_partition_bs(const l_vector &v_frequencies, int keys)
{
    long max_limit = accumulate(v_frequencies.begin(), v_frequencies.end(), 0LL) * keys;
    long min_limit = *min_element(v_frequencies.begin(), v_frequencies.end());
    long average;
    
    cout << "Limits: " << min_limit << " " << max_limit << endl;

    while(min_limit < max_limit) {
        average = min_limit + (max_limit - min_limit) / 2;
        if( check_partitions(v_frequencies, average, keys) )
            max_limit = average;
        else
            min_limit = average + 1;
    }
    
	return max_limit;
}



int main()
{
    int i_testcases, i_no_letters, i_no_keys;
    long i_frecv;
    char pch_line[100];
    scanf("%d", &i_testcases);
    
    cout << "Testcases: " << i_testcases << endl;

    for(int i = 0; i < i_testcases; i++){
        scanf("%d %d", &i_no_keys, &i_no_letters);
        vector<char> v_keys = vector<char>(i_no_keys);
        //fgets(pch_line, 100, stdin);
		scanf("%s", pch_line);
		cout << "line: " << pch_line << endl;
		
        for(int j = 0; j < i_no_letters; j++)
            v_keys[j] = pch_line[j];

        //fgets(pch_line, 100, stdin);
		scanf("%s", pch_line);
        vector<char> v_letters = vector<char>(i_no_letters);
        l_vector v_frequency = l_vector(i_no_letters);

        for (int j = 0; j < i_no_letters; j++)
        {
            scanf("%ld", &i_frecv);
            // cout << i_frecv << endl;
            v_frequency[j] = i_frecv;
            v_letters[j] = pch_line[j];
        }

        cout << max_partition_bs(v_frequency, i_no_keys) << endl;
    }
    
    return 0;
	
}