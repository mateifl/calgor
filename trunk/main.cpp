#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <vector>
using namespace std;

void read_input();

int main()
{
    read_input();
    return 0;
}


vector<vector<long>> calculate_partitions(vector<long> input_vector) {
    vector<long>::iterator it;
    vector<long> slice;
    long sum = 0;

    for(it  = input_vector.begin(); it != input_vector.end(); it++)
        sum += *it;

    double median = sum / input_vector.size();

    cout << "Median: " << median << endl;



}
