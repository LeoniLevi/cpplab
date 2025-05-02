#pragma once

#include "tree_node.hpp"

#include <memory>
#include <functional>

void testBinaryTreeAdding();
void testBinaryTreeRotating();



class BinaryTree : public TreeNode<int> {
public:    
    int data() const override { return data_; }
    const BinaryTree* left() const override { return left_.get(); }
    const BinaryTree* right() const override { return right_.get(); }


    BinaryTree(int data) : data_(data) {}
    void addData(int data); 

    //void iterateNodes(std::function<void(const BinaryNode&)>) const;
    bool isLeaf() const;
    
    

    BinaryTree* left() { return left_.get(); }
    BinaryTree* right() { return right_.get(); }

    bool rotateLeftChildRight();
    bool rotateLeftChildLeft();

    bool rotateRightChildRight();
    bool rotateRightChildLeft();

    static std::shared_ptr<BinaryTree> rotateRight(std::shared_ptr<BinaryTree> node);
    static std::shared_ptr<BinaryTree> rotateLeft(std::shared_ptr<BinaryTree> node);
    

    void printNodes() const;
    void printNodes1() const;
    int calculateDepth() const;

private:    
    void addNode(std::shared_ptr<BinaryTree> node);

    
private:
    int data_;
    std::shared_ptr<BinaryTree> left_;
    std::shared_ptr<BinaryTree> right_;
};