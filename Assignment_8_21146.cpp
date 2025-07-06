// Given sequence k = k1 <k2 < … <kn of n sorted keys, with a successful and unsuccessful 
// search probability pi and qi for each key ki. Build the Binary search tree that 
// has the least search cost given the access probability for each key. 

#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node(int val):data(val), left(nullptr), right(nullptr) {}
};

vector<vector<double>> w, c;
vector<vector<int>> r;
vector<int> keys;

Node* create_tree(int i, int j) {
    if (i>=j) return nullptr;

    int k = r[i][j];
    Node* node = new Node(keys[k-1]);
    node->left = create_tree(i, k-1);
    node->right = create_tree(k, j);
    return node;
}

void inorder(Node* val){
    if (val==nullptr){
        return;
    }
    inorder(val->left);
    cout<<val->data<<" ";
    inorder(val->right);
}

Node* OBST(const vector<double>& p, const vector<double>& q, const vector<int>& inputKeys) {
    int n = p.size();
    keys = inputKeys;

    w = c = vector<vector<double>>(n+1, vector<double>(n+1, 0));
    r = vector<vector<int>>(n+1, vector<int>(n+1, 0));

    for (int i=0; i<=n; i++){
        w[i][i] = q[i];
        c[i][i] = 0;
        r[i][i] = 0;
        if (i<n){
            w[i][i+1] = q[i] + p[i] + q[i+1];
            c[i][i+1] = w[i][i+1];
            r[i][i+1] = i+1;
        } 
    }

    for (int m = 2; m <= n; m++){
        for (int i = 0; i <= n - m; i++){
            int j = i+m;
            w[i][j] = w[i][j-1]+p[j-1]+q[j];
            c[i][j] = numeric_limits<double>::infinity();

            for (int k = r[i][j-1]; k <= r[i+1][j]; k++){
                double cost = c[i][k-1] + c[k][j] + w[i][j];
                if (cost<c[i][j]) {
                    c[i][j] = cost;
                    r[i][j] = k;
                }
            }
        }
    }

    return create_tree(0, n);
}

int main() {
    vector<int> keys = {1,2,3}; 
    vector<double> p = {0.4, 0.2, 0.1};   
    vector<double> q = {0.1, 0.1, 0.05, 0.05}; 
    Node* root = OBST(p, q, keys);

    cout<<"Required Optimal Binary Search Tree structure: ";
    inorder(root);
    cout<<endl;
    cout<<"Minimum Expected Search Cost: "<<c[0][keys.size()]<<endl;
    return 0;
}
