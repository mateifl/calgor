#include <ctime>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <set>
using namespace std;

typedef vector< set<int> > graph;
typedef vector< vector<int> > list_graph;

void print(vector<int> v)
{
	vector<int>::iterator it;
	for(it = v.begin(); it != v.end(); it++)
		cout << *it << " ";
	cout << endl;

}

void process_disk(const int disk_number,
                    const int i_first_disk,
					graph &in_graph, list_graph &out_graph,
					int &i_installed1, int &i_installed2,
					vector<int> &s_ready1, vector<int> &s_ready2) {
	if (disk_number == 1) {
        vector<int> s = s_ready1;
    	vector<int>::iterator it;
		vector<int>::iterator it2;
    	vector<int> temp;

        while (!s.empty()) {
        	for(it = s.begin(); it != s.end(); it++)
        	{
				if(out_graph[*it].empty())
					continue;
				for(it2 = out_graph[*it].begin(); it2 != out_graph[*it].end(); it2++) {
					in_graph[*it2].erase(*it);
					if(in_graph[*it2].empty() && *it2 > i_first_disk)
						s_ready2.push_back(*it2);
					else if(in_graph[*it2].empty() && *it2 <= i_first_disk) 
						temp.push_back(*it2);
				}
        	}
			i_installed1 += s.size();
        	s = temp;
        	temp.clear();
        }
		s_ready1.clear();
    }
    else {
        vector<int> s = s_ready2;
    	vector<int>::iterator it;
		vector<int>::iterator it2;
    	vector<int> temp;

        while (!s.empty()) {
        	for(it = s.begin(); it != s.end(); it++)
        	{
        		if(out_graph[*it].empty())
					continue;
				for(it2 = out_graph[*it].begin(); it2 != out_graph[*it].end(); it2++) {
					in_graph[*it2].erase(*it);
					if(in_graph[*it2].empty() && *it2 <= i_first_disk)
						s_ready1.push_back(*it2);
					else if(in_graph[*it2].empty() && *it2 > i_first_disk) 
						temp.push_back(*it2);
				}
        	}
			i_installed2 += s.size();
        	s = temp;
        	temp.clear();
        }
		s_ready2.clear();
    }
}


void solve(graph &in_graph, list_graph &out_graph, int i_first_disk, int i_second_disk) {
	vector<int> s_ready1 = vector<int>();
	vector<int> s_ready2 = vector<int>();
	vector<int> s_nodep1 = vector<int>();
	vector<int> s_nodep2 = vector<int>();
	int i_installed1 = 0, i_installed2 = 0;

	for (int i = 1; i < in_graph.size(); i++) {
        if (in_graph[i].size() == 0 && i <= i_first_disk && out_graph[i].size() > 0 ) {
			s_ready1.push_back(i);
		}
		else if (in_graph[i].size() == 0 && i <= i_first_disk && out_graph[i].size() == 0) {
			s_nodep1.push_back(i);
		}
		else if (in_graph[i].size() == 0 && i > i_first_disk && out_graph[i].size() > 0) {
			s_ready2.push_back(i);
        }
		else if (in_graph[i].size() == 0 && i > i_first_disk && out_graph[i].size() == 0) {
			s_nodep2.push_back(i);
		}
    }

    int start = 1;
    if(s_ready1.size() < s_ready2.size())
    	start = 2;

	if (s_ready1.size() == s_ready2.size()){
		if (s_ready1.size() + s_nodep1.size() == i_first_disk)
			start = 1;
		if (s_ready2.size() + s_nodep2.size() == i_second_disk)
			start = 2;
	}

	//if (s_ready1.size() == s_ready2.size())
	//	printf("=");
	//cout << "Start processing: " << i_first_disk << " " << i_second_disk << endl;
    int counter = 0;
	s_ready1.insert(s_ready1.begin() + s_ready1.size(), s_nodep1.begin(), s_nodep1.end());
	s_ready2.insert(s_ready2.begin() + s_ready2.size(), s_nodep2.begin(), s_nodep2.end());
    while(i_installed1 + i_installed2 <  i_first_disk + i_second_disk )
    {
    	counter += 1;
		process_disk(start, i_first_disk, in_graph, out_graph, i_installed1, i_installed1, s_ready1, s_ready2);

		if (i_installed1 + i_installed2 == i_first_disk + i_second_disk)
    		break;

    	if (start == 1)
    		start = 2;
    	else
    		start = 1;

    	counter += 1;
		process_disk(start, i_first_disk, in_graph, out_graph, i_installed1, i_installed1, s_ready1, s_ready2);

    	if (start == 1)
    		start = 2;
    	else
    		start = 1;
    }

	counter += 1;
    if(counter < 3)
    	counter = 3;
    printf("%d\n", counter);
}


int main(int argc, char** argv) {
	clock_t t0 = clock();

	FILE *ifile = stdin;
	if(ifile == NULL) {
		printf("ERROR no input file\n");
		return 0;
	}

	int i_first_disk, i_second_disk, i_dependencies;
	int x = 1;
	while (true) {
		//cout << x << "." << endl;
		x += 1;
		int rs = fscanf(ifile, "%d %d %d\n", &i_first_disk, &i_second_disk, &i_dependencies);

		if (i_first_disk == 0 && i_second_disk == 0 && i_dependencies == 0)
			break;

		graph in_graph = graph(i_first_disk + i_second_disk + 1);
		list_graph out_graph = list_graph(i_first_disk + i_second_disk + 1);

		int i_tail, i_head;
		for (int i = 0; i < i_dependencies; i++) {
			rs = fscanf(ifile, "%d %d\n", &i_tail, &i_head);
			in_graph[i_tail].insert(i_head);
			out_graph[i_head].push_back(i_tail);
		}

		solve(in_graph, out_graph, i_first_disk, i_second_disk);
	}

	clock_t t1 = clock();

	//cout << "Read time: " << (float)(t1 - t0) / CLOCKS_PER_SEC << endl;

}
