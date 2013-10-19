#ifndef SAT_H_INCLUDED
#define SAT_H_INCLUDED

struct scondition {
    int t1;
    int t2;
};

typedef struct scondition scondition;

map<int, scondition> read_sat_data(string filename, set<int> &numbers);
bool check_condition(const scondition & cond, const vector<bool> numbers);
set<int> preprocess( map<int, scondition> & conditions, set<int> & numbers );
map<int, scondition> remove_conditions(map<int, scondition> & conditions, set<int> & numbers);
#endif // SAT_H_INCLUDED
