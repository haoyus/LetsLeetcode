#include "../common.h"


void Merge(Object objs[], int lo1, int lo2, int hi)
{
    int i=lo1, j=lo2;
    int k = 0;

    //Object tmp[hi-lo1+1];
    Object* tmp = new Object[hi-lo1+1];

    while(i<lo2 && j<=hi){

        if(objs[i].x<objs[j].x){
            tmp[k++] = objs[i++];
        }
        else{
            tmp[k++] = objs[j++];
        }

    }

    while(i<lo2){
        tmp[k++] = objs[i++];
    }
    while(j<=hi){
        tmp[k++] = objs[j++];
    }

    for(int m=lo1; m<=hi; ++m){
        objs[m] = tmp[m-lo1];
    }
    
    delete[] tmp;
}

void MergeSort(Object objs[], int lo, int hi)
{
    if(lo >= hi) return;

    int mid = lo + ((hi-lo)>>1);//to avoid int overflow

    MergeSort(objs,lo,mid);
    MergeSort(objs,mid+1,hi);

    Merge(objs,lo,mid+1,hi);
}


int main()
{
    const int SIZE = 9;
    Object objects[SIZE];
    for(int i = 0; i < SIZE; ++i){
        objects[i].x = SIZE-i;
    }
    PrintObjX(objects,SIZE);

    MergeSort(objects,0,SIZE-1);
    PrintObjX(objects,SIZE);
}