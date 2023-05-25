#pragma once

#include "tree_node.hpp"

#include <memory>
#include <functional>

#define USE_BDL_WEAK_PTR


enum class DepthBalanceStatus {
    Ok = 0,
    LeftLeft =1,
    LeftRight = 2,
    RightLeft = 3,
    RightRight = 4,
};

#ifdef USE_BDL_WEAK_PTR
    class BdlTreeNode : public TreeNode<int>, public std::enable_shared_from_this<BdlTreeNode>
#else
    class BdlTreeNode : public TreeNode<int>
#endif
{
public:

    int data() const override { return data_; }
    const BdlTreeNode* left() const override { return left_.get(); }
    const BdlTreeNode* right() const override { return right_.get(); }


    BdlTreeNode(int data) : data_(data), depth_(1) {}

    void addDataAVL(int data);
    bool isLeaf() const;

    unsigned depth() const { return depth_; }

    //void addData(int data);    

    std::shared_ptr<BdlTreeNode> sleft() { return left_; }
    std::shared_ptr<BdlTreeNode> sright() { return right_; }

    
    static std::shared_ptr<BdlTreeNode> ProvideNodeBalance(std::shared_ptr<BdlTreeNode> workChild);

    static std::shared_ptr<BdlTreeNode> rotateRight(std::shared_ptr<BdlTreeNode> node);
    static std::shared_ptr<BdlTreeNode> rotateLeft(std::shared_ptr<BdlTreeNode> node);


    void printNodes() const;
    void printNodes1() const;
    int calculateDepth() const;


    //int getLeftMinusRightDepth() const;
    DepthBalanceStatus getDepthBalanceStatus() const;
private:
    void addNode(std::shared_ptr<BdlTreeNode> node);
    void addNodeAVL(std::shared_ptr<BdlTreeNode> node);
    void updateDepthByChildren();
    void updateDepthsRecursivelyUpToRoot();
    

    void makeMeParentOf(std::shared_ptr<BdlTreeNode> node);
private:
    int data_;
    unsigned depth_;
#ifdef USE_BDL_WEAK_PTR
    std::weak_ptr<BdlTreeNode> parent_;
#else
    BdlTreeNode* parent_ = nullptr;
#endif
    std::shared_ptr<BdlTreeNode> left_;
    std::shared_ptr<BdlTreeNode> right_;
};


class BdlTree {
public:
    BdlTree() {}

    std::shared_ptr<BdlTreeNode> root() { return root_; }
    
    void addDataAVL(int data) {
        if (!root_)
            root_ = std::make_shared<BdlTreeNode>(data);
        else {
            root_->addDataAVL(data);
        }

        std::shared_ptr<BdlTreeNode> upChild = BdlTreeNode::ProvideNodeBalance(root_);
        if (upChild) 
            root_ = upChild;
    }


private:
    std::shared_ptr<BdlTreeNode> root_;
};