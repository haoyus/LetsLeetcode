#include "treeNode.hpp"

int main()
{
    BinNode<int>* root = new BinNode<int>(0);
    BinNode<int>* root_lc = root->InsertAsLc(1);
    BinNode<int>* root_rc = root->InsertAsRc(2);
    root_lc->InsertAsLc(3);
    root_lc->InsertAsRc(4);
    root_rc->InsertAsLc(5);
    root_rc->InsertAsRc(6);

    BinNode<int>* root1 = new BinNode<int>(0);
    BinNode<int>* root1_lc = root1->InsertAsLc(1);
    BinNode<int>* root1_rc = root1->InsertAsRc(2);
    root1_lc->InsertAsLc(3);
    root1_lc->InsertAsRc(4);
    root1_rc->InsertAsLc(5);
    root1_rc->InsertAsRc(6);

    // PrintBinNode(root);
    // PrintBinNode(root->lc_);
    // PrintBinNode(root->rc_);

    PreTraverse(root);
    std::cout<<std::endl;
    InTraverse(root);
    std::cout<<std::endl;
    PostTraverse(root);
    std::cout<<std::endl;

    int result = CompareTrees(root->lc_,root1->lc_);
    std::cout<<"Compare result: "<<result<<std::endl;
}