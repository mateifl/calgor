#include <vector>
#include <iostream>
#include <map>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

typedef map<string, string> string_map;
typedef map<long, string> long_string_map;
typedef map<int, string> int_string_map;

struct new_recruit {
    int code;
    int birth_date;
};

struct center_move {
	char pch_old_name[5];
	char pch_new_name[5];
};

typedef center_move center_move;
typedef new_recruit new_recruit;


vector<int_string_map> read_recruits(FILE *f, int size_first, int size_second) {
    vector<int_string_map> recruits(100000);

    int line_length = size_first + size_second + 4;
    char pch_line[line_length], pch_birthdate[7], pch_code[6], pch_mro[6];
    int number_of_pairs, birth_date, code;
    string second;

    fscanf(f, "%d\n", &number_of_pairs);

    for(int i = 0; i < number_of_pairs; i++)
    {
        fgets(pch_line, line_length, f);
        strncpy(pch_birthdate, pch_line, 6);
        birth_date = atoi( pch_birthdate );

        strncpy(pch_code, pch_line + 6, 6);
        pch_code[5] = '\0';
        code = atoi( pch_code );

        strncpy(pch_mro, pch_line + 12, 5);
        pch_mro[4] = '\0';
        second = pch_mro;

        recruits[code].insert( make_pair(birth_date, second) );
    }


    return recruits;
}

vector<new_recruit> read_new_recruits(FILE *f) {
     int number_of_pairs, birth_date, code;
     fscanf(f, "%d\n", &number_of_pairs);
     vector<new_recruit> new_r(number_of_pairs);

    int line_length = 13;
    char pch_line[line_length], pch_birthdate[7], pch_code[6];
    new_recruit new_rec;
    for(int i = 0; i < number_of_pairs; i++)
    {
        fgets(pch_line, line_length, f);
        strncpy(pch_birthdate, pch_line, 6);
        birth_date = atoi( pch_birthdate );

        strncpy(pch_code, pch_line + 6, 6);
        pch_code[5] = '\0';
        code = atoi( pch_code );
        new_rec.code = code;
        new_rec.birth_date = birth_date;
        new_r[i] =  new_rec;
    }

    return new_r;
}

vector<center_move> read_pairs(FILE *f, int size_first, int size_second) {
    int number_of_pairs;

    fscanf(f, "%d\n", &number_of_pairs);
    vector<center_move> center_moves = vector<center_move>(number_of_pairs);
    for(int i = 0; i < number_of_pairs; i++)
    {
    	center_move nc;
        fscanf(f, "%s %s", nc.pch_old_name, nc.pch_new_name);
        center_moves[i] = nc;
    }
    return center_moves;
}

string_map new_centers(string_map &centers) {
    string_map new_c = centers;
    string_map::iterator it;
    vector<string> old_names;
    for( it = centers.begin(); it != centers.end(); it++ ) {
        string old_center = it->first, new_center = it->second;
        string_map::iterator it2;

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


int main(int argc, char** argv) {
    FILE *f = stdin;

    int testcases_number;
    fscanf(f, "%d\n", &testcases_number);

    while(testcases_number > 0){
        vector<int_string_map> recruits = read_recruits(f, 12, 6);
        string_map centers = read_pairs(f, 4, 4);
        vector<new_recruit> v = read_new_recruits(f);
        string_map new_c = new_centers(centers);

        vector<new_recruit>::iterator it;
        string mro, new_mro;
        for( it = v.begin(); it != v.end(); it++ ){
            if( !it->birth_date )
                continue;

            mro = recruits[it->code][it->birth_date];
            new_mro = new_c[mro];

            if( new_mro.size() > 0 ) {
                printf("%d%d %s\n", it->birth_date, it->code, new_mro.c_str() );
            }
            else
            {
                printf("%d%d %s\n", it->birth_date, it->code, mro.c_str() );
            }
        }

        testcases_number--;
    }
    return 0;
}

