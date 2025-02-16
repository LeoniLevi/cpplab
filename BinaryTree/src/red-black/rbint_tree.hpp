#pragma once

#include "rb_common.hpp"
#include "tree_node.hpp"
#include <memory>

class RBIntNode : public TreeNode<int> 
{
public:
    RBIntNode(int value, RBColor color)
        : value_(value), color_(color)
        , parent_(0), left_(0), right_(0)
    {}
    
    /// TreeNode<int> implementation
    int data() const override { return value(); }
    const TreeNode<int>* left() const override { return left_; }
    const TreeNode<int>* right() const override { return right_; }
    
    int value() const { return value_; }
    RBColor color() const { return color_; }

    RBIntNode* parent() { return parent_; }
    RBIntNode* nleft() { return left_; }
    RBIntNode* nright() { return right_; }

    void setColor(RBColor color) { color_ = color; }

    //static void rotateLeftToLeft();

    RBIntNode* rotateLeft();
    RBIntNode* rotateRight();
    //RBIntNode* addChild(int value, RBColor color);
    RBIntNode* addChild(int value);
private:
    int value_;
    RBColor color_;

    
    RBIntNode* parent_;
    //std::unique_ptr<RBIntNode> left_;
    //std::unique_ptr<RBIntNode> right_;

    RBIntNode* left_;
    RBIntNode* right_;

};

class RBIntTree {
public:
    RBIntTree(int rootValue);
    RBIntNode* root() const { return root_; }
    void add(int value);
    void fixTreeForNode(RBIntNode* node);
private:
    RBIntNode* root_;
};
