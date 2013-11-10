#include "hmro.h"
/*
#include <vector>
//#include <algorithm>
#include <iostream>
#include <map>
//#include <numeric>
#include <cstdio>
using namespace std;
*/
//typedef map<string, string> string_map;
//string_map new_centers(string_map &centers);
//string_map read_pairs(FILE *f, int size_first, int size_second); 
//vector<string> read_items(FILE *f, int item_size); 


string_map read_pairs_console(int size_first, int size_second) {
    int number_of_pairs;
    char pch_first[size_first], pch_second[size_second];
    string first, second;
    string_map result;
    scanf("%d\n", &number_of_pairs);
    for(int i = 0; i < number_of_pairs; i++)
    {
        scanf("%s %s\n", pch_first, pch_second);
        first = pch_first;
        second = pch_second;
        result.insert( make_pair(first, second) );
    }
    return result;
}

vector<string> read_items_console(int item_size) {
    int number_of_items;
    char pch_item[item_size];
    string item;
    vector<string> result;
    
    scanf("%d\n", &number_of_items);
    
    for(int i = 0; i < number_of_items; i++)
    {
        scanf("%s\n", pch_item);
        item = pch_item;
        result.push_back(item);
    }
    
    return result;
}


string_map new_centers(string_map &centers) {
    string_map new_c = centers;
    string_map::iterator it;
    
    for( it = centers.begin(); it != centers.end(); it++ ) {
        string old_center = it->first, new_center = it->second;
        string_map::iterator it2;
        vector<string> old_names;
        
        while(true) {
            it2  = centers.find( new_center );

            if( it2 == centers.end() )  
                break;
        
            //cout << "FOCEN: " << old_center << endl;
            old_names.push_back(old_center); 
            new_center = it2->second;
        }
        
        if( old_names.size() > 0 ){
            vector<string>::iterator it_vect;
            for( it_vect = old_names.begin(); it_vect != old_names.end(); it_vect++)
                new_c[*it_vect] = new_center;
        }
        
        old_names.clear();
    }
    
    return new_c;
}

/*
int main(int argc, char** argv) {
    int testcases_number;
    scanf("%d\n", &testcases_number);
    
    while(testcases_number > 0){
        string_map recruits = read_pairs_console(12, 5);
        string_map centers = read_pairs_console(5, 5);
        vector<string> new_r = read_items_console(12);
        string_map new_c = new_centers(centers);
 
        vector<string>::iterator it;
        string mro;
        for( it = new_r.begin(); it != new_r.end(); it++ ){
            mro = recruits[*it];
            if( new_c.find(mro) != new_c.end() ) {
                printf("%s %s\n", it->c_str(), new_c[mro].c_str() );
            }
            else
            {
                printf("%s %s\n", it->c_str(), mro.c_str() );
            }
        }
        
        testcases_number--;
    }
    
}
*/


int main(int argc, char** argv) {
    if(argc != 2)
    {
        cout << "wrong number of parameters!" << endl;
        return -1;
    }
    clock_t t = clock();
    FILE *f;
    f = fopen(argv[1], "r");
    string_map recruits = read_pairs(f, 12, 6);
    cout << "Recruits: " << recruits.size() << endl;
    
    string_map centers = read_pairs(f, 5, 5);
    cout << "Centers: " <<  centers.size() << endl;
    
    vector<string> v = read_items(f, 12);
    cout << "New Recruits: " << v.size() << endl;
    
    fclose(f);
    clock_t t1 = clock();    
    cout << "Read:" <<  ((float)(t1 - t))/CLOCKS_PER_SEC << endl;
    string_map new_c = new_centers(centers);
    clock_t t2 = clock();    
    cout << "Remap:" <<  ((float)(t2 - t1))/CLOCKS_PER_SEC << endl;
        
    vector<string>::iterator it;
    string mro, new_mro;
    
    for( it = v.begin(); it != v.end(); it++ ){
        mro = recruits[*it];
        new_mro = new_c[mro];
        if( new_mro.size() > 0 ) {
            printf("%s %s\n", it->c_str(), new_mro.c_str() );
        }
        else
        {
            printf("%s %s\n", it->c_str(), mro.c_str() );
        }
    }
    clock_t t3 = clock();    
    cout << "Write:" <<  ((float)(t3 - t2))/CLOCKS_PER_SEC << endl;
    cout << "Total:" <<  ((float)(t3 - t))/CLOCKS_PER_SEC << endl;
    return 0;
}