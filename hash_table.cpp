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

	srand (time(NULL));
	vector<int> index;
	vector<int>::iterator it;
	size_t keys_number = keys.size();

	for(int i = 0; i < keys_number / 10; i++)
		index.push_back( rand() % keys_number );

	clock_t t = clock();
	hash_table<string, string> htable = hash_table<string, string>(ps_keys, ps_values, keys.size());

	cout << "Done creating hash table" << endl;
	string tmp;
	for(it = index.begin(); it != index.end(); it++)
		tmp = htable.get( keys[*it] );
	clock_t t1 = clock();
	cout << "Time custom hash: " << (float)(t1 - t)/CLOCKS_PER_SEC << endl;

	t = clock();
	map<string, string> m;

	for(int i = 0; i < keys.size(); i++)
		m.insert( make_pair(keys[i], values[i]));

	for(it = index.begin(); it != index.end(); it++)
		tmp = m[keys[*it]];
	t1 = clock();
	cout << "Time hash: " << (float)(t1 - t)/CLOCKS_PER_SEC << endl;

	cout << htable.get("111111") << endl;
	cout << m["84102766549"] << endl;

	return 0;
}