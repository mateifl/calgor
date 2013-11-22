#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include <string>
#include <vector>
using namespace std;

template <typename key, typename value>  class hash_table {
    private:
        vector<value> values;
        
    public:
        value get(key k);
        void insert(key k, value v);
        void remove(key k);
        void clear() {
            values.clear();
        }

};


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