#include "ppath.h"


set<int> prime_numbers(int low, int high) {
	vector<short> test;

	for(int i = 0; i <= high; i++) {
		test.push_back(1);
	}
	
	int sqr = sqrt((double)high) + 1;

	for(int i = 2; i <= sqr; i++) {
		for(int j = i * i; j <= high; j += i) {
			test[ j ] = 0;
		}
	}

	set<int> result;
	for(int i = low; i <= high; i++)
		if(test[i])
			result.insert(i);

	return result;
}

graph create_graph(const set<int> &numbers) {
   graph g;
   set<int>::const_iterator it; 
   set<int> neighboors;

   int number;
   for(it = numbers.begin(); it != numbers.end(); it ++)
   {
       number = *it;
       // change one char and check 
       for( char i = '0'; i <= '9'; i++)
       { 
           if(i != '0')
               check_string_in_primes(number, 0, i, neighboors, numbers);
           check_string_in_primes(number, 1, i, neighboors, numbers);
           check_string_in_primes(number, 2, i, neighboors, numbers);
		   check_string_in_primes(number, 3, i, neighboors, numbers);
       }
       g.insert( make_pair(number, neighboors) );
	   neighboors.clear();
   }
   return g;
}

void check_string_in_primes(int prime, int position, char number, 
                           set<int> &neighbors, const set<int> &numbers )
{
   stringstream ss;
   ss << prime;
   string s = ss.str();
   if( s[position] == number ) 
       return;
   s[position] = number;
   int new_prime = atoi(s.c_str());
   
   if( numbers.find(new_prime) != numbers.end() )
   {
	   neighbors.insert(new_prime);
   }
   
}


// Breath first implementation.
int bfs(graph g, int start_node, int end_node) {
    if(end_node == start_node)
        return 0;
    queue<int> q;
    q.push(start_node);
    int node;
    set<int> visited_nodes, neighbors;
    set<int>::iterator it;
    int path_length;
    map<int, int> distances;
    distances.insert( make_pair(start_node, 0));

    while(q.size() > 0){
        node = q.front();
        q.pop();
        visited_nodes.insert(node);
        neighbors = g[node];
        path_length = distances[node];
        
        if( neighbors.find(end_node) != neighbors.end() ) {
            distances.insert( make_pair(end_node, path_length + 1));
            break;
        }

        for(it = neighbors.begin(); it != neighbors.end(); it++) {
            if( visited_nodes.find(*it) == visited_nodes.end() ) {
                visited_nodes.insert(*it);
                distances.insert( make_pair(*it, path_length + 1));
                q.push(*it);
            }
        }
    }

    return distances[end_node];
}


// Breath first implementation.
int bfs2(graph g, int start_node, int end_node) {
    if(end_node == start_node)
        return 0;
    queue<int> q;
    q.push(start_node);
    int node;
    set<int> neighbors;
    set<int>::iterator it;
    int path_length;
    unordered_map<int, int> distances, visited_nodes;
    distances.insert( make_pair(start_node, 0));

    while(q.size() > 0){
        node = q.front();
        q.pop();
        visited_nodes.insert(make_pair(node, 1));
        neighbors = g[node];
        path_length = distances[node];
        /*
        if( neighbors.find(end_node) != neighbors.end() ) {
            distances.insert( make_pair(end_node, path_length + 1));
            break;
        }
        */
        for(it = neighbors.begin(); it != neighbors.end(); it++) {
            if(*it == end_node)
                return path_length + 1;
            if( visited_nodes.find(*it) == visited_nodes.end() ) {
                visited_nodes.insert( make_pair(*it, 1) );
                neighbors.erase(*it);
                distances.insert( make_pair(*it, path_length + 1));
                q.push(*it);
            }
        }
    }

    return distances[end_node];
}