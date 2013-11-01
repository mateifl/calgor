#include "books.h"

bool check_partitions(const vector<long long> &numbers, const long long max_partition, const int partition_number) {
    int p_number = 0;
    int len = numbers.size() - 1;
    long long tmp_sum = 0;
    
    while( len > 0 )
    {
        tmp_sum += numbers[len];
        cout << tmp_sum << " " << tmp_sum + numbers[len - 1] << endl;
        if( (tmp_sum + numbers[len - 1]) > max_partition )
        {
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
    long long max_limit = accumulate(numbers.begin(), numbers.end(), 0);
    long long min_limit = *max_element(numbers.begin(), numbers.end());
    cout << max_limit << " " << min_limit << endl;
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


long long max_partition(	vector<long long> numbers, int numbers_size, int partition_number, map<pair<int, int>, long long> &subproblems)
{
    map<pair<int, int>, long long>::iterator it = subproblems.find(make_pair(numbers_size,partition_number));
	if (it != subproblems.end()) {
//        cout << "SP" << endl;
        return it->second;
	}
	if(partition_number == 1) {
		long long s = accumulate(numbers.begin(), numbers.begin() + numbers_size, 0ll);
		subproblems[make_pair(numbers_size, partition_number)] = s; 
		return s;
	}

	if(numbers_size == 0) {
		subproblems.insert(make_pair( make_pair(numbers_size, partition_number), numbers[0])); 
		return numbers[0];
	}
	
	long long max_p = 500 * 10000000l;
	
	for(int i = partition_number - 1; i < numbers_size; i++) {
		long long acc = accumulate(numbers.begin() + i, numbers.begin() + numbers_size, 0ll) ;	
		long long mp = max_partition(numbers, i, partition_number - 1, subproblems);
		max_p = min(max_p, max(mp, acc));
	}
	
	subproblems[make_pair(numbers_size, partition_number)] = max_p; 
	return max_p;
}


void process(string filename) {
    FILE *input_file;
    input_file = fopen(filename.c_str(), "r");
    char pch_line[5120], *pch, pch_line1[128];
    const char *delim = " ";    
    long number;
    int numbers_size, partition_number;
    vector<long long> v1;
    map<pair<int, int>, long long> subproblems;
        
    while(!feof(input_file))
    {
        fscanf(input_file, "%d %d\n", &numbers_size, &partition_number);
        cout << numbers_size << " " << partition_number << endl;
        fgets(pch_line, 5120, input_file);
        pch = strtok(pch_line, delim);
        while( pch != NULL ){
            number = atol(pch);
            v1.push_back(number);
            pch = strtok(NULL, delim);
        }
        cout << "input vector created. size: " << v1.size() << endl;
        cout << max_partition(v1, numbers_size, partition_number, subproblems) << endl;
        v1.clear();
        subproblems.clear();
    }    
    
}

void process_bs(string filename) {
    FILE *input_file;
    input_file = fopen(filename.c_str(), "r");
    char pch_line[5120], *pch, pch_line1[128];
    const char *delim = " ";    
    long number;
    int numbers_size, partition_number;
    vector<long long> v1;
        
    while(!feof(input_file))
    {
        fscanf(input_file, "%d %d\n", &numbers_size, &partition_number);
        cout << numbers_size << " " << partition_number << endl;
        fgets(pch_line, 5120, input_file);
        pch = strtok(pch_line, delim);
        while( pch != NULL ){
            number = atol(pch);
            v1.push_back(number);
            pch = strtok(NULL, delim);
        }
        cout << "input vector created. size: " << v1.size() << endl;
        cout << "sum : " << accumulate(v1.begin(), v1.begin() + 420, 0) << endl;
        cout << max_partition_bs(v1, partition_number) << endl;
        v1.clear();
        
    }    
    
}