#ifndef HASH_TABLE_H
#define	HASH_TABLE_H
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <cmath>
#include <string>
#include <fstream>
#include <ctime>
#include <map>
using namespace std;


template <typename K, typename V> 
class hash_entry {
public:
	hash_entry(K k, V v){
		key = k;
		value = v;
	};
	hash_entry() {};
	K get_key() { return key; };
	V get_value() { return value; };
private:
	K key;
	V value;
};

template <typename K, typename V> 
class hash_table {
public:
    hash_table(K *keys, V *values, size_t items_number);
    ~hash_table();
    V get(const K &key);
    //void put(const K key, const V value);
    bool has_key(const K key);
	size_t size() { return m_items_number; }
private:
    vector< vector< hash_entry<K, V> >* >  v_buffer;
	
	long hash(const char *key);
	long hash(string key);
	long hash(long key);
	long compress(long hash_value);
	size_t m_items_number;
	size_t m_prime;
	long long modpow(long long a, long long b, long long n);
	bool is_composite(long a, long d, long s, long l_number);
	bool is_prime(long l_number);

};

template <typename K, typename V> 
hash_table<K, V>::hash_table(K *keys, V *values, size_t items_number) {
	m_items_number = items_number;
	m_prime = 4 * items_number + 1;
	
	while(!is_prime(m_prime))
		m_prime += 2;
	
	// resize the bucket vector
	v_buffer.resize(m_prime);

	typename vector< hash_entry<K, V> >::iterator it;
	for( size_t i = 0; i < items_number; i++)
	{
		// create the hash key
		long hash_key = hash(keys[i]);
		hash_key = compress(hash_key);

		if( v_buffer[hash_key] == NULL)
	 		v_buffer[hash_key] = new vector< hash_entry<K, V> >();

		// ckeck if the key already exists
		bool exists = false;
		for(it = v_buffer[hash_key]->begin(); it != v_buffer[hash_key]->end(); it++)
		{
			if( it->get_key() == keys[i] ){
				exists = true;
				break;
			}
		}

		if(!exists) {
			hash_entry<K, V> entry = hash_entry<K, V>(keys[i], values[i]);
			v_buffer[hash_key]->push_back(entry);
		}
	}	

}

template <typename K, typename V> 
hash_table<K, V>::~hash_table() {

}

template <typename K, typename V> 
long hash_table<K, V>::hash(const char *key) {
    unsigned long hash_key = 5381;

    for(size_t i = 0; i < strlen(key); i++)
		hash_key = ((hash_key << 5) + hash_key) + key[i];

    return hash_key;
}

template <typename K, typename V> 
long hash_table<K, V>::hash(string key) {
    return hash(key.c_str());
}

template <typename K, typename V> 
long hash_table<K, V>::hash(long key) {
	char pch_key[32];
	int i_char_number = sprintf(pch_key, "%ld", key);
    unsigned long hash = 5381;

    for(size_t i = 0; i < i_char_number; i++)
		hash = ((hash << 5) + hash) + pch_key[i];

    return hash;
}

template <typename K, typename V> 
long hash_table<K, V>::compress(long hash_value) {

	long p = 19999993, a = 7151, b = 65993;	
	return abs((long)(((a * hash_value + b)) % m_prime));
}

template <typename K, typename V> 
V hash_table<K, V>::get(const K &k) {
	V v;
	long index = compress(hash(k));
	if( index >= m_prime )
		return v;
	
	if ( v_buffer[index] != NULL ) {
		//if( v_buffer[index]->size() > 4)
		//cout << v_buffer[index]->size() << endl;
		typename vector< hash_entry<K, V> >::iterator it;
		for (it = v_buffer[index]->begin(); it != v_buffer[index]->end(); it++) {
			if ( k == it->get_key()) 
				return it->get_value();
		}
	}

	return v;

}

template <typename K, typename V>
bool hash_table<K, V>::has_key(const K key) {
	long index = compress(hash(key));
	if( index >= m_prime )
		return false;
	if ( v_buffer[index] != NULL ) {
		typename vector< hash_entry<K, V> >::iterator it;
		for (it = v_buffer[index]->begin(); it != v_buffer[index]->end(); it++) {
			if ( key == it->get_key()) 
				return true;
		}
	}

	return false;
}

template <typename K, typename V>
long long hash_table<K, V>::modpow(long long a, long long b, long long n) {
	long long res = 1;
	//int counter = 0;
	while (b)
	{
		//counter += 1;
		if (b % 2) { res = (res * a) % n; }
		a = (a * a) % n;
		b /= 2;
	}
	//cout << "counter "<< counter << endl;
	return res;
}

template <typename K, typename V>
bool hash_table<K, V>::is_composite(long a, long d, long s, long l_number)
{
    if( modpow(a, d, l_number ) == 1)
        return false;

    for(long l = 0; l < s; l++)
        if( (long)modpow(a, pow( (long double)2, l) * d, l_number ) == l_number - 1 )
            return false;
    return true;
}

template <typename K, typename V>
bool hash_table<K, V>::is_prime(long l_number) {
//	printf("prime %ld \n", l_number);
	if( l_number == 1 || l_number % 2 == 0)
		return false;
	if( l_number == 2 || l_number == 3 || l_number == 5 || l_number == 7 || l_number == 11 )
		return true;
	if( l_number == 13 || l_number == 17 || l_number == 23 || l_number == 19 || l_number == 29 )
		return true;
	if( (l_number - 1) % 6 != 0 && (l_number + 1) % 6 != 0 )
		return false;

	long lnr = l_number - 1;
	long s = 0;

	while(lnr % 2 == 0) {
		s += 1;
		lnr = lnr / 2;
	}

	if( l_number < 1373653 )
		return !(is_composite(2, lnr, s, l_number) && is_composite(3, lnr, s, l_number));	
	if( l_number == 1373653 || l_number == 25326001 )
		return false;
	if( l_number < 25326001)
		return !(is_composite(2, lnr, s, l_number) && is_composite(3, lnr, s, l_number) && is_composite(5, lnr, s, l_number));
	
	return !( is_composite(2, lnr, s, l_number) && is_composite(3, lnr, s, l_number) && 
			  is_composite(5, lnr, s, l_number) && is_composite(7, lnr, s, l_number) );	    
}

#endif
