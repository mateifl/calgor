#ifndef _PARTITION_FUNCTION_H_
#define _PARTITION_FUNCTION_H_

#include "main.h"

class CMedianPartition {

    public:
        CMedianPartition() {
        	mi_partition_number = 0;
        	mp_memotable = NULL;
        };
        CMedianPartition(vector<int> numbers, int partition_number);
        vector<int> median_partition();
        CMedianPartition::~CMedianPartition();
    private:
        int median_partition(vector<int> numbers, unsigned int end_index, int partition_number);
        vector<int> m_numbers;
        int mi_partition_number;
        int** mp_memotable;
};

#endif
