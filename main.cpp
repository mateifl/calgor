#include "main.h"
#include "util.h"
#include "tsp.h"





int main()
{

	vector<point> points = read_data("tsp_tc1.txt");
	/*
    vector<point>::iterator it;

    for(it = points.begin(); it != points.end(); it++)
        cout << it->x << " " << it->y << " ";

    cout << endl;
    */
    cout << points_distance( points[0], points[1] ) << endl;

    map<pair<short, short>, float> d = distances( points );
    /*
    cout << d[ pair<short, short>(1, 2) ] << endl;
    cout << d[ pair<short, short>(1, 3) ] << endl;
    cout << d[ pair<short, short>(1, 4) ] << endl;
    cout << d[ pair<short, short>(2, 3) ] << endl;
    cout << d[ pair<short, short>(2, 4) ] << endl;
    cout << d[ pair<short, short>(3, 4) ] << endl;
    */
	tsp(points);
}


vector<int> read_test_data(const string& file_name) {
    vector<int> v;
    string buffer;
    int l;

    ifstream file(file_name.c_str());
	if(! file) {
		cerr << "Error opening file" << endl;
		exit(EXIT_FAILURE);
	}

    while( !file.eof() )
    {
        getline(file, buffer);
        l = atol(buffer.c_str());
        v.push_back(l);
    }
    file.close();
    return v;
}
