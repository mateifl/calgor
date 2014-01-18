#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <cmath>
using namespace std;
vector<int> prime_numbers(int high);
bool is_prime(long l_number);
long find_smallest_div(long number, vector<int> &primes);

vector<long> sieve(const long LIMIT) {
	int size;
	if( LIMIT == 30030 )
		size = 5760;
	vector<long> v_indexes = vector<long>(size);
	int j = 0;
	for(long i = 2; i <= LIMIT; i++ ) {
		if( i % 2 == 0 || i % 3 == 0 || i % 5 == 0 || i % 7 == 0 || i % 11 == 0 || i % 13 == 0   )
			continue;
		else 
		{
			v_indexes[j] = i;
			j += 1;
		}
	}

	return v_indexes;
}

int main(int argc, char** argv) {
	vector<long> v_indexes = sieve(30030);
	vector<int> primes = prime_numbers(33000);

	int i_nr_tests;
    long l_number;
/*
	fscanf(stdin, "%d\n", &i_nr_tests);

	for(int i = 0; i < 100; i++){
		fscanf(stdin, "%ld\n", &l_number);
	}
*/

	long long sum = 0;
	clock_t t1 = clock();
	for(int i = 284; i < 301; i++)
	{
		sum += 76167;
		for(int j = 0; j < v_indexes.size(); j++)
			sum += find_smallest_div( i * 30030 + v_indexes[j], primes);
	}
	clock_t t2 = clock();
	cout << " time: " << (float)(t2 - t1)/CLOCKS_PER_SEC << endl;
	cout << sum << endl;
}

long find_smallest_div(long number, vector<int> &primes) {
	if(is_prime(number))
		return number;

	for(int i = 0; i < primes.size() ; i++)
	{
		if( number % primes[i] == 0)
			return primes[i];
		if( primes[i] > sqrt(number) + 1 )
			return number;
	}
	return number;
}

vector<short> select_primes(int high) {
	vector<short> test = vector<short>(high + 1);
	for(int i = 0; i <= high; i++) 
		test[i] = 1;
	
	int sqr = sqrt((double)high) + 1;

	for(int i = 2; i <= sqr; i++) {
		for(int j = i * i; j <= high; j += i) {
			test[ j ] = 0;
		}
	}

    return test;
}

vector<int> prime_numbers(int high) {
    vector<short> test = select_primes(high);
	vector<int> result;
	for(int i = 2; i <= high; i++)
		if(test[i])
			result.push_back(i);

	return result;
}

long long modpow(long long a, long long b, long long n) {
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

bool is_composite(long a, long d, long s, long l_number)
{
    if( modpow(a, d, l_number ) == 1)
        return false;

    for(long l = 0; l < s; l++)
        if( modpow(a, pow( (long double)2, l) * d, l_number ) == l_number - 1 )
            return false;
    return true;
}

bool is_prime(long l_number) {
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
