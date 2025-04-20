 // Beginning with an empty binary tree, construct binary tree by inserting the values in
// the order given. After constructing a binary tree perform following operations on it-
// 1. Perform inorder, preorder and post order traversal
// 2. Change a tree so that the roles of the left and right pointers are swapped at every node
// 3. Find the height of tree
// 4. Copy this tree to another [operator=]
// 5. Count number of leaves, number of internal nodes.
// 6. Erase all nodes in a binary tree. (Implement both recursive and non-recursive methods)

#include <iostream>
#include <stack>
using namespace std;

class Node{
    int data;
    Node *left, *right;
public:
    Node(){
        data = 0;
        left = right = nullptr;
    }
    friend class binary_tree;
};

class binary_tree{
    Node *root, *root2;
    int leaf_count=0;
    int int_node_count=0;
    int heit, max_height;
    Node* create_tree();
    void inorder_traversal(Node*);
    void preorder_traversal(Node*);
    void postorder_traversal(Node*);
    void swap(Node*);
    void node_count(Node*);
    void erase_bintree(Node*);
    void erase_bintree_non(Node*);
    int height(Node*);
    Node* operator=(Node*);
public:
    binary_tree(){
        root = nullptr;
    }
    void create(){
        root = create_tree();
    }
    void print_bintree(){
        cout<<"Available Choices of Traversal:\n";
        cout<<"1. Inorder Traversal\n";
        cout<<"2. Preorder Traversal\n";
        cout<<"3. Postorder Traversal\n";
        int c;
        cout<<"Enter Choice of traversal: ";
        cin>>c;
        switch (c){
            case 1:
            cout<<"Inorder Traversal is: ";
            inorder_traversal(root);
            break;
            case 2:
            preorder_traversal(root);
            break;
            case 3:
            postorder_traversal(root);
            break;
            default:
            cerr<<"Invalid Choice!!"<<endl;
            break;
        }
        cout<<endl;
    }
    void swap_nodes(){
        swap(root);
    }
    void n_c(){
        node_count(root);
        cout<<"No. of leaves: "<<leaf_count<<endl;
        cout<<"No. of internal nodes: "<<int_node_count<<endl;
        return;
    }

    void hight(){
        cout<<"The height of the binary tree is: "<<height(root)+1<<endl;
        return;
    }
    void erase(){
        cout<<"1. Recursive Deletion\n2. Non Recursive Deletion\n";
        cout<<"Enter the choice of deletion: ";
        int ch;
        cin>>ch;
        switch (ch){
            case 1:
            erase_bintree(root);
            break;
            case 2:
            erase_bintree_non(root);
            break;
            default:
            cout<<"Invalid Choice... PLease Try Again!!!"<<endl;
        }
        root = nullptr;
        cout<<"Tree destroyed successfully!!"<<endl;
    }
};

Node* binary_tree::create_tree(){
    Node* temp;
    char ch;
    temp = new Node();
    cout<<"Enter Data: ";
    cin>>temp->data;
    cout<<"Enter Right Node? (y/n): ";
    cin>>ch;
    if (ch=='y'){
        temp->right = create_tree();
    }
    cout<<"Enter Left Node? (y/n): ";
    cin>>ch;
    if (ch=='y'){
        temp->left = create_tree();
    }
    return temp;
}

void binary_tree::preorder_traversal(Node* var){
    if (var == nullptr){
        return;
    }
    cout<<var->data<<" ";
    preorder_traversal(var->left);
    preorder_traversal(var->right);
}

void binary_tree::inorder_traversal(Node* var){
    if (var == nullptr){
        return;
    }
    inorder_traversal(var->left);
    cout<<var->data<<" ";
    inorder_traversal(var->right);
}

void binary_tree::postorder_traversal(Node* var){
    if (var == nullptr){
        return;
    }
    postorder_traversal(var->left);
    postorder_traversal(var->right);
    cout<<var->data<<" ";
}

void binary_tree::swap(Node* var){
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

void binary_tree::node_count(Node* var){
    if (var == nullptr){
        return;
    }
    if (var->left==nullptr && var->right==nullptr){
        leaf_count++;
    }
    else{
        int_node_count++;
    }
    node_count(var->left);
    node_count(var->right);
}

int binary_tree::height(Node* var){
    if (var == nullptr){
        return -1;
    }
    int a = height(var->left);
    int b = height(var->right);
    return (max(a,b)+1);
}

void binary_tree::erase_bintree(Node* var){
    if (var==nullptr){
        return;
    }
    erase_bintree(var->left);
    erase_bintree(var->right);
    delete var;
}

void binary_tree::erase_bintree_non(Node* root) {
    if (!root) return;

    stack<Node*> st;
    st.push(root);

    while (!st.empty()) {
        Node* current = st.top();
        st.pop();
        if (current->left) st.push(current->left);
        if (current->right) st.push(current->right);
        delete current;
    }
}


Node* binary_tree::operator=(Node* var){
    if (var == nullptr){
        return nullptr;
    }
    Node* temp;
    temp = var;
    temp->left = var->left;
    temp->right = var->right;
    operator=(var->left);
    operator=(var->right);
    return temp;
}

int main(){
    cout<<"Enter the data for creation of the binary tree: "<<endl;
    binary_tree bt;
    binary_tree bt2;
    bt.create();
    int ch;
    char ans  = 'y';
    do{
        cout<<"Ch1. Print Binary Tree\nCh2. Swap Nodes\nCh3. Get count of leaf and internal nodes\nCh4. Get height\nCh5. Copy one tree to another\nCh6. Erase Tree\n";
        cout<<"Enter the choice of operation: ";
        cin>>ch;
        switch (ch){
            case 1:
            bt.print_bintree();
            break;
            case 2:
            bt.swap_nodes();
            cout<<"Contents successfully swapped!!"<<endl;
            break;
            case 3:
            bt.n_c();
            break;
            case 4:
            bt.hight();
            break;
            case 5:
            bt2 = bt;
            cout<<"Contents Successfully copied!!"<<endl;
            bt2.print_bintree();
            break;
            case 6:
            bt.erase();
            cout<<"Contents successfully erased!!"<<endl;
            break;
            default:
            cout<<"Enter valid choice!! Please try again!!"<<endl;
        }
        cout<<"More Operations? (y/n)";
        cin>>ans;
    }while (ans=='y');
    return 0;
}