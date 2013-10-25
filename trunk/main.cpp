#include "main.h"
#include "util.h"
#include "tsp.h"

/*
int main() {
	cout << "start" << endl;
    set<int> numbers;
	map<int, scondition> conditions = read_sat_data("2sat6.txt", numbers);
	int max_set =  *numbers.rbegin();

	vector<bool> initial(max_set);
	for(int i = 0; i < max_set; i++)
        initial.push_back(true);

    cout << "conditions: " << conditions.size() << endl;
    for(int i = 0 ; i < 30; i++)
        conditions = preprocess(conditions, initial);
    cout << "conditions: " << conditions.size() << endl;
}
*/

int main()
{

    int n = 5;
    char letters[5] = {'a', 'b', 'c', 'd', 'e' };
    vector<char> v;

    for(int i = 0; i < n; i++)
        v.push_back(letters[i]);

    vector< vector<char> > res;
    vector< vector<char> >::iterator it;
	for(int i = 2; i < n; i++) {
		cout << i << endl;
		res = subsets2(v, i);
		for(it = res.begin(); it != res.end(); it++){
                    dprint(*it);
		}
        res.clear();
	}

//    vector<point> points = read_data("tsp.txt");
//    tsp(points);

    /*
    map< pair<short, short>, float> m = distances(points);

     cout << m[make_pair(1, 1)] << endl;
    cout << m[make_pair(1, 2)] << endl;
    cout << m[make_pair(1, 3)] << endl;
    cout << m[make_pair(1, 4)] << endl;
    cout << m[make_pair(2, 3)] << endl;
    cout << m[make_pair(3, 4)] << endl;
    */
    
//    points = read_data("tsp_tc4.txt");
//    tsp(points);
//    points = read_data("tsp_tc4.txt");
//    tsp(points);

}
