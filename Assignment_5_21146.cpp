// Implement all the functions of a dictionary (ADT) using open hashing technique: 
// separate chaining using linked list Data: Set of (key, value) pairs, Keys are mapped to 
// values, Keys must be comparable, and Keys must be unique. Standard Operations: 
// Insert(key, value), Find(key), Delete(key)

#include <iostream>
using namespace std;

class word{
    string key;
    string meaning;
    word* next;
public:
    word(string w, string m){
        key = w;
        meaning = m;
        next = nullptr;
    }
    friend class dictionary;
};

class dictionary{
    word *dict[26] = {nullptr};
public:
    int hashing_function(char key){
        return ((tolower(key)-'a')%26);
    }

    void add_word_to_dictionary(string _key, string mean) {
        int hf = hashing_function(_key[0]); 
        if (dict[hf] == nullptr){ 
            dict[hf] = new word(_key, mean);
        } 
        else{
            word* temp = dict[hf];
            word* prev = nullptr;
            while (temp != nullptr && _key > temp->key) {
                prev = temp;
                temp = temp->next;
            }
            word* newword = new word(_key, mean);
            if (prev == nullptr) {
                newword->next = dict[hf];
                dict[hf] = newword;
            }
            else {
                newword->next = temp;
                prev->next = newword;
            }
        }
    }

    bool search(string _key){
        int hf = hashing_function(_key[0]);
        if (dict[hf]==nullptr){
            cout<<"Word not found!"<<endl;
            return false;
        }
        else{
            word* temp = dict[hf];
            while(temp->key<_key){
                temp=temp->next;
            }
            if (temp->key!=_key){
                cout<<"Word not found"<<endl;
                return false;
            }
            else{
                cout<<"Word found in the dictionary!"<<endl;
                cout<<"Word: "<<_key<<" -> "<<temp->meaning<<endl;
                return true;
            }
        }
    }

    void print_dictionary(){
        for (int i=0; i<26; i++){
            if (dict[i]!=nullptr){
                word* temp = dict[i];
                while (temp!=nullptr){
                    cout<<"Word: "<<temp->key<<" -> "<<"Meaning: "<<temp->meaning<<endl;
                    temp=temp->next;
                }
            }
        }
    }

    bool delete_word_from_dictionary(string _key){
        int hf = hashing_function(_key[0]);
        if (dict[hf]==nullptr){
            cout<<"Word not found!"<<endl;
            return false;
        }
        else{
            word* temp = dict[hf];
            word* prev = nullptr;
            while(temp->key<_key){
                prev = temp;
                temp=temp->next;
            }
            if (temp->key!=_key){
                cout<<"Word not found"<<endl;
                return false;
            }
            if (prev!=nullptr){
                prev->next = temp->next;
                delete temp;
                cout<<"Word successfully deleted!!"<<endl;
                return true;
            }
            else{
                dict[hf] = temp->next;
                delete temp;
                cout<<"Word successfully deleted!!"<<endl;
                return true;
            }
            
        }

    }

};
int main(){
    dictionary d;
    d.add_word_to_dictionary("apologies", "being sorry for something");
    d.add_word_to_dictionary("illerate", "not educated");
    d.add_word_to_dictionary("dark", "having low light");
    d.add_word_to_dictionary("computer", "machine that performs computations");
    d.add_word_to_dictionary("invade", "to attack");
    d.add_word_to_dictionary("interrogate", "to question");
    d.add_word_to_dictionary("snare", "a trap");
    d.add_word_to_dictionary("attire", "to dress");
    d.add_word_to_dictionary("copra", "a dried coconut");
    d.add_word_to_dictionary("invent", "to originate");
    //d.print_dictionary();
    //d.search("snare");
    //d.search("zomato");
    d.delete_word_from_dictionary("attire");
    d.print_dictionary();
    return 0;
}