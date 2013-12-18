
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

	if( l_number < 1373653 )
		return !(is_composite(2, lnr, s, l_number) && is_composite(3, lnr, s, l_number));	
	if( l_number == 1373653 || l_number == 25326001 )
		return false;
	if( l_number < 25326001)
		return !(is_composite(2, lnr, s, l_number) && is_composite(3, lnr, s, l_number) && is_composite(5, lnr, s, l_number));
	
	return !( is_composite(2, lnr, s, l_number) && is_composite(3, lnr, s, l_number) && 
			  is_composite(5, lnr, s, l_number) && is_composite(7, lnr, s, l_number) );	    

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

bool check_number2( long long number) {
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
		if( !is_prime(n) )
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

		if( is_prime(rest) )
			return true;
		else 
			return check_number2(rest);
	}
	return false;
}

template <typename T> vector<T> read_data(FILE *file)
{
	vector<T> v_data;
	T nr1, nr2, nr3, nr4, nr5, nr6, nr7, nr8;

	while( !feof(file) )
	{
		fscanf(file, "%ld %ld %ld %ld %ld %ld %ld %ld\n", &nr1, &nr2, &nr3, &nr4, &nr5, &nr6, &nr7, &nr8);
		v_data.push_back(nr1);
		v_data.push_back(nr2);
		v_data.push_back(nr3);
		v_data.push_back(nr4);
		v_data.push_back(nr5);
		v_data.push_back(nr6);
		v_data.push_back(nr7);
		v_data.push_back(nr8);
		// cout << nr8 << endl;
	}

	return v_data;
}


/*
int main(int argc, char** argv) {
	FILE *f = fopen("primes48.txt", "r");

	vector<long> data = read_data<long>(f);
	vector<long>::iterator it;
	cout << "Data read" << endl;

	clock_t t2 = clock();

	for(it = data.begin(); it != data.end(); it++)
	{
		if( !is_prime(*it))
			cout << *it << endl;
	}

	clock_t t3 = clock();
    cout << "Calculus: " << (float)(t3 - t2)/CLOCKS_PER_SEC << endl;


	cout << is_prime(838041637 ) << endl;
	cout << is_prime(817504253 ) << endl;
	cout << is_prime(776531419 ) << endl;
	cout << is_prime(99923 ) << endl; 
	cout << is_prime(33191 ) << endl; 
	  
	cout << is_prime(104729 ) << endl;
	cout << is_prime(22303   ) << endl;
	cout << is_prime(1373653) << endl;
	cout << is_prime(25326001) << endl;

	fclose(f);
	/*
	long i_nr_tests, nr;
	char pch_nr[12];

	scanf("%ld\n", &i_nr_tests);
	cout << i_nr_tests << endl;
    clock_t t2 = clock();

	for(int i = 0; i < i_nr_tests; i++) {
        fgets(pch_nr, 11, stdin);			
        nr = atol(pch_nr);
		cout << nr << endl;
		if( nr % 2 == 0)
			nr+=1;
		while(1) {

			bool prime = is_prime(nr);
			if( prime ) {
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
*/


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
			bool prime = is_prime(nr);
			if( prime && check_number2(nr) ){
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
