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

int RBIntTree::createdNodes_ = 0;
int RBIntTree::destroyedNodes_ = 0;

RBIntTree::RBIntTree() : root_(nullptr) {}

RBIntTree::~RBIntTree()
{
    if (root_) {
        destroyNode(root_);
    }
}

//static 
RBIntNode* RBIntTree::createNode(int value, RBColor color) 
{
    createdNodes_ += 1;
    return new RBIntNode(value, color);
}
//static 
void RBIntTree::destroyNode(RBIntNode* node) 
{
    if (node->left())
        destroyNode(node->nleft());
    if (node->right())
        destroyNode(node->nright());

    destroyedNodes_ += 1;
    delete node;
}

void RBIntTree::add(int value)
{
    if (!root_) {
        root_ = createNode(value, RBColor::Black);
        return;
    }

    //RBIntNode* newNode = root_->addChild(value);
    RBIntNode* newNode = root_->addNode(createNode(value, RBColor::Black));
    newNode->setColor(RBColor::Red); //
    fixTreeForNode(newNode);
}


bool RBIntTree::remove(int value)
{
    RBIntNode* foundNode = root_->searchNode(value);
    if (!foundNode)
        return false;

    RBIntNode* vnode = foundNode;
    if (foundNode->right()) {
        for (vnode = foundNode->nright(); vnode->left(); ) {
            vnode = vnode->nleft();
        }
    }
    else if (vnode->left()) {
        for (vnode = foundNode->nleft(); vnode->right(); ) {
            vnode = vnode->nright();
        }
    }
    rassert(!(vnode->left() && vnode->right()), "RBIntTree::remove - unode: more than one children");

    if (vnode == root_) {
        destroyNode( root_);
        root_ = nullptr;
        return true;
    }

    RBIntNode* unode = vnode->right() ? vnode->nright() : vnode->nleft();

    if (isRed(vnode) || isRed(unode)) {
        foundNode->setValue(vnode->data());
        vnode->substituteWith(unode);
        if (isRed(unode))
            unode->setColor(RBColor::Black);
        delete vnode;
        return true;
    }

    /// if we are here - unode && vnode are BLACK (unode CAN BE NULL !!)

    // Set VNode as DoubleBlack, Fix DoubleBlack, AFTER that substitute VNode with U-Node
    fixDoubleBlackNode(vnode);
    // now vnode DoubleBlack is fixed, we can move 'U' into 'V' and delete 'V'(which must be deleted)
    vnode->substituteWith(unode);
    delete vnode;
    return true;
}


void RBIntTree::fixDoubleBlackNode(RBIntNode* node)
{
    RBIntNode* snode = node->sibling();
    if (!snode) {
        err_exit("RBIntTree::fixDoubleBlackNode - sibling is NULL");
        return; // to appeace compiler
    }

    if (isBlack(snode)) {
        if (isBlack(snode->nleft()) && isBlack(snode->nright())) {
            snode->setColor(RBColor::Red);
            if (isRed(snode->parent())) {
                snode->parent()->setColor(RBColor::Black);
            }
            else {
                fixDoubleBlackNode(snode->parent());
            }
            return;
        }
        // if we are here - at least once sibling's child is Red
        if (snode->isRight()) {
            if (isRed(snode->nright())) {
                snode->parent()->rotateLeft();
                return;
            }
            else if (isRed(node->nleft())) {
                snode->nleft()->setColor(RBColor::Black);
                snode->setColor(RBColor::Red);
                snode->parent()->rotateLeft();
                return;
            }
        }
        else { // if snode is Left - symmetically reversed actions
            if (isRed(snode->nleft())) {
                snode->parent()->rotateRight();
                return;
            }
            else if (isRed(node->nright())) {
                snode->nright()->setColor(RBColor::Black);
                snode->setColor(RBColor::Red);
                snode->parent()->rotateRight();
                return;
            }
        }
    }
    else { // if isRed(snode)
        if (snode->isRight()) {
            snode->setColor(RBColor::Black);
            snode->parent()->setColor(RBColor::Red);
            snode->parent()->rotateLeft();
            return;
        }
        else { // if snode is Left - symmetically reversed actions
            snode->setColor(RBColor::Black);
            snode->parent()->setColor(RBColor::Red);
            snode->parent()->rotateRight();
            return;
        }
    }
}
void RBIntTree::fixTreeForNode(RBIntNode* node)
{
    rassert(isRed(node), "RBIntTree::fixTreeForNode - node is not RED");

    RBIntNode* parent = node->parent();

    if (!parent || isBlack(parent))
        return; // it's OK, no need to fix

    //// Parent is RED

    RBIntNode* gparent = parent->parent();
    if (!gparent) {
        err_exit("RBIntTree::fixTreeForNode - no grandparent(when parent is RED)");
        return; // to appeace compiler
    }

    rassert(isBlack(gparent), "RBIntTree::fixTreeForNode - no grandparent(when parent is RED)");


    //// Grandparent is BLACK

    RBIntNode* uncle
        = gparent->nleft() == parent ? gparent->nright()
        : gparent->nright() == parent ? gparent->nleft()
        : 0;

    bool gparentIsRoot = gparent == root_;
    if (isRed(uncle)) {
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
        rassert(isRed(newGParent), "RBIntTree::fixTreeForNode(LR) - newGrandparent isn't RED");
        if(gparentIsRoot) {
            root_ = newGParent;
        }
        
        node->setColor(RBColor::Black);
        gparent->setColor(RBColor::Red);
    }
    else if (gparent->right() == parent && parent->right() == node) { // RightRight case
        RBIntNode* newGParent = gparent->rotateLeft();
        rassert(isRed(newGParent), "RBIntTree::fixTreeForNode(RR) - newGrandparent isn't RED");

        if (gparentIsRoot) {
            root_ = newGParent;
        }
        newGParent->setColor(RBColor::Black);
        gparent->setColor(RBColor::Red);
    }
    else if (gparent->right() == parent && parent->left() == node) { // RightLeft case
        RBIntNode* newParent = parent->rotateRight();
        RBIntNode* newGParent = gparent->rotateLeft();
        rassert(isRed(newGParent), "RBIntTree::fixTreeForNode(RL) - nnewGrandparent isn't RED");
        if (gparentIsRoot) {
            root_ = newGParent;
        }
        node->setColor(RBColor::Black);
        gparent->setColor(RBColor::Red);
    }
}

//-------------------------------------
//--------------------- RBIntNode
//-------------------------------------

RBIntNode* RBIntNode::addNode(RBIntNode* node)
{
    int value = node->data();
    if (value <= value_) {
        if (left_) {
            return left_->addNode(node);
        }
        left_ = node;
        left_->parent_ = this;
        return left_;
    }
    else {
        if (right_) {
            return right_->addNode(node);
        }
        right_ = node;
        right_->parent_ = this;
        return right_;
    }
}

RBIntNode* RBIntNode::searchNode(int value)
{    
    return value == value_ ? this
        : left_ && value < value_ ? left_->searchNode(value)
        : right_ && value > value_ ? right_->searchNode(value)
        : nullptr;
}

void RBIntNode::substituteWith(RBIntNode* node)
{
    if (parent_) {
        if (isLeft())
            parent_->left_ = node;
        else
            parent_->right_ = node;
    }
    if (node)
        node->parent_ = parent_;

    // Clear THIS tree-related links (because it's substituted with another for now)
    left_ = nullptr;
    right_ = nullptr;
    parent_ = nullptr;
}

RBIntNode* RBIntNode::rotateLeft()
{
    rassert(right_, "RBIntNode::rotateLeft - right is NULL");


    RBIntNode* upNode = right_;
    RBIntNode* downNode = this;
    RBIntNode* upNodeOldLeft = upNode->left_;

    RBIntNode* parentNode = downNode->parent_;
    if (parentNode) {
        if (parentNode->left_ == this)
            parentNode->left_ = upNode;
        else if (parentNode->right_ == this)
            parentNode->right_ = upNode;
        else
            err_exit("RBIntNode::rotateLeft - node is not a child of parent");
    }

    
    upNode->parent_ = parentNode;
    upNode->left_ = downNode;

    downNode->parent_ = upNode;
    downNode->right_ = upNodeOldLeft;
    if (upNodeOldLeft)
        upNodeOldLeft->parent_ = downNode;

    return upNode;
}

RBIntNode* RBIntNode::rotateRight()
{
    rassert(left_, "RBIntNode::rotateRight - left is absent");

    RBIntNode* upNode = left_;
    RBIntNode* downNode = this;
    RBIntNode* upNodeOldRight = upNode->right_;

    RBIntNode* parentNode = downNode->parent_;
    if (parentNode) {
        if (parentNode->left_ == this)
            parentNode->left_ = upNode;
        else if (parentNode->right() == this)
            parentNode->right_ = upNode;
        else
            err_exit("RBIntNode::rotateRight - node is not a child of parent");
    }

    
    upNode->parent_ = parentNode;
    upNode->right_ = downNode;

    downNode->parent_ = upNode;

    downNode->left_ = upNodeOldRight;
    if (upNodeOldRight)
        upNodeOldRight->parent_ = downNode;

    return upNode;
}

//==========
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

void drawRBNodeTree(const RBIntNode* root, int slotLen)
{
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


void testRBIntTree()
{
    printf("==== testRBIntTree - start...\n");

    RBIntTree rbtree;
    rbtree.add(12);
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

    rbtree.add(17);

    
    int valToRemove = 10;
    drawRBNodeTree(rbtree.root(), 3);
    printf(" ~~~~~~~~~~~~~~~~~~~ before remove %d ~~~~~~~~~~~~~\n", valToRemove);
    rbtree.remove(valToRemove);
    drawRBNodeTree(rbtree.root(), 3);
    printf(" ~~~~~~~~~~~~~~~~~~~ after remove %d ~~~~~~~~~~~~~\n", valToRemove);

    int depth = rbtree.root()->max_deepness();
    printf(" ~~~~ testRBIntTree(depth=%d): iterateTreeNodesDF..\n", depth);
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
 