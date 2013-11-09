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

void read_data(string filename) {
    FILE *f;
    f = fopen( filename.c_str(), "r");
    
    
    fclose(f);
}


void new_recruits( string_map new_list, string_map old_list,  string_map centers) {
    string_map::iterator it;
    
    for(it = new_list.begin(); it != new_list.end(); it++ ){
        
        
        //if( it->second  )
        
    }
    
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
