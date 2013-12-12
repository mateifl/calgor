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
#include <set>
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

template <typename T> bool check_if_prime(T l_number, vector<T> &primes, set<T> &prime_set) {
	if( l_number == 1)
		return false;
	if( l_number == 2 || l_number == 3 || l_number == 5 || l_number == 7 || l_number == 11 )
		return true;

	if( (l_number - 1) % 6 != 0 && (l_number + 1) % 6 != 0 )
		return false;

	if( prime_set.find( l_number ) != prime_set.end() )
	{
		//cout << "hit" << endl; 
		return true;
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
		strncpy(pch_buffer, pch_number, i_copy_lenght);
		pch_buffer[i_copy_lenght] = '\0';
		n = atol(pch_buffer);

		if( !check_if_prime<long long>(n, primes, primes_set) )
		{
			i++;
			continue;
		}

		strncpy(pch_buffer, pch_number + i_copy_lenght, i);
		pch_buffer[i + 1] = '\0';
		// leading zeros not allowed

		if(pch_buffer[0] == '0')
		{
			i++;
			continue;
		}
		rest = atol(pch_buffer);		
		//cout << n << " " << rest << endl;

		// if the first part is string, check the last
		if(check_if_prime<long long>(rest, primes, primes_set)){
		// if it is, number can be split, so return true
		//		cout << "Solution: " << n << " " << rest << endl;				
			return true;
		}

		//	cout << "recurse on " << rest << endl;
		bool result = check_number2(rest, primes, primes_set);

		if(result)
			return result;
		else{
			i++;
			continue;
		}
	}
	return false;
}

int main(int argc, char** argv) {
	long i_nr_tests;
    long long nr;
	scanf("%d\n", &i_nr_tests);
    char pch_nr[12];
    clock_t t1 = clock();
	vector<long long> primes = prime_numbers<long long>(2LL, 40000LL);
	vector<long long>::iterator it; 
	set<long long> primes_set; 

	for(it = primes.begin(); it != primes.end(); it++)
		primes_set.insert(*it);

    clock_t t2 = clock();
    cout << "Primes: " << (float)(t2 - t1)/CLOCKS_PER_SEC << endl;
	
	for(int i = 0; i < i_nr_tests; i++) {
        fgets(pch_nr, 11, stdin);			
        nr = atol(pch_nr);
		if( nr % 2 == 0)
			nr+=1;
		while(1) {
//            cout << "nr = " << nr << endl;
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

