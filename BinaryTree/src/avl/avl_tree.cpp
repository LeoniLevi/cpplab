#include "avl_tree.hpp"
#include "util.h"

//AvlTree<int> ggNode(123);

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