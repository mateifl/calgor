#include "tsp.h"

set< set<short> > subsets(set<short> initial_set, size_t sub_set_size)
{
    set< set<short> > v_result;
    size_t v_set_size = initial_set.size();
    char *v_mask = new char[v_set_size];

    for(unsigned short i = 0; i < v_set_size; i++ )
    {
        if( i < (v_set_size - sub_set_size))
            v_mask[i] = 0;
        else
            v_mask[i] = 1;
        cout << v_mask[i] << " ";
    }
    cout << endl;
    set<short>::iterator it;
    set<short> v_set;
    short i;

    for(it = initial_set.begin(); it != initial_set.end(); it++)
    {
        if( v_mask[i] == 1 )
            v_set.insert( *it );
        i++;
    }
    v_result.insert(v_set);
    v_set.clear();

    while( next_permutation( v_mask, v_mask + v_set_size ) )
    {
    	i = 0;
        for(it = initial_set.begin(); it != initial_set.end(); it++)
        {
            if( v_mask[i] == 1 )
                v_set.insert( *it );
            i++;
        }
        v_result.insert(v_set);
        v_set.clear();
    }

    delete[] v_mask;
    return v_result;
}

float distance(point p1, point p2) {
    return sqrt( (p1.x - p2.x) * (p1.x - p2.x) + (p1.x - p2.x) * (p1.x - p2.x) );
}

map<pair<short, short>, float> distances( vector<point> coordinates) {
    map<pair<short, short>, float> result;
    size_t vector_length = coordinates.size();
    
    for(short i = 0; i < vector_length; i++) {
        for(short j = 0; j < vector_length; j++) {
            result.insert( pair< pair<short, short>, float > pair<short, short>(i, j), distance( coordinates[i], coordinates[j] )   );
        }
    }
    return result;
}

vector<point> read_data(string filename) {
    vector<point> points;
    ifstream file(filename.c_str());

    if(!file.is_open()) {
        cout << "Error opening file!" << endl;
        exit(1);
    }

    string buffer, sx, sy;
    getline(file, buffer);

    point temp_point;

    while( !file.eof() ){
        getline(file, buffer);
        sx = buffer.substr(0, buffer.find(" "));
        sy = buffer.substr(buffer.find(" ") + 1);
        temp_point.x = atof(sx.c_str());
        temp_point.y = atof(sy.c_str());
        points.push_back(temp_point);
    }

    return points;
}

float tsp(vector<point> &vertices_coord) {
    size_t vertices_number = vertices_coord.size();
    set<short> v_vertices_set;

    for(short i = 1; i <= vertices_number; i++)
        v_vertices_set.insert(i);

    short vertex_one = 1;
    map<set<short>, map<short, float> > a;
    set< set<short> >::iterator v_sets_iterator;

    // initialize the solution matrix
    for(short i = 1; i <= vertices_number; i++) {
        set< set<short> > sets = subsets(v_vertices_set, i);

        for( v_sets_iterator = sets.begin(); v_sets_iterator != sets.end(); v_sets_iterator++ ) {
            set<short> v_set = *v_sets_iterator;
            if( v_set.find(short(1)) != v_set.end() && v_set.size() == 1) {
                map<short, float> m;
                m.insert( pair<short, float>(short(1), 0.0f) );
                a.insert( pair< set<short>, map<short, float> >(v_set, m) );
            }
            else if( v_set.find(short(1)) != v_set.end() ) {
                map<short, float> m;
                m.insert( pair<short, float>(short(1), 1000000.0f) );
                a.insert( pair< set<short>, map<short, float> >(v_set, m) );
            }
        }
    }

    for(short i = 2; i <= vertices_number; i++) {
        // subsets of size i
        set< set<short> > sets = subsets(v_vertices_set, i);

        for( v_sets_iterator = sets.begin(); v_sets_iterator != sets.end(); v_sets_iterator++ ) {
            set<short> v_set = *v_sets_iterator;

            // if 1 not in v_set
            if( v_set.find(short(1)) == v_set.end() )
                continue;

            set<short>::iterator it;
            for(it = v_set.begin(); it != v_set.end(); it++) {
                if(*it == (short)1)
                    continue;
                set<short> v_new_set(v_set);
                v_new_set.erase(*it);
                float minim = 1000000.0f;
                // calculate the minimum of the path
                set<short>::iterator new_set_it;
                for(new_set_it = v_new_set.begin(); new_set_it != v_new_set.end(); new_set_it++) {
                    float sum = a[v_new_set][*new_set_it];
                    if(sum < minim) 
                        minim = sum;
                    
                }
            }
        }
    }

    float result = 0.0;
    
    return result;
}
