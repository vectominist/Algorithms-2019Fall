// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2019/9/6 Cheng-Yun Hsieh]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    for(int j = 1; j < data.size(); ++j){
        int i = j - 1;
        int key = data[j];
        while(i >= 0 && data[i] > key){
            data[i + 1] = data[i];
            --i;
        }
        data[i + 1] = key;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
inline void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    if(low < high){
        int mid = Partition(data, low, high);
        QuickSortSubVector(data, low, mid);
        QuickSortSubVector(data, mid + 1, high);
    }
}

inline int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    // Hint : Textbook page 171
    int x = data[low];
    int i = low - 1;
    int j = high + 1;
    while(true){
        do{ --j; } while(data[j] > x);
        do{ ++i; } while(data[i] < x);

        if(i < j){
            swap(data[i], data[j]);
        } else {
            return j;
        }
    }
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    int tmp_array[data.size()];
    MergeSortSubVector(data, tmp_array , 0, data.size() - 1);
}

// Sort subvector (Merge sort)
inline void SortTool::MergeSortSubVector(vector<int>& data, int* array, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if(low < high){
        int mid = (low + high) >> 1;
        MergeSortSubVector(data, array, low, mid);
        MergeSortSubVector(data, array, mid + 1, high);
        Merge(data, array, low, mid, high);
    }
}

// Merge
inline void SortTool::Merge(vector<int>& data, int* array, int low, int middle, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int l = low, r = middle + 1, i = low;
    while(l <= middle && r <= high){
        if(data[l] <= data[r])
            array[i++] = data[l++];
        else
            array[i++] = data[r++];
    }
    while(l <= middle)
        array[i++] = data[l++];
    while(r <= high)
        array[i++] = data[r++];
    for(i = low; i <= high; ++i)
        data[i] = array[i];
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
inline void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int l = (root << 1) + 1;
    int r = l + 1;
    int largest;

    if(l < heapSize && data[l] > data[root])
        largest = l;
    else largest = root;

    if(r < heapSize && data[r] > data[largest])
        largest = r;
    
    if(largest != root){
        swap(data[root], data[largest]);
        MaxHeapify(data, largest);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for(int i = (heapSize - 1) >> 1; i >= 0; --i){
        MaxHeapify(data, i);
    }
}