#include "bst_node.hpp"

#include <string>
#include <iostream>
#include <iomanip>

void printBT(const std::string& prefix, const BSTNode* node, bool isLeft)
{
    if (node != nullptr)
    {
        std::cout << prefix;

        std::cout << (isLeft ? "|--" : "---");

        // print the value of the node
        std::cout << node->m_val << std::endl;

        // enter the next tree level - left and right branch
        printBT(prefix + (isLeft ? "|   " : "    "), node->m_left, true);
        printBT(prefix + (isLeft ? "|   " : "    "), node->m_right, false);
    }
}

void printBT(const BSTNode* node)
{
    printBT("", node, false);
}

void deleteNode(BSTNode* node)
{
    if (node->m_left)
        deleteNode(node->m_left);
    if (node->m_right)
        deleteNode(node->m_right);

    delete node;
}



void Display(BSTNode* current, int indent)
{
    using namespace std;
    if (current != nullptr)
    {
        Display(current->m_left, indent + 4);
        if (indent > 0)
            cout << setw(indent) << " ";
        cout << current->m_val << endl;
        Display(current->m_right, indent + 4);
    }
}

void test_bst_tree()
{
    auto node0 = new BSTNode{ 16, 0, 0 };
    auto node10 = new BSTNode{ 8, 0, 0 };
    auto node11 = new BSTNode{ 24, 0, 0 };

    node0->m_left = node10;
    node0->m_right = node11;

    auto node20 = new BSTNode{ 4, 0, 0 };
    auto node21 = new BSTNode{ 12, 0, 0 };
    auto node22 = new BSTNode{ 20, 0, 0 };
    auto node23 = new BSTNode{ 28, 0, 0 };


    node10->m_left = node20;
    node10->m_right = node21;
    node11->m_left = node22;
    node11->m_right = node23;

    auto node30 = new BSTNode{ 2, 0, 0 };
    auto node31 = new BSTNode{ 6, 0, 0 };
    auto node32 = new BSTNode{ 10, 0, 0 };
    auto node33 = new BSTNode{ 14, 0, 0 };
    auto node34 = new BSTNode{ 18, 0, 0 };
    auto node35 = new BSTNode{ 22, 0, 0 };
    auto node36 = new BSTNode{ 26, 0, 0 };
    auto node37 = new BSTNode{ 30, 0, 0 };

    node20->m_left = node30;
    node20->m_right = node31;
    node21->m_left = node32;
    node21->m_right = node33;
    node22->m_left = node34;
    node22->m_right = node35;
    node23->m_left = node36;
    node23->m_right = node37;

    std::cout << "\n\n";

    printBT(node0);

    std::cout << "\n----------------------------------\n";
    Display(node0, 0);
    std::cout << "\n----------------------------------\n";

    deleteNode(node0);

    std::cout << "\n\n";

}
