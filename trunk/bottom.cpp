#include "bottom.h"

graph dfs(graph &g, int start_node) {
    graph dfs_tree;
    stack<int> node_stack;
    node_stack.push(start_node);

    int node;

    vector<int> neighbors;
    vector<int>::iterator it;

    while(node_stack.size() > 0){
        node = node_stack.top();
        node_stack.pop();
        neighbors = g[node];
        for(it = neighbors.begin(); it != neighbors.end(); it++) {
            if( dfs_tree.find(*it) != dfs_tree.end() ){
                node_stack.push(*it);  
                dfs_tree[node].push_back(*it);
            }
        }
    }

    return dfs_tree;
}