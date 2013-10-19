#include "main.h"
#include "sat.h"

map<int, scondition> read_sat_data(string filename, set<int> &numbers) {
    map<int, scondition> conditions;
    ifstream file(filename.c_str());

    if(!file.is_open()) {
        cout << "Error opening file!" << endl;
        exit(1);
    }

    string buffer;
    int t1, t2;
    getline(file, buffer);

    scondition c;
	int i = 0;

    while(!file.eof()) {
        getline(file, buffer);
        if(buffer.size() == 0)
            continue;

        t1 = atoi( buffer.substr(0, buffer.find(" ")).c_str() );
        t2 = atoi( buffer.substr(buffer.find(" ") + 1).c_str() );
        c.t1 = t1;
        c.t2 = t2;
        numbers.insert(t1);
        numbers.insert(t2);
		conditions.insert(pair<int, scondition>(i ,c));
		i++;
    }

    return conditions;
}
/*
void sat(string filename) {
    int no_numbers;
    vector<condition> data = read_sat_data(filename, no_numbers);
    int iteration_number = no_numbers + 1;

    vector<bool> numbers;
    for(int i = 0; i < no_numbers; i++  ){
        numbers.push_back(true);
    }

    bool result;
    // main loop
    for(int i = 0; i <= iteration_number; i++)
    {
        for(int j = 0; j <= 2 * no_numbers * no_numbers; j++) {
            vector<condition>::iterator it;
            for(it = data.begin(); it != data.end(); i++) {
                result = check_condition(*it, numbers);
                if(! result ) {

                }
            }
        }
    }
}
*/
bool check_condition(const scondition & cond, const vector<bool> numbers) {
    int idx1 = abs(cond.t1);
    bool v1_bool = numbers.at(idx1);
    bool v2_bool = numbers.at(abs(cond.t2));

    if( cond.t1 < 0 )
        v1_bool = !v1_bool;

    if( cond.t2 < 0 )
        v2_bool = !v2_bool;

    return (v1_bool || v2_bool);
}

map<int, scondition> preprocess(map<int, scondition> & conditions, vector<bool> & initial_numbers) {
    set<int> numbers = numbers_from_conditions(conditions);
    cout << "numbers: " << numbers.size() << endl;
    set<int> numbers_to_remove = find_numbers_to_remove(numbers, initial_numbers);
    cout << "numbers to remove: " << numbers_to_remove.size() << endl;
    return remove_conditions(conditions, numbers_to_remove);

}

set<int> find_numbers_to_remove(set<int> & numbers, vector<bool> & initial_numbers) {
    set<int> numbers_copy(numbers);
	set<int> numbers_to_remove;
    set<int>::iterator it;
    for(it = numbers_copy.begin(); it != numbers_copy.end(); it++){
        int n = (-1) * (*it);
        if( numbers_copy.find(n) == numbers_copy.end() ) {
			numbers_to_remove.insert(*it);

			if(*it < 0)
                initial_numbers[abs(*it)] = false;
            else
                initial_numbers[abs(*it)] = true;

        }
    }
	return numbers_to_remove;
}

map<int, scondition> remove_conditions(map<int, scondition> & conditions, set<int> & numbers) {
	map<int, scondition> new_conditions(conditions);
	map<int, scondition>::iterator it;

	for(it = conditions.begin(); it != conditions.end(); it++){
		if( numbers.find( it->second.t1 ) != numbers.end() || numbers.find( it->second.t2 ) != numbers.end() )
			new_conditions.erase(it->first);
	}
	return new_conditions;
}

set<int> numbers_from_conditions(map<int, scondition> & conditions) {
	map<int, scondition>::iterator it;
	set<int> numbers;
	for(it = conditions.begin(); it != conditions.end(); it++){
		numbers.insert(it->second.t1);
		numbers.insert(it->second.t2);
	}
	return numbers;
}
