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
        //cout << v_mask[i] << " ";
    }
    //cout << endl;
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
}

float points_distance(const point & p1, const point & p2) {
    return sqrt( (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) );
}

map<pair<short, short>, float> distances( vector<point> coordinates) {

    vector<point>::iterator it;

    for(it = coordinates.begin(); it != coordinates.end(); it++)
        cout << it->x << " " << it->y;

    cout << endl;

    for(int i = 0; i < coordinates.size(); i++)
        cout << coordinates[i].x << " " << coordinates[i].y;

    cout << endl;
    cout << sizeof(point) << endl;
    cout << coordinates[6].x << " " << coordinates[6].y << endl;

    map<pair<short, short>, float> result;
    size_t vector_length = coordinates.size();
	//vector<point>::iterator it1, it2;
    for(short i = 0; i < vector_length; i++) {
        for(short j = 0; j < vector_length; j++) {
			pair<short, short> indexes = pair<short, short>(i + 1, j + 1);
			point p1 = coordinates[i];
			point p2 = coordinates[j];
			float dist = points_distance(p1, p2);
			cout << " dist = " << dist << " " << p1.x << " " << p1.y << " " << p2.x << " " << p2.y  << endl;
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
    getline(file, buffer);

    point temp_point;
	cout << "Start reading" << endl;
    while( !file.eof() ){
        getline(file, buffer);
        sx = buffer.substr(0, buffer.find(" "));
        sy = buffer.substr(buffer.find(" ") + 1);
        temp_point.x = atof(sx.c_str());
        temp_point.y = atof(sy.c_str());
        points.push_back(temp_point);
    }
	cout << "Data read" << endl;
    return points;
}

float tsp(vector<point> &vertices_coord) {
    size_t vertices_number = vertices_coord.size();
    set<short> v_vertices_set;
	map<pair<short, short>, float> v_dist = distances( vertices_coord );

	cout << "Distances calculated" << endl;

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
			if( v_set.find(short(1)) == v_set.end() )
				continue;

			print_set(v_set);

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

    for(short i = 2; i <= vertices_number; i++) {
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
            }

        }
    }

    set<float> costs;
	set< set<short> > sets = subsets(v_vertices_set, vertices_number);
	cout << "Max sets " << sets.size() << endl;
	set< set<short> >::iterator it = sets.begin();

	for(short i = 1; i <= vertices_number; i++  )
	{
		cout <<  a[*it][i + 1] + v_dist[pair<short, short>( 1, i )] << endl;
	}

	return 0.0f;
}

void print_set( set<short> s ) {
	set<short>::iterator it;
	for( it = s.begin(); it != s.end(); it++)
		cout << " " << *it;

	cout << endl;
}
