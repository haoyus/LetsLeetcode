#include "common.h"

void SelectSort(Object objs[], int size)
{
    for(int i=0; i<size; ++i){

        //Object minObj = objs[i];
        int minInd = i;

        for(int j=i+1;j<size;++j){
            if(objs[j].x < objs[minInd].x){
                //minObj = objs[j];
                minInd = j;
            }
        }

        Object tmp = objs[i];
        objs[i] = objs[minInd];//minObj;
        objs[minInd] = tmp;
    }
}

int main()
{
    const int SIZE = 10;
    Object objects[SIZE];
    for(int i = 0; i < SIZE; ++i){
        objects[i].x = SIZE-i;
    }
    PrintObjX(objects,SIZE);

    SelectSort(objects,SIZE);
    PrintObjX(objects,SIZE);
}