#pragma once


#include "tree_node.hpp"
#include "rb_common.hpp"
#include <memory>

void testRBQIntTree();


class RBQIntNode : public TreeNode<int>
{
public:
    RBQIntNode(int value, RBColor color)
        : value_(value), color_(color)
        , parent_(0)
    {}

    /// TreeNode<int> implementation
    int data() const override { return value(); }
    const TreeNode<int>* left() const override { return left_.get(); }
    const TreeNode<int>* right() const override { return right_.get(); }

    int value() const { return value_; }
    RBColor color() const { return color_; }

    RBQIntNode* parent() { return parent_; }
    RBQIntNode* nleft() { return left_.get(); }
    RBQIntNode* nright() { return right_.get(); }

    void setColor(RBColor color) { color_ = color; }


    RBQIntNode* rotateLeft();
    RBQIntNode* rotateRight();
    RBQIntNode* addChild(int value);
    bool isRoot() const { return parent_ && parent_->parent_ == 0; }
private:
    int value_;
    RBColor color_;


    RBQIntNode* parent_;
    std::unique_ptr<RBQIntNode> left_;
    std::unique_ptr<RBQIntNode> right_;
};

class RBQIntTree {
public:
    RBQIntTree(int rootValue);
    RBQIntNode* root() { return sentinel_.nleft(); }
    void add(int value);
    void fixTreeForNode(RBQIntNode* node);
private:
    RBQIntNode sentinel_; // !! sentinel's left is a Tree Root !!
};
