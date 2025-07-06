// Consider telephone book database of N clients. Make use of a hash table implementation 
// to quickly look up client's telephone number. Make use of two collision handling 
// techniques and compare them using number of comparisons required to find a set of 
// telephone numbers (Note: Use linear probing with replacement and without replacement) 

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class hashing{
    string name;
    long long tele_num;
    int chain;
public:
    hashing(){
        name = "";
        tele_num = 0;
        chain = -1;
    }
    hashing(string nme, long long tele){
        name = nme;
        tele_num = tele;
        chain = -1;
    }
    friend class hash_table;
};

class hash_table{
    hashing *arr[26] = {nullptr};
public:
    int hashing_function(char key){
        return ((tolower(key)-'a')%26);
    }
    bool linear_prob_without_replacement(string nme, long long tele){
        int hf = hashing_function(nme[0]);
        int index = hf;
        while (arr[index]!=nullptr){
            index = (index+1)%26;
            if (index == hf){
                cout<<"Hash Table is full!!"<<endl;
                return false;
            }
        }
        arr[index] = new hashing(nme, tele);
        if (hf != index) {
            int prev = hf;
            while (arr[prev]!=nullptr && arr[prev]->chain != -1 && arr[prev]->chain!=index) {
                prev = arr[prev]->chain;
            }
            if (arr[prev]!=nullptr){
                arr[prev]->chain = index;
            }
        }
        return true;
    }

    bool linear_prob_with_replacement(string nme, long long tele) {
        int hf = hashing_function(nme[0]);
        int index = hf;
        int original_hf = hf;

        while (arr[index] != nullptr) {
            int existing_ind = hashing_function(arr[index]->name[0]);
            if (existing_ind != index && existing_ind <= hf) {
                swap(nme, arr[index]->name);
                swap(tele, arr[index]->tele_num);
                hf = existing_ind;
            }

            index = (index + 1) % 26;
            if (index == hf) {
                cout << "Hash Table is full!!" << endl;
                return false;
            }
        }
        arr[index] = new hashing(nme, tele);
        if (hf != index) {
            int prev = hf;
            while (arr[prev] != nullptr && arr[prev]->chain != -1 && arr[prev]->chain != index) {
                prev = arr[prev]->chain;
            }
            if (arr[prev]!=nullptr){
               arr[prev]->chain = index;
            }
        }
        return true;
    }

    void search(string key){
        int hf = hashing_function(key[0]);
        while (arr[hf]->name != key && arr[hf]->chain!=-1){
            hf = arr[hf]->chain;
        }
        if (arr[hf]->name == key){
            cout<<"Key found!!"<<endl;
            cout<<"Details: "<<"Name: "<<arr[hf]->name<<" -> "<<"Telephone Number: "<<arr[hf]->tele_num<<endl;
        }
        else{
            cout<<"Key not found!"<<endl;
        }
        return;
    }
    void display_hashtable(){
        cout<<"Hash Table:"<<endl;
        for (int i=0; i<26; i++){
            if (arr[i] != nullptr) {
                cout<<arr[i]->name << " -> " << arr[i]->tele_num;
                if (arr[i]->chain != -1)
                    cout << " -> (chained to " << arr[i]->chain << ")";
                cout << endl;
            }
            else{
                cout<<"Cell Number "<<i<<" is empty!"<<endl;
            }
        }
    }
};

int main(){
    hash_table ht;
    ht.linear_prob_with_replacement("RBI", 9579265842);
    ht.linear_prob_with_replacement("RY", 7447440369);
    ht.linear_prob_with_replacement("KJM", 9850811573);
    ht.linear_prob_with_replacement("SSS", 9850226197);
    ht.linear_prob_with_replacement("ARD", 9579265842);
    ht.linear_prob_with_replacement("ARG", 9579265842);
    ht.linear_prob_with_replacement("AGP", 9579265842);
    ht.linear_prob_with_replacement("EM", 9579265842);
    ht.linear_prob_with_replacement("GVK", 9579265842);
    ht.linear_prob_with_replacement("SAJ", 9579265842);
    ht.linear_prob_with_replacement("MST", 9579265842);
    ht.linear_prob_with_replacement("RK", 9579265842);

    // ht.linear_prob_without_replacement("RBI", 9579265842);
    // ht.linear_prob_without_replacement("RY", 7447440369);
    // ht.linear_prob_without_replacement("KJM", 9850811573);
    // ht.linear_prob_without_replacement("SSS", 9850226197);
    // ht.linear_prob_without_replacement("ARD", 9579265842);
    // ht.linear_prob_without_replacement("ARG", 9579265842);
    // ht.linear_prob_without_replacement("AGP", 9579265842);
    // ht.linear_prob_without_replacement("EM", 9579265842);
    // ht.linear_prob_without_replacement("GVK", 9579265842);
    // ht.linear_prob_without_replacement("SAJ", 9579265842);
    // ht.linear_prob_without_replacement("MST", 9579265842);
    // ht.linear_prob_without_replacement("RK", 9579265842);
    ht.display_hashtable();
    ht.search("AAA");
    ht.search("SAJ");

}