#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <numeric>
#include <algorithm>
#include <ctime>
using namespace std;

template <typename T> vector<short> select_primes(T low, T high) {
	vector<short> test;

	for(T i = 0; i <= high; i++) {
		test.push_back(1);
	}
	
	T sqr = (T)(sqrt( (long double)high) + 1);

	for(T i = 2; i <= sqr; i++) {
		for(T j = i * i; j <= high; j += i) {
			test[j] = 0;
		}
	}

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

template <typename T> bool check_if_prime(T l_number, vector<T> &primes) {
	if( l_number == 1)
		return false;
	if( l_number == 2 || l_number == 3 || l_number == 5 || l_number == 7 || l_number == 11 )
		return true;
    
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

bool check_number2( long long number, vector<long long> primes) {
	long long n, rest;
	char pch_number[11], pch_buffer[11];
	sprintf(pch_number, "%d", number);
	pch_number[11] = '\0';
	unsigned int i = 0, i_copy_lenght;
	
	while(i < strlen(pch_number) - 1) {
		i_copy_lenght = strlen(pch_number) - i;
		strncpy(pch_buffer, pch_number, strlen(pch_number) - i);
		pch_buffer[i_copy_lenght - 1] = '\0';
		n = atol(pch_buffer);
		strncpy(pch_buffer, pch_number + i_copy_lenght - 1, i + 1);
		pch_buffer[i + 1] = '\0';
		// leading zeros not allowed

		if(pch_buffer[0] == '0')
		{
			i++;
			continue;
		}
		rest = atol(pch_buffer);		
		//cout << n << " " << rest << endl;

		if( check_if_prime<long long>(n, primes) ){
			// if the first part is string, check the last
			if(check_if_prime<long long>(rest, primes)){
				// if it is, number can be split, so return true
		//		cout << "Solution: " << n << " " << rest << endl;				
				return true;
			}

		//	cout << "recurse on " << rest << endl;
			bool result = check_number2(rest, primes);

			if(result)
				return result;
			else{
				i++;
				continue;
			}
		}
		else  
			i++;
	}
}

int main(int argc, char** argv) {
	long i_nr_tests;
    long long nr;
	scanf("%d\n", &i_nr_tests);
    char pch_nr[12];
    clock_t t1 = clock();
	vector<long long> primes = prime_numbers<long long>(2LL, 33000LL);
    for(int i = 0; i < i_nr_tests; i++) {
        fgets(pch_nr, 11, stdin);			
        nr = atol(pch_nr);
		while(1) {
//            cout << "nr = " << nr << endl;


			bool is_prime = check_if_prime<long long>(nr, primes);
			if( is_prime && check_number2(nr, primes) ){
				cout << nr << endl;
				break;
			}
			else
				nr++;
		}	
	}
    clock_t t2 = clock();
    cout << "Calculus: " << (float)(t2 - t1)/CLOCKS_PER_SEC << endl;

    vector<long> primes2 = prime_numbers<long>(2LL, 50000000LL);
    clock_t t3 = clock();
    cout << "Primes: " << (float)(t3 - t2)/CLOCKS_PER_SEC << endl;
    
//	cout << check_if_prime(15487469L, primes) << endl;
	// cout << check_number2(nr, primes) << endl;
	return 0;
}

