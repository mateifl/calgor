#ifndef _BOTTOM_H_
#define _BOTTOM_H_

#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <string>
#include <cstdio>
#include <set>
#include <stack>
#include <ctime>
#include <cstring>
using namespace std;

typedef map<int, vector<int> > graph;
typedef vector< vector<int> > graph2;

template <typename T> class  dfs_visitor {
public:
    virtual void visit(vector<T> nodes) = 0;
};

template <typename T> class finishing_times_visitor : public dfs_visitor<T> {
public:
	vector<T> finish_times(){
		return mv_finishing_times;
	}

    virtual void visit(vector<T> nodes) {
		mv_finishing_times.push_back(nodes[0]);
	}
private:
    vector<T> mv_finishing_times;
};

template <typename T> class sccs_leader_visitor : public dfs_visitor<T> {
public:

	map<T, T> leaders() { 
		return mm_leaders;
	}
	virtual void visit(vector<T> nodes){
		mm_leaders.insert(make_pair(nodes[0], nodes[1]));
	};
private:
	map<T, T> mm_leaders;
};


template <typename G, typename T> 
void generic_dfs(G &g, T start_node, map<T, short> &processed_nodes, dfs_visitor<T> *visitor){
	stack<T> node_stack;
    node_stack.push(start_node);
	T node;

	vector<T> neighbors;
    typename vector<T>::iterator it;
	vector<T> nodes;

    while(node_stack.size() > 0){
		nodes.clear();
        node = node_stack.top();
		// mark node as discovered
		processed_nodes[node] = 1;
		// get the neighbours
        neighbors = g[node];
		bool continue_flag = false;

		for(it = neighbors.begin(); it != neighbors.end(); it++) {
			short node_state = processed_nodes[*it];

			if( node_state == 2 )
				continue;
			else if(node_state == 0)
			{
				processed_nodes[*it] = 1;
				node_stack.push(*it);
				continue_flag = true;
				break;
			}
		}

		if(continue_flag)
			continue;
		// node processed
		processed_nodes[node] = 2;
		node_stack.pop();
		nodes.push_back(node);
		nodes.push_back(start_node);
		visitor->visit(nodes);
    }
}

template <typename T> T access_iterator(vector<T> i, int j) { return j; }

template <typename T> T access_iterator(pair<const T, T> &i, int j) { return i.first; }

template <typename G, typename T> map<T, T> calculate_sccs( G &g, G &g_reversed) {
	// run dfs on the reversed graph
	finishing_times_visitor<T> *v = new finishing_times_visitor<T>();
	typename G::iterator it;
	map<T, short> processed_nodes;
    int j = 0;
	for(it = g_reversed.begin(); it != g_reversed.end(); it++)
	{
        T node = access_iterator<T>(*it, j);
		if(processed_nodes[node] == 2)
			continue;
		generic_dfs<G,T>(g_reversed, node, processed_nodes, v);
        j += 1;		
	}
	vector<int> finishing_times = v->finish_times();
	delete v;

    // run dfs on the initial graph in order of the finishing times

	sccs_leader_visitor<T> *v2 = new sccs_leader_visitor<T>();
	vector<int>::reverse_iterator rit;
	processed_nodes.clear();
	for(rit = finishing_times.rbegin(); rit != finishing_times.rend(); ++rit){
		if(processed_nodes[*rit] == 2)
			continue;

		generic_dfs<G,T>(g, *rit, processed_nodes, v2);
	}
	map<T, T> leaders = v2->leaders();
	delete v2;

	return leaders;
}

void read_data(FILE *f, graph &g, graph &g_reversed);
#endif