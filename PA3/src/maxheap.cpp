#include "maxheap.h"
#include <vector>
#include <algorithm>

void BinaryHeap::MaxHeapify(long node, long length){

    long left = 2*node+1,         
        right = 2*node+2,    
        largest;             

    if (left <= length && heap[left].key() > heap[node].key())
        largest = left;
    else
        largest = node;

    if (right <= length && heap[right].key() > heap[largest].key())
        largest = right;

    if (largest != node) {           
        swap(heap[largest], heap[node]);   
        MaxHeapify(largest, length);      
    }
}

void BinaryHeap::BuildMaxHeap(vector<Vertex>& array){
    this->heap = array;
    for (int i = (int)heap.size()/2-1; i >= 0 ; i--) {
        MaxHeapify(i, (int)heap.size()-1);   
    }
}

long BinaryHeap::FindPosition(long node){

    long idx = -1;
    for (long i = 0; i < heap.size(); i++) {
        if (heap[i].no() == node) {
            idx = i;
        }
    }
    return idx;
}
long BinaryHeap::ExtractMax(){

    if (IsHeapEmpty()) {
        cout << "error: heap is empty\n";
        exit(-1);
    }
    long max = heap[0].no();    
    // delete the first element/vertex
    heap[0] = heap[heap.size()-1];          
    heap.pop_back();   
    MaxHeapify(0, (long)heap.size()-1);       

    return max;     
}

void BinaryHeap::DecreaseKey(long node, long newKey, long prev){

    long index_node = FindPosition(node);     
    
    heap[index_node].update_key(newKey);
    heap[index_node].update_pi(prev);
    //cout<<heap[index_node].no()<<' '<<heap[index_node].pi()<<' '<<heap[index_node].key()<<endl;
    
    while (index_node >0 && heap[GetParentNode(index_node)].key() < heap[index_node].key()) {
        swap(heap[index_node], heap[GetParentNode(index_node)]);
        index_node = GetParentNode(index_node);
    }    
}
