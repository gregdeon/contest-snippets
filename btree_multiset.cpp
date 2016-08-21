// Implementation of a multiset using a binary tree.
// 
// The multiset uses a binary tree with TREE_LEVELS levels, so it can store
// numbers from 0 to M (where M = 2**TREE_LEVELS - 1).
//
// Operations on the multiset:
// 1. add_value(v): O(log M)
//   Adds a value to the multiset.
// 2. remove_value(v): O(log M)
//   Removes a value from the multiset.
//   Has no effect if v is not in the multiset.
// 3. has_value(v): O(log M)
//   Returns the number of elements with the value v in the multiset.
//   Returns 0 if v is not in the multiset.
//
// Space: O(N), where N is the number of elements in the set

#include <iostream>

using namespace std;

const int TREE_LEVELS = 30;
typedef struct node node;

struct node
{
	node* child[2] = {NULL, NULL};
	int count = 0;

	void add_value(int value, int level = TREE_LEVELS)
	{
		count++; 

		if(level == 0)
			return;

		int branch = (value >> (level-1)) & 0x01;

		if(!child[branch])
			child[branch] = new node();

		child[branch]->add_value(value, level-1);
	}

	void remove_value(int value, int level = TREE_LEVELS)
	{
		count--;

		if(level == 0)
			return;
		
		int branch = (value >> (level-1)) & 0x01;

		if(child[branch])
		{
			child[branch]->remove_value(value, level-1);
			if(child[branch]->count == 0)
			{
				delete child[branch];
				child[branch] = NULL;
			}
		}
	}

	int has_value(int value, int level = TREE_LEVELS)
	{
		if(level == 0)
			return count;

		int branch = (value >> (level-1)) & 0x01;

		if(!child[branch])
			return 0;

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

	root.add_value(1);
	cout << root.has_value(1) << endl;

	root.remove_value(1);
	cout << root.has_value(1) << endl;

	return 0;
}
