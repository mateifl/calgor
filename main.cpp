#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <vector>
using namespace std;

void read_input();

int main()
{

    return 0;
}


vector<long> calculate_partitions(vector<long> input_vector) {
    vector<long>::iterator it;
    vector<long> indexes;
    long sum = 0;

    for(it  = input_vector.begin(); it != input_vector.end(); it++)
        sum += *it;

    double median = sum / input_vector.size();

    cout << "Median: " << median << endl;

    sum = 0;
    for(it  = input_vector.begin(); it != input_vector.end(); it++) {
        sum += *it;
        if (modulus(median - sum) < 0.6) {
            // reset sum to 0 and
            sum = 0;
        }
    }


    return indexes;
}
