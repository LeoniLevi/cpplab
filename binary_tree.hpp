#pragma once

#include <memory>
#include <functional>

class TreeNode0 {
public:    
    TreeNode0(int data) : data_(data) {}
    void addData(int data); 

    void iterateNodes(std::function<void(const TreeNode0&)>) const;
    bool isLeaf() const;

    int data() const { return data_; }
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