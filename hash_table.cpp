#include "hash_table.h"

#include <iostream>
#include <fstream>
using namespace std;


void read_data(string filename, vector<string> &keys, vector<string> &values) {
	
	ifstream input_file(filename.c_str());
	string key, value;
    while(!input_file.eof())
    {
        input_file >> key >> value;
        keys.push_back(key);
		values.push_back(values);
    }
    input_file.close();

}

int main(int argc, char** argv) {

	hash_table<string, string> htable;



	return 0;
}