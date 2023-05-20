#include "bdl_tree.hpp"

#include <assert.h>

void BdlTreeNode::addData(int data)
{
    auto newNode = std::make_shared<BdlTreeNode>(data);
    addNode(newNode);
}

void BdlTreeNode::addDataAVL(int data)
{
    auto newNode = std::make_shared<BdlTreeNode>(data);
    addNodeAVL(newNode);
}

void BdlTreeNode::updateDepthByChildren()
{
    unsigned ld = left_ ? left_->depth() : 0;
    unsigned rd = right_ ? right_->depth() : 0;

    depth_ = (ld > rd ? ld : rd) + 1;
}

void BdlTreeNode::updateDepthsRecursivelyUpToRoot()
{
    updateDepthByChildren();

    // call parent->updateDepthsRecursivelyUpToRoot()
#ifdef USE_BDL_WEAK_PTR
    auto parent = parent_.lock();
    if (parent)
        parent->updateDepthsRecursivelyUpToRoot();
#else
    if (parent_)
        parent_->updateDepthsRecursivelyUpToRoot();
#endif
}

int BdlTreeNode::getLeftMinusRightDepth() const
{
    int ld = left_ ? left_->depth() : 0;
    int rd = right_ ? right_->depth() : 0;
    return ld - rd;
}
DepthBalanceStatus BdlTreeNode::getDepthBalanceStatus() const
{
    int ld = left_ ? left_->depth() : 0;
    int lld = left_ ? (left_->left_ ? left_->left_->depth() : 0) : 0;
    int lrd = left_ ? (left_->right_ ? left_->right_->depth() : 0) : 0;

    int rd = right_ ? right_->depth() : 0;
    int rld = right_ ? (right_->left_ ? right_->left_->depth() : 0) : 0;
    int rrd = right_ ? (right_->right_ ? right_->right_->depth() : 0) : 0;

    if (ld - rd > 1) {
        if (lrd > lld)
            return DepthBalanceStatus::LeftRight;
        return DepthBalanceStatus::LeftLeft;
    }
    if (rd - ld > 1) {
        if (rld > rrd)
            return DepthBalanceStatus::RightLeft;
        return DepthBalanceStatus::RightRight;
    }
    return DepthBalanceStatus::Ok;
}


void BdlTreeNode::makeMeParentOf(std::shared_ptr<BdlTreeNode> node)
{
#ifdef USE_BDL_WEAK_PTR
    auto sft = shared_from_this();
    node->parent_ = sft;
#else
    node->parent_ = this;
#endif
}

// static
std::shared_ptr<BdlTreeNode> BdlTreeNode::ProvideNodeBalance(std::shared_ptr<BdlTreeNode> node)
{
    std::shared_ptr<BdlTreeNode> upChild;
    auto status = node->getDepthBalanceStatus();
    if (status == DepthBalanceStatus::Ok)
        return node;

    if (status == DepthBalanceStatus::LeftLeft) {
        upChild = BdlTreeNode::rotateRight(node);
    }
    else if (status == DepthBalanceStatus::LeftRight) {
        BdlTreeNode::rotateLeft(node->sleft());
        upChild = BdlTreeNode::rotateRight(node);
    }
    else if (status == DepthBalanceStatus::RightRight) {
        upChild = BdlTreeNode::rotateLeft(node);
    }
    else if (status == DepthBalanceStatus::RightLeft) {
        BdlTreeNode::rotateRight(node->sright());
        upChild = BdlTreeNode::rotateLeft(node);
    }
    return upChild;
}

void BdlTreeNode::addNodeAVL(std::shared_ptr<BdlTreeNode> node)
{    
    auto& workChild = node->data_ <= data_ ? left_ : right_;
    //auto& 
    if (workChild) {
        workChild->addNodeAVL(node);
    }
    else {
        workChild = node;
        if (node->data_ <= data_)
            left_ = workChild;
        else 
            right_ = workChild;

        // set workChild parent into this
        makeMeParentOf(workChild);
    }
    updateDepthByChildren();

    BdlTreeNode::ProvideNodeBalance(workChild);

}


void BdlTreeNode::addNode(std::shared_ptr<BdlTreeNode> node)
{
    auto& workChild = node->data_ <= data_ ? left_ : right_;
    if (workChild) {
        workChild->addNode(node);
    }
    else {       
        workChild = node;

        // set workChild parent into this
        makeMeParentOf(workChild);
    }
    updateDepthByChildren();

}

bool BdlTreeNode::isLeaf() const
{
    return !left_ && !right_;
}

// static
std::shared_ptr<BdlTreeNode> BdlTreeNode::rotateRight(std::shared_ptr<BdlTreeNode> node)
{
    auto parent = node->parent_;

    auto upNode = node->left_;
    auto downNode = node;

    auto newDownNodeLeft = upNode->right_;
    upNode->right_ = downNode;
    downNode->left_ = newDownNodeLeft;
    if (newDownNodeLeft)
        downNode->makeMeParentOf(newDownNodeLeft);

#ifdef USE_BDL_WEAK_PTR    
    if (!parent.expired()) {
        //parent.lock()->left_ = upNode;
        auto sparent = parent.lock();
        if (sparent) {
            bool isLeftOfParent = node == sparent->left_;
            assert(isLeftOfParent || node == sparent->right_);
            if (isLeftOfParent)
                sparent->left_ = upNode;
            else
                sparent->right_ = upNode;
        }
    }
    downNode->parent_ = upNode;
#else
    if (parent) {
        //parent->left_ = upNode;
        bool isLeftOfParent = node == parent->left_;
        assert(isLeftOfParent || node == parent->right_);
        if (isLeftOfParent)
            parent->left_ = upNode;
        else
            parent->right_ = upNode;
    }
    downNode->parent_ = upNode.get();
#endif
    upNode->parent_ = parent;

    downNode->updateDepthByChildren();
    upNode->updateDepthsRecursivelyUpToRoot();

    return upNode;
}

std::shared_ptr<BdlTreeNode> BdlTreeNode::rotateLeft(std::shared_ptr<BdlTreeNode> node)
{
    auto parent = node->parent_;
    auto upNode = node->right_;
    auto downNode = node;

    auto newDownNodeRight = upNode->left_;
    upNode->left_ = downNode;
    downNode->right_ = newDownNodeRight;
    if (newDownNodeRight)
        downNode->makeMeParentOf(newDownNodeRight);

#ifdef USE_BDL_WEAK_PTR
    if (!parent.expired()) {
        //parent.lock()->right_ = upNode;
        auto sparent = parent.lock();
        if (sparent) {
            bool isLeftOfParent = node == sparent->left_;
            assert(isLeftOfParent || node == sparent->right_);
            if (isLeftOfParent)
                sparent->left_ = upNode;
            else
                sparent->right_ = upNode;
        }
    }
    downNode->parent_ = upNode;
#else
    if (parent) {
        //parent->right_ = upNode;
        bool isLeftOfParent = node == parent->left_;
        assert(isLeftOfParent || node == parent->right_);
        if (isLeftOfParent)
            parent->left_ = upNode;
        else
            parent->right_ = upNode;
    }
    downNode->parent_ = upNode.get();
#endif
    upNode->parent_ = parent;

    downNode->updateDepthByChildren();
    upNode->updateDepthsRecursivelyUpToRoot();    

    return upNode;
}

int BdlTreeNode::calculateDepth() const
{
    if (isLeaf())
        return 1;

    int ld = left_ ? left_->calculateDepth() : 0;
    int rd = right_ ? right_->calculateDepth() : 0;
    int dd = ld < rd ? rd : ld;
    return dd + 1;
}

void BdlTreeNode::iterateNodes(std::function<void(const BdlTreeNode&)> fn) const
{
    if (left_)
        left_->iterateNodes(fn);
    fn(*this);
    if (right_)
        right_->iterateNodes(fn);
}

void BdlTreeNode::printNodes() const
{
    printf("(");
    if (left_)
        left_->printNodes();
    printf(" %d ", data_);
    if (right_)
        right_->printNodes();
    printf(")");
}

void BdlTreeNode::printNodes1() const
{
    printf("(");
    if (left_) {
        if (left_->isLeaf())
            printf(" %d ", left_->data());
        else
            left_->printNodes1();
    }
    else {
        printf(" _ ");
    }
    printf(" %d ", data_);
    if (right_) {
        if (right_->isLeaf())
            printf(" %d ", right_->data());
        else
            right_->printNodes1();
    }
    else {
        printf(" _ ");
    }
    printf(")");
}