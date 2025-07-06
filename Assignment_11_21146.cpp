// Department maintains a student information. The file contains roll
// number, name, division and address. Allow user to add, delete
// information of student. Display information of particular student. If
// record of student does not exist an appropriate message is displayed. If
// it is, then the system displays the student details. Use Sequential File
// to maintain the data.


#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
using namespace std;

class Student{
    int roll;
    char name[20];
    char divi;
    
public:
    Student(){
        roll=0;
        strcpy(name, "");
        divi='a';
        
    }

    void get_student_data(){
        cout<<"Enter the Roll No.: ";
        cin>>this->roll;
        cout<<"Enter Name: ";
        cin>>this->name;
        cout<<"Enter Division: ";
        cin>>this->divi;
        
    }
    void display_student_data(){
        cout<<"Roll No. "<<roll<<", Name: "<<name<<", Division: "<<divi<<endl;
    }
    friend class student_database;
};

class student_database{
public:
    void add_record(){
        fstream file;
        file.open("assign11.dat", ios::app|ios::binary);
        if (!file){
            cerr<<"Error opening file!"<<endl;
            return;
        }
        Student s;
        s.get_student_data();
        file.write((char*)&s, sizeof(s));
        file.close();
    }

    void display_record(){
        fstream file;
        file.open("assign11.dat", ios::in|ios::binary);
        if (!file){
            cerr<<"Error opening file!"<<endl;
            return;
        }
        Student s;
        while (file.read((char*)&s, sizeof(s))){
            s.display_student_data();
        }
        file.close();
    }

    void find_record(){
        char name[20];
        cout<<"Name to be found: ";
        cin>>name;
        fstream file;
        Student s;
        file.open("assign11.dat", ios::in|ios::binary);
        if (!file){
            cerr<<"Error opening file!"<<endl;
            return;
        }
        while(file.read((char*)&s, sizeof(s))){
            if (strcmp(s.name, name)==0){
                cout<<"Record Found!!"<<endl;
                s.display_student_data();
                file.close();
                return;
            }
        }
        cout<<"record not found!"<<endl;
        file.close();
    }

    void delete_record(){
        fstream orig_file;
        fstream new_file;
        orig_file.open("assign11.dat", ios::in|ios::binary);
        new_file.open("assign11_2.dat", ios::out|ios::binary);
        if (!orig_file || !new_file){
            cerr<<"Error opening file!"<<endl;
            return;
        }
        char name[20];
        cout<<"Name of student to be deleted: ";
        cin>>name;
        Student s;
        int count=0;
        while (orig_file.read((char*)&s, sizeof(s))){
            if (strcmp(s.name, name)==0){
                count++;
            }
            else{
                new_file.write((char*)&s, sizeof(s));
            }
        }
        if (count==0){
            cout<<"No record to be deleted found!"<<endl;
        }
        else{
            cout<<"Record Deleted successfully"<<endl;
        }
        orig_file.close();
        new_file.close();
        remove("assign11.dat");
        rename("assign11_2.dat", "assign11.dat");

        return;
    }
};

int main(){
    vector<Student> stu_data;
    fstream file;
    file.open("assign11.txt", ios::out|ios::trunc); //clears the contents of the file before file operations
    file.close();
    student_database s;
    int ch;
    int roll;
    char ch1;
    do{
        cout<<"-----------File Operations----------"<<endl;
        cout<<"Ch1. Enter Data to the file"<<endl;
        cout<<"Ch2. Display the file contents"<<endl;
        cout<<"Ch3. Search for a particular student"<<endl;
        cout<<"Ch4. Delete Record"<<endl;
        cout<<"Enter Choice: ";
        cin>>ch;
        switch (ch){
            case 1:
            s.add_record();
            break;

            case 2:
            s.display_record();
            break;

            case 3:
            s.find_record();
            break;

            case 4:
            s.delete_record();
            break;

            default:
            cout<<"Invalid Option! Please Try Again!"<<endl;
            break;
        }
        cout<<"More Operations? (y/n)";
        cin>>ch1;
    } while (ch1=='y');
    return 0;
}