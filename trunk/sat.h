#ifndef SAT_H_INCLUDED
#define SAT_H_INCLUDED

struct condition {
    int t1;
    int t2;
};

vector<condition> read_sat_data(string filename, set<int> &numbers);
typedef struct condition condition;
bool check_condition(const condition & cond, const vector<bool> numbers);
void preprocess( vector<condition> & conditions, set<int> & numbers );

#endif // SAT_H_INCLUDED
