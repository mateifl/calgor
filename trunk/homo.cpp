#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <ctime>
#include <list>
#include <map>
using namespace std;

const char [][] operations = {"insert", "delete"};

void homo(map<long, int> &numbers, char* pch_operation, long number) {
	if( strcmp(pch_operation, operations[0] ) // insert
		numbers[number] += 1;
		
	if( strcmp(pch_operation, operations[1] ) // delete
	{
		int count = numbers[number];
		if( count > 0 ){
			count--;
			if( count == 0)
				numbers.erase[number];
			else 
				numbers[number] = count;
		}
	}
	
	if(numbers.size() == 0) 
		printf("%s\n", "hetero");
		
	if(
		printf("%s\n", "hetero");
}

int main(int argc, char** argv) { 
	
	char* operation = new char[7];
	long number;
	int numbers; 
	fscanf(stdin, "%d\n", &numbers); 
	
	for(int i = 0; i < numbers; i++)
	{	
		fscanf(stdin, "%s %d\n", operation, &number);
		
	}
    return 0;
}