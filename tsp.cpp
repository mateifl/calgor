#include "tsp.h"

void add_to_vector(vector<short*> &result, vector<short> &initial_set, const char *v_mask, int sub_set_size) {
    vector<short>::iterator it;
    short *p_set = new short[sub_set_size];
    int i = 0;
    
    for(it = initial_set.begin(); it != initial_set.end(); it++)
    {
        if( v_mask[i] == 1 )
        {
            p_set[i] = *it;
            i++;
        }
    }

    result.push_back(p_set);
}


vector<short*> subsets(vector<short> initial_set, size_t sub_set_size)
{
    vector<short*> v_result;
    size_t v_set_size = initial_set.size();
    char *v_mask = new char[v_set_size];

    for(unsigned short i = 0; i < v_set_size; i++ )
    {
        if( i < (v_set_size - sub_set_size))
            v_mask[i] = 0;
        else
            v_mask[i] = 1;
    }

    add_to_vector(v_result, initial_set, v_mask, sub_set_size);

    while( next_permutation( v_mask, v_mask + v_set_size ) )
        add_to_vector(v_result, initial_set, v_mask, sub_set_size);

    delete[] v_mask;
    return v_result;
}

/*
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
    }

    set<short>::iterator it;
    set<short> v_set;
    short i = 0;

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
}*/

float points_distance(const point & p1, const point & p2) {
    return sqrt( (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) );
}

map<pair<short, short>, float> distances( vector<point> coordinates) {
    map<pair<short, short>, float> result;
    size_t vector_length = coordinates.size();

    for(unsigned short i = 0; i < vector_length; i++) {
        for(unsigned short j = 0; j < vector_length; j++) {
			pair<short, short> indexes = pair<short, short>(i + 1, j + 1);
			point p1 = coordinates[i];
			point p2 = coordinates[j];
			float dist = points_distance(p1, p2);
			pair<pair<short, short>, float> d = pair<pair<short, short>, float>( indexes, dist);
			result.insert( d );
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
    int number_of_points;
    float x, y;

    file >> number_of_points;

    point temp_point;
	cout << "Start reading" << endl;
    while( file >> x >> y ){
        temp_point.x = x;
        temp_point.y = y;
        points.push_back(temp_point);
    }
	cout << "Data read" << endl;
    return points;
}

bool find_in_array(short *a, size_t size, short value_to_find) {
    for(unsigned int i = 0; i < size; i++)
        if(a[i] == value_to_find){
            return true;
        }
    return false;
}

short* copy_array(short *a, size_t size, short element_to_remove) {
    short *copy = new short[size];
    for(unsigned int i = 0; i < size; i++)
        if(a[i] != copy[i])
            copy[i] = a[i];
    return copy;
}

float tsp(const vector<point> &vertices_coord) {
    size_t vertices_number = vertices_coord.size();
    vector<short> v_vertices;
	map<pair<short, short>, float> v_dist = distances( vertices_coord );
	
	cout << "Distances calculated" << endl;

    for(unsigned short i = 1; i <= vertices_number; i++)
        v_vertices.push_back(i);

    short vertex_one = 1;
    map<short*, map<short, float> > a;
    vector<short*>::iterator v_sets_iterator;

    // initialize the solution matrix
    for(unsigned short i = 1; i <= vertices_number; i++) {
        vector<short*> sets = subsets(v_vertices, i);
        for( v_sets_iterator = sets.begin(); v_sets_iterator != sets.end(); v_sets_iterator++ ) {
            short* v_set = *v_sets_iterator;
			if( find_in_array(v_set, i, vertex_one) )
				continue;

            if( i == 1) {
                map<short, float> m;
                m.insert( pair<short, float>(short(1), 0.0f) );
                a.insert( pair<short*, map<short, float> >(v_set, m) );
            }
            else {
                map<short, float> m;
                m.insert( pair<short, float>(short(1), 1000000.0f) );
                a.insert( pair<short*, map<short, float> >(v_set, m) );
            }
        }
    }

	cout << "Solution matrix init done " << a.size() << endl;

    for(unsigned short i = 2; i <= vertices_number; i++) {
		cout << i << endl;
        // subsets of size i
        vector<short*> sets = subsets(v_vertices, i);

        for( v_sets_iterator = sets.begin(); v_sets_iterator != sets.end(); v_sets_iterator++ ) {
            short* v_set = *v_sets_iterator;

            // if 1 not in v_set
            if( !find_in_array(v_set, i, vertex_one) )
                continue;

            for(int j = 0; j < i; j ++) {
                if(v_set[j] == vertex_one)
                    continue;

                short* v_new_set = copy_array(v_set, i, j);
                float minim = 10000000.0f;
                // calculate the minimum of the path
                for(int k = 0; k < i - 1; k++) {
					float sum = a[v_new_set][k] + v_dist[pair<short, short>( j, k )];
                    if(sum < minim)
                        minim = sum;
                }
				a[v_set].insert( pair<short, float>(j, minim));
            }
            delete [] v_set;
        }
    }

    vector<short*> sets = subsets(v_vertices, vertices_number);
	cout << "Max sets (should be 1): " << sets.size() << endl;
	vector<short*>::iterator it = sets.begin();
    float cost = 100000000;

	for(unsigned short i = 1; i < vertices_number; i++  )
	{
        float c = a[*it][i + 1] + v_dist[pair<short, short>( 1, i + 1)];
        if(cost > c)
            cost = c;
	}

    cout << "min cost: " << cost << endl;
	return cost;
}

/*
float tsp2(const vector<point> &vertices_coord) {
    size_t vertices_number = vertices_coord.size();
    set<short> v_vertices_set;
	map<pair<short, short>, float> v_dist = distances( vertices_coord );
	
	cout << "Distances calculated" << endl;

    for(unsigned short i = 1; i <= vertices_number; i++)
        v_vertices_set.insert(i);

    short vertex_one = 1;
    map<set<short>, map<short, float> > a;
    set< set<short> >::iterator v_sets_iterator;

    // initialize the solution matrix
    for(unsigned short i = 1; i <= vertices_number; i++) {
        set< set<short> > sets = subsets(v_vertices_set, i);

        for( v_sets_iterator = sets.begin(); v_sets_iterator != sets.end(); v_sets_iterator++ ) {
            set<short> v_set = *v_sets_iterator;
			if( v_set.find(short(1)) == v_set.end() )
				continue;

            if( v_set.size() == 1) {
                map<short, float> m;
                m.insert( pair<short, float>(short(1), 0.0f) );
                a.insert( pair< set<short>, map<short, float> >(v_set, m) );
            }
            else {
                map<short, float> m;
                m.insert( pair<short, float>(short(1), 1000000.0f) );
                a.insert( pair< set<short>, map<short, float> >(v_set, m) );
            }
        }
    }

	cout << "Solution matrix init done " << a.size() << endl;

    for(unsigned short i = 2; i <= vertices_number; i++) {
		cout << i << endl;
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
					float sum = a[v_new_set][*new_set_it] + v_dist[pair<short, short>( *it, *new_set_it )];
                    if(sum < minim)
                        minim = sum;

                }
				a[v_set].insert( pair<short, float>( *it, minim ));
				//print_set(v_set, false);
				//cout << " " << *it << " " << minim << endl;
            }

        }
    }

    set< set<short> > sets = subsets(v_vertices_set, vertices_number);
	cout << "Max sets (should be 1): " << sets.size() << endl;
	set< set<short> >::iterator it = sets.begin();
    float cost = 100000000;

	for(unsigned short i = 1; i < vertices_number; i++  )
	{
        float c = a[*it][i + 1] + v_dist[pair<short, short>( 1, i + 1)];
        if(cost > c)
            cost = c;
	}

    cout << "min cost: " << cost << endl;
	return cost;
}
*/

void print_set( set<short> s, bool with_newline = true ) {
	set<short>::iterator it;
	cout << "{";
	for( it = s.begin(); it != s.end(); it++)
		cout << " " << *it;
	cout << "}";
	if(with_newline)
		cout << endl;
}