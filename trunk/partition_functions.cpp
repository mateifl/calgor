#include "partition_functions.h"


vector<long> median_partition(vector<long> numbers) {
    long l_sum = 0, l_deviation = 0;
    vector<long>::iterator it;
	vector<long> v_indexes;
	
	// this part must be replaced with a STL algorithm 
    for(it  = numbers.begin(); it != numbers.end(); it++)
        sum += *it;

    long median = sum / partition_number;
    cout << "Median: " << median << endl;

	// the next problem is how to determine the deviation median 
	
	sum = 0;
    long index = 0;
    for(it  = numbers.begin(); it != numbers.end(); it++) {
        sum += *it;
        cout << sum << endl;
        if (abs(median - sum) < i_deviation) {
            indexes.push_back(index);
            sum = 0;
        }
        index += 1;
    }

    return indexes;

}

