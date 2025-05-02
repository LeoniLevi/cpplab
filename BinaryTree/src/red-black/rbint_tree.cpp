#include "rbint_tree.hpp"
#include <stdexcept>

inline void err_exit(const char* errmsg) 
{
    printf(" !! ERROR(R-ABORT): %s\n", errmsg);
    abort();
}

inline void rassert(bool condition, const char* errmsg)
{
    if (!condition)
        err_exit(errmsg);
}



//----------------------------

RBIntTree::RBIntTree(int rootValue) : root_(new RBIntNode(rootValue, RBColor::Black))
{}

void RBIntTree::add(int value)
{
    RBIntNode* newNode = root_->addChild(value);
    newNode->setColor(RBColor::Red); //
    fixTreeForNode(newNode);
}

void RBIntTree::fixTreeForNode(RBIntNode* node)
{
    rassert(node->color() == RBColor::Red, "RBIntTree::fixTreeForNode - node is not RED");

    RBIntNode* parent = node->parent();

    if (!parent || parent->color() == RBColor::Black)
        return; // it's OK, no need to fix

    //// Parent is RED

    RBIntNode* gparent = parent->parent();
    if (!gparent)
        err_exit("RBIntTree::fixTreeForNode - no grandparent(when parent is RED)");

    rassert(gparent->color() == RBColor::Black, "RBIntTree::fixTreeForNode - no grandparent(when parent is RED)");


    //// Grandparent is BLACK

    RBIntNode* uncle
        = gparent->nleft() == parent ? gparent->nright()
        : gparent->nright() == parent ? gparent->nleft()
        : 0;


    bool gparentIsRoot = gparent == root_;

    RBColor uncleColor = uncle ? uncle->color() : RBColor::Black;

    if (uncleColor == RBColor::Red) {
        parent->setColor(RBColor::Black);
        uncle->setColor(RBColor::Black);
        if (!gparentIsRoot) {
            gparent->setColor(RBColor::Red);
            fixTreeForNode(gparent);
        }
        return;
    }

    //// Uncle is BLACK
    

    if (gparent->left() == parent && parent->left() == node) { // LeftLeft case
        RBIntNode* newGParent = gparent->rotateRight();
        if (gparentIsRoot) {
            root_ = newGParent;
        }
        parent->setColor(RBColor::Black);
        gparent->setColor(RBColor::Red);
    }
    else if (gparent->left() == parent && parent->right() == node) { // LeftRight case
        RBIntNode* newParent = parent->rotateLeft();
        RBIntNode* newGParent = gparent->rotateRight();
        rassert(newGParent->color() == RBColor::Red, "RBIntTree::fixTreeForNode(LR) - new grandparent isn't RED");
        if(gparentIsRoot) {
            root_ = newGParent;
        }
        
        node->setColor(RBColor::Black);
        gparent->setColor(RBColor::Red);
    }
    else if (gparent->right() == parent && parent->right() == node) { // RightRight case
        RBIntNode* newGParent = gparent->rotateLeft();
        rassert(newGParent->color() == RBColor::Red, "RBIntTree::fixTreeForNode(RR) - new grandparent isn't RED");

        if (gparentIsRoot) {
            root_ = newGParent;
        }
        newGParent->setColor(RBColor::Black);
        gparent->setColor(RBColor::Red);
    }
    else if (gparent->right() == parent && parent->left() == node) { // RightLeft case
        RBIntNode* newParent = parent->rotateRight();
        RBIntNode* newGParent = gparent->rotateLeft();
        rassert(newGParent->color() == RBColor::Red, "RBIntTree::fixTreeForNode(RL) - new grandparent isn't RED");
        if (gparentIsRoot) {
            root_ = newGParent;
        }
        node->setColor(RBColor::Black);
        gparent->setColor(RBColor::Red);
    }
}

//-----------------------

RBIntNode* RBIntNode::addChild(int value)
{
    if (value <= value_) {
        if (left_) {
            return left_->addChild(value);
        }
        left_ = new RBIntNode(value, RBColor::Red);
        left_->parent_ = this;   
        //return left_.get();
        return left_;
    }
    else {
        if (right_) {
            return right_->addChild(value);
        }        
        right_ = new RBIntNode(value, RBColor::Red);
        right_->parent_ = this;
        return right_;
    }
}

RBIntNode* RBIntNode::rotateLeft()
{
    rassert(right_, "RBIntNode::rotateLeft - right is absent");

    RBIntNode* upNode = right_;
    RBIntNode* downNode = this;

    RBIntNode* parentNode = downNode->parent_;
    if (parentNode) {
        if (parentNode->left_ == this)
            parentNode->left_ = upNode;
        else if (parentNode->right_ == this)
            parentNode->right_ = upNode;
        else
            err_exit("RBIntNode::rotateLeft - node is not a child of parent");
    }

    RBIntNode* upNodeOldLeft = upNode->left_;

    upNode->parent_ = parentNode;
    upNode->left_ = downNode;

    downNode->parent_ = upNode;
    downNode->right_ = upNodeOldLeft;

    return upNode;
}

RBIntNode* RBIntNode::rotateRight()
{
    rassert(left_, "RBIntNode::rotateRight - left is absent");


    RBIntNode* upNode = left_;
    RBIntNode* downNode = this;

    RBIntNode* parentNode = downNode->parent_;
    if (parentNode) {
        if (parentNode->left_ == this)
            parentNode->left_ = upNode;
        else if (parentNode->right() == this)
            parentNode->right_ = upNode;
        else
            err_exit("RBIntNode::rotateRight - node is not a child of parent");
    }

    RBIntNode* upNodeOldRight = upNode->right_;

    upNode->parent_ = parentNode;
    upNode->right_ = downNode;

    downNode->parent_ = upNode;
    downNode->left_ = upNodeOldRight;

    return upNode;
}


//==============


void testRBIntTree()
{
    printf("==== testRBIntTree - start...\n");

    RBIntTree rbtree(12);
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

    rbtree.add(10);
    rbtree.add(22);
    rbtree.add(6);
    rbtree.add(9);
    rbtree.add(13);
    rbtree.add(2);
    rbtree.add(1);

    int depth = rbtree.root()->max_deepness();
    drawNodeTree<int>(rbtree.root(), 3);
    printf(" ~~~~ testRBIntTree(depth=%d): iterateTreeNodesDF..\n", depth);
    iterateTreeNodesDF<int>(rbtree.root(), [](const TreeNode<int>& n) {
        auto rbn = (const RBIntNode&)n;
        char cc = rbn.color() == RBColor::Black ? 'B' : rbn.color() == RBColor::Red ? 'R' : '?';
        printf("%d(%c),", rbn.data(), cc);
                            });
    printf("\niterateTreeNodesBF..\n");
    iterateTreeNodesBF<int>(rbtree.root(), [](const TreeNode<int>& n) {
        auto rbn = (const RBIntNode&)n;
        char cc = rbn.color() == RBColor::Black ? 'B' : rbn.color() == RBColor::Red ? 'R' : '?';
        printf("%d(%c),", rbn.data(), cc);
                            });
    printf("\n");
    printf("====  testRBIntTree - Done!\n");
}
 