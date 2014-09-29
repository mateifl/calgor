#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <numeric>
using namespace std;
vector<int> prime_numbers(int high);

//int main(int argc, char** argv) {
//	//clock_t t1 = clock();
//	const long MILLION = 10000000;
//	vector<int> primes = prime_numbers(3200);
//    vector<long> numbers = vector<long>(MILLION / 2, 0);
//
//	for(int i = 1; i < primes.size(); i++) {
//		for(long j = (primes[i] * primes[i] - 1) / 2; j <= MILLION / 2; j += primes[i]) {
//			if( !numbers[j] ) {
//				numbers[j] = primes[i];
//			}
//		}
//	}
//
//	for(int i = 1; i <= numbers.size(); i++)
//		if(!numbers[i])
//			numbers[i] += 2*i + 1;
//
//	int testcases;
//	fscanf(stdin, "%d\n", &testcases);
//	long number;
//	long long sum;
//	for(int i = 0; i < testcases; i++){
//		fscanf(stdin, "%ld\n", &number);
//		sum = number;
//		if(number % 2 == 0)
//			printf("%lld\n", accumulate(numbers.begin(), numbers.begin() + (sum / 2), sum));
//		else
//			printf("%lld\n", accumulate(numbers.begin(), numbers.begin() + ((sum + 1)/2), sum) - 1);
//	}
//
//
//    return 0;
//
//}

vector<short> select_primes(int high) {
	vector<short> test = vector<short>(high + 1);
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
    vector<short> test = select_primes(high);
	vector<int> result;
	for(int i = 2; i <= high; i++)
		if(test[i])
			result.push_back(i);

	return result;
}
