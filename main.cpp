#include "main.h"
#include "util.h"
#include "partition_functions.h"

vector<int> read_test_data(const string& file_name);

int main()
{
    vector<int> input_data;
    input_data = read_test_data("tc1.txt");
    dprint(input_data);

    CMedianPartition median_partition = CMedianPartition(input_data, 3);
	vector<int> indexes = median_partition.median_partition();
	dprint(indexes);
    return 0;
}


vector<int> read_test_data(const string& file_name) {
    vector<int> v;
    string buffer;
    int l;

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
