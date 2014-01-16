#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <cmath>
using namespace std;


vector<long> sieve(const long LIMIT) {

	int count_2 = 0, count_3 = 0, count_5 = 0, count_7 = 0, count_11 = 0, count_13 = 0;
	int size;
	if( LIMIT == 30030 )
		size = 5760;
	vector<long> v_indexes = vector<long>(size);
	int j = 0;
	for(long i = 2; i <= LIMIT; i++ ) {
		if( i % 2 == 0 )
			count_2 += 1;
		else if( i % 3 == 0 )
			count_3 += 1;
		else if( i % 5 == 0 )
			count_5 += 1;
		else if( i % 7 == 0 )
			count_7 += 1;
		else if( i % 11 == 0 )
			count_11 += 1;
		else if( i % 13 == 0 )
			count_13 += 1;
		else 
		{
			v_indexes[j] = i;
			j += 1;
		}
	}

	long sum = count_2 * 2 + count_3 * 3 + count_5 * 5 + count_7 * 7 + count_11 * 11 + count_13 * 13;
	cout << sum;
	return v_indexes;
}


int main(int argc, char** argv) {
	const long MILLION = 1000000;
	vector<long> v_indexes = sieve(30030);
	vector<int> primes = prime_numbers(33000);

	int i_nr_tests;
    long l_number;
	fscanf("%d\n", &i_nr_tests);

	for(int i = 0; i < 100; i++){
		fscanf("%ld\n", &l_number);

	}

}

vector<short> select_primes(int high) {
	vector<short> test = vector<short>(high);


	for(int i = 0; i <= high; i++) {
		test[i] = 1;
	}
	
	int sqr = sqrt((double)high) + 1;

	for(int i = 2; i <= sqr; i++) {
		for(int j = i * i; j <= high; j += i) {
			test[ j ] = 0;
		}
	}

    return test;
}

vector<int> prime_numbers(int high) {
    vector<short> test = select_primes(low, high);
	vector<int> result;
	for(int i = 2; i <= high; i++)
		if(test[i])
			result.push_back(i);

	return result;
}