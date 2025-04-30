#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include <functional>
#include <queue>

#include <sstream>

enum class DepthBalanceStatus {
    Ok = 0,
    LeftLeft = 1,
    LeftRight = 2,
    RightLeft = 3,
    RightRight = 4,
};

template <typename T>
class TreeNode {
public:
    virtual T data() const = 0;
    virtual const TreeNode<T>* left() const = 0;
    virtual const TreeNode<T>* right() const = 0;

    int max_deepness() const {
        const int left_dps = left() ? left()->max_deepness() : 0;
        const int right_dps = right() ? right()->max_deepness() : 0;
        return (left_dps > right_dps ? left_dps : right_dps) + 1;
    }
};

template <typename T>
int getDepth(const TreeNode<T>* node)
{
    if (!node)
        return 0;
    int dl = 1 + getDepth(node->left());
    int dr = 1 + getDepth(node->right());
    return dl > dr ? dl : dr;
}

template <typename T>
void iterateTreeNodesDF(const TreeNode<T>* treeNode, std::function<void(const TreeNode<T>&)> fn) 
{
    if (treeNode->left())
        iterateTreeNodesDF(treeNode->left(), fn);
    fn(*treeNode);
    if (treeNode->right())
        iterateTreeNodesDF(treeNode->right(), fn);
}

template <typename T>
void iterateTreeNodesBF(const TreeNode<T>* treeNode, 
                        std::function<void(const TreeNode<T>&)> fn)
{
    std::queue<const TreeNode<T>*> nq;
    nq.push(treeNode);

    while (!nq.empty()) {
        auto node = nq.front();
        nq.pop();

        fn(*node);
        
        if (node->left())
            nq.push(node->left());
        if (node->right())
            nq.push(node->right());            
    }
}

template <typename T>
std::string treeNodeToString(const TreeNode<T>* node, int level=-1)
{
    if (!node)
        return std::string();

    // set left/right delimiter - various if level >= 0
    int nextLevel = level;
    char ldelim = '(';
    char rdelim = ')';
    if (level > -1) {
        int nm = level % 3;
        ldelim = nm == 0 ? '(' : nm == 1 ? '[' : '<';
        rdelim = nm == 0 ? ')' : nm == 1 ? ']' : '>';
    }

    std::stringstream ss;
    ss << ldelim << treeNodeToString(node->left(), nextLevel)
       << ' ' << node->data() << ' ' 
       << treeNodeToString(node->right(), nextLevel) << rdelim;
    return ss.str();
}

template<typename T>
void drawSlot(int slotLen, const TreeNode<T>* node = 0) {
    if (node)
        std::cout << std::setfill('0') << std::setw(slotLen) << node->data() << std::setfill(' ');
    else
        std::cout << std::setw(slotLen) << "";
    //std::cout << std::setfill(' ');
}

template<typename T>
void drawSlotZone(int zoneLen, int slotLen, const TreeNode<T>* node)
{
    int prefixLen = (zoneLen - slotLen) / 2;
    std::cout << std::setw(prefixLen) << "";
    drawSlot(slotLen, node);
    std::cout << std::setw(zoneLen - prefixLen - slotLen) << "";
}

template<typename T>
void drawNodeTree(const TreeNode<T>* root, int slotLen)
{
    int treeDepth = getDepth(root);
    int maxDepNumSlots = 1; // initially
    for (int i = 2; i <= treeDepth; ++i) {
        maxDepNumSlots *= 2;
    }
    int lineLen = (maxDepNumSlots * 2) * slotLen;

    int numDepSlots = 1;
    std::vector<const TreeNode<T>*> lineNodes {root};
    for (int dep = 1; dep <= treeDepth; ++dep) {
        int zoneLen = lineLen / numDepSlots;
        for (int j = 0; j < numDepSlots; ++j) {
            drawSlotZone(zoneLen, slotLen, lineNodes[j]);
        }
        std::cout << '\n';

        int nextNumDepSlots = numDepSlots * 2;
        std::vector<const TreeNode<T>*> nextLineNodes(nextNumDepSlots);
        for (int j = 0; j < numDepSlots; ++j) {
            const TreeNode<T>* nd = lineNodes[j];
            if (nd) {
                nextLineNodes[j * 2] = nd->left();
                nextLineNodes[j * 2 + 1] = nd->right();
            }
        }

        numDepSlots = nextNumDepSlots;
        lineNodes = nextLineNodes;
    }
}

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
void DisplayBT(const TreeNode<T>* node, int indent)
{
    if (node) {
        //DisplayBT(node->left(), indent + 4);
        DisplayBT(node->right(), indent + 4);
        if (indent > 0)
            std::cout << std::setw(indent) << ' ';
        std::cout << node->data() << std::endl;
        //DisplayBT(node->right(), indent + 4);
        DisplayBT(node->left(), indent + 4);
    }
}