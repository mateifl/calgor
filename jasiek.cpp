
#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <ctime>
using namespace std;
typedef unsigned int u_int;
struct min_max {
    u_int min;
    u_int max;
    min_max() : min(100000), max(0) {}

}; 
typedef min_max min_max;

void  print_vector(vector<bool> v) {
	for (ulong i = 0; i < v.size(); i++)
		cout << v[i] << " ";
	cout << endl;
}

void solution(vector<char> moves, u_int n, u_int s, u_int e, u_int w)
{
    time_t t = clock();
    vector< vector<bool> > m(2 * n + 1);

    for (int i = 0; i < m.size(); i++)
        m[i] = vector<bool>(2 * e + 1);
    u_int current_x = e;
    u_int current_y = n;
    m[current_y][current_x] = true;

    cout << current_x << " " << current_y << endl;
    u_int minx = current_x;
    u_int maxx = current_x;
    u_int miny = current_y;
    u_int maxy = current_y;
    time_t t1 = clock();
    cout << "Allocation: "  << (float)(t1 - t)/CLOCKS_PER_SEC << endl; 
    for (int i = 0; i < moves.size(); i++)
    {
        if (moves[i] == 'N')
        {
            current_y -= 1;
            if (current_y < miny)
                miny = current_y;
        }
        if (moves[i] == 'S')
        {
            current_y += 1;
            if (current_y > maxy)
                maxy = current_y;
        }
        if (moves[i] == 'E')
        {
            current_x -= 1;
            if (current_x < minx)
                minx = current_x;
        }
        if (moves[i] == 'W')
        {
            current_x += 1;
            if (current_x > maxx)
                maxx = current_x;
        }
        m[current_y][current_x] = true;
    }

    vector<min_max> hlines(2 * n + 1);
    vector<min_max> vlines(2 * e + 1);

    cout << minx << " " << maxx << endl;
    cout << miny << " " << maxy << endl;
    time_t t2 = clock();
    cout << "Set bitmap: "  << (float)(t2 - t1)/CLOCKS_PER_SEC << endl; 
    // for (int i = 0; i < m.size(); i++)
    // {
    //     print_vector(m[i]);
    // }
    // cout << endl;
    u_int sum = 0;
    for(u_int i = miny; i <= maxy; i++) {
        // print_vector(m[i]);
        for(uint j = minx; j <= maxx; j++) {
            if (m[i][j] == false)
                continue;
            sum += 1;
            if (hlines[i].min > j)
                hlines[i].min = j;
            if (hlines[i].max < j)
                hlines[i].max = j;
            if (vlines[j].min > i)
                vlines[j].min = i;
            if (vlines[j].max < i)
                vlines[j].max = i;
        }
    }
    time_t t3 = clock();
    cout << "Compute max: "  << (float)(t3 - t2)/CLOCKS_PER_SEC << endl; 

    
    for(u_int i = miny; i <= maxy; i++) {
        for(uint j = minx; j <= maxx; j++) {
            // cout << i << " " << j << " " << m[i][j] << endl;
            if (m[i][j] == 1)
                continue;
            else if (vlines[j].min < i && i < vlines[j].max  && hlines[i].min < j && j < hlines[i].max)
                sum += 1;
        }
    }

    time_t t4 = clock();
    cout << "Compute: "  << (float)(t4 - t3)/CLOCKS_PER_SEC << endl; 

    cout << sum << endl;
}

int main(int argc, char const *argv[])
{
    u_int max_index = 0;
    u_int n = 0, s = 0, e = 0, w = 0;
    vector<char> moves(20000);
    char c;
    scanf(" %c", &c);
    for (int i = 0; i < moves.size(); i++)
    {
        scanf(" %c", &moves[i]);
        // cout << (int)moves[i] << endl;
        if(moves[i] == 'K')
            break;   
     
        if (moves[i] == 'N')
            n += 1;
        if (moves[i] == 'S')
            s += 1;
        if (moves[i] == 'E')
            e += 1;
        if (moves[i] == 'W')
            w += 1;
        max_index += 1;
    }
    cout << n << " " << e << " " << s << " " << w << endl;
    moves.erase(moves.begin() + max_index, moves.end());
    solution(moves, n, s, e, w);

    return 0;
}