#pragma once

#include "rb_common.hpp"
#include "tree_node.hpp"

class RBIntNode;

class RBIntTree {
public:
    RBIntTree();
    ~RBIntTree();
    //const RBIntNode* root() const { return root_; }
    RBIntNode* root() const { return root_; }
    void add(int value);
    bool remove(int value);
private:
    void fixTreeForNode(RBIntNode* node);
    void fixDoubleBlackNode(RBIntNode* node);
    static RBIntNode* createNode(int value, RBColor color);
    static void destroyNode(RBIntNode* node);
private:
    RBIntNode* root_;

    static int createdNodes_;
    static int destroyedNodes_;
};

bool isRBIntTreeValid(const RBIntTree* tree);

class RBIntNode : public TreeNode<int> 
{
public:
    RBIntNode(int value, RBColor color)
        : value_(value), color_(color)
        , parent_(0), left_(0), right_(0)
    {}
    
    /// TreeNode<int> implementation
    int data() const override { return value_; }
    const TreeNode<int>* left() const override { return left_; }
    const TreeNode<int>* right() const override { return right_; }
    
    RBColor color() const { return color_; }

    const RBIntNode* parent() const { return parent_; }
    const RBIntNode* nleft() const { return left_; }
    const RBIntNode* nright() const { return right_; }

    bool isLeft() const { return parent_ && parent_->left_ == this; }
    bool isRight() const { return parent_ && parent_->right_ == this; }

private:
    friend class RBIntTree;

    RBIntNode* addNode(RBIntNode* node);
    RBIntNode* searchNode(int value);
    RBIntNode* rotateLeft();
    RBIntNode* rotateRight();

    RBIntNode* parent() { return parent_; }
    RBIntNode* nleft() { return left_; }
    RBIntNode* nright() { return right_; }

    RBIntNode* sibling() { 
        if (!parent_)
            return nullptr;
        return isLeft() ? parent_->right_ : parent_->left_;
    }

    void setColor(RBColor color) { color_ = color; }
    void setValue(int value) { value_ = value; }

    void substituteWith(RBIntNode* node);

private:
    int value_;
    RBColor color_;
    
    RBIntNode* parent_;

    RBIntNode* left_;
    RBIntNode* right_;
};

inline bool isRed(const RBIntNode* nd) { return nd && nd->color() == RBColor::Red; }
inline bool isBlack(const RBIntNode* nd) { return !isRed(nd); }

