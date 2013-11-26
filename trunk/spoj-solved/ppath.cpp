#include "ppath.h"

void check_string_in_primes(int prime, int position, char number, 
                           unordered_map<int, short> &neighbors, const unordered_map<int, short> &numbers )
{
   stringstream ss;
   ss << prime;
   string s = ss.str();
   if( s[position] == number ) 
       return;
   s[position] = number;
   int new_prime = atoi(s.c_str());
   if( new_prime % 2 > 0)
       return;
   if( numbers.find(new_prime) != numbers.end() )
   {
	   neighbors.insert(make_pair(new_prime, (short)1) );
   }
}


// Breath first implementation.
int bfs2(graph2 g, int start_node, int end_node) {
    if(end_node == start_node)
        return 0;
    queue<int> q;
    q.push(start_node);

    int node, path_length;

    unordered_map<int, short> neighbors;
    unordered_map<int, short>::iterator it;
    unordered_map<int, int> distances, visited_nodes;
    distances.insert( make_pair(start_node, 0));

    while(q.size() > 0){
        node = q.front();
        q.pop();
        visited_nodes.insert(make_pair(node, 1));
        neighbors = g[node];
        path_length = distances[node];

        for(it = neighbors.begin(); it != neighbors.end(); it++) {
            if(it->first == end_node)
                return path_length + 1;
            if( visited_nodes.find(it->first) == visited_nodes.end() ) {
                visited_nodes.insert( make_pair(it->first, 1) );
                //neighbors.erase(*it);
                distances.insert( make_pair(it->first, path_length + 1));
                q.push(it->first);
            }
        }
    }

    return distances[end_node];
}