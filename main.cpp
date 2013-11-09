#include "hmro.h"

int main(int argc, char **argv)
{
    string_map s;
    /*
    s.insert( make_pair("test1", "test2") );
    s.insert( make_pair("test2", "test3") );
    s.insert( make_pair("test3", "test4") );
    s.insert( make_pair("test5", "test6") );
    s.insert( make_pair("test6", "test7") );
    s.insert( make_pair("test_key4", "test_value4") );
    
    string_map s1 = new_centers(s);
    
    string_map::iterator it;
    
    for( it = s1.begin(); it != s1.end(); it++ ) {
        cout << it->first << " " << it->second << endl;
    }
     */
    FILE *f;
    f = fopen("hmro_tc.txt", "r");
    s = read_pairs(f, 11, 5);
    cout << s.size() << endl;
    string_map centers = read_pairs(f, 5, 5);
    cout << centers.size() << endl;
    fclose(f);
    string_map new_c = new_centers(centers);
        
    return 0;
}