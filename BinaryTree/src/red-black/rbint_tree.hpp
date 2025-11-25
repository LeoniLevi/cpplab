#pragma once

#include "rb_common.hpp"
#include "tree_node.hpp"
#include <memory>

void testRBIntTree();

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

//private:
    //friend class RBIntTree;

    RBIntNode* parent() { return parent_; }
    RBIntNode* nleft() { return left_; }
    RBIntNode* nright() { return right_; }

    RBIntNode* sibling() { return parent_ ? (isLeft() ? left_ : right_) : nullptr; }

    void setColor(RBColor color) { color_ = color; }
    void setValue(int value) { value_ = value; }

    RBIntNode* addNode(RBIntNode* node);

    RBIntNode* searchNode(int value);

    bool isLeft() const { return parent_ && parent_->left_ == this; }

    void substituteWith(RBIntNode* node);

    RBIntNode* rotateLeft();
    RBIntNode* rotateRight();
    

private:
    int value_;
    RBColor color_;
    
    RBIntNode* parent_;

    RBIntNode* left_;
    RBIntNode* right_;

};


inline bool isRed(const RBIntNode* nd) { return nd && nd->color() == RBColor::Red; }
inline bool isBlack(const RBIntNode* nd) { return !isRed(nd); }

class RBIntTree {
public:
    RBIntTree();
    ~RBIntTree();
    RBIntNode* root() const { return root_; }
    void add(int value);
    bool remove(int value);
private:
    void fixTreeForNode(RBIntNode* node);
    void fixDoubleBlackNode(RBIntNode* node);
    static RBIntNode* CreateNode(int value, RBColor color);
    static void DestroyNode(RBIntNode* node);
private:
    RBIntNode* root_;

    static int createdNodes_;
    static int destroyedNodes_;
};
