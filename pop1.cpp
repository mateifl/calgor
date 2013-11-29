#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <numeric>
#include <algorithm>
#include <set>
#include <map>
using namespace std;

template <typename T> vector<short> select_primes(T low, T high) {
	vector<short> test;

	for(T i = 0; i <= high; i++) {
		test.push_back(1);
	}
	
	T sqr = (T)(sqrt(high) + 1);

	for(T i = 2; i <= sqr; i++) {
		for(T j = i * i; j <= high; j += i) {
			test[ j ] = 0;
		}
	}

    return test;
}

template <typename T> vector<T> prime_numbers(T low, T high) {
    vector<short> test = select_primes(low, high);
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
	T sqr = (T)(sqrt(l_number) + 1);
	typename vector<T>::iterator it;
	for(it = primes.begin(); it != primes.end(); it++){
		if( l_number % *it == 0 )
			return false;
		if( sqr < *it )
			break;
	}
	return true;
}

bool check_number2( long number, vector<long> primes) {
	long n, rest;

	char pch_number[11], pch_buffer[11];
	sprintf(pch_number, "%d", number);
	pch_number[11] = '\0';
	int i = 0, i_copy_lenght;
	cout << strlen(pch_number) << endl;
	while(i < strlen(pch_number) - 1) {
		i_copy_lenght = strlen(pch_number) - i;
		strncpy(pch_buffer, pch_number, strlen(pch_number) - i);
		pch_buffer[i_copy_lenght - 1] = '\0';
		n = atol(pch_buffer);
		strncpy(pch_buffer, pch_number + i_copy_lenght - 1, i + 1);
		pch_buffer[i + 1] = '\0';
		rest = atol(pch_buffer);
		cout << n <<  " " << rest << " " << i << endl;
		i += 1;
	}

}

bool check_number( long number, vector<long> &primes) {
	long n;
	long i = 1;
	while(1)
	{
		n = (long)number / pow(10,i);
		cout << n << endl;
		if( n < 2)
			break;
		if( check_if_prime(n, primes) ){
			long rest = number -  (n * pow(10,i));
			
			if(check_if_prime(rest, primes)){
				cout << n << " " << rest << endl;
				return true;
			}

			bool result = check_number(rest, primes);

			if(result)
				return result;
			else{
				i++;
				continue;
			}
		}
		else
		{
			i++;
			continue;
		}
	}
	return false;
}

long long pop_number(long long l_number) {
	return 0;
}

int main(int argc, char** argv) {
	
	vector<long> primes = prime_numbers(2L, 33000L);

//	cout << check_if_prime(15487469L, primes) << endl;
//	cout << check_if_prime(15487467L, primes) << endl;
	check_number2(1234567, primes);
	return 0;
}