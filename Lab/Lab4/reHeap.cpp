#include <bits/stdc++.h>

using namespace std;

void reheapDown(int maxHeap[], int numberOfElements, int index)
{
    if (index >= numberOfElements){
        return;
    }   
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int max = index;
    if (left < numberOfElements && maxHeap[left] > maxHeap[max]){
        max = left;
    }
    if (right < numberOfElements && maxHeap[right] > maxHeap[max]){
        max = right;
    }
    if (max != index){
        swap(maxHeap[max],maxHeap[index]);
        reheapDown(maxHeap,numberOfElements,max);
    }   
}

void reheapUp(int maxHeap[], int numberOfElements, int index)
{
    if (index >= numberOfElements){
        return;
    }    
    int root;
    root = (index - 1)/2;
    int max = maxHeap[index];
    if (root >= 0 && maxHeap[root] < max){
        swap(maxHeap[root],maxHeap[index]);
        reheapUp(maxHeap,numberOfElements,root);
    }
}

