#pragma once

#include <iostream>
struct Object
{
    int x,y,vx,vy;

    Object(int xx=0,int yy=0,int vvx=0,int vvy=0) : x(xx),y(yy),vx(vvx),vy(vvy) {};
};

void PrintObjX(Object* start, int size)
{
    for(int i=0;i<size;++i){
        std::cout << start++ ->x <<" ";
    }
    std::cout<<std::endl;
}