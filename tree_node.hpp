#pragma once

#include <string>
#include <iostream>
#include <iomanip>

template <typename T>
class TreeNode {
public:
    virtual T data() const = 0;
    virtual const TreeNode<T>* left() const = 0;
    virtual const TreeNode<T>* right() const = 0;
};

template <typename T>
int getDepth(const TreeNode<T>* node)
{
    if (!node)
        return 0;
    int dl = getDepth(node->left);
    int dr = getDepth(node->right);
    return dl > dr ? dl : dr;
}
/*
* // !! NOT FINISHED YET !!
template<typename T>
void drawNodeTree(const TreeNode<T>* root, int slotLen)
{
    int treeDepth = getDepth(root);
    int maxDepNumSlots = 1; // initially
    for (int i = 2; i <= treeDepth; ++i) {
        maxDepNumSlots *= 2;
    }
    int lineLen = (maxDepNumSlots * 2 - 1) * slotLen;

    int spaceLen = lineLen / 2 - slotLen / 2;
    std::cout << std::setw(spaceLen) << " ";
    int numDepSlots = 1;
    for (i = 2; i <= treeDepth) {
        numDepSlots *= 2;
        spaceLen = (lineLen - numDepSlots * slotLen) / numDepSlots;
        for (j = 0; j < numDepSlots; ++j) {

        }


        //spaceLen = lineLen / 2 - slotLen / 2;
        //std::cout << std::setw(spaceLen) << " ";
    }

}
*/

template <typename T>
void PrintBT(const std::string& prefix, const TreeNode<T>* node, bool isLeft)
{
    if (node) {
        std::cout << prefix;
        std::cout << (isLeft ? "|--" : "---");

        // print the value of the node
        std::cout << node->data() << std::endl;

        // enter the next tree level - left and right branch
        PrintBT(prefix + (isLeft ? "|   " : "    "), node->left(), true);
        PrintBT(prefix + (isLeft ? "|   " : "    "), node->right(), false);
    }
}

template <typename T>
void PrintBT(const TreeNode<T>* node)
{
    PrintBT("", node, false);
}

//========================

template <typename T>
void DisplayBT(const TreeNode<T>* current, int indent)
{
    //using namespace std;
    if (current != nullptr)
    {
        DisplayBT(current->left(), indent + 4);
        if (indent > 0)
            std::cout << std::setw(indent) << " ";
        std::cout << current->data() << std::endl;
        DisplayBT(current->right(), indent + 4);
    }
}