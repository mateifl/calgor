#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <ctime>
#include <set>
#include <map>
using namespace std;

const char *operations[2] = {"insert", "delete"};

void homo(map<long, int> &numbers, char* pch_operation, long number, set<long> &number_more_then1) {
	//cout << pch_operation << " " << number << endl;

	if( strcmp(pch_operation, operations[0] ) == 0 ) // insert
	{
		int count = numbers[number];
		count++;

		numbers[number] = count;
		if( count == 2)
			number_more_then1.insert(number);
	}	

	if( strcmp(pch_operation, operations[1] ) == 0 && numbers.find(number) != numbers.end())// delete
	{
		int count = numbers[number];
		int initial_count = count;
		if( count > 0 ){
			count--;
			if( count == 0)
				numbers.erase(number);
			else 
				numbers[number] = count;

			if(count == 1 && initial_count > 1) 
				number_more_then1.erase(number);
		}
	}
	
	bool is_homo = number_more_then1.size() > 0;

	//cout << "size first " << numbers.size() << " " << (*(numbers.begin())).second << endl;
	//cout << "set number: " << number_more_then1.size() << endl;
	//cout << "map number: " << numbers.size() << endl;

	if(numbers.size() == 0 || (numbers.size() == 1 && (*(numbers.begin())).second == 1))
		printf("%s\n", "neither");
		
	if(numbers.size() == 1 && (*(numbers.begin())).second >= 2) 
		printf("%s\n", "homo");

	if(numbers.size() >= 2 && !is_homo) 
		printf("%s\n", "hetero");

	if(numbers.size() >= 2 && is_homo) 
		printf("%s\n", "both");

}

int main(int argc, char** argv) { 
	
	char* operation = new char[7];
	long number;
	int numbers; 
	set<long> number_more_then1;
	fscanf(stdin, "%d\n", &numbers); 
	map<long, int> m_numbers;
	for(int i = 0; i < numbers; i++)
	{	
		fscanf(stdin, "%s %d\n", operation, &number);
		homo(m_numbers, operation, number, number_more_then1 );
	}
    return 0;
}