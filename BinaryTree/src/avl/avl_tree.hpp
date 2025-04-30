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
    AvlNode<T>* search(T val);
    int NumCreated = 0;
    int NumDestroyed = 0;

#ifdef ENABLE_OBSOLETE
    void addValue00(T val);
#endif
private:
    AvlNode<T>* root_;
};

//-------------------------

template<typename T>
AvlTree<T>::~AvlTree() {
    AvlNode<T>::destroy(root_, NumDestroyed);
    printf(" ~~ AvlTree deallocated: NCreated=%d; NDestroy=%d\n", NumCreated, NumDestroyed);
}

#ifdef ENABLE_OBSOLETE

template<typename T>
void AvlTree<T>::addValue00(T val) {
    AvlNode<T>* newNode = AvlNode<T>::create(val, NumCreated);
    if (!root_)
        root_ = newNode;
    else
        AvlNode<T>::addNode00(root_, newNode);
    bool bres = root_->check_depths();
    assert(bres);
    AvlNode<T>* newParentNode = AvlNode<T>::provideNodeBalance00(root_);
    if (newParentNode != root_)
        root_ = newParentNode;
}

#endif // ENABLE_OBSOLETE

template<typename T>
void AvlTree<T>::addValue(T val) {
    AvlNode<T>* newNode = AvlNode<T>::create(val, NumCreated);
    if (!root_)
        root_ = newNode;
    else
        root_ = AvlNode<T>::addNode(root_, newNode);
}

template<typename T>
AvlNode<T>* AvlTree<T>::search(T val) {
    return root_ ? AvlNode<T>::searchNode(root_, val) : nullptr;
}

