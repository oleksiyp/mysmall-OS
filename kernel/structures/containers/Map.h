#include <structures/trees/RedNBlackTree.h>

namespace structures
{
	namespace containers
	{
		using namespace structures::trees;

		template <class Key, class Value, class Comparator = algorithms::utility::operators::Less<Key> >
		class Map
		{
			typedef struct
			{
				Key key;
				Value value;
				RNBTreeData data;
			} Node;

			class KeyComparator
			{
			public:
				Comparator cmp;
				KeyComparator() { }
				int operator ()(const Node &a, const Node &b)
				{
					return cmp(a.key, b.key);
				}
			};
			

			RedNBlackTree<Node, KeyComparator> tree;
			Node temp;

			class KeySearcher
			{
				Comparator cmp;
				const Key *key;
			public:
				KeySearcher(const Key *key)
				{
					this->key = key;
				}
				int operator ()(const Node &n)
				{
					if (cmp(n.key, *key))
						return -1;
					if (cmp(*key, n.key))
						return 1;
					return 0;
				}
			};
			Value nullValue;
		public:
			Map()
				: tree(STRUCT_OFFSET(temp, data)), nullValue()
			{

			}

			~Map()
			{
				clear();
			}

			void clear()
			{
		//		tree.traverse(tree.getRoot(), removeNodes);
		//		tree.clear();
			}


			void insert(const Key &k, const Value &v)
			{
				Node *node = tree.search(tree.getRoot(), KeySearcher(k));
				if (node)
				{
					node->value = v;
				} else {
					Node *node = new Node;
					node->key = k;
					node->value = v;
					tree.insert(node);
				}
			}

			void remove(const Key &k)
			{
				Node *node = tree.search(tree.getRoot(), KeySearcher(&k));
				if (node)
				{
					tree.remove(node);
				}
			}

			Value get(const Key &k)
			{
				Node *node = tree.search(tree.getRoot(), KeySearcher(&k));
				if (node)
				{
					return node->value;
				}
				return Value();
			}

			const Value &operator [](const Key &k) const
			{
				Node *node = tree.search(tree.getRoot(), KeySearcher(&k));
				if (node)
				{
					return node->value;
				}
				return Value();
			}
			Value &operator [](const Key &k)
			{
				Node *node = tree.search(tree.getRoot(), KeySearcher(&k));
				if (node)
				{
					return node->value;
				}
				node = new Node;
				node->key = k;
				tree.insert(node);
				return node->value;
			}

			bool contains(const Key &k)
			{
				Node *node = tree.search(tree.getRoot(), KeySearcher(&k));
				return node != 0;
			}

			dword size()
			{
				return tree.size();
			}
		};
	}
}