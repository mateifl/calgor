#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;

vector<long> calculate_partitions(vector<long> input_vector, int partition_number);

int main()
{
    vector<long> input_data;

    input_data.push_back(100);
    input_data.push_back(200);
    input_data.push_back(300);
    input_data.push_back(400);
    input_data.push_back(500);
    input_data.push_back(600);
    input_data.push_back(700);
    input_data.push_back(800);
    input_data.push_back(900);

    vector<long> indexes = calculate_partitions(input_data, 3);

    vector<long>::iterator it;
    for(it  = indexes.begin(); it != indexes.end(); it++)
        cout << *it << endl;
    return 0;
}


vector<long> calculate_partitions(vector<long> input_vector, int partition_number) {
    vector<long>::iterator it;
    vector<long> indexes;
    long sum = 0;

    for(it  = input_vector.begin(); it != input_vector.end(); it++)
        sum += *it;

    long median = sum / partition_number;
    cout << "Median: " << median << endl;

    sum = 0;
    long index = 0;
    for(it  = input_vector.begin(); it != input_vector.end(); it++) {
        sum += *it;
        cout << sum << endl;
        if (abs(median - sum) < 400) {
            indexes.push_back(index);
            sum = 0;
        }
        index += 1;
    }

    return indexes;
}
