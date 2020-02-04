#pragma once

#include <iostream>

template<typename T>
struct ListNode
{
    T data;
    ListNode* prev;
    ListNode* next;
    

    ListNode(const T& d, ListNode* prv = nullptr, ListNode* nxt = nullptr)
        : data(d)
        , prev(prv)
        , next(nxt)
        {}
};