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
/*
	vector<point> points = read_data("tsp_tc2.txt");
    cout << "Coordinates: " << endl;	
    vector<point>::iterator it;
    for(it = points.begin(); it != points.end(); it++)
        cout << it->x << " " << it->y << endl;
    cout << endl;
*/
    int n = 10;
    vector<short> v;
	for(int i = 0; i < n; i++)
		v.push_back(i);
    
    vector<short*> res = subsets(v, 5);

    for(it = res.begin(); it != res.end(); it++)
    {
        delete [] *it;
    }
	/*set<short> s;
	for(int i = 0; i < n; i++)
		s.insert(i);

	for(int i = 1; i < n; i++) {
		cout << i << endl;
		subsets(s, i);
	} 

    vector<short> v;
	for(int i = 0; i < n; i++)
		v.push_back(i);

    vector<short*> res;
    vector<short*>::iterator it;

	for(int i = 2; i < n; i++) {
		cout << i << endl;
		res = subsets(v, i);
        for(it = res.begin(); it != res.end(); it++)
        {
            delete [] *it;
        }
        res.clear();
	}
    */
    /*
    map<pair<short, short>, float> d = distances( points );
    cout << d[ pair<short, short>(1, 2) ] << endl;
    cout << d[ pair<short, short>(1, 3) ] << endl;
    cout << d[ pair<short, short>(1, 4) ] << endl;
    cout << d[ pair<short, short>(2, 3) ] << endl;
    cout << d[ pair<short, short>(2, 4) ] << endl;
    cout << d[ pair<short, short>(3, 4) ] << endl;
    */
	//tsp(points);
//    vector<point> points = read_data("tsp_tc1.txt");
//    tsp(points);
/*    points = read_data("tsp_tc3.txt");
    tsp(points);
    points = read_data("tsp_tc4.txt");
    tsp(points);
*/
}