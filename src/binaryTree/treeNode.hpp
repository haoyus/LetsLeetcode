#pragma once
#include <iostream>

template<typename T>
struct BinNode
{
    BinNode<T>* lc_;
    BinNode<T>* rc_;
    T data_;

    BinNode(T data=T(), BinNode* left=nullptr, BinNode* right=nullptr) 
        : data_(data)
        , lc_(left)
        , rc_(right) {}

    BinNode* InsertAsLc(const T& data)
    {
        return lc_ = new BinNode(data);
    }

    BinNode* InsertAsRc(const T& data)
    {
        return rc_ = new BinNode(data);
    }

};

void PrintBinNode(BinNode<int>* node)
{
    if(node == nullptr)
        std::cout << "Null node!\n";
    std::cout << node->data_ << " ";
}

void PreTraverse(BinNode<int>* node)
{   
    if(node == nullptr) return;
    PrintBinNode(node);
    PreTraverse(node->lc_);
    PreTraverse(node->rc_);
}

void InTraverse(BinNode<int>* node)
{
    if(!node) return;
    InTraverse(node->lc_);
    PrintBinNode(node);
    InTraverse(node->rc_);
}

void PostTraverse(BinNode<int>* node)
{
    if(!node) return;
    PostTraverse(node->lc_);
    PostTraverse(node->rc_);
    PrintBinNode(node);
}


bool CompareTrees(BinNode<int>* node1, BinNode<int>* node2)
{
    bool flag = true;
    
    if(node1==nullptr && node2!=nullptr) return false;
    else if(node1!=nullptr && node2==nullptr) return false;
    else if(node1==nullptr && node2==nullptr) return true;
    else{
        if(node1->data_ != node2->data_) return false;
        else{
            flag &= CompareTrees(node1->lc_, node2->lc_);
            flag &= CompareTrees(node1->rc_, node2->rc_);
            return flag;
        }
    }
}