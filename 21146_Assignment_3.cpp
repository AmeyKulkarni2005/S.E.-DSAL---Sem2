//Create an inordered threaded binary search tree. Perform inorder, preorder traversals 
//without recursion and deletion of a node. Analyze time and space complexity of the algorithm. 

#include <iostream>
#include <stack>
using namespace std;

class Node{
    int data;
    Node* left;
    int lbit;
    Node* right;
    int rbit;

public:                                                    
    Node(){
        data = 0;
        left = nullptr;
        right = nullptr;
        lbit = 0; 
        rbit = 0;
    }
    Node(int data_){
        data = data_;
        left = nullptr;
        right = nullptr;
        lbit = 0; 
        rbit = 0;
    }
    friend class TBST;
    friend class TBST1;
    friend class s1;
};

class TBST{
    Node *head, *root;
    void insert_left(Node* child, Node* parent){
        parent->lbit = 1;
        child->left = parent->left;
        child->right = parent;
        parent->left = child;
    }

    void insert_right(Node* child, Node* parent){
        parent->rbit = 1;
        child->right = parent->right;
        child->left = parent;
        parent->right = child;
    }

    Node* inorder_succ(Node* ptr){
        if (ptr->rbit==1){
            return ptr->right;
        }
        ptr = ptr->right;
        while (ptr->lbit!=0){
            ptr = ptr->left;
        }
        return ptr;
    }

    Node* inorder_pre(Node* ptr){
        if (ptr->lbit==0){
            return ptr->left;
        }
        ptr = ptr->left;
        while (ptr->rbit==1){
            ptr=ptr->right;
        }
        return ptr;
    }

    void leaf_del(Node* par, Node* ptr){
        if (ptr->data<par->data){
            par->lbit = 0;
            par->left = ptr->left;
        }
        else{
            par->rbit=0;
            par->right = ptr->right;
        }
        delete ptr;
    }

    void one_del(Node* par, Node* ptr){
        Node* child = (ptr->lbit==1)?ptr->left:ptr->right;
        if (ptr == root){
            root = child;
        }
        else if (ptr==par->left){
            par->left = child;
        }
        else{
            par->right = child;
        }
        delete ptr;
    }

    void two_del(Node* par, Node* ptr){
        Node* succ = inorder_succ(ptr);
        ptr->data = succ->data;
        if (succ->lbit == 0 && succ->rbit == 0){
            leaf_del(ptr, succ);
        }
        else{
            one_del(ptr, succ);
        }
    }

    void in_trav(Node*);
    void pre_trav(Node*);

public:
    TBST(){
        root = nullptr;
        Node* newnode = new Node(-1);
        head = newnode;
        newnode->left = root;
        newnode->lbit = 0;
        newnode->rbit = 0;
        newnode->right = newnode;
    }
    
    void insert_to_TBST(int data_){
        Node *parent=nullptr, *child=root;
        Node* newnode = new Node(data_);
        if (root==nullptr){
            root = newnode;
            newnode->left = head;
            newnode->right = head;
            head->left = newnode;
            head->lbit = 1;
            return;
        }
        while (child!=head){
            parent = child;
            if (data_<parent->data){
                if (parent->lbit==1){
                    child = parent->left;
                }
                else{
                    break;
                }
            }
            else if (data_>parent->data){
                if (parent->rbit==1){
                    child = parent->right;
                }
                else{
                    break;
                }
            }
        }
        if (data_<parent->data){
            insert_left(newnode, parent);
        }
        else{
            insert_right(newnode, parent);
        }
    }

    void inorder(){
        cout<<"The inorder traversal of Threaded Binary Tree is: ";
        in_trav(root);
        cout<<endl;
    }

    void preorder(){
        cout<<"The preorder traversal of Threaded Binary Tree is: ";
        pre_trav(root);
        cout<<endl;
    }

    void delete_from_TBST(){
        cout<<"Enter the data that is to be deleted from the Threaded Binary Tree: ";
        int c;
        cin>>c;
        Node* ptr = root;
        Node* par = nullptr;
        while (ptr != head && ptr->data != c){
            par = ptr;
            ptr = (c<ptr->data) ? ptr->left:ptr->right;
        }

        if (ptr==head){
            cout<<"The key not found!! Try Again!"<<endl;
            return;
        }

        if (ptr->lbit==0 && ptr->rbit==0){
            leaf_del(par, ptr);
        }
        else if (ptr->lbit==1 ^ ptr->rbit==1){
            one_del(par, ptr);
        }
        else{
            two_del(par, ptr);
        }
        cout<<"The required key has been successfully deleted!!"<<endl;
    }
};

void TBST::in_trav(Node* var) {
    Node* temp = var;
    while (temp != head) {
        while (temp->lbit == 1) {
            temp = temp->left;
        }
        cout << temp->data << " ";
        while (temp->rbit == 0 && temp->right != head) {
            temp = temp->right;
            cout << temp->data << " ";
        }
        temp = temp->right;
    }
}

void TBST::pre_trav(Node* var){
    Node* temp = root;
    while (temp!=head){
        cout<<temp->data<<" ";
        if (temp->lbit == 1){
            temp = temp->left;
        }
        else{
            while (temp->rbit == 0 && temp->right != head){
                temp = temp->right;
            }
            temp = temp->right;
        }
    }
}

// int main(){
//     TBST tree;
//     int ch;
//     char ans;
//     do{
//         cout<<"1. Insert data to TBST\n2. Print Inorder Traversal\n3. Print Preorder Traversal\n4. Perform Deletion of the Node\n";
//         cout<<"Enter choice: ";
//         cin>>ch;
//         switch(ch){
//             case 1:
//                 int data;
//                 cout<<"Enter data: ";
//                 cin>>data;
//                 tree.insert_to_TBST(data);
//                 break;
//             case 2:
//                 tree.inorder();
//                 break;
//             case 3:
//                 tree.preorder();
//                 break;
//             case 4:
//                 tree.delete_from_TBST();
//                 break;
//             default:
//                 cout<<"Invalid choice!"<<endl;
//         }
//         cout<<"More Operations? (y/n)";
//         cin>>ans;
//     }while (ans=='y');
// }


class s1{
    public:
    int top;
    s1(){
        top=-1;
    }
    Node* arr[10];
    Node* pop(){
        if (empty()){
            return nullptr;
        }
        return arr[top--];
    }
    void push(Node* s){
        if (full()){
            return;
        }
        arr[++top] = s;
    }
    bool empty(){
        return (top==-1)?true:false;
    }
    bool full(){
        return (top==9)?true:false;
    }
};

class TBST1{
    Node* head;
    Node* root;
public:
    TBST1(){
        head = new Node(-1);
        head->left = head;
        head->lbit = 1;
        head->rbit = 0;
        head->right = head;
        root = nullptr;
    }

    void create_TBST(int data){
        if (root==nullptr){
            root = new Node(data);
            root->lbit = 0;
            root->left = head;
            root->rbit = 0;
            root->right = head;
            head->right = root;
            return;
        }
        Node* child, *parent;
        child = root;
        parent = nullptr;
        while (child != head) {
            parent = child;
            if (data == child->data) {
                cout << "Duplicate Data!!" << endl;
                return;
            } else if (data < child->data) {
                if (child->lbit == 0) break;
                child = child->left;
            } else {
                if (child->rbit == 0) break;
                child = child->right;
            }
        }
        if (data<parent->data){
            Node* newnode = new Node(data);
            newnode->left = parent->left;
            newnode->lbit = parent->lbit;
            newnode->rbit = 0;
            newnode->right = parent;
            parent->lbit = 1;
            parent->left = newnode;
        }
        else{
            Node* newnode = new Node(data);
            newnode->right = parent->right;
            newnode->rbit = parent->rbit;
            newnode->rbit = 0;
            newnode->left = parent;
            parent->rbit = 1;
            parent->right = newnode;
        }
    }



void inorder(Node* var) {
    stack<Node*> s;
    while (true) {
        while (var != head) {  // Traverse left subtree
            s.push(var);
            if (var->lbit == 0) break;  // Stop when left thread is found
            var = var->left;
        }

        if (s.empty()) return;  // End traversal if stack is empty

        var = s.top();  
        s.pop();  

        cout << var->data << " ";

        if (var->rbit == 0) {  
            var = var->right;  // Move to in-order successor
        } else {  
            var = var->right;
            while (var->lbit == 1) {  // Traverse leftmost of right subtree
                s.push(var);
                var = var->left;
            }
        }
    }
}

    void in(){
        inorder(root);
    }
};


int main(){
    TBST1 tree;
    tree.create_TBST(90);
    tree.create_TBST(100);
    tree.create_TBST(70);
    tree.create_TBST(65);
    tree.create_TBST(80);
    tree.create_TBST(85);
    tree.in();
    cout<<"Hello World";
    return 0;
}