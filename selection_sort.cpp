#include<iostream>
using namespace std;

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

void selectionSort(int arr[], int n){
    int i, j, min_index;

    for (int i=0; i<n-1; i++){
        min_index = i;
        for (j=i+1; j<n; j++){
            if (arr[j] < arr[min_index]){
                min_index = j;
            }
        }
        swap(&arr[min_index], &arr[i]);
    }
}

void print(int arr[], int size){
    for (int i=0; i<size; i++){
        cout << arr[i] << " ";
    }
    cout << "\n"; 
}

int main() {
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr)/sizeof(arr[0]);
    selectionSort(arr, n);
    cout << "Sorted array: \n";
    print(arr, n);
    return 0;
}