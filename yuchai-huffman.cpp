#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <string>

using namespace std;

class Node {
public:
    char symbol;
    int freq;
    Node *left;
    Node *right;
    
    Node(char _c, int f, Node *l = NULL, Node *r = NULL)
    :symbol(_c), freq(f), left(l), right(r) { }
    
    bool operator<(const Node &node) const {
        return freq > node.freq;
    }
};

void initNode(priority_queue<Node> &q) {
    Node nodeList[6] = {
        {'a', 45, NULL, NULL},
        {'b', 13, NULL, NULL},
        {'c', 12, NULL, NULL},
        {'d', 16, NULL, NULL},
        {'e', 9, NULL, NULL},
        {'f', 5, NULL, NULL}
    };
    for(int i = 0; i < 6; ++i){
        q.push(nodeList[i]);
    }
}

void huffmanTree(priority_queue<Node> &q) {
    while (q.size() != 1) {
        Node *left = new Node(q.top()); q.pop();
        Node *right = new Node(q.top()); q.pop();
        
        Node node('R', left->freq + right->freq, left, right);
        q.push(node);
    }
}



void huffmanCode(Node *root, string &prefix, map<char, string> &result) {
    string m_prefix = prefix;
    
    if (root->left == NULL)
        return;
    
    //handle with left subtree
    prefix += "0";
    //if it's a leaf, print it; otherwise recusively call huffmanCode on left subtree
    if (root->left->left == NULL)
        result[root->left->symbol] = prefix;

    else
        huffmanCode(root->left, prefix, result);
    
    //go back
    prefix = m_prefix;
    
    //handle with right subtree
    prefix += "1";
    //if it's a leaf, print it; otherwise recusively call huffmanCode on right subtree
    if (root->right->right == NULL)
        result[root->right->symbol] = prefix;

    else
        huffmanCode(root->right, prefix, result);
    
}

void printResult(map<char, string> result) {
    //map container
    map<char, string>::const_iterator it = result.begin();
    while (it != result.end()) {
        cout << it->first << ": " << it->second << endl;
        ++it;
    }
}
int main() {
    priority_queue<Node> q;
    initNode(q);
    
    huffmanTree(q);
    
    Node root = q.top();
    string prefix = "";
    map<char, string> result;  
    huffmanCode(&root, prefix, result);  
    printResult(result);
    return 0;  
}
