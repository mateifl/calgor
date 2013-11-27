#include "hash_table.h"

string_hash_table::string_hash_table() {
   table = new char*[1024*128];
}

string_hash_table::string_hash_table(long size) {
    table = new char*[size];
}

string_hash_table::~string_hash_table() {
    delete []table;
}

long string_hash_table::hash_code(string &key) {
    long hcode;
    return hcode;
}

long string_hash_table::hash_code(long key) {
    long hcode;
    return hcode;
}

long string_hash_table::compress(long hash_code) {
    return 0L;
}

string string_hash_table::get(string key) {
    return "";
}

string string_hash_table::get(int key) {
    return "";
}

void string_hash_table::insert(string key, string value) {
}

void string_hash_table::insert(int key, string value) {
}

void string_hash_table::remove(string key) {
}

void string_hash_table::remove(int key) {
} 