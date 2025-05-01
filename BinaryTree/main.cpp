#include "binary_tree.hpp"
#include "avl/bdl_tree.hpp"
#include "avl/avl_tree.hpp"
#include "red-black/rbint_tree.hpp"
#include "red-black/rbq_int_tree.hpp"

//#define TEST_LEGACY_TREES
#ifdef TEST_LEGACY_TREES
#include "legacy/_my_bin_tree.hpp"
#include "legacy/_bst_node.hpp"
#include "legacy/_bin_tree.hpp"
#endif


#include <vector>
#include <stdio.h>

void testBinaryTreeAdding();
void testBinaryTreeRotating();

void testRBQIntTree();
void testRBIntTree();
void testAvlTree();
void testBdlTree();

int main()
{
	printf("-- BinaryTree Test program...\n");

#ifdef TEST_LEGACY_TREES

	testBinaryTreeAdding();
	testBinaryTreeRotating();

	test_bst_tree();
	test_bin_tree();
#endif

	testAvlTree();
	return 0;

	testRBQIntTree();
	//return 0;
	testRBIntTree();

	testAvlTree();
	//return 0;


	testBdlTree();
	
	printf("-- Completed!\n");
	return 0;
}

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

void drawRbqTreeAsList(RBQIntTree& rbtree)
{
	printf("[");
	iterateTreeNodesDF<int>(rbtree.root(), [](const TreeNode<int>& n) {
		auto rbn = (const RBIntNode&)n;
		char cc = rbn.color() == RBColor::Black ? 'B' : rbn.color() == RBColor::Red ? 'R' : '?';
		printf(" %d(%c)", rbn.data(), cc);
	});
	printf(" ]\n");
}

void testRBQIntTree()
{
	printf("==== testRBQIntTree - start...\n");
#undef CHECK_MONOTONE_ADDING
#ifdef CHECK_MONOTONE_ADDING	
	
	int addCount = 17;
	int step = -1;

	int startValue = step > 0 ? 1 : addCount + 1 ;

	RBQIntTree rbtree(startValue);
	for (int i = 0; i < addCount; ++i) {
		int num = startValue + step + step * i;
		rbtree.add(num);

		//drawNodeTree<int>(rbtree.root(), 3);
		//drawRbqTreeAsList(rbtree);
	}
#else
	
	RBQIntTree rbtree(12);
	rbtree.add(15);
	rbtree.add(18);

	rbtree.add(10);
	rbtree.add(22);
	rbtree.add(6);
	rbtree.add(9);
	rbtree.add(13);
	rbtree.add(7);
	rbtree.add(2);
	rbtree.add(1);
#endif
	int depth = rbtree.root()->max_deepness();
	printf(" ~~~~ testRBQIntTree(depth=%d)\n", depth);
	drawNodeTree<int>(rbtree.root(), 3);
	drawRbqTreeAsList(rbtree);
	/*
	iterateTreeNodesDF<int>(rbtree.root(), [](const TreeNode<int>& n) {
		auto rbn = (const RBIntNode&)n;
		char cc = rbn.color() == RBColor::Black ? 'B' : rbn.color() == RBColor::Red ? 'R' : '?';
		printf("%d(%c),", rbn.data(), cc);
	});
	*/
	printf("====  testRBQIntTree - Done!\n");

}

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

void testAvlTree()
{
	printf(" ==== testAvlTree start...\n");
	//std::vector<int> numbers{ 1, 2, 3 };
	//std::vector<int> numbers{ 0, 2, 8, 1, 6, 4,  };
	std::vector<int> numbers{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
	//std::vector<int> numbers{ 0, 1, 2,  4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
	//std::vector<int> numbers = get_random_arr(24, 99);
	int val0 = 6;
	int val1 = 43;

	printf(" ~~ addDataAVL ...\n");
	{
		AvlTree<int> avlTree;
		int numItems = numbers.size() > 19 ? 19 : numbers.size();
		for (int i = 0; i < numItems; ++i) {
			//avlTree.addValue(numbers[i]);
			avlTree.addValue(numbers[i]);
			
			//printf("!!=== Added N=%d:\n", numbers[i]);
			//drawNodeTree(avlTree.root(), 2);
			//printf("\n");
			bool bres = avlTree.root()->is_avl_valid();
			assert(bres);			
		}
		std::string stree = treeNodeToString(avlTree.root());
		printf(" ~~ STree: %s\n", stree.c_str());


		avlTree.deleteNodeByValue(9);
		stree = treeNodeToString(avlTree.root());
		printf(" ~~ STree after del: %s\n", stree.c_str());



		drawNodeTree(avlTree.root(), 2);
		printf(" !! Adding completed(NumItems=%d)\n", numItems);

		auto node0 = avlTree.search(val0);
		auto node1 = avlTree.search(val1);
		if (node0)
			assert(node0->data() == val0);
		if (node1)
			assert(node1->data() == val1);
	}

	



	printf("==== testAvlTree done!\n");
}



void testBdlTree()
{
	printf(" ==== testBdlTree start...\n");

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

		printf(" ~~ Iterate nodes(Depth-First): \n");
		iterateTreeNodesDF<int>(root.get(), [](auto& nd) { printf("%d, ", nd.data()); });
		printf("\n");
		printf(" ~~ Iterate nodes(Breadth-First): \n");
		iterateTreeNodesBF<int>(root.get(), [](auto& nd) { printf("%d, ", nd.data()); });
		printf("\n");
	}	

	printf("==== testBdlTree done!\n");
}

#ifdef TEST_LEGACY_TREES

void testBinaryTreeAdding()
{
	printf(" ==== testBinaryTreeAdding start...\n");
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

	printf("==== testBinaryTreeAdding done!\n");
}

void testBinaryTreeRotating()
{
	printf(" ==== testBinaryTreeRotating start...\n");
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

	printf("==== testBinaryTreeRotating done!\n");
}

#endif