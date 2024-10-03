#include "binary_tree.hpp"
#include <stdio.h>

//!!
void BinaryTree::addData(int data)
{
    auto newNode = std::make_shared<BinaryTree>(data);
    addNode(newNode);
}

void BinaryTree::addNode(std::shared_ptr<BinaryTree> node)
{
    auto& child = node->data_ <= data_ ? left_ : right_;
    if (child)
        child->addNode(node) ;
    else  
        child = node;
}

bool BinaryTree::isLeaf() const 
{
    return !left_ && !right_;
}




bool BinaryTree::rotateLeftChildRight()
{
    if (!left_ || !left_->left_)
        return false;
    left_ = rotateRight(left_);
    return true;
}

bool BinaryTree::rotateLeftChildLeft()
{
    if (!left_ || !left_->right_)
        return false;
    left_ = rotateLeft(left_);
    return true;
}

bool BinaryTree::rotateRightChildRight()
{
    if (!right_ || !right_->left_)
        return false;
    right_ = rotateRight(right_);
    return true;
}

bool BinaryTree::rotateRightChildLeft()
{
    if (!right_ || !right_->right_)
        return false;
    right_ = rotateLeft(right_);
    return true;
}

// static
 std::shared_ptr<BinaryTree> BinaryTree::rotateRight(std::shared_ptr<BinaryTree> node)
{
    auto upNode = node->left_;
    auto downNode = node;

    auto newDownNodeLeft = upNode->right_;
    upNode->right_ = downNode;
    downNode->left_ = newDownNodeLeft;

    return upNode;
}

 // static
std::shared_ptr<BinaryTree> BinaryTree::rotateLeft(std::shared_ptr<BinaryTree> node)                              
{
    auto upNode = node->right_;
    auto downNode = node;

    auto newDownNodeRight = upNode->left_;
    upNode->left_ = downNode;
    downNode->right_ = newDownNodeRight;

    return upNode;
}
/*
void BinaryNode::iterateNodes(std::function<void(const BinaryNode&)> fn) const
{
    if (left_)
        left_->iterateNodes(fn);
    fn(*this);
    if (right_)
        right_->iterateNodes(fn);
}
*/
int BinaryTree::calculateDepth() const
{    
    if (isLeaf())
        return 1;

    int ld = left_ ? left_->calculateDepth() : 0;
    int rd = right_ ? right_->calculateDepth() : 0;
    int dd = ld < rd ? rd : ld;
    return dd + 1;
}

void BinaryTree::printNodes() const
{
    printf("(");
    if (left_) 
        left_->printNodes();
    printf(" %d ", data_);
    if (right_)
        right_->printNodes();
    printf(")");
}

void BinaryTree::printNodes1() const
{
    printf("(");
    if (left_) {
        if (left_->isLeaf())
            printf(" %d ", left_->data());
        else
            left_->printNodes1();
    }
    else {
        printf(" _ ");
    }
    printf(" %d ", data_);
    if (right_) {
        if (right_->isLeaf())
            printf(" %d ", right_->data());
        else
            right_->printNodes1();
    }
    else {
        printf(" _ ");
    }
    printf(")");
}
