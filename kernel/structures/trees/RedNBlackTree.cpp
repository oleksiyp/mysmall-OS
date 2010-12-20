#include <xp/testing.h>
#include <structures/trees/RedNBlackTree.h>

#ifdef TESTING

#pragma warning (disable : 4786)
#include <stdio.h>
namespace tests
{
	using namespace structures::trees;
	
	class MyNode {
	public:
		int key;
		RNBTreeData treeData;
		int data;
	};

	bool operator <(const MyNode &a, const MyNode &b)
	{
		return a.key < b.key;
	}

	class KeySearcher
	{
		int key;
	public:
		KeySearcher(int key)
		{
			this->key = key;
		}
		int operator ()(const MyNode &n)
		{
			if (n.key > key)
				return 1;
			if (n.key < key)
				return -1;
			return 0;
		}
	};

	class MyCounter
	{
		int lastkey;
	public:
		dword cnt;
		bool fail;
		MyCounter()
		{
			lastkey = -10000000;
			cnt = 0;
			fail = false;
		}
		void operator () (const MyNode &node)
		{
			if (node.key < lastkey)
				fail = true;
			lastkey = node.key;
			cnt++;
		}
	};

	class MyFreeNodes
	{
	public:
		void operator ()(MyNode &node)
		{
			delete &node;
		}
	};


	class RBTreeTU : public TestUnit
	{
	public:
		RBTreeTU()
			: TestUnit("Red&Black tree test unit")
		{
		}


		virtual void test()
		{
			MyNode node;
			RedNBlackTree<MyNode>	tree(STRUCT_OFFSET(node, treeData));

			for (int i = 0; i < 50; i++)
			{
				MyNode *node = new MyNode;
				node->key = (i * 66666) % 2341;
				node->data = i * i;
				tree.insert(node);
				assert(tree.checkIntegrity(), "tree integrity");
			}	

			MyNode *xx = tree.search(tree.getRoot(),
				KeySearcher((22 * 66666) % 2341));
			
			assert(xx->data == 22 * 22, "Failed to find node");

			MyCounter counter;
			tree.traverse(tree.getRoot(), counter);

			assert(!counter.fail, "Bad tree order");
			assert(counter.cnt == tree.nodes(tree.getRoot()), "Traversing not all nodes");

			{
				for (int i = 0; i < 10; i++)
				{
					MyNode *n = tree.getRoot();
					for (int j = 0; j < i; j++)
						n = tree.successor(n);
					if (n)
						tree.remove(n);
					assert(tree.checkIntegrity(), "tree integrity");
				}
			}

			while (tree.getRoot())
			{
				MyNode *n = tree.getRoot();
				tree.remove(n);
				delete n;
			}
			assert(tree.checkIntegrity(), "tree integrity");
			assert(tree.nodes(tree.getRoot()) == 0, "Not all nodes removed");
		}
	};
	static RegisterTestUnit unit(new RBTreeTU());
}

#endif