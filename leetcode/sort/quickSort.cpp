#include <iostream>
#include "../common.h"

int Partition(Object obj[], int lo, int hi)
{
    int piv = hi;

    int i=lo;
    for(int j=lo; j<hi; ++j){
        if(obj[j].x < obj[hi].x){
            Object tmp = obj[i];
            obj[i] = obj[j];
            obj[j] = tmp;
            ++i;
        }
    }

    Object tmp = obj[i];
    obj[i] = obj[piv];
    obj[piv] = tmp;

    return i;
}


void QuickSort(Object obj[], int lo, int hi)
{
    if(lo >= hi) return;

    int piv = Partition(obj,lo,hi);

    QuickSort(obj, lo, piv-1);
    QuickSort(obj,piv+1,hi);
}


int main()
{
    const int SIZE = 10;
    Object objects[SIZE];
    for(int i = 0; i < SIZE; ++i){
        objects[i].x = SIZE-i;
    }
    PrintObjX(objects,SIZE);

    QuickSort(objects,0,SIZE-1);
    PrintObjX(objects,SIZE);
}