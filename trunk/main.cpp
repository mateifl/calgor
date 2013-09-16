#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
using namespace std;

vector<long> calculate_partitions(vector<long> input_vector, int partition_number);
vector<long> read_test_data(const string& file_name);
template <class T> void print(vector<T> v); 

int main()
{
    vector<long> input_data;
    
    input_data = read_test_data("tc1.txt");
    print(input_data);
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

vector<long> read_test_data(const string& file_name) {
    vector<long> v;
    string buffer;
    long l;
    ifstream file(file_name);

    while( !file.eof() )
    {
        getline(file, buffer);
        l = atol(buffer.c_str());
        v.push_back(l);
    }
    file.close();
    return v;
}

template <class T> void print(vector<T> v) {
    cout << "Size: " << v.size() << endl;
    for(int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
}