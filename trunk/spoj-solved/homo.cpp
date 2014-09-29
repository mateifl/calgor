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

void homo(map<long, int> &numbers, char* pch_operation, long number, set<long> &number_more_then1, char *pch_result, int &i_position) {
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

	if(numbers.size() == 0 || (numbers.size() == 1 && (*(numbers.begin())).second == 1)){
		memcpy(pch_result + i_position, "neither\n", 8);
		i_position += 8;
	}

	if(numbers.size() == 1 && (*(numbers.begin())).second >= 2) {
		memcpy(pch_result + i_position, "homo\n", 5);
		i_position += 5;
	}

	if(numbers.size() >= 2 && !is_homo){
		memcpy(pch_result + i_position, "hetero\n", 7);
		i_position += 7;
	}

	if(numbers.size() >= 2 && is_homo) {
		memcpy(pch_result + i_position, "both\n", 5);
		i_position += 5;
	}
	return;
}
//
//int main(int argc, char** argv) {
//	clock_t t1 = clock();
//	char* operation = new char[7];
//	long number;
//	int numbers;
//	set<long> number_more_then1;
//	fscanf(stdin, "%d\n", &numbers);
//	map<long, int> m_numbers;
//	char *pch_result = new char[9 * numbers];
//	memset(pch_result, '\0', 9 * numbers);
//	int i_position = 0;
//	for(int i = 0; i < numbers; i++)
//	{
//		fscanf(stdin, "%s %d\n", operation, &number);
//		homo(m_numbers, operation, number, number_more_then1, pch_result, i_position);
//	}
//	clock_t t2 = clock();
//
//	fwrite(pch_result, i_position, 1, stdout);
//	clock_t t3 = clock();
//	cout << i_position << endl;
//	cout << "Time: " << (float)(t2 - t1)/CLOCKS_PER_SEC << endl;
//	cout << "Time: " << (float)(t3 - t1)/CLOCKS_PER_SEC << endl;
//    return 0;
//}
