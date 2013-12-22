#include "hash_table.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


void read_data(string filename, vector<string> &keys, vector<string> &values) {
	
	ifstream input_file;
	input_file.open(filename.c_str());
	if(!input_file)
		cout << "Read file error!" << endl;
	string key, value;
    while(!input_file.eof())
    {
        input_file >> key >> value;
        keys.push_back(key);
		values.push_back(value);
    }
    input_file.close();
}

int main(int argc, char** argv) {
	vector<string> keys;
	vector<string> values;
	read_data("hash_test.txt", keys, values);
	cout << "Data read!" << endl;
//	hash_entry<string,string> he = hash_entry<string,string>("key", "value");
//	pair<long, hash_entry<string,string> > p = make_pair(1L, he);
//	vector< pair<long, hash_entry<string, string> > > v(5);
//	v.push_back(p);
	hash_table<string, string> htable(keys, values, keys.size());



	return 0;
}