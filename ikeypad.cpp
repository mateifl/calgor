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
	for(it = v.begin() + i_start; it != v.begin() + i_end + 1; it++){
		value += *it * i_index;
		i_index += 1;
	}
	return value;
}


void solution(int i_letters_number, int i_keys_number, l_vector &v_frequency, char *p_keys, char *p_letters) {
	lp_matrix memo = lp_matrix(i_keys_number + 1);
	for (int i = 0; i < i_keys_number + 1; i++)
		memo[i] = lp_vector(i_letters_number + 1);

	vector<int> v1; 
	v1.push_back(1);
	for (int i = 1; i <= i_letters_number; i++)
		memo[1][i] = make_pair(memo[0][i - 1].first + i * v_frequency[i - 1], v1);

	for (int i = 2; i <= i_keys_number; i++) {
		for (int j = i; j <= i_letters_number; j++)
		{
			vector<int> v;
			long l_letter_sum = accum(v_frequency, i - 1, j - 1);
			long l_frecv_sum = accumulate(v_frequency.begin() + i - 1, v_frequency.begin() + j, 0L);
			cout << i << "-" << j << " " << l_letter_sum << " -- " << l_frecv_sum << endl;
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
				cout << k << "--> " << l_letter_sum << "--> " << l_frecv_sum << endl;
			}
			cout << "k1 " << k1 << endl;
			if (k1 == 0) continue;
			memo[i][j].first = l_min;
			memo[i][j].second = vector<int>(memo[i - 1][k1 - 1].second.size());
			copy(memo[i - 1][k1 - 1].second.begin(), memo[i - 1][k1 - 1].second.end(), memo[i][j].second.begin());
			memo[i][j].second.push_back(k1);
		}
	}

	vector<int> indices_list = memo.back().back().second;
	for (vector<int>::const_iterator i = indices_list.begin(); i != indices_list.end(); ++i)
		cout << *i << ' ';
	cout << endl;
	//cout << p_keys << " " << p_letters << endl;

	for (int i = 0; i < indices_list.size() - 1; i++)
	{
		int i_string_size = indices_list[i + 1] - indices_list[i];
		char *pch_partition = new char[i_string_size + 1];
		strncpy(pch_partition, p_letters + indices_list[i] - 1, i_string_size);
		pch_partition[i_string_size] = '\0';
		printf("%c: %s\n", p_keys[i], pch_partition);
		delete[] pch_partition;
	}

	int i_string_size = strlen(p_letters) - indices_list.back() + 1;
	char *pch_partition = new char[i_string_size + 1];
	strncpy(pch_partition, p_letters + indices_list.back() - 1, i_string_size);
	pch_partition[i_string_size] = '\0';
	printf("%c: %s\n", p_keys[strlen(p_keys) - 1], pch_partition);
	printf("\n");
}


int main()
{
    int i_testcases, i_no_letters, i_no_keys;
    long i_frecv;
	char pch_letters[100], pch_keys[100];
    scanf("%d", &i_testcases);
    
    //cout << "Testcases: " << i_testcases << endl;

    for(int i = 0; i < i_testcases; i++){
        scanf("%d %d", &i_no_keys, &i_no_letters);
        //fgets(pch_line, 100, stdin);
		scanf("%s", pch_keys);
		scanf("%s", pch_letters);
        l_vector v_frequency = l_vector(i_no_letters);

        for (int j = 0; j < i_no_letters; j++)
        {
            scanf("%ld", &i_frecv);
            v_frequency[j] = i_frecv;
        }
		printf("Keypad #%d:\n", i + 1);

		if (i_no_keys == 1){
			printf("%c: %s\n", pch_keys[0], pch_letters);
			printf("\n");
			continue;
		}

		if (i_no_keys == i_no_letters){
			for (int i = 0; i < i_no_keys; i++)
				printf("%c: %c\n", pch_keys[i], pch_letters[i]);
			printf("\n");
			continue;
		}

		solution(i_no_letters, i_no_keys, v_frequency, pch_keys, pch_letters);
    }
    
    return 0;
}