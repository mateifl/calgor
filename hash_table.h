#ifndef HASH_TABLE_H
#define	HASH_TABLE_H

#include <vector>
#include <utility>
using namespace std;


template <typename K, typename V> 
class hash_entry {
public:
	hash_entry(K k, V v);
private:
	K key;
	V value;
};

template <typename K, typename V> 
hash_entry<K, V>::hash_entry(K k, V v) {
	key = k;
	value = v;
};


template <typename K, typename V> 
class hash_table {
public:
    hash_table(K *keys, V *values, size_t items_number);
    ~hash_table();
    V get(const K &key);
    //void put(const K key, const V value);
    bool has_key(const K key);
private:
    vector< hash_entry<K, V> >  v_buffer;
	long hash(K key);
	long compress(long hash_value);
};

template <typename K, typename V> 
hash_table<K, V>::hash_table(K *keys, V *values, size_t items_number) {
	vector< pair<long, hash_entry<K, V> > > hash_codes(items_number);  
	long hash_key = 0, min_hash_key, max_hash_key;
	hash_entry<K, V> entry;

	// Create the hash codes. Detect the min and max hash key 

	for( size_t i = 0; i < items_number; i++)
	{
		long hash_key = hash(keys[i]);
		hash_key = compress(hash_key);	

		if( min_hash_key > hash_key )
			min_hash_key = hash_key;
		if( max_hash_key < hash_key )
			max_hash_key = hash_key;

		entry = hash_entry(keys[i], values[i]);
		hash_codes[i] = make_pair(hash_key, entry);
	}	

	v_buffer = vector< *vector< hash_entry<K, V> > >(max_hash_key);
	vector< pair<long, hash_entry> >::iterator it;

	for( it = hash_codes.begin(); it != hash_codes.end(); it++ )
	{
	 	if( v_buffer[it->first] == null)
	 		v_buffer[it->first] = new vector< hash_entry<K, V> >();
	 	v_buffer[it->first]->push_back(it->second);
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