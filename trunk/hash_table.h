#ifndef HASH_TABLE_H
#define	HASH_TABLE_H
#include <string>
#include <vector>
using namespace std;



class hash_table {
public:
    hash_table();
    hash_table(size_t size);
    ~hash_table();
    string get(string key);
private:
    vector<string> table;
    int hash_function( string s );
};


#endif	

