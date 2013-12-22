#include "hash_table.h"



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


	read_data("test_data.txt", keys, values);
	cout << "Data read!" << endl;
	string *ps_keys = &keys[0];
	string *ps_values = &values[0];
	hash_table<string, string> htable = hash_table<string, string>(ps_keys, ps_values, keys.size());

	cout << "Done creating hash table" << endl;
	cout << "Items: " << htable.size() << endl;
	cout << htable.has_key("1212") << endl;
	cout << htable.has_key("84122233538") << endl;
	
	return 0;
}