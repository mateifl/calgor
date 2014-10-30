#include <ctime>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
using namespace std;

typedef vector< set<int> > graph;


void process_disk(	const int disk_number, 
					set<int> &s_installed1, set<int> &s_installed2,
					set<int> &s_ready1, set<int> &s_ready2) {
	if (disk_number == 1) {
        s = state.get(READY_INSTALL1);

        while (!s.empty()) {
        	set<int>::iterator it;
        	for( it = s.start(); i != s.end() ; i++)
        	{
        		
        	}
        }
    }
    else {

    }
}


void solve(graph &in_graph, graph &out_graph, int i_first_disk, int i_second_disk) {
	set<int> s_installed1 = set<int>();
	set<int> s_installed2 = set<int>();
	set<int> s_ready1 = set<int>();
	set<int> s_ready2 = set<int>();

	for (int i = 1; i < inGraph.size(); i++) {
        if (inGraph[i].size() == 0 && i <= i_first_disk) {
            s_ready1.insert(i);
        } else if (inGraph.get(i).size() == 0 && i > i_first_disk) {
            s_ready2.insert(i);
        }
    }

    int start = 1;
    if(s_ready1.size() < s_ready2.size())
    	start = 2;

    while(s_installed1.size() + s.s_installed2.size() <  i_first_disk + i_second_disk )
    {




    }
}



int main(int argc, char** argv) {
	clock_t t0 = clock();

	FILE *ifile = stdin;
	if(ifile == NULL) {
		printf("ERROR no input file\n");
		return 0;
	}

	int i_first_disk, i_second_disk, i_dependencies;
	while (true) {
		int rs = fscanf(ifile, "%d %d %d\n", &i_first_disk, &i_second_disk, &i_dependencies);

		if (i_first_disk == 0 && i_second_disk == 0 && i_dependencies == 0)
			break;

		graph in_graph = graph(i_first_disk + i_second_disk + 1);
		graph out_graph = graph(i_first_disk + i_second_disk + 1);

		int i_tail, i_head;
		for (int i = 0; i < i_dependencies; i++) {
			rs = fscanf(ifile, "%d %d\n", &i_tail, &i_head);
			in_graph[i_tail].insert(i_head);
			out_graph[i_head].insert(i_tail);
		}

		solve(graph in_graph, graph out_graph);

	}

}
