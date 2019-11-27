#pragma once
#include <iostream>

struct Node
{
    Node* left = nullptr;
    Node* right = nullptr;
    int data = 0;
};

void PrintNode(Node* node)
{
    if(node == nullptr)
        std::cout << "Null node!\n";
    std::cout << node->data << " ";
}