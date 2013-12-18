#ifndef HASH_TABLE_H
#define	HASH_TABLE_H
#include <string>
#include <vector>
using namespace std;


template <typename K, typename V> class hash_entry<K, V> {
public:
	K key;
	V value;
};


template <typename K, typename V> class hash_table {
public:
    hash_table(K *keys, V *values);
    ~hash_table();
    V get(const K &key);
    //void put(const K key, const V value);
    bool has_key(const K key);
private:
    vector< hash_entry<K, V> >  v_buffer;
	long hash(K key);
	long compress(long hash_value);
};

hash_table::hash_table(K *keys, V *values) {

	i = 0;
	while( keys[0] && values[0] )
	{

	}
}

hash_table::~hash_table() {

}

long hash_table::hash(K key) {
	long hash_key = 0;

	return hash_key;	
}

long hash_table::compress(long hash_value) {
	return 0L;
}

V hash_table::get(const Key &k) {
	long hash_key = hash(key);
	hash_key = compress(hash_key);
	
}

#endif