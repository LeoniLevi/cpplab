#pragma once

#include "tree_node.hpp"

#include <memory>
#include <functional>

class TreeNode0 : public TreeNode<int> {
public:    
    int data() const override { return data_; }
    const TreeNode0* left() const override { return left_.get(); }
    const TreeNode0* right() const override { return right_.get(); }


    TreeNode0(int data) : data_(data) {}
    void addData(int data); 

    void iterateNodes(std::function<void(const TreeNode0&)>) const;
    bool isLeaf() const;

    
    

    TreeNode0* left() { return left_.get(); }
    TreeNode0* right() { return right_.get(); }

    bool rotateLeftChildRight();
    bool rotateLeftChildLeft();

    bool rotateRightChildRight();
    bool rotateRightChildLeft();

    static std::shared_ptr<TreeNode0> rotateRight(std::shared_ptr<TreeNode0> node);
    static std::shared_ptr<TreeNode0> rotateLeft(std::shared_ptr<TreeNode0> node);
    

    void printNodes() const;
    void printNodes1() const;
    int calculateDepth() const;

private:    
    void addNode(std::shared_ptr<TreeNode0> node);

    
private:
    int data_;
    std::shared_ptr<TreeNode0> left_;
    std::shared_ptr<TreeNode0> right_;
};