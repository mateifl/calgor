#include "main.h"
#include "util.h"
#include "sat.h"


int main() {
	cout << "start" << endl;
    set<int> numbers;
	map<int, scondition> conditions = read_sat_data("2sat1.txt", numbers);
	cout << "data read" << endl;
	cout << "conditions: " << conditions.size() << endl;
    cout << "initial numbers " << numbers.size() << endl;
    set<int> numbers_to_remove = preprocess(conditions, numbers);
    cout << "numbers to remove "<< numbers_to_remove.size() << endl;
	map<int, scondition> new_conditions = remove_conditions(conditions, numbers_to_remove);
	cout << new_conditions.size() << endl;

	numbers = numbers_from_conditions(new_conditions);
	cout << "initial numbers " << numbers.size() << endl;
	numbers_to_remove.clear();
	numbers_to_remove = preprocess(new_conditions, numbers);
	cout << "numbers to remove "<< numbers_to_remove.size() << endl;
	new_conditions = remove_conditions(new_conditions, numbers_to_remove);
	cout << new_conditions.size() << endl;

	numbers = numbers_from_conditions(new_conditions);
	cout << "initial numbers " << numbers.size() << endl;
	numbers_to_remove.clear();
	numbers_to_remove = preprocess(new_conditions, numbers);
	cout << "numbers to remove "<< numbers_to_remove.size() << endl;
	new_conditions = remove_conditions(new_conditions, numbers_to_remove);
	cout << new_conditions.size() << endl;

	numbers = numbers_from_conditions(new_conditions);
	cout << "initial numbers " << numbers.size() << endl;
	numbers_to_remove.clear();
	numbers_to_remove = preprocess(new_conditions, numbers);
	cout << "numbers to remove "<< numbers_to_remove.size() << endl;
	new_conditions = remove_conditions(new_conditions, numbers_to_remove);
	cout << new_conditions.size() << endl;

		numbers = numbers_from_conditions(new_conditions);
	cout << "initial numbers " << numbers.size() << endl;
	numbers_to_remove.clear();
	numbers_to_remove = preprocess(new_conditions, numbers);
	cout << "numbers to remove "<< numbers_to_remove.size() << endl;
	new_conditions = remove_conditions(new_conditions, numbers_to_remove);
	cout << new_conditions.size() << endl;

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

/*
int main()
{

	//vector<point> points = read_data("tsp_tc1.txt");
	/*
    vector<point>::iterator it;

    for(it = points.begin(); it != points.end(); it++)
        cout << it->x << " " << it->y << " ";

    cout << endl;
    */
    // cout << points.at(1).x << " " << points.at(1).y << endl;

    //map<pair<short, short>, float> d = distances( points );
    /*
    cout << d[ pair<short, short>(1, 2) ] << endl;
    cout << d[ pair<short, short>(1, 3) ] << endl;
    cout << d[ pair<short, short>(1, 4) ] << endl;
    cout << d[ pair<short, short>(2, 3) ] << endl;
    cout << d[ pair<short, short>(2, 4) ] << endl;
    cout << d[ pair<short, short>(3, 4) ] << endl;
    */
	//tsp(points);
//}
