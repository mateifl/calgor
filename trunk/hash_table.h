#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include <string>
using namespace std;

/*
class hash_table<typename key, typename value> {
private:

public:
};
*/

class string_hash_table {
    
private:
    char **table;
    long hash_code(string &str);
    long hash_code(long number);
    long compress(long hash_code);
public:
    /* contructors */
    string_hash_table();
    string_hash_table(long size);

    ~string_hash_table();
    
    /* accesors */
    string get(string key);
    string get(int key);
    /* modifiers */
    void insert(string key, string value);
    void insert(int key, string value);
    void remove(string key);
    void remove(int key);
};


#endif