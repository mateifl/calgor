#include "hmro.h"

string_map read_pairs(FILE *f, int size_first, int size_second) {
    int number_of_pairs;
    int line_length = size_first + size_second + 4;
    char pch_line[line_length];
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

vector<string> read_items(FILE *f, int item_size) {
    int number_of_items;
    char pch_item[item_size];
    string item;
    char *p;
    
    fscanf(f, "%d\n", &number_of_items);
    vector<string> result;
    for(int i = 0; i < number_of_items; i++)
    {
        p = fgets(pch_item, item_size, f);
        if(p == NULL)
            cerr << "Error reading items!" << endl;
        item = pch_item;
        result.push_back(item);
    }
    
    return result;
}