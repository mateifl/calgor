#include "main.h"
#include "util.h"
#include "partition_functions.h"

vector<long> read_test_data(const string& file_name);


int main()
{
    vector<long> input_data;

    input_data = read_test_data("tc1.txt");
    dprint(input_data);

	vector<long> indexes = median_partition(input_data, 3);
	dprint(indexes);
    return 0;
}



vector<long> read_test_data(const string& file_name) {
    vector<long> v;
    string buffer;
    long l;

    ifstream file(file_name.c_str());
	if(! file) {
		cerr << "Error opening file" << endl;
		exit(EXIT_FAILURE);
	}

    while( !file.eof() )
    {
        getline(file, buffer);
        l = atol(buffer.c_str());
        v.push_back(l);
    }
    file.close();
    return v;
}


