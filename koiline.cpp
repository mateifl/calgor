
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;


void solution(vector<int> &heights, vector<int> &people, vector<int> &result ) {
    int place = 0;
    for (int i = 0; i < people.size(); i++) {
        place = people[i];
        if( result[place] == 0 )
            result[place] = heights[i];
            
    }    
    
}




