#include "ppath.h"


set<int> prime_numbers(int low, int high) {
	vector<short> test;

	for(int i = 0; i <= high; i++) {
		test.push_back(1);
	}
	
	int sqr = sqrt(high) + 1;

	for(int i = 2; i <= sqr; i++) {
		for(int j = i * i; j <= high; j += i) {
			test[ j ] = 0;
		}
	}

	set<int> result;
	for(int i = low; i <= high; i++)
		if(test[i])
			result.insert(i);

	return result;
}

graph create_graph(const set<int> &numbers) {
   graph g;
   set<int>::const_iterator it; 
   set<int> neighboors;

   int number;
   for(it = numbers.begin(); it != numbers.end(); it ++)
   {
       number = *it;
       // change one char and check 
       for( char i = '0'; i <= '9'; i++)
       { 
           if(i != '0')
               check_string_in_primes(number, 0, i, neighboors, numbers);
           check_string_in_primes(number, 1, i, neighboors, numbers);
           check_string_in_primes(number, 2, i, neighboors, numbers);
		   check_string_in_primes(number, 3, i, neighboors, numbers);
       }
       g.insert( make_pair(number, neighboors) );
	   neighboors.clear();
   }
   return g;
}

void check_string_in_primes(int prime, int position, char number, 
                           set<int> &neighbors, const set<int> &numbers )
{
   stringstream ss;
   ss << prime;
   string s = ss.str();
   s[position] = number;
   int new_prime = atoi(s.c_str());
   
   if( numbers.find(new_prime) != numbers.end() )
   {
       //cout << "found " << p << " neighbor" << endl; 
	   neighbors.insert(new_prime);
   }
   
}