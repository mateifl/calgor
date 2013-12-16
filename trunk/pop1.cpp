
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <set>
using namespace std;

long modpow(long a, long b, long n) {
	long res = 1;
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
	if( l_number == 1 || l_number % 2 == 0)
		return false;
	if( l_number == 2 || l_number == 3 || l_number == 5 || l_number == 7 || l_number == 11 )
		return true;
	if( (l_number - 1) % 6 != 0 && (l_number + 1) % 6 != 0 )
		return false;

	long lnr = l_number - 1;
	long s = 0;

	while(lnr % 2 == 0) {
		s += 1;
		lnr = lnr / 2;
	}

    srand ( time(NULL) );
    long random_number;

    for(int i = 1; i <= 5; i++) 
    {
        random_number = rand() % (l_number - 1);

    }



}

template <typename T> vector<short> select_primes(T low, T high) {
	vector<short> test;

	for(T i = 0; i <= high; i++)
		test.push_back(1);
	
	T sqr = (T)(sqrt( (long double)high) + 1);

	for(T i = 2; i <= sqr; i++) 
		for(T j = i * i; j <= high; j += i) 
			test[j] = 0;

    return test;
}

template <typename T> vector<T> prime_numbers(T low, T high) {
    vector<short> test = select_primes<T>(low, high);
	vector<T> result;
	for(T i = low; i <= high; i++)
		if(test[i])
			result.push_back(i);

	return result;
}

template <typename T> bool check_if_prime(T l_number, vector<T> &primes, set<T> &prime_set) {
	if( l_number == 1)
		return false;
	if( l_number == 2 || l_number == 3 || l_number == 5 || l_number == 7 || l_number == 11 )
		return true;

	if( (l_number - 1) % 6 != 0 && (l_number + 1) % 6 != 0 )
		return false;

	if( l_number < 35000LL  )
	{
		return (prime_set.find( l_number ) != prime_set.end());
	}

    T sqr =  sqrt( ( long double )l_number ) + 1;
	typename vector<T>::iterator it;
	for(it = primes.begin(); it != primes.end(); it++){
		if( l_number % *it == 0 )
			return false;
		if( sqr < *it )
			break;
	}
	return true;
}

bool check_number2( long long number, vector<long long> &primes, set<long long> &primes_set) {
	long long n, rest;
	char pch_number[11], pch_buffer[11];
	sprintf(pch_number, "%d", number);
	pch_number[10] = '\0';
	unsigned int i = 1, i_copy_lenght;
	
	while(i < strlen(pch_number)) {
		i_copy_lenght = strlen(pch_number) - i;
		strncpy(pch_buffer, pch_number, i);
		pch_buffer[i] = '\0';
		n = atol(pch_buffer);
		//cout << "n = " << n << endl;
		if( !check_if_prime<long long>(n, primes, primes_set) )
		{
			i++;
			continue;
		}
		//cout << "n is prime" << endl;
		strncpy(pch_buffer, pch_number + i, i_copy_lenght);
		pch_buffer[i_copy_lenght] = '\0';
		// leading zeros not allowed

		if(pch_buffer[0] == '0')
		{
			i++;
			continue;
		}
		rest = atol(pch_buffer);	

		bool res = check_number2(rest, primes, primes_set);

		if(res)
			return res;

		return check_if_prime(rest, primes, primes_set);
	}
	return false;
}

int main(int argc, char** argv) {
	long i_nr_tests;
    long long nr;
	scanf("%ld\n", &i_nr_tests);
    char pch_nr[12];
    clock_t t1 = clock();
	vector<long long> primes = prime_numbers<long long>(2LL, 35000LL);
	vector<long long>::iterator it; 
	set<long long> primes_set; 

	for(it = primes.begin(); it != primes.end(); it++) {
		primes_set.insert(*it);
	}

    clock_t t2 = clock();
    cout << "Primes: " << (float)(t2 - t1)/CLOCKS_PER_SEC << endl;
	
    cout << i_nr_tests << endl;

	for(int i = 0; i < i_nr_tests; i++) {
        fgets(pch_nr, 11, stdin);			
        nr = atol(pch_nr);
		if( nr % 2 == 0)
			nr+=1;
		while(1) {

			bool is_prime = check_if_prime<long long>(nr, primes, primes_set);
			if( is_prime && check_number2(nr, primes, primes_set) ){
				printf("%d\n", nr);
				break;
			}
			else
				nr+=2;
		}	
	}
    clock_t t3 = clock();
    cout << "Calculus: " << (float)(t3 - t2)/CLOCKS_PER_SEC << endl;

	return 0;
}

