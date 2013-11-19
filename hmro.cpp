#include "hmro.h"

string_map read_pairs(FILE *f, int size_first, int size_second) {
    int number_of_pairs;
    int line_length = size_first + size_second + 4;
    char *pch_line;
    pch_line = new char[line_length];
    string first, second;
    string_map result;
    fscanf(f, "%d\n", &number_of_pairs);
    for(int i = 0; i < number_of_pairs; i++)
    {
        fgets(pch_line, line_length, f);
        first = strtok(pch_line, " \n");
        second = strtok(NULL, " \n");
        result.insert( make_pair(first, second) );
    }
    return result;
}
