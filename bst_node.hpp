#pragma once

struct BSTNode {
    int m_val;
    BSTNode* m_left;
    BSTNode* m_right;
};

void deleteNode(BSTNode* node);

void printBT(const BSTNode* node);
void Display(BSTNode* current, int indent);

void test_bst_tree();

