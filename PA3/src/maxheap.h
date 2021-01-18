#ifndef MAXHEAP_H_
#define MAXHEAP_H_

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <limits>
#include <iterator>
#include <cmath>
#include "graph.h"

//min heap
class BinaryHeap{
    public:
    void swap(Vertex &v1, Vertex &v2){
        Vertex temp = v1;
        v1 = v2;
        v2 = temp;
    }
    long FindPosition(long node);
    long GetParentNode(long node){
        if(node%2==0) return int(node/2);
        else return int((node-1)/2);
    };
    vector<Vertex> heap;      
    BinaryHeap(){             
        heap.resize(0);        
    }
    BinaryHeap(vector<Vertex>& array){
        heap = array;
    }
    bool IsHeapEmpty(){ return (heap.size()<1); };

    // Max-Priority Queue
    void MaxHeapify(long node,long length);
    void BuildMaxHeap(vector<Vertex>& array);
    void DecreaseKey(long node, long newKey, long prev);
    void MaxHeapInsert(long node, long key);
    long Maximum(){
        return heap[0].no();
    }               
    long ExtractMax();            

};

#endif