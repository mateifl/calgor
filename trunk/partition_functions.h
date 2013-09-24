#ifndef _PARTITION_FUNCTION_H_
#define _PARTITION_FUNCTION_H_

#include "main.h"

class CMedianPartition {
    public:
        CMedianPartition() {};
        CMedianPartition(vector<int> numbers, int partition_number);

        vector<int> median_partition();

    private:
        vector<int> m_numbers;
        int mi_partition_number;
        int** m_memotable;
};

#endif
