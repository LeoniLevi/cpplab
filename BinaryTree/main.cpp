#include "avl/bdl_tree.hpp"
#include "avl/avl_tree.hpp"
#include "red-black/rbint_tree.hpp"
#include "red-black/rbq_int_tree.hpp"

//#define TEST_LEGACY_TREES
#ifdef TEST_LEGACY_TREES
#include "binary_tree.hpp"
#include "legacy/_bst_node.hpp"
#include "legacy/_bin_tree.hpp"
#endif


#include <vector>
#include <stdio.h>

int main()
{
	printf("-- BinaryTree Test program...\n");

#ifdef TEST_LEGACY_TREES

	testBinaryTreeAdding();
	testBinaryTreeRotating();

	test_bst_tree();
	test_bin_tree();
#endif

	//testAvlTree();
	//return 0;

	testRBIntTree();
	return 0;

	testRBQIntTree();
	//return 0;

	testAvlTree();
	//return 0;


	testBdlTree();
	
	printf("-- Completed!\n");
	return 0;
}
