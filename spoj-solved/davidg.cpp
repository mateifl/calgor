#include <ctime>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <queue>
#include <cmath>
using namespace std;

typedef unsigned int uint;
typedef double float_point;
struct edge
{
    // uint head;
    uint tail;
    float_point val;
};

typedef edge edge;

typedef struct point
{
    float_point x;
    float_point y;
    float_point x_2;
    float_point y_2;
} point;

typedef vector<vector<edge>> graph;

template <class T>
struct greater_edge : binary_function<T, T, bool>
{
    bool operator()(const T &x, const T &y) const
    {
	return x.val > y.val;
    }
};
typedef priority_queue<edge, vector<edge>, greater_edge<edge>> heap;

graph create(vector<point> &points)
{
    clock_t t0 = clock();
    graph g(points.size());

    for (uint i = 0; i < g.size(); i++)
	g[i] = vector<edge>(g.size());

    clock_t t1 = clock();
    // cout << "allocation time: " << (float)(t1 - t0) / CLOCKS_PER_SEC << endl;
    int h = 0;

    for (uint i = 0; i < g.size(); i++)
    {
	for (uint j = i + 1; j < g.size(); j++)
	{
	    // cout << i << " " << j << endl;
	    if (i == j)
		continue;
	    float_point dist = sqrt(pow(points[i].x - points[j].x, 2) + pow(points[i].y - points[j].y, 2));
	    // float_point dist = sqrt(points[i].x_2 + points[j].x_2 + points[i].y_2 + points[j].y_2);
	    g[i][j].tail = j;
	    g[i][j].val = dist;
	    g[j][i].tail = i;
	    g[j][i].val = dist;
	}
    }
    // cout << h << endl;
    clock_t t2 = clock();
    // cout << "compute time: " << (float)(t2 - t1) / CLOCKS_PER_SEC << endl;
    return g;
}

vector<edge> prim(graph &g, int i_source_node)
{
    // the heap
    heap nodes_heap;
    vector<bool> v_bool_visited = vector<bool>(g.size());
    v_bool_visited[i_source_node] = true;

    for (uint i = 0; i < g[i_source_node].size(); i++)
    {
	if (i == i_source_node)
	    continue;
	nodes_heap.push(g[i_source_node][i]);
    }

    vector<edge> v_mst;

    edge next_edge;
    uint i_node_index = 0;

    while (i_node_index < g.size() - 1)
    {
	next_edge = nodes_heap.top();
	nodes_heap.pop();

	// check if the tail is already visited (avoid cycles)
	if (v_bool_visited[next_edge.tail])
	    continue;

	// put the edge in the MST.
	v_mst.push_back(next_edge);

	// add the neighbouring edges in the heap
	for (uint i = 0; i < g[next_edge.tail].size(); i++)
	{
	    if (!v_bool_visited[g[next_edge.tail][i].tail])
	    {
		edge e = g[next_edge.tail][i];
		nodes_heap.push(e);
	    }
	}

	// mark node as visited
	v_bool_visited[next_edge.tail] = true;
	i_node_index += 1;
	//if (i_node_index % 10 == 0)
	//	printf("%d %d\n", i_node_index, nodes_heap.size());
    }

    return v_mst;
}

int main(int argc, char **argv)
{
    clock_t t0 = clock();
    uint i_nodes, i_cost, i_test_cases;
    // FILE *ifile = stdin;
    FILE *ifile = fopen("tc_davidg.in", "r");
    fscanf(ifile, "%d", &i_test_cases);

    for (uint i = 0; i < i_test_cases; i++)
    {
	fscanf(ifile, "%d %d", &i_nodes, &i_cost);
	vector<point> points(i_nodes);

	for (uint j = 0; j < i_nodes; j++)
	    fscanf(ifile, "%lf %lf", &points[j].x, &points[j].y);
	for (uint j = 0; j < i_nodes; j++)
	{
	    points[j].x_2 = points[j].x * points[j].x;
	    points[j].y_2 = points[j].y * points[j].y;
	}
	clock_t t1 = clock();
	cout << "read time: " << (float)(t1 - t0) / CLOCKS_PER_SEC << endl;
	graph g = create(points);
	clock_t t11 = clock();
	cout << "create time: " << (float)(t11 - t1) / CLOCKS_PER_SEC << endl;
	vector<edge> mst = prim(g, 0);
	uint val_mst = 0;
	clock_t t2 = clock();
	cout << "mst time: " << (float)(t2 - t11) / CLOCKS_PER_SEC << endl;

	for (int k = 0; k < mst.size(); k++)
	    val_mst += ceil(mst[k].val * i_cost);
	//cout << "mst = " << val_mst << endl;
	unsigned long int value = val_mst % 1000000007;
	//printf("%lf\n", val_mst * i_cost);
	printf("Scenario #%d: %ld\n", i + 1, value);
    }
    // fclose(ifile);
    return 0;
}