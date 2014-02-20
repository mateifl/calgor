#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <ctime>
#include <set>
#include <map>
using namespace std;

long mkbudget(vector<int> v_required_emp, int hire, int sal, int sev) {
	vector<map<pair<long, long>, long> > v_memo(v_required_emp.size());

	pair<long, long> p = make_pair(0, v_required_emp[0]);
	v_memo[0].insert(make_pair(p, (hire + sal) * v_required_emp[0]));
	long max_emp_nr = max_element(v_required_emp.begin(), v_required_emp.end());

	for(int i = 1; i < v_required_emp.size(); i++) {

		if( i < v_required_emp.size() - 1 && v_required_emp[i] <= v_required_emp[i + 1] ) {

		}
		else if( i < v_required_emp.size() - 1 && v_required_emp[i] <= v_required_emp[i + 1] ) {

		}
		else {

		}
	}

	return 0;
}

int main(int argc, char const *argv[])
{
	
	return 0;
}