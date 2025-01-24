#pragma once

#include "avl_node.hpp"
#include <assert.h>

template<typename T>
class AvlTree {
public: 
    AvlTree() : root_(0) {}
    ~AvlTree();
    AvlNode<T>* root() {return root_;}
    void addValue(T val);
    int NumCreated = 0;
    int NumDestroyed = 0;
private:
    AvlNode<T>* root_;
};

//-------------------------

template<typename T>
AvlTree<T>::~AvlTree() {
    AvlNode<T>::destroy(root_, NumDestroyed);
    printf(" ~~ AvlTree deallocated: NCreated=%d; NDestroy=%d\n", NumCreated, NumDestroyed);
}

template<typename T>
void AvlTree<T>::addValue(T val) {
    AvlNode<T>* newNode = AvlNode<T>::create(val, NumCreated);
    if (!root_)
        root_ = newNode;
    else
        AvlNode<T>::addNode(root_, newNode);
    bool bres = root_->check_depths();
    assert(bres);
    AvlNode<T>* newParentNode = AvlNode<T>::provideNodeBalance(root_);
    if (newParentNode != root_)
        root_ = newParentNode;
}

