// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2019/9/6 Cheng-Yun Hsieh]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>
#include <limits>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    int n = data.size();
    int j, key;
    for (int i=1; i<n; i++)
    {
        j = i;
        key = data[i];
        while (j>0 && data[j-1]>key)
        {
            data[j]=data[j-1];
            j--;
        }
        data[j] = key;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
       
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    int q;
    if(low<high){
        q = Partition(data,low,high);
        QuickSortSubVector(data, low, q-1);
        QuickSortSubVector(data, q+1, high);
    }
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    // Hint : Textbook page 171
    int i = low-1;
    for(int j=low;j<high;j++){
        if(data[j]<=data[high]){
            i++;
            swap(data[i],data[j]);
        }
    }
    swap(data[i+1],data[high]);
    return i+1;
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if(low<high){
        int mid = (low+high)/2;
        MergeSortSubVector(data, low, mid);
        MergeSortSubVector(data, mid+1, high);
        Merge(data,low,mid,mid+1,high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int MAX = std::numeric_limits<int>::max();
    vector<int> leftsub(data.begin()+low,data.begin()+middle2);
    vector<int> rightsub(data.begin()+middle2,data.begin()+high+1);
    leftsub.push_back(MAX);
    rightsub.push_back(MAX);
    int l_idx=0, r_idx=0;
    for (int i = low; i <= high; i++) {
        if(leftsub[l_idx]<=rightsub[r_idx]){
            data[i]=leftsub[l_idx];
            l_idx++;
        }
        else{
            data[i]=rightsub[r_idx];
            r_idx++;
        }
    }
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root){
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int largest = root;
    int left = root*2+1;
    int right = root*2+2;
    if (left < heapSize && data[left] > data[root]) { largest = left; }
    if (right < heapSize && data[right] > data[largest]) { largest = right; }
    if (largest != root) {
        swap(data[largest], data[root]);
        MaxHeapify(data, largest);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for (int i = ((int)data.size()/2)-1; i >= 0 ; i--) {
        MaxHeapify(data, i);
    }
}
