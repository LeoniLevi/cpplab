#include "binary_tree.hpp"
#include "bdl_tree.hpp"
#include "avl_tree.hpp"

#include "_bst_node.hpp"
#include "_bin_tree.hpp"
#include "_my_bin_tree.hpp"

#include <vector>
#include <stdio.h>

void drawTree(const TreeNode<int>* root)
{
	//printf("~~~~~~~~~~~~~~~~~\n");
	//PrintBT(root);
	printf("~~~~~~~~~~~~~~~~~\n");
	DisplayBT(root, 0);
	//drawNodeTree(root, 2);
	printf("~~~~~~~~~~~~~~~~~\n");
}

std::vector<int> get_random_arr(int arr_len, int max_val)
{
	std::vector<int> numbers;
	int maxNum = max_val;
	unsigned  nseed = (unsigned)time(NULL);
	srand(nseed);
	for (int i = 0; i < arr_len; ++i) {
		int num = rand() % maxNum;
		while (std::find(numbers.begin(), numbers.end(), num) != numbers.end()) {
			num = rand() % maxNum;
		}
		numbers.push_back(num);
	}
	return numbers;
}

void testSimpleAdding()
{
	printf(" ==== testSimpleAdding start...\n");
	auto root = std::make_shared<BinaryTree>(10);
	//root->addData(16);
	root->addData(5);
	root->addData(7);
	root->addData(16);
	root->addData(3);
	root->addData(13);
	printf(" ~~ Depth: (calc=%d)\n", root->calculateDepth());

	//root->printNodes(); printf("\n");
	drawTree(root.get());

	{
		printf(" ~~ MyBinTree experiment start...\n");
		MyBinTree mbt(root.get());
		mbt.Dump();

		printf(" ~~ MyBinTree experiment done.\n");
	}

	//drawNodeTree(root.get(), 2);

	printf("==== testSimpleAdding done!\n");
}

void testRotating()
{
	printf(" ==== testRotating start...\n");
	auto root = std::make_shared<BinaryTree>(10);
	
	root->addData(11);
	root->addData(9);
	root->addData(8);

	root->addData(7); 
	//root->printNodes(); printf("\n");
	drawTree(root.get());

	printf(" ~~ Depth: (calc=%d)\n", root->calculateDepth());

	printf(" ~~ rotateLeft(root)...\n");
	root = BinaryTree::rotateLeft(root);
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
	root = BinaryTree::rotateRight(root);
	//root->printNodes(); printf("\n");
	drawTree(root.get());

	printf(" ~~ Depth: (calc=%d)\n", root->calculateDepth());

	printf("==== testRotate0 done!\n");
}

void testNewAvlTree()
{
	printf(" ==== testNewAvlTree start...\n");
	//std::vector<int> numbers{ 0, 2, 8, 1, 6, 4,  };
	//std::vector<int> numbers{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
	//std::vector<int> numbers{ 0, 1, 2,  4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
	std::vector<int> numbers = get_random_arr(24, 99);


	printf(" ~~ addDataAVL ...\n");
	{
		AvlTree<int> avlTree(3);
		int numItems = 14;
		for (int i = 0; i < numItems; ++i) {
			avlTree.addValue(numbers[i]);
			
			//printf("!!=== Added N=%d:\n", numbers[i]);
			//drawNodeTree(avlTree.root(), 2);
			//printf("\n");
			bool bres = avlTree.root()->check_depths();
			assert(bres);			
		}
		drawNodeTree(avlTree.root(), 2);
		printf(" !! Adding completed(NumItems=%d)\n", (int)numbers.size());
	}
	printf("==== testNewAvlTree done!\n");
}



void testAddingAVL()
{
	printf(" ==== testAddingAVL start...\n");

	//std::vector<int> numbers{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
	//std::vector<int> numbers{ 0, 92, 1, 3, 4, 5, 6, 7, 9, 10, 11, 12, 13, 14 };
	//std::vector<int> numbers{0, 2, 1, 2, 3, 4, 4};
	//std::vector<int> numbers{ 2, 4, 1, 7, 0, 5, 6 };
	//std::vector<int> numbers{ 2, 4, 1, 7, 0, 5, 6};
	
	std::vector<int> numbers = get_random_arr(24, 99);

	printf(" ~~ addDataAVL ...\n");
	{
		BdlTree avlTree;
		
		for (int i = 0; i < numbers.size(); ++i) {
			avlTree.addDataAVL(numbers[i]);
			/*
			printf("!!=== Added N=%d:\n", numbers[i]);
			drawNodeTree(avlTree.root().get(), 2);
			printf("\n");
			*/
		}
		printf(" !! Adding completed(NumItems=%d)\n", (int)numbers.size());

		auto root = avlTree.root();
		//root->printNodes(); printf("\n");
		drawTree(root.get());
		printf(" ~~ Depth: %d(calc=%d)\n", root->depth(), root->calculateDepth());
		drawNodeTree(root.get(), 2);

		{
			printf(" ~~ MyBinTree experiment start...\n");
			MyBinTree mbt(root.get());
			mbt.Dump();

			printf(" ~~ MyBinTree experiment done.\n");
		}

		printf(" ~~ Iterate nodes(Depth-First): \n");
		iterateTreeNodesDF<int>(root.get(), [](auto& nd) { printf("%d, ", nd.data()); });
		printf("\n");
		printf(" ~~ Iterate nodes(Breadth-First): \n");
		iterateTreeNodesBF<int>(root.get(), [](auto& nd) { printf("%d, ", nd.data()); });
		printf("\n");
	}	

	printf("==== testAddingAVL done!\n");
}

int main()
{
	printf("-- BinaryTree Test program...\n");

	testNewAvlTree();
	//return 0;


	testSimpleAdding();
	testRotating();

	test_bst_tree();
	test_bin_tree();

	testAddingAVL();
	
	printf("-- Completed!\n");
	return 0;
}