#include "partition_functions.h"

CMedianPartition::CMedianPartition(vector<int> numbers, int partition_number)
{
    m_numbers = numbers;
    mi_partition_number = partition_number;
    pi_memotable = new int*[m_numbers.size()];
    for(unsigned int i = 0; i < m_numbers.size(); i++)

}

vector<int> CMedianPartition::median_partition() {

    int l_sum = 0;
    vector<int>::iterator it;
	vector<int> v_indexes;

    for(unsigned int i = 0; i < m_numbers.size(); i++)
    {
        max(median_partition());
    }
	// this part must be replaced with a STL algorithm
    return v_indexes;
}

vector<int> median_partition(vector<int> numbers, int partition_number) {

    int best = MAX;

    for(unsigned int i = 0; i < m_numbers.size(); i++) {

        best = min(best, max(median_partition(), accumulate());
    }
}

vector<vector<int> > partition_on_slots(vector<int> frequecies, int slots_number) {
    vector<vector<int> > slots;
    vector<int>::iterator it;

    for(it = frequecies.begin(); it != frequecies.end(); it++) {

    }

    return slots;
}
