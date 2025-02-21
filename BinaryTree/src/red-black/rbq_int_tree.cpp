#include "rbq_int_tree.hpp"

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

RBQIntTree::RBQIntTree(int rootValue) //: root_(new RBQIntNode(rootValue, RBColor::Black))
    : sentinel_(0, RBColor::Black)
{
    RBQIntNode* root = sentinel_.addChild(rootValue);
    root->setColor(RBColor::Black);
}

void RBQIntTree::add(int value) { 
    RBQIntNode* root = this->root();
    rassert(root, "RBQIntTree::add - root is NULL");
    RBQIntNode* newNode = root->addChild(value);
    newNode->setColor(RBColor::Red); //
    fixTreeForNode(newNode);
}

void RBQIntTree::fixTreeForNode(RBQIntNode* node)
{
    rassert(node->color() == RBColor::Red, "RBQIntTree::fixTreeForNode - node is not RED");

    RBQIntNode* parent = node->parent();

    if (!parent || parent->color() == RBColor::Black)
        return; // it's OK, no need to fix

    //// Parent is RED

    if (parent->isRoot())
        return;
    
    RBQIntNode* gparent = parent->parent();
    if (!gparent)
        return;
        //err_exit("RBQIntTree::fixTreeForNode - no grandparent(when parent is RED)");
        
    rassert(gparent->color() == RBColor::Black, "RBQIntTree::fixTreeForNode - no grandparent(when parent is RED)");


    //// Grandparent is BLACK

    RBQIntNode* uncle
        = gparent->nleft() == parent ? gparent->nright()
        : gparent->nright() == parent ? gparent->nleft()
        : 0;


    bool gparentIsRoot = gparent->isRoot();

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
        RBQIntNode* newGParent = gparent->rotateRight();
        rassert(newGParent->color() == RBColor::Red, "RBQIntTree::fixTreeForNode(LL) - new grandparent isn't RED");

        parent->setColor(RBColor::Black);
        gparent->setColor(RBColor::Red);
    }
    else if (gparent->left() == parent && parent->right() == node) { // LeftRight case
        RBQIntNode* newParent = parent->rotateLeft();
        RBQIntNode* newGParent = gparent->rotateRight();
        rassert(newGParent->color() == RBColor::Red, "RBQIntTree::fixTreeForNode(LR) - new grandparent isn't RED");
        
        node->setColor(RBColor::Black);
        gparent->setColor(RBColor::Red);
    }
    else if (gparent->right() == parent && parent->right() == node) { // RightRight case
        RBQIntNode* newGParent = gparent->rotateLeft();
        rassert(newGParent->color() == RBColor::Red, "RBQIntTree::fixTreeForNode(RR) - new grandparent isn't RED");
        
        newGParent->setColor(RBColor::Black);
        gparent->setColor(RBColor::Red);
    }
    else if (gparent->right() == parent && parent->left() == node) { // RightLeft case
        RBQIntNode* newParent = parent->rotateRight();
        RBQIntNode* newGParent = gparent->rotateLeft();
        rassert(newGParent->color() == RBColor::Red, "RBQIntTree::fixTreeForNode(RL) - new grandparent isn't RED");
        
        node->setColor(RBColor::Black);
        gparent->setColor(RBColor::Red);
    }
}

//-----------------------

RBQIntNode* RBQIntNode::addChild(int value)
{
    if (!parent_) { // if it's sentinel
        left_ = std::make_unique<RBQIntNode>(value, RBColor::Red);
        left_->parent_ = this;
        return left_.get();
    }

    if (value <= value_) {
        if (left_) {
            return left_->addChild(value);
        }
        left_ = std::make_unique<RBQIntNode>(value, RBColor::Red);
        left_->parent_ = this;   
        return left_.get();
    }
    else {
        if (right_) {
            return right_->addChild(value);
        }        
        right_ = std::make_unique<RBQIntNode>(value, RBColor::Red);
        right_->parent_ = this;
        return right_.get();
    }
}

RBQIntNode* RBQIntNode::rotateLeft()
{
    rassert((bool)right_, "RBQIntNode::rotateLeft - right is absent");

    RBQIntNode* parentNode = this->parent_;
    rassert(parentNode, "RBQIntNode::rotateLeft - parent is absent");

    bool isLeftChild = parentNode->left() == this;
    if (!isLeftChild && parentNode->right() != this)
        err_exit("RBQIntNode::rotateLeft - node has parent but not its child");

    auto downUptr = isLeftChild ? std::move(parentNode->left_) : std::move(parentNode->right_);
    auto upUptr = std::move(this->right_);

    upUptr->parent_ = parentNode;
    downUptr->parent_ = upUptr.get();

    downUptr->right_ = std::move(upUptr->left_);
    upUptr->left_ = std::move(downUptr);

    auto upPtr = upUptr.get();

    if (isLeftChild)
        parentNode->left_  = std::move(upUptr);
    else
        parentNode->right_ = std::move(upUptr);

    return upPtr;
}

RBQIntNode* RBQIntNode::rotateRight()
{
    rassert((bool)left_, "RBQIntNode::rotateRight - left is absent");

    RBQIntNode* parentNode = this->parent_;
    rassert(parentNode, "RBQIntNode::rotateRight - parent is absent");


    bool isLeftChild = parentNode->left() == this;
    if (!isLeftChild && parentNode->right() != this)
        err_exit("RBQIntNode::rotateRight - node has parent but not its child");

    auto downUptr = isLeftChild ? std::move(parentNode->left_) : std::move(parentNode->right_);
    auto upUptr = std::move(this->left_);

    upUptr->parent_ = parentNode;
    downUptr->parent_ = upUptr.get();

    downUptr->left_ = std::move(upUptr->right_);
    upUptr->right_ = std::move(downUptr);

    auto upPtr = upUptr.get();

    if (isLeftChild)
        parentNode->left_ = std::move(upUptr);
    else
        parentNode->right_ = std::move(upUptr);    

    return upPtr;
}


