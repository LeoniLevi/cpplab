#pragma once

#include "tree_node.hpp"
#include <assert.h>

#undef ENABLE_OBSOLETE

template<typename T>
class AvlNode : public TreeNode<T> {
public:
    T data() const override { return data_; }
    const AvlNode<T>* left() const override { return left_; }
    const AvlNode<T>* right() const override { return right_; }

    static AvlNode<T>* create(T value);
    static void destroy(AvlNode<T>* node);

    static AvlNode<T>* addNode(AvlNode<T>* parent, AvlNode<T>* newNode);
    static AvlNode<T>* deleteNodeByValue(AvlNode<T>* parent, T value);
    static AvlNode<T>* searchNode(AvlNode<T>* parent, T value);

    bool is_avl_valid() const;
private:

#ifdef ENABLE_OBSOLETE
    static void addNode00(AvlNode<T>* parent, AvlNode<T>* newNode);
    static AvlNode<T>* provideNodeBalance00(AvlNode<T>* node);
#endif

private:
    AvlNode(T val) : data_(val), left_(0), right_(0), depth_(0) {}
    ~AvlNode() {}
    static AvlNode<T>* rotateRight(AvlNode<T>* node);
    static AvlNode<T>* rotateLeft(AvlNode<T>* node);

    static AvlNode<T>* searchMinNode(AvlNode<T>* parent);
    static AvlNode<T>* provideNodeBalance(AvlNode<T>* node);
    static void recalcNodeDepth(AvlNode<T>* node);

    void recalcDepth();
    DepthBalanceStatus getDepthBalanceStatus() const;
    unsigned depth() const { return depth_; }

private:
    T data_;
    AvlNode<T>* left_;
    AvlNode<T>* right_;
    unsigned depth_;
};

//static 
template<typename T>
AvlNode<T>* AvlNode<T>::create(T value) {
    return new AvlNode<T>(value);
}

//static 
template<typename T>
void AvlNode<T>::destroy(AvlNode<T>* node) {
    if (node->left_)
        destroy(node->left_);
    if (node->right_)
        destroy(node->right_);
    delete node;
}

// static
template<typename T>
AvlNode<T>* AvlNode<T>::addNode(AvlNode<T>* parent, AvlNode<T>* newNode) {
    T value = newNode->data();
    if (value <= parent->data()) {
        if (parent->left_)
            parent->left_ = addNode(parent->left_, newNode);
        else
            parent->left_ = newNode;

        if (parent->depth_ <= parent->left_->depth_)
            parent->depth_ = parent->left_->depth_ + 1;
    }
    else { // value > parent->data()
        if (parent->right_)
            parent->right_ = addNode(parent->right_, newNode);
        else
            parent->right_ = newNode;

        if (parent->depth_ <= parent->right_->depth_)
            parent->depth_ = parent->right_->depth_ + 1;
    }
    return provideNodeBalance(parent);
}

// static
template<typename T>
void AvlNode<T>::recalcNodeDepth(AvlNode<T>* node)
{
    if (!node->left_ && !node->right_)
        node->depth_ = 0;
    else if (node->left_ && !node->right_)
        node->depth_ = node->left_->depth_ + 1;
    else if (!node->left_ && node->right_)
        node->depth_ = node->right_->depth_ + 1;
    else { // if (node->left_ && node->right_) 
        if (node->left_->depth_ >= node->right_->depth_)
            node->depth_ = node->left_->depth_ + 1;
        else
            node->depth_ = node->left_->depth_ + 1;
    }
}

//static 
template<typename T>
AvlNode<T>* AvlNode<T>::deleteNodeByValue(AvlNode<T>* node, T value)
{
    if (node->data_ == value) {
        if (!node->left_ && !node->right_) {
            destroy(node);
            return nullptr;
        }
        else if (node->left_ && !node->right_) {
            auto newNode = node->left_;
            destroy(node);
            return newNode;
        }
        else if (!node->left_ && node->right_) {
            auto newNode = node->right_;
            destroy(node);
            return newNode;
        }
        // if (node->left_ && node->right_)
        auto minNode = searchMinNode(node->right_);
        node->data_ = minNode->data_;
        node->right_ = deleteNodeByValue(node->right_, minNode->data_);
        recalcNodeDepth(node);
        return node;
    }
    if (value < node->data_) {
        node->left_ = deleteNodeByValue(node->left_, value);
        recalcNodeDepth(node);
        return node;
    }
    //if (value > node->data_)
    {
        node->right_ = deleteNodeByValue(node->right_, value);
        recalcNodeDepth(node);
        return node;
    }    
}

// static
template<typename T>
AvlNode<T>* AvlNode<T>::searchNode(AvlNode<T>* parent, T value)
{
    T nodeValue = parent->data();
    if (nodeValue == value)
        return parent;
    if (value < nodeValue && parent->left_)
        return searchNode(parent->left_, value);
    if (value > nodeValue && parent->right_)
        return searchNode(parent->right_, value);
    return nullptr;
}

template<typename T>
AvlNode<T>* AvlNode<T>::searchMinNode(AvlNode<T>* parent)
{
    if (parent->left_)
        return searchMinNode(parent->left_);    
    return parent;
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
bool AvlNode<T>::is_avl_valid() const {
    auto nd = this->max_deepness();
    if (nd != this->depth_ + 1)
        return false;
    if (this->left_ && !this->left_->is_avl_valid())
        return false;

    if (this->right_ && !this->right_->is_avl_valid())
        return false;
    return true;
}


#ifdef ENABLE_OBSOLETE

// static
template<typename T>
void AvlNode<T>::addNode00(AvlNode<T>* parent, AvlNode<T>* newNode) {
    T value = newNode->data();
    if (value <= parent->data()) {
        if (parent->left_)
            addNode00(parent->left_, newNode);
        else
            parent->left_ = newNode;

        if (parent->depth_ <= parent->left_->depth_)
            parent->depth_ = parent->left_->depth_ + 1;
    }
    else { // value > parent->data()
        if (parent->right_)
            addNode00(parent->right_, newNode);
        else
            parent->right_ = newNode;

        if (parent->depth_ <= parent->right_->depth_)
            parent->depth_ = parent->right_->depth_ + 1;
    }
}

// static
template<typename T>
AvlNode<T>* AvlNode<T>::provideNodeBalance00(AvlNode<T>* node)
{
    if (node->left_)
        node->left_ = provideNodeBalance00(node->left_);
    if (node->right_)
        node->right_ = provideNodeBalance00(node->right_);
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

#endif // ENABLE_OBSOLETE