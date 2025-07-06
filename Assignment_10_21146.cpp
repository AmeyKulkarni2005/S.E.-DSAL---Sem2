// Read the marks obtained by students of second year in an online examination of particular subject. 
// Find out maximum / minimum marks obtained in that subject. Use
// heap data structure. Analyze the algorithm.


#include <bits/stdc++.h>
using namespace std;

void heapify(float arr[], int n, int i){
    int largest = i;
    int left = 2*i+1;
    int right = 2*i+2;

    if (left<n && arr[left]>arr[largest]){
        largest = left;
    }
    if (right<n && arr[right]>arr[largest]){
        largest = right;
    }
    if (largest != i){
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heap_sort(float arr[], int n){
    for (int i=((n/2)-1); i>=0; i--){
        heapify(arr, n, i);
    }
    for (int i=n-1; i>0; i--){
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
    return;
}


int main(){
    int n;
    cout<<"Enter the No. of SE Students: ";
    cin>>n;
    float arr[n];
    for (int i=0; i<n; i++){
        cout<<"Enter the marks of Student "<<i+1<<": ";
        cin>>arr[i];
    }
    heap_sort(arr, n);
    cout<<"Maximum Marks are: "<<arr[n-1]<<endl;
    cout<<"Minimum Marks are: "<<arr[0]<<endl;
    cout<<"Sorted Array is: ";
    for (int i=0; i<n; i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    return 0;

}