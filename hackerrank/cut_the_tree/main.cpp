#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
using l_int = long long;
int sub_tree_sum(int root,
    vector<bool> visited,
    vector<vector<int>>& nodes,
    vector<int>& weight,
    vector<int>& subtree_weight){
    int sum = 0;
    for(int i = 0; i < (int)nodes[root].size();  ++i){
        int v = nodes[root][i];
        if(visited[v]==false){
            visited[v] = true;
            sum += sub_tree_sum(v, visited, nodes, weight, subtree_weight);
        }
    }
    sum += weight[root];
    subtree_weight[root] = sum;
    return sum;
}

int main() {
    int N; cin >> N;
    vector<vector<int>> nodes(N);
    vector<int> weight;
    vector<int> subtree_weight(N);
    vector<bool> visited(N, false);
    for(int i = 0; i < N; ++i){
        int t; cin >> t;
        weight.push_back(t);
    }
    for(int i = 0; i < N-1; ++i){
        int u,v; cin >> u >> v;
        u--;v--;
        nodes[u].push_back(v);
        nodes[v].push_back(u);
    }
    visited[0] = true;
    sub_tree_sum(0, visited, nodes, weight, subtree_weight);
    int T = subtree_weight[0]; int min = T+1;
    int mini = -1;
    for(int i = 0; i < N; ++i){
        if(abs(2*subtree_weight[i] - T) < min){
            mini = i;
            min =abs(2*subtree_weight[i] - T); 
        }
    }
    cout << min << endl;
    


    return 0;
}

