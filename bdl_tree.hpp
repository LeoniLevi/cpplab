#pragma once

#include <memory>
#include <functional>

#define USE_BDL_WEAK_PTR




#ifdef USE_BDL_WEAK_PTR
    class BdlTreeNode : public std::enable_shared_from_this<BdlTreeNode>
#else
    class BdlTreeNode
#endif
{
public:
    BdlTreeNode(int data) : data_(data), depth_(1) {}


    void addData(int data);
    void addDataAVL(int data);

    void iterateNodes(std::function<void(const BdlTreeNode&)>) const;
    bool isLeaf() const;
    
    int data() const { return data_; }
    unsigned depth() const { return depth_; }
    std::shared_ptr<BdlTreeNode> left() { return left_; }
    std::shared_ptr<BdlTreeNode> right() { return right_; }

    static std::shared_ptr<BdlTreeNode> rotateRight(std::shared_ptr<BdlTreeNode> node);
    static std::shared_ptr<BdlTreeNode> rotateLeft(std::shared_ptr<BdlTreeNode> node);


    void printNodes() const;
    void printNodes1() const;
    int calculateDepth() const;


    int getLeftMinusRightDepth() const;
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

    void addData(int data) {
        if (!root_)
            root_ = std::make_shared<BdlTreeNode>(data);
        else
            root_->addData(data);
    }

    void addDataAVL(int data) {
        if (!root_)
            root_ = std::make_shared<BdlTreeNode>(data);
        else
            root_->addDataAVL(data);

        int diff = root_->getLeftMinusRightDepth();
        std::shared_ptr<BdlTreeNode> upChild;
        if (diff < -1)
            upChild = BdlTreeNode::rotateLeft(root_);
        else if (diff > 1)
            upChild = BdlTreeNode::rotateRight(root_);
        if (upChild) {
            root_ = upChild;
        }
    }


private:
    std::shared_ptr<BdlTreeNode> root_;
};