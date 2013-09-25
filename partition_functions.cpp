#include "partition_functions.h"

CMedianPartition::CMedianPartition(vector<int> numbers, int partition_number)
{
    m_numbers = numbers;
    mi_partition_number = partition_number;
    mp_memotable = new int*[m_numbers.size()];
    for(unsigned int i = 0; i < m_numbers.size(); i++)
        mp_memotable[i] = new int[m_numbers.size()];
}

vector<int> CMedianPartition::median_partition() {
    vector<int>::iterator it;
	vector<int> v_indexes;
    return v_indexes;
}

int CMedianPartition::median_partition(vector<int> numbers, int partition_number) {
    if(partition_number == 0)
        return 0;
    else if(numbers.size() == 1)
        return numbers[0];

    int best = 10000000;
    for(unsigned int i = 0; i < m_numbers.size(); i++) {
        best = min(best, max(median_partition(), accumulate( numbers.begin(), numbers.begin() + i, 0));
    }

    return best;
}