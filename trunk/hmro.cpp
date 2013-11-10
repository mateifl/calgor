#include "hmro.h"

string_map read_pairs(FILE *f, int size_first, int size_second) {
    int number_of_pairs;
    char pch_first[size_first], pch_second[size_second];
    string first, second;
    string_map result;
    fscanf(f, "%d\n", &number_of_pairs);
    for(int i = 0; i < number_of_pairs; i++)
    {
        fscanf(f, "%s %s\n", pch_first, pch_second);
        first = pch_first;
        second = pch_second;
        result.insert( make_pair(first, second) );
    }
    return result;
}

vector<string> read_items(FILE *f, int item_size) {
    int number_of_items;
    char pch_item[item_size];
    string item;
    
    fscanf(f, "%d\n", &number_of_items);
    vector<string> result(number_of_items);
    for(int i = 0; i < number_of_items; i++)
    {
        fscanf(f, "%s\n", pch_item);
        item = pch_item;
        result[i] = item;
    }
    
    return result;
}