#include "rbint_tree.hpp"
#include "util.h"


void drawRBSlot(int slotLen, const RBIntNode* node = 0) {
    char clr = isRed(node) ? 'R' : 'B';
    if (node) {
        int parval = node->parent() ? node->parent()->data() : 0;
        std::cout << std::setfill('0') << std::setw(slotLen) <<
            node->data() << clr << parval << std::setfill(' ');
    }
    else {
        std::cout << std::setw(slotLen) << "";
    }
    //std::cout << std::setfill(' ');
}

void drawRBSlotZone(int zoneLen, int slotLen, const RBIntNode* node)
{
    int prefixLen = (zoneLen - slotLen) / 2;
    std::cout << std::setw(prefixLen) << "";
    drawRBSlot(slotLen, node);
    std::cout << std::setw(zoneLen - prefixLen - slotLen) << "";
}

void drawRBNodeTree(const RBIntTree* tree, int slotLen)
{
    const RBIntNode* root = tree->root();
    int treeDepth = getDepth(root);
    int maxDepNumSlots = 1; // initially
    for (int i = 2; i <= treeDepth; ++i) {
        maxDepNumSlots *= 2;
    }
    int lineLen = (maxDepNumSlots * 2) * slotLen;

    int numDepSlots = 1;
    std::vector<const RBIntNode*> lineNodes{ root };
    for (int dep = 1; dep <= treeDepth; ++dep) {
        int zoneLen = lineLen / numDepSlots;
        for (int j = 0; j < numDepSlots; ++j) {
            drawRBSlotZone(zoneLen, slotLen, lineNodes[j]);
        }
        std::cout << '\n';

        int nextNumDepSlots = numDepSlots * 2;
        std::vector<const RBIntNode*> nextLineNodes(nextNumDepSlots);
        for (int j = 0; j < numDepSlots; ++j) {
            const RBIntNode* nd = lineNodes[j];
            if (nd) {
                nextLineNodes[j * 2] = nd->nleft();
                nextLineNodes[j * 2 + 1] = nd->nright();
            }
        }

        numDepSlots = nextNumDepSlots;
        lineNodes = nextLineNodes;
    }
}


//==============


int getSomePathNumBlacks(const RBIntTree* tree)
{
    int numBlacks = 0;

    const RBIntNode* node = tree->root();
    while (node) {
        if (isBlack(node))
            numBlacks += 1;
        node = node->nleft() ? node->nleft() : node->nright();
    }

    return numBlacks;
}

bool isNodePathValid(const RBIntNode* node, int numUpperBlacks, int requiredNumBlacks)
{
    if (!node)
        return numUpperBlacks == requiredNumBlacks;
    if (isRed(node->parent()) && isRed(node))
        return false;
    int numBlacks = numUpperBlacks + (isBlack(node) ? 1 : 0);
    return isNodePathValid(node->nleft(), numBlacks, requiredNumBlacks) &&
        isNodePathValid(node->nright(), numBlacks, requiredNumBlacks);
}

bool isRBIntTreeValid(const RBIntTree* tree)
{
    int reqNumBlacks = getSomePathNumBlacks(tree);
    return isNodePathValid(tree->root(), 0, reqNumBlacks);
}

void testRBIntTree()
{
    printf("==== testRBIntTree - start...\n");

    RBIntTree rbtree;
    RASSERT(isRBIntTreeValid(&rbtree), "RBTree NOT VAlid");

    rbtree.add(12);

    RASSERT(isRBIntTreeValid(&rbtree), "RBTree NOT VAlid");

    /*
    rbtree.add(10);
    rbtree.add(7);
    rbtree.add(6);
    rbtree.add(5);
    rbtree.add(4);
    rbtree.add(3);
    rbtree.add(2);
    rbtree.add(1);
    */
    rbtree.add(15);
    rbtree.add(18);

    RASSERT(isRBIntTreeValid(&rbtree), "RBTree NOT VAlid");

    rbtree.add(10);
    rbtree.add(22);

    RASSERT(isRBIntTreeValid(&rbtree), "RBTree NOT VAlid");

    rbtree.add(6);
    rbtree.add(9);

    RASSERT(isRBIntTreeValid(&rbtree), "RBTree NOT VAlid");

    rbtree.add(13);
    rbtree.add(2);
    RASSERT(isRBIntTreeValid(&rbtree), "RBTree NOT VAlid");

    rbtree.add(1);

    rbtree.add(17);

    RASSERT(isRBIntTreeValid(&rbtree), "RBTree NOT VAlid");


    int valToRemove = 10;
    printf(" ~~~~~~~~~~~~~~~~~~~ before remove %d ~~~~~~~~~~~~~\n", valToRemove);
    drawRBNodeTree(&rbtree, 3);

    rbtree.remove(valToRemove);

    drawRBNodeTree(&rbtree, 3);
    printf(" ~~~~~~~~~~~~~~~~~~~ after remove %d ~~~~~~~~~~~~~\n", valToRemove);

    RASSERT(isRBIntTreeValid(&rbtree), "RBTree NOT VAlid");


    int numBlacks = getSomePathNumBlacks(&rbtree);
    int depth = rbtree.root()->max_deepness();
    printf(" ~~~~ testRBIntTree(depth=%d, numBlacks=%d): iterateTreeNodesDF..\n", depth, numBlacks);
    iterateTreeNodesDF<int>(rbtree.root(), [](const TreeNode<int>& n)
                            {
                                auto rbn = (const RBIntNode&)n;
                                char cc = isRed(&rbn) ? 'R' : 'B';
                                printf("%d(%c),", rbn.data(), cc);
                            });
    printf("\niterateTreeNodesBF..\n");
    iterateTreeNodesBF<int>(rbtree.root(), [](const TreeNode<int>& n)
                            {
                                auto rbn = (const RBIntNode&)n;
                                char cc = isRed(&rbn) ? 'R' : 'B';
                                printf("%d(%c),", rbn.data(), cc);
                            });
    printf("\n");
    printf("====  testRBIntTree - Done!\n");
}