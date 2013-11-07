#include "ppath.h"

int main(int argc, char* argv[])
{
    clock_t c1 = clock();
    set<int> primes = prime_numbers(1000, 10000);
    clock_t c2 = clock() - c1;
    cout << "primes: " << ((float)c2)/CLOCKS_PER_SEC << endl;
    graph g = create_graph(primes);
    clock_t c3 = clock() - c2;
    cout << "graph: " << ((float)c3)/CLOCKS_PER_SEC << endl;
    int path_len = bfs(g, 1033, 8179);
    cout << "bfs: " << path_len << endl;
    clock_t c4 = clock() - c3;
    
    for(int i = 1; i < 20; i++)
    {
        path_len = bfs(g, 1373, 8017);
        cout << "bfs: " << path_len << endl;

        path_len = bfs(g, 1049, 8089);
        cout << "bfs: " << path_len << endl;

        path_len = bfs(g, 7103, 4441);
        cout << "bfs: " << path_len << endl;

        path_len = bfs(g, 8243, 1013);
        cout << "bfs: " << path_len << endl;

        path_len = bfs(g, 6569, 7211);
        cout << "bfs: " << path_len << endl;
    }
    c4 = clock() - c4;
    cout << "Total calls: " << ((float)c4)/CLOCKS_PER_SEC << endl;

    return 0;
}

