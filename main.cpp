#include "binary_tree.hpp"
#include "bdl_tree.hpp"

#include "bin_tree.hpp"

#include <vector>
#include <stdio.h>

void drawTree(const TreeNode<int>* root)
{
	printf("~~~~~~~~~~~~~~~~~\n");
	PrintBT(root);
	printf("~~~~~~~~~~~~~~~~~\n");
	DisplayBT(root, 0);
	printf("~~~~~~~~~~~~~~~~~\n");
}

void test0()
{
	printf(" ==== test0 start...\n");
	auto root = std::make_shared<TreeNode0>(10);
	//root->addData(16);
	root->addData(5);
	root->addData(7);
	root->addData(16);
	root->addData(3);
	root->addData(13);
	printf(" ~~ Depth: (calc=%d)\n", root->calculateDepth());

	//root->printNodes(); printf("\n");
	drawTree(root.get());

	printf("==== test0 done!\n");
}

void testRotate0()
{
	printf(" ==== testRotate0 start...\n");
	auto root = std::make_shared<TreeNode0>(10);
	
	root->addData(11);
	root->addData(9);
	root->addData(8);

	root->addData(7); 
	//root->printNodes(); printf("\n");
	drawTree(root.get());

	printf(" ~~ Depth: (calc=%d)\n", root->calculateDepth());

	printf(" ~~ rotateLeft(root)...\n");
	root = TreeNode0::rotateLeft(root);
	//root->printNodes(); printf("\n");
	drawTree(root.get());

	printf(" ~~ Depth: (calc=%d)\n", root->calculateDepth());

	auto llnode = root->left()->left();
	printf(" ~~ rotateLeftLeftChild(data=%d) - rotateRight...\n", llnode->data());
	bool rotatedOk = root->left()->rotateLeftChildRight();
	//root->printNodes(); printf("\n");
	drawTree(root.get());

	printf(" ~~ Depth: (calc=%d)\n", root->calculateDepth());

	printf(" ~~ rotateRight(root)...\n");
	root = TreeNode0::rotateRight(root);
	//root->printNodes(); printf("\n");
	drawTree(root.get());

	printf(" ~~ Depth: (calc=%d)\n", root->calculateDepth());

	printf("==== testRotate0 done!\n");
}

void test1()
{
	printf(" ==== test1 start...\n");

	int depth;

	auto root = std::make_shared<BdlTreeNode>(10);
	//root->addData(16);
	/*
	BdlTreeNode::addDataToDescendant(root, 5);
	BdlTreeNode::addDataToDescendant(root, 7);
	BdlTreeNode::addDataToDescendant(root, 16);
	BdlTreeNode::addDataToDescendant(root, 3);
	BdlTreeNode::addDataToDescendant(root, 13);
	*/
	
	root->addData(5);
	depth = root->depth();
	root->addData(7);
	depth = root->depth();
	root->addData(16);
	depth = root->depth();
	root->addData(3);
	depth = root->depth();
	root->addData(13);
	depth = root->depth();
	
	printf(" ~~ Depth: (calc=%d)\n", root->calculateDepth());

	//root->printNodes(); printf("\n");
	//root->printNodes1(); printf("\n");
	drawTree(root.get());
	printf("==== test1 done!\n");
}

void testAddingAVL()
{
	printf(" ==== testAddingAVL start...\n");

	std::vector<int> numbers{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };

	printf(" ~~ addData ...\n");
	{
		BdlTree avlTree;
		for (auto num : numbers)
			avlTree.addData(num);

		auto root = avlTree.root();

		//root->printNodes(); printf("\n");
		drawTree(root.get());
		printf(" ~~ Depth: %d(calc=%d)\n", root->depth(), root->calculateDepth());
	}
	printf(" ~~ addDataAVL ...\n");
	{
		BdlTree avlTree;
		
		for (auto num : numbers)
			avlTree.addDataAVL(num);

		auto root = avlTree.root();
		//root->printNodes(); printf("\n");
		drawTree(root.get());
		printf(" ~~ Depth: %d(calc=%d)\n", root->depth(), root->calculateDepth());
	}

	printf("==== testAddingAVL done!\n");
}

void testRotate1()
{
	printf(" ==== testRotate1 start...\n");
	auto root = std::make_shared<BdlTreeNode>(10);

	root->addData(11);
	root->addData(9);
	root->addData(8);
	root->addData(7);

	//BdlTreeNode::addDataToDescendant(root, 11);
	//BdlTreeNode::addDataToDescendant(root, 9);
	//BdlTreeNode::addDataToDescendant(root, 8);

	//BdlTreeNode::addDataToDescendant(root, 7);

	//root->printNodes(); printf("\n");
	drawTree(root.get());
	printf(" ~~ Depth: %d(calc=%d)\n", root->depth(), root->calculateDepth());

	printf(" ~~ rotateLeft(root)...\n");
	root = BdlTreeNode::rotateLeft(root);
	//root->printNodes1(); printf("\n"); 
	//root->printNodes(); printf("\n");
	drawTree(root.get());
	printf(" ~~ Depth: %d(calc=%d)\n", root->depth(), root->calculateDepth());

	auto lnode = root->sleft()->sleft();
	printf(" ~~ LeftLeftChild(data=%d) rotateRight...\n", lnode->data());
	
	auto nnode = BdlTreeNode::rotateRight(lnode);
	//root->printNodes1(); printf("\n");
	//root->printNodes(); printf("\n");
	drawTree(root.get());
	printf(" ~~ Depth: %d(calc=%d)\n", root->depth(), root->calculateDepth());

	printf(" ~~ rotateRight(root)...\n");
	root = BdlTreeNode::rotateRight(root);
	//root->printNodes(); printf("\n");
	drawTree(root.get());
	printf(" ~~ Depth: %d(calc=%d)\n", root->depth(), root->calculateDepth());

	printf("==== testRotate1 done!\n");
}


int main()
{
	printf("-- BinaryTree Test program...\n");
	test0();
	testRotate0();

	test1();
	testRotate1();

	testAddingAVL();

	//my_draw0();
	//my_draw1();

	
	printf("-- Completed!\n");
	return 0;
}