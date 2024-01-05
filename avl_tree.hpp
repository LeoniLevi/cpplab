#pragma once

#include "tree_node.hpp"
#include <assert.h>

template<typename T>
class AvlNode : public TreeNode<T> {
public:
    T data() const override { return data_; }
    const AvlNode<T>* left() const override {return left_;}
    const AvlNode<T>* right() const override { return right_; }


    static AvlNode<T>* create(T value, int& counter) { ++counter; return new AvlNode<T>(value); }
    static void destroy(AvlNode<T>* node, int& counter) { 
        if (node->left_)
            destroy(node->left_, counter);
        if (node->right_)
            destroy(node->right_, counter);
        delete node; 
        ++counter;
    }

    static void addNode(AvlNode<T>* parent, AvlNode<T>* newNode);
    static AvlNode<T>* provideNodeBalance(AvlNode<T>* node);

    bool check_depths() const;

private:
    AvlNode(T val) : data_(val), left_(0), right_(0), depth_(0) {}

    void recalcDepth();    
    static AvlNode<T>* rotateRight(AvlNode<T>* node);
    static AvlNode<T>* rotateLeft(AvlNode<T>* node); 
    DepthBalanceStatus getDepthBalanceStatus() const;

    unsigned depth() const { return depth_; }

private:
    T data_;
    AvlNode<T>* left_;
    AvlNode<T>* right_;
    unsigned depth_;
};

template<typename T>
class AvlTree {
public: 
    AvlTree(T value) : root_(AvlNode<T>::create(value, NumCreated)) {}
    ~AvlTree() { 
        AvlNode<T>::destroy(root_, NumDestroyed); 
        printf(" ~~ AvlTree deallocated: NCreated=%d; NDestroy=%d", NumCreated, NumDestroyed);
    }
    AvlNode<T>* root() {return root_;}
    void addValue(T val) {
        AvlNode<T>* newNode = AvlNode<T>::create(val, NumCreated);
        AvlNode<T>::addNode(root_, newNode);
        bool bres = root_->check_depths();
        assert(bres);
        AvlNode<T>* newParentNode = AvlNode<T>::provideNodeBalance(root_);
        if (newParentNode != root_)
            root_ = newParentNode;
    }
    int NumCreated = 0;
    int NumDestroyed = 0;
private:
    AvlNode<T>* root_;
};

// static
template<typename T>
void AvlNode<T>::addNode(AvlNode<T>* parent, AvlNode<T>* newNode) {
    T value = newNode->data();
    if (value <= parent->data()) {
        if (parent->left_)
            addNode(parent->left_, newNode);
        else
            parent->left_ = newNode;

        if (parent->depth_ <= parent->left_->depth_)
            parent->depth_ = parent->left_->depth_ + 1;
    }
    else { // value > parent->data()
        if (parent->right_)
            addNode(parent->right_, newNode);
        else
            parent->right_ = newNode;

        if (parent->depth_ <= parent->right_->depth_)
            parent->depth_ = parent->right_->depth_ + 1;
    }
}

template<typename T>
AvlNode<T>* AvlNode<T>::rotateRight(AvlNode<T>* node) {
    if (!node->left())
        return node;

    auto old_left_right = node->left_->right_;
    auto new_top = node->left_;
    auto new_right = node;

    new_top->right_ = new_right;
    new_right->left_ = old_left_right;
    
    new_right->recalcDepth();
    new_top->recalcDepth();

    return new_top;
}

template<typename T>
AvlNode<T>* AvlNode<T>::rotateLeft(AvlNode<T>* node) {
    if (!node->right())
        return node;

    auto old_right_left = node->right_->left_;
    auto new_top = node->right_;
    auto new_left = node;

    new_top->left_ = new_left;
    new_left->right_ = old_right_left;

    new_left->recalcDepth();
    new_top->recalcDepth();

    return new_top;
}

template<typename T>
DepthBalanceStatus AvlNode<T>::getDepthBalanceStatus() const
{
    int ld = left_ ? left_->depth() + 1 : 0;
    int lld = left_ ? (left_->left_ ? left_->left_->depth() + 1 : 0) : 0;
    int lrd = left_ ? (left_->right_ ? left_->right_->depth() + 1 : 0) : 0;

    int rd = right_ ? right_->depth() + 1 : 0;
    int rld = right_ ? (right_->left_ ? right_->left_->depth() + 1 : 0) : 0;
    int rrd = right_ ? (right_->right_ ? right_->right_->depth() + 1 : 0) : 0;
    
    if (ld - rd > 1) {
        if (lrd > lld)
            return DepthBalanceStatus::LeftRight;
        return DepthBalanceStatus::LeftLeft;
    }
    if (rd - ld > 1) {
        if (rld > rrd)
            return DepthBalanceStatus::RightLeft;
        return DepthBalanceStatus::RightRight;
    }
    return DepthBalanceStatus::Ok;
}

// static
template<typename T>
AvlNode<T>* AvlNode<T>::provideNodeBalance(AvlNode<T>* node)
{
    if (node->left_)
        node->left_ = provideNodeBalance(node->left_);
    if (node->right_)
        node->right_ = provideNodeBalance(node->right_);
    node->recalcDepth();

    auto status = node->getDepthBalanceStatus();
    switch (status) {
    case DepthBalanceStatus::LeftLeft:
        return rotateRight(node);
    case DepthBalanceStatus::LeftRight:
        node->left_ = rotateLeft(node->left_);
        return rotateRight(node);
    case DepthBalanceStatus::RightRight:
        return rotateLeft(node);
    case DepthBalanceStatus::RightLeft:
        node->right_ = rotateRight(node->right_);
        return rotateLeft(node);
    default:
        return node;
    }
}

template<typename T>
void AvlNode<T>::recalcDepth() {
    if (left_ && right_)
        depth_ = (left_->depth_ > right_->depth_ ? left_->depth_ : right_->depth_) + 1;
    else if (left_)
        depth_ = left_->depth_ + 1;
    else if (right_)
        depth_ = right_->depth_ + 1;
    else
        depth_ = 0;

    auto d = this->max_deepness();
    assert(d == depth_ + 1);
}

template<typename T>
bool AvlNode<T>::check_depths() const {
    auto nd = this->max_deepness();
    if (nd != this->depth_ + 1)
        return false;
    if (this->left_ && !this->left_->check_depths())
        return false;

    if (this->right_ && !this->right_->check_depths())
        return false;
    return true;
}
