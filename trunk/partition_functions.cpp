#include "partition_functions.h"


vector<long> median_partition(vector<long> numbers, int partition_number) {
    long l_sum = 0;
    vector<long>::iterator it;
	vector<long> v_indexes;

	// this part must be replaced with a STL algorithm
    for(it = numbers.begin(); it != numbers.end(); it++)
        l_sum += *it;

	long median = l_sum / partition_number;
    cout << "Median: " << median << endl;

	// the next problem is how to determine the deviation median

	l_sum = 0;
    long index = 0; //, l_deviation = 100;
	//l_deviation = median / partition_number;

    for(it  = numbers.begin(); it != numbers.end(); ) {
        l_sum += *it;
		it++;
		if ( l_sum + *it - median >= median - l_sum) {
			cout << "Sum: " << l_sum << endl;
            v_indexes.push_back(index);
            l_sum = 0;
        }

        index += 1;
    }

	l_sum = 0;
	index = numbers.size() - 1; //, l_deviation = 100;
	//l_deviation = median / partition_number;

    for(it  = numbers.end(); it != numbers.begin(); ) {
        l_sum += *it;
		it--;
		if ( l_sum + *it - median >= median - l_sum) {
			cout << "Sum: " << l_sum << endl;
            v_indexes.push_back(index);
            l_sum = 0;
        }

        index -= 1;
    }

    return v_indexes;
}
