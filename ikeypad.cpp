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
typedef vector<pair<long, vector<int> > > lp_vector;
typedef vector<lp_vector> lp_matrix;

void solution(int i_letters_number, int i_keys_number, l_vector &v_frequency) {
	lp_matrix memo = lp_matrix(i_keys_number + 1);
	for (int i = 0; i <= i_keys_number; i++)
		memo[i] = lp_vector(i_letters_number + 1);

	vector<int> v1; 
	v1.push_back(1);
	for (int i = 1; i <= i_letters_number; i++)
		memo[1][i] = make_pair(memo[1][i - 1].first + i * v_frequency[i - 1], v1);

	for (int i = 0; i <= i_keys_number; i++) {
		for (int j = i; j <= i_letters_number; j++)
		{
			vector<int> v;
			for (int k = i; k <= j; k++)
			{

			}
		}
	}
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

    }
    
    return 0;
	
}