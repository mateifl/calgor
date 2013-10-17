#include "main.h"
#include "util.h"
#include "tsp.h"





int main()
{
    set<short> input_set;
    input_set.insert((short)1);
    input_set.insert((short)2);
    input_set.insert((short)3);
    input_set.insert((short)4);
    input_set.insert((short)5);

    set< set<short> > sets = subsets(input_set, 3);

    set<short>::iterator it1;
    set< set<short> >::iterator it2;
    set<short> s;

    for( it2 = sets.begin(); it2 != sets.end(); it2++ ) {
        s = *it2;
        for( it1 = s.begin(); it1 != s.end(); it1++ ) {
            cout << *it1 << " ";
        }
        cout << endl;
    }


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
