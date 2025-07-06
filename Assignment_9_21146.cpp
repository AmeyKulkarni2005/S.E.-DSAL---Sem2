// A Dictionary stores keywords and its meanings. Provide facility for adding new key
// words. Provide facility to display whole data sorted in ascending/ Descending order. 
// Also find how many maximum comparisons may require for finding any keyword. 
// Use Height balance tree and find the complexity for finding a keyword. 

#include <iostream>
#include <vector>
using namespace std;

class word{
    string key;
    string mean;
    word* left;
    word* right;
    int bf;
    word(){
        key = "abc";
        mean = "letters";
        left = right = nullptr;
        bf=0;
    }
    word(string l, string m){
        key = l;
        mean = m;
        left = right = nullptr;
        bf = 0;
    }
    friend class dictionary;
};

class dictionary{
    word* root;
public:
    dictionary(){
        root = nullptr;
    }
private:
    int height(word* var){
        if (var==nullptr){
            return 0;
        }
        if (height(var->left)>=height(var->right)){
            return 1+height(var->left);
        }
        else{
            return 1+height(var->right);
        }
    }
    int balancefactor(word* var){
        return (height(var->left)-height(var->right));
    }
    word* rotate_right(word* x){
        word* y;
        if (x->left==nullptr){
            y=nullptr;
            return y;
        }
        y = x->left;
        x->left = y->right;
        y->right = x;
        x->bf = height(x);
        y->bf = height(y);
        return y;
    }
    word* rotate_left(word* x){
        word* y;
        if (x->right == nullptr){
            y=nullptr;
            return y;
        }
        x->right = y->left;
        y->left = x;
        x->bf = height(x);
        y->bf = height(y);
        return y;
    }
    word* RR_rotation(word* var){
        var = rotate_left(var);
        return var;
    }
    word* LL_rotation(word* var){
        var = rotate_right(var);
        return var;
    }
    word* LR_rotation(word* var){
        var->left = rotate_left(var->left);
        var = rotate_right(var);
        return var;
    }
    word* RL_rotation(word* var){
        var->right = rotate_right(var->right);
        var = rotate_left(var);
        return var;
    }
    word* insert(word* var, string key, string mean){
        if (var==nullptr){
            var = new word(key, mean);
            var->left = nullptr;
            var->right = nullptr;
            var->bf = 0;
        }
        else{
            if (key>var->key){
                var->right = insert(var->right, key, mean);
                if (balancefactor(var)==-2){
                    if (key>var->right->key){
                        var = RR_rotation(var);
                    }
                    else{
                        var = RL_rotation(var); 
                    }
                }
            }
            else if (key<var->key){
                var->left = insert(var->left, key, mean);
                if (balancefactor(var)==2){
                    if (key<var->left->key){
                        var = LL_rotation(var);
                    }
                    else{
                        var = LR_rotation(var);
                    }
                }
            }
        }
        var->bf = height(var);
        return var;
    }
    void inorder(word* var){
        if (var==nullptr){
            return;
        }
        inorder(var->left);
        cout<<"Word: "<<var->key<<" -> "<<"Meaning: "<<var->mean<<endl;
        inorder(var->right);
    }
    void inorder_dec(word* var){
        if (var==nullptr){
            return;
        }
        inorder(var->right);
        cout<<"Word: "<<var->key<<" -> "<<"Meaning: "<<var->mean<<endl;
        inorder(var->left);
    }
public:
    void create(string key, string mean){
        root = insert(root, key, mean);
    }
    void in_trav(){
        inorder(root);
    }
    void in_trav_dec(){
        inorder_dec(root);
    }
    bool search(string key){
        if (root==nullptr){
            cout<<"Word not found!!"<<endl;
            cout<<"No. of Comparisons = 0"<<endl;
            return false;
        }
        word* temp = root;
        int comp=0;
        while (temp!=nullptr){
            if(key==temp->key){
                cout<<endl;
                cout<<"Word found in the dictionary!!"<<endl;
                cout<<"Word: "<<key<<" -> "<<"Meaning: "<<temp->mean<<endl;
                cout<<"Total No. of comparisons: "<<++comp<<endl;
                return true;
            }
            else if (key>temp->key){
                temp = temp->right;
                comp++;
            }
            else{
                temp = temp->left;
                comp++;
            }
        }
        cout<<"Word not found!!"<<endl;
        cout<<"Total No. of Comparisons made: "<<comp<<endl;
        return false;
    }
};

int main(){
    dictionary d;
    int ch;
    char ch1;
    do{
        cout<<"Ch1. Add word to dictionary\nCh2. Search for a word from Dictionary\nCh3. Display all words in ascending order\nCh4. Display all words in descending order\nEnter Choice: ";
        cin>>ch;
        switch (ch){
            case 1:
            {
                string w, m;
                cout<<"Enter the word: "<<endl;
                cin>>w;
                cout<<"Enter its meaning: "<<endl;
                cin>>m;
                d.create(w, m);
                cout<<"Word added successfully!!"<<endl;
                break;
            }

            case 2:
            {
                string word_ser;
                cout<<"Enter the word to be searched in the dictionary: ";
                cin>>word_ser;
                d.search(word_ser);
                break;
            }
            
            case 3:
            {
                cout<<"Words in the dictionary in Ascending Order are: "<<endl;
                d.in_trav();
                break;
            }

            case 4:
            {
                cout<<"Word in the dictionary in Descending Order are: "<<endl;
                d.in_trav_dec();
                break;
            }
            
            default:
            cout<<"Invalid option! Please try again!!"<<endl;
            break;
        }
        cout<<"More Operations? (y/n)";
        cin>>ch1;
    } while (ch1 == 'y');
    return 0;
}
