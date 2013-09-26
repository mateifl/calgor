#include "partition_functions.h"

CMedianPartition::CMedianPartition(vector<int> numbers, int partition_number)
{
    m_numbers = numbers;
    mi_partition_number = partition_number;
    mp_memotable = new int*[m_numbers.size()];
    for(unsigned int i = 0; i < m_numbers.size(); i++)
        mp_memotable[i] = new int[m_numbers.size()];
}

CMedianPartition::~CMedianPartition()
{
    delete[] mp_memotable;
}

vector<int> CMedianPartition::median_partition() {
    vector<int>::iterator it;
	vector<int> v_sums;

	for(unsigned int i = 0; i < m_numbers.size() ; i++) {
		int res = median_partition(m_numbers, i, mi_partition_number);
		cout << "returned " << res << endl;
		v_sums.push_back( res );
	}
    return v_sums;
}

int CMedianPartition::median_partition(vector<int> numbers, unsigned int end_index,  int partition_number) {
    if(partition_number == 0)
        return 0;
    else if(numbers.size() == 1)
        return numbers[0];

//    cout << partition_number << " " << end_index << endl;
    int best = 10000000, sum, recursive_result;
    for(unsigned int i = 0; i < end_index; i++) {
    	sum = accumulate( numbers.begin() + i, numbers.begin() + end_index - 1, 0);
    	recursive_result = median_partition( numbers, end_index, partition_number - 1);
//    	cout << "Sum = " << sum << " " << recursive_result << endl;
        best = min( best, max(recursive_result , sum) );
//        cout << "best: " << best << endl;
    }
//    cout << "best(returned): " << best << endl;
    return best;
}
