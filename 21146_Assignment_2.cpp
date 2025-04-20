// Construct the binary search tree by inserting the values in given order.
// After constructing binary search tree perform following operations:
// 1) Insert a new node 2) Find numbers of node in longest path 3) Mini-
// mum and maximum data value found in tree 4) Change a tree so that the
// roles of the left and right pointers are swapped at every node 5) Search
// an element

#include <iostream>
#include <vector>
using namespace std;

class Node{
    int data;
    Node* left;
    Node* right;
public:
    Node(){
        data = 0;
        left = nullptr;
        right = nullptr;
    }
    Node(int data_){
        data = data_;
        left = nullptr;
        right = nullptr;
    }
    friend class BST;
};

class BST{
    Node* root;
    vector<int> inorder;
    int num_nodes(Node*);
    void inorder_traversal(Node*);
    void swap(Node*);
public:
    BST(){
        root = nullptr;
    }
    void create_BST(int data){
        Node* newnode = new Node(data);
        if (root == nullptr){
            root = newnode;
            return; 
        }
        Node* parent = nullptr;
        Node* child = root;
        while (child!=nullptr){
            parent = child;
            if (data<parent->data){
                child=parent->left;
            }
            else if (data>parent->data){
                child=parent->right;
            }
            else{
                cout<<"Duplicate Data!!! Data=="<<data<<endl;
                return;
            }
        }
        if (data<parent->data){
            parent->left = newnode;
        }
        else{
            parent->right = newnode;
        }
    }

    void no_of_nodes(){
        int n = num_nodes(root);
        cout<<"The no. of nodes on the longest path is: "<<n+1<<endl; //height+1
        return; 
    }

    void min_max(){
        inorder.clear();
        inorder_traversal(root);
        if (!inorder.empty()){
            cout<<"Max Element is: "<<inorder.back()<<endl;
            cout<<"Min Element is: "<<inorder.front()<<endl;
        }
        else{
            cout<<"Tree is empty!!"<<endl;
        }
        
        return;
    }
    
    void swap_each_node(){
        swap(root);
        cout<<"Nodes swapped successfully!!!"<<endl;
    }

    void search(int data){
        Node* temp = root;
        while (temp!=nullptr){
            if (temp->data==data){
                cout<<"Element found!!"<<endl;
                return;
            }
            else if (temp->data>data){
                temp=temp->left;
            }
            else{
                temp=temp->right;
            }
        }
        cout<<"Element not found!!"<<endl;
        return;
    }

    void in_trav(){
        inorder.clear();
        inorder_traversal(root);
        for (int i=0; i<inorder.size(); i++){
            cout<<inorder[i]<<" ";
        }
        cout<<endl;
    }
};

int BST::num_nodes(Node* var){
    if (var == nullptr){
        return -1;
    }
    int a = num_nodes(var->left);
    int b = num_nodes(var->right);
    return (max(a,b)+1);
}

void BST::inorder_traversal(Node* var){
    if (var == nullptr){
        return;
    }
    inorder_traversal(var->left);
    inorder.push_back(var->data);
    inorder_traversal(var->right);
}

void BST::swap(Node* var){
    if (var == nullptr){
        return;
    }
    Node *templ;
    templ = var->left;
    var->left = var->right ;
    var->right = templ;
    swap(var->left);
    swap(var->right);
}

int main(){
    cout<<"Enter the data for creation of the binary tree: "<<endl;
    BST tree;
    cout<<"Enter no. of elements to be inserted: ";
    int x,n;
    cin>>n;
    int arr[n];
    for (int i=0; i<n; i++){
        cout<<"Enter Element "<<i+1<<": ";
        cin>>arr[i];
    }
    for (int i=0; i<n; i++){
        tree.create_BST(arr[i]);
    }
    
    int ch;
    char ans  = 'y';
    do{
        cout<<"Ch1. Print inorder traversal of BST\nCh2. Find no. of nodes in longest path\nCh3. Find minimum and maximum values in the Binary Search Tree\nCh4. Swap Nodes\nCh5. Search particular element\n";
        cout<<"Enter the choice of operation: ";
        cin>>ch;
        switch (ch){
            case 1:
            tree.in_trav();
            break;
            case 2:
            tree.no_of_nodes();
            break;
            case 3:
            tree.min_max();
            break;
            case 4:
            tree.swap_each_node();
            break;
            case 5:
            cout<<"Enter element to be searched: ";
            cin>>x;
            tree.search(x);
            break;
            default:
            cout<<"Enter valid choice!! Please try again!!"<<endl;
        }
        cout<<"More Operations? (y/n)";
        cin>>ans;
    }while (ans=='y');
    return 0;
}

