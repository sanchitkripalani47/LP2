#include<iostream>
#include<bits/stdc++.h>
using namespace std;

void SelectionSort(int a[],int n){
    int min,step;
    for(step=0;step<n;step++){
        min=step;
        for(int j=step+1;j<n;j++){
            if(a[j]<a[min])
                min=j;
        }
        swap(a[min],a[step]);
    }
}
void Print(int a[],int n){
    for(int i=0;i<n;i++){
        cout<<a[i]<<" ";
    }
    cout<<"}";
}
int main(){
    int array[20],n,i;
    cout<<"\n Enter no. of elements to be added: ";
    cin>>n;
    cout<<"\n Enter array elements to be sorted: ";
    for(i=0;i<n;i++){
        cin>>array[i];
    }
    SelectionSort(array,n);
    cout<<"Array elements in ascending order = {";
        for(int i=0;i<n;i++){
        cout<<array[i]<<" ";
    }
    cout<<"}";
}