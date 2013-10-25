#include "tsp.h"
#include "util.h"


void add_to_vector(vector<vector<short> > &result, const vector<short> &initial_set, const char *v_mask, int sub_set_size) {
    vector<short> subset = vector<short>(sub_set_size);
    int j = 0;
    for(int i = 0; i < initial_set.size(); i++)
    {
        if( v_mask[i] == 1 ){
            subset[j]  = initial_set.at(i);
            j++;
        }
    }

    result.push_back(subset);
}


vector<vector<short> > subsets(vector<short> initial_set, size_t sub_set_size)
{
    vector<vector<short> > v_result;
    unsigned short v_set_size = initial_set.size();
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


float points_distance(const point & p1, const point & p2) {
    return sqrt( (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) );
}


map<pair<short, short>, float> distances( vector<point> coordinates) {
    map<pair<short, short>, float> result;
    size_t vector_length = coordinates.size();

    for(unsigned short i = 0; i < vector_length; i++) {
        for(unsigned short j = 0; j < vector_length; j++) {
			pair<short, short> indexes = make_pair(i + 1, j + 1);
			point p1 = coordinates[i];
			point p2 = coordinates[j];
			float dist = points_distance(p1, p2);
			pair<pair<short, short>, float> d = make_pair(indexes, dist);
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


bool find_in_vector(vector_short v, short value_to_find) {
    for(unsigned int i = 0; i < v.size(); i++)
        if(v.at(i) == value_to_find){
            return true;
        }
    return false;
}


float tsp(const vector<point> &vertices_coord) {
    size_t vertices_number = vertices_coord.size();
    vector<short> v_vertices;
	map<pair<short, short>, float> v_dist = distances( vertices_coord );

	cout << "Distances calculated" << endl;

    for(unsigned short i = 1; i <= vertices_number; i++)
        v_vertices.push_back(i);

    short vertex_one = v_vertices[0];
    map< vector_short, map<short, float> > a;
    vector<vector_short>::iterator v_sets_iterator;

    // initialize the solution matrix
    for(unsigned short i = 1; i <= vertices_number; i++) {
        vector< vector_short > sets = subsets(v_vertices, i);
        for( v_sets_iterator = sets.begin(); v_sets_iterator != sets.end(); v_sets_iterator++ ) {
            vector_short v_set = *v_sets_iterator;
			if( !find_in_vector(v_set, vertex_one) )
				continue;

            map<short, float> m;
            if( i == 1) {
                m.insert( make_pair(vertex_one, 0.0f) );
                a.insert( make_pair(v_set, m) );
            }
            else {
                m.insert( make_pair(vertex_one, 10000000.0f) );
                a.insert( make_pair(v_set, m) );
            }
        }
    }

    cout << "Init matrix size: " << a.size() << endl;

    /*
    map< vector_short, map<short, float> >::iterator it1;

    for(it1 = a.begin(); it1 != a.end(); it1 ++) 
        print_set(it1->first, true);

    cout << "end" << endl;
    */
    for(unsigned short i = 2; i <= vertices_number; i++) {
		//cout << "Iteration: " << i << endl;
        // subsets of size i
        vector<vector_short> sets = subsets(v_vertices, i);

        for( v_sets_iterator = sets.begin(); v_sets_iterator != sets.end(); v_sets_iterator++ ) {
            vector_short v = *v_sets_iterator;
            // if 1 not in v_set
            if( !find_in_vector(v, vertex_one) )
                continue;

            for(int j = 0; j < i; j ++) {
                if(v[j] == vertex_one)
                    continue;

                vector_short v_new = v;
                v_new.erase(remove(v_new.begin(), v_new.end(), v[j]), v_new.end());
                /*
                cout << " v = ";
                print_set(v, true);
                cout << " v_new = ";
                print_set(v_new, true);
                */
                // ok here, sets are printed correctly.
                float minim = 10000000.0f;
                // calculate the minimum of the path
                for(int k = 0; k < i - 1; k++) {
                    if( v_new[k] == v [j]){
                        cerr << "Error: " << v[k] << endl;
                        continue;
                    }
                    /*
                    cout << "a";
                    print_set(v_new, false);
                    cout << "[" << v[k] << "] = " << a[v_new][v[k]] <<  endl;
                    cout << "dist[" << v[j] << "][" << v[k] << "] = " << v_dist[make_pair(v[j], v[k])] << endl;
                    */
					float sum = a[v_new][v_new[k]] + v_dist[make_pair(v[j], v_new[k])];
                    if(sum < minim)
                        minim = sum;
                    //cout << "sum: " << sum << " minim: " << minim << endl;
                }
                //cout << "setting result element =======================================================" << endl;
				a[v].insert(make_pair(v[j], minim));
            }
        }
    }

    vector<vector_short> sets = subsets(v_vertices, vertices_number);
	cout << "Max sets (should be 1): " << sets.size() << endl;
	vector<vector_short>::iterator it = sets.begin();
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


void print_set( vector_short s, bool with_newline = true ) {
	vector_short::iterator it;
	cout << "[";
	for( it = s.begin(); it != s.end(); it++)
		cout << " " << *it;
	cout << " ]";
	if(with_newline)
		cout << endl;
}
