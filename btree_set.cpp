// Implementation of a set using a binary tree.
// 
// The set uses a binary tree with TREE_LEVELS levels, so it can store
// numbers from 0 to M (where M = 2**TREE_LEVELS - 1).
//
// Supports three operations:
// 1. add_value(v): O(log M)
//   Adds a value to the set.
//   Has no effect if v is already in the set.
// 2. remove_value(v): O(log M)
//   Removes a value from the set.
//   Has no effect if v is not in the set.
// 3. has_value(v): O(log M)
//   Returns true iff v is in the set.
//
// Space: approximately O(N), where N is the number of elements in the set
// (just needs O(log M) of overhead for the first few elements)

#include <iostream>

using namespace std;

const int TREE_LEVELS = 30;
typedef struct node node;

struct node
{
	node* child[2] = {NULL, NULL};

	void add_value(int value, int level = TREE_LEVELS)
	{
		if(level == 0)
			return;

		int branch = (value >> (level-1)) & 0x01;

		if(!child[branch])
			child[branch] = new node();

		child[branch]->add_value(value, level-1);
	}

	void remove_value(int value, int level = TREE_LEVELS)
	{
		if(level == 0)
			return;
		
		int branch = (value >> (level-1)) & 0x01;

		if(child[branch])
		{
			child[branch]->remove_value(value, level-1);
			delete child[branch];
			child[branch] = NULL;
		}
	}

	int has_value(int value, int level = TREE_LEVELS)
	{
		if(level == 0)
			return true;

		int branch = (value >> (level-1)) & 0x01;

		if(!child[branch])
			return false;

		return child[branch]->has_value(value, level-1);
	}
};

int main(void)
{
	node root;

	root.add_value(0);
	cout << root.has_value(1) << endl;

	root.add_value(1);
	cout << root.has_value(1) << endl;

	root.remove_value(1);
	cout << root.has_value(1) << endl;

	root.remove_value(1);
	cout << root.has_value(1) << endl;

	return 0;
}
