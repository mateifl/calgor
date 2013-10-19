#include "main.h"
#include "sat.h"

vector<condition> read_sat_data(string filename, set<int> &numbers) {
    vector<condition> conditions;
    ifstream file(filename.c_str());

    if(!file.is_open()) {
        cout << "Error opening file!" << endl;
        exit(1);
    }

    string buffer;
    int t1, t2;
    getline(file, buffer);
    //numbers = atoi(buffer.c_str());
    condition c;

    while(!file.eof()) {
        getline(file, buffer);
        t1 = atoi( buffer.substr(0, buffer.find(" ")).c_str() );
        t2 = atoi( buffer.substr(buffer.find(" ") + 1).c_str() );
        c.t1 = t1;
        c.t2 = t2;
        numbers.insert(t1);
        numbers.insert(t2);
        conditions.push_back(c);
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
bool check_condition(const condition & cond, const vector<bool> numbers) {
    int idx1 = abs(cond.t1);
    bool v1_bool = numbers.at(idx1);
    bool v2_bool = numbers.at(abs(cond.t2));

    if( cond.t1 < 0 )
        v1_bool = !v1_bool;

    if( cond.t2 < 0 )
        v2_bool = !v2_bool;

    return (v1_bool || v2_bool);
}

void preprocess( vector<condition> & conditions, set<int> & numbers ) {
    set<int> numbers_copy(numbers);
    set<int>::iterator it;
    for(it = numbers_copy.begin(); it != numbers_copy.end(); it++){
        int n = (-1) * (*it);
        if( numbers_copy.find(n) == numbers_copy.end() )
            numbers.erase(*it);
    }
}

