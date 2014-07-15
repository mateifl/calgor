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
typedef struct mem{
	long value;
	int position[90];
}  mem;

typedef vector<pair<long, vector<int> > > lp_vector;
typedef vector<lp_vector> lp_matrix;

long accum(l_vector v, int i_start, int i_end)
{
	long value = 0L;
	int i_index = 1;
	l_vector::iterator it;
	for(it = v.begin() + i_start; it != v.begin() + i_start; it++){
		value += *it * i_index;
		i_index += 1;
	}
	return value;
}


void solution(int i_letters_number, int i_keys_number, l_vector &v_frequency) {
	lp_matrix memo = lp_matrix(i_keys_number + 1);
	for (int i = 0; i <= i_keys_number; i++)
		memo[i] = lp_vector(i_letters_number + 1);

	vector<int> v1; 
	v1.push_back(1);
	for (int i = 1; i <= i_letters_number; i++)
		memo[1][i] = make_pair(memo[1][i - 1].first + i * v_frequency[i - 1], v1);

	for (int i = 2; i <= i_keys_number; i++) {
		for (int j = i; j <= i_letters_number; j++)
		{
			vector<int> v;
			long l_letter_sum = accum(v_frequency, i, j);
			long l_frecv_sum = accumulate(v_frequency.begin() + i, v_frequency.begin() + j, 0L);
			memo[i][j] = make_pair(0, v);
			long l_min = 10000000L;
			int k1 = 0;
			for (int k = i; k <= j; k++)
			{
				long s1 = memo[i - 1][k - 1].first + l_letter_sum;
				if (s1 < l_min) {
					l_min = s1;
					k1 = k;
				}
				l_letter_sum -= l_frecv_sum;
				l_frecv_sum -= v_frequency[k - 1];
			}
			if (k1 == 0) continue;
			memo[i][j].first = l_min;
			memo[i][j].second = vector<int>(memo[i - 1][k1 - 1].second.size());
			copy(memo[i - 1][k1 - 1].second.begin(), memo[i - 1][k1 - 1].second.end(), memo[i][j].second.begin());
			memo[i][j].second.push_back(k1);
		}
	}

	vector<int> indices_list = memo[i_keys_number][i_letters_number].second;
	for (vector<int>::const_iterator i = indices_list.begin(); i != indices_list.end(); ++i)
		cout << *i << ' ';
	cout << endl;
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
		
        for(int j = 0; j < i_no_keys; j++)
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
		solution(i_no_letters, i_no_keys, v_frequency);
    }
    
    return 0;
}