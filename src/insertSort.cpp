#include <iostream>
#include "common.h"

void insertSort(Object* pObj, int N)
{
    for(int j=1;j<N;++j){
        Object key = pObj[j];

        int i = j-1;
        while(i>=0 && pObj[i].y>key.y){
            pObj[i+1] = pObj[i];//move
            --i;
        }
        pObj[i+1] = key;//insert

        for (int k = 0; k < N; ++k)
        {
            std::cout << pObj[k].y << " ";
        }
        std::cout << "\n";
    }
}

int main()
{
    int num = 10;
    Object* head= new Object[num];
    Object* tmp = head;
    for(int i=0;i<num;++i){
        (tmp++)->y = num-i;
        std::cout<<num-i<<" ";
    } std::cout<<"\n";

    insertSort(head,num);

    Object *tmp2 = head;
    for (int i = 0; i < num; ++i)
    {
        std::cout<<tmp2[i].y <<" ";
    } std::cout << "\n";

    delete[] head;
}