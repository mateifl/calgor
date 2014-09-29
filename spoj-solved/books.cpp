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

bool check_partitions(const vector<long long> &numbers, const long long max_partition, const int partition_number) {
    int p_number = 0;
    int len = numbers.size() - 1;
    long long tmp_sum = 0;
    
    while( len > 0 )
    {
        tmp_sum += numbers[len];
        //cout << tmp_sum << " " << tmp_sum + numbers[len - 1] << endl;
        if( (tmp_sum + numbers[len - 1]) > max_partition )
        {
            // increase the partition number by one if max_partition value 
            // was reached
            p_number += 1;
            tmp_sum = 0;
        }
        len--;
    }
    
    p_number += 1;
    return p_number <= partition_number;
}


long long max_partition_bs(const vector<long long> &numbers, int partition_number)
{
    long long max_limit = accumulate(numbers.begin(), numbers.end(), 0LL);
    long long min_limit = *max_element(numbers.begin(), numbers.end());
    long long average;
    
    while(min_limit < max_limit) {
        average = min_limit + (max_limit - min_limit) / 2;
        if( check_partitions(numbers, average, partition_number) )
            max_limit = average;
        else
            min_limit = average + 1;
    }
    
	return max_limit;
}

void print_partitions(const vector<long long> numbers, const long long max_partition, const int partition_number)
{
    size_t i = numbers.size() - 1, partition_num = partition_number;
    ostringstream line;
    long long temp_sum = 0LL;
    string result = "";
    
    while( i > 0 )
    {

        line << numbers[i];
        result = line.str() + " " + result; 
        
		if ( partition_num == i + 1 ) {
			result =   "/ " + result;
			i--;
			partition_num--; 
			line.clear();
			line.str("");
			continue;
		}

		temp_sum += numbers[i];

        if (temp_sum + numbers[i - 1] > max_partition){
            result =   "/ " + result;
			partition_num -= 1;
            temp_sum = 0LL;
        }
        line.clear();
		line.str("");
        i--;
    }
	line.clear();
	line.str("");
    line << numbers[0];
    cout << line.str() + " " + result << endl;
}

void process_bs() {
    char pch_line[5120], *pch;
    const char *delim = " ";    
    long number;
    int numbers_size, partition_number, testcases;
    vector<long long> v1;
    
    scanf("%d\n", &testcases);
    
    while(testcases > 0)
    {
        scanf("%d %d\n", &numbers_size, &partition_number);
        //cout << numbers_size << " " << partition_number << endl;
        gets(pch_line);
        pch = strtok(pch_line, delim);
        while( pch != NULL ){
            number = atol(pch);
            v1.push_back(number);
            pch = strtok(NULL, delim);
        }
        long long mp = max_partition_bs(v1, partition_number);
        //cout << "Max. partition: " << mp << endl;
	    print_partitions(v1, mp, partition_number);
        v1.clear();
        testcases--;
    }    
    
}
//
//int main(int argc, char* argv[])
//{
//    process_bs();
//    return 0;
//}
//
