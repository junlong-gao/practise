/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;

    Node() {}

    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/
class Solution {
    unordered_map<int, Node*> visited;
    void search(Node* node){
        Node* clone = new Node(node->val);
        visited[node->val] = clone;
        for(auto v : node->neighbors){
            if(visited.count(v->val) == 0){
                search(v);
            }
            clone->neighbors.push_back(visited[v->val]);
        }
    }
public:
    Node *cloneGraph(Node *node) {
        if(node == NULL) return node;
        search(node);
        return visited[node->val];
    }
};
