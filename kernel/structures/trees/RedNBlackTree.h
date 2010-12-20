#ifndef _REDNBLACKTREE_H_
#define _REDNBLACKTREE_H_

#include <config.h>

#include <algorithms/utility/operators.h>
#include <basic/types.h>

#define STRUCT_OFFSET(s, m) ((char *)&((s).m) - (char *)&(s))

namespace structures
{
	namespace trees
	{

		typedef struct _RNBTreeData
		{
			struct _RNBTreeData *parent, *left, *right;
			enum {black, red} color;
			dword size;
			
			void initialize()
			{
				color = red;
				parent = left = right = 0;
				size = 0;
			}

			bool isBlack()
			{
				if (this == 0)
					return true;
				return color == black;
			}
			bool isRed()
			{
				if (this == 0)
					return false;
				return color == red;
			}
		} RNBTreeData;

		template <class Node, class Comparator = algorithms::utility::operators::Less<Node> >
			class RedNBlackTree
		{
			typedef RNBTreeData TreeData;
			
			TreeData *root;
			int treeDataOffset;
			Comparator comparator;
			
			TreeData *getTreeData(Node *node) const
			{
				if (node == 0)
					return 0;
				return (TreeData*)((byte *)node + treeDataOffset);
			}
			
			Node *getNode(TreeData *treeData) const
			{
				if (treeData == 0)
					return 0;
				return (Node*)((byte *)treeData - treeDataOffset);
			}

			void rightRotate(TreeData *x)
			{
				TreeData *y = x->left;
				if (!y)
					return;

				x->left = y->right;

				if (y->right)
					y->right->parent = x;
				y->parent = x->parent;
				if (x->parent == 0)
					root = y;
				else
					if (x == x->parent->right)
						x->parent->right = y;
					else
						x->parent->left = y;
				y->right = x;
				x->parent = y;

				x->size = (x->left ? x->left->size : 0)
					+ (x->right ? x->right->size : 0) + 1;
				y->size = (y->left ? y->left->size : 0)
					+ (y->right ? y->right->size : 0) + 1;
			}

			void leftRotate(TreeData *x)
			{
				TreeData *y = x->right;
				if (!y)
					return;

				x->right = y->left;

				if (y->left)
					y->left->parent = x;
				y->parent = x->parent;
				

				if (x->parent == 0)
					root = y;
				else
					if (x == x->parent->left)
						x->parent->left = y;
					else
						x->parent->right = y;
				y->left = x;
				x->parent = y;

				x->size = (x->left ? x->left->size : 0)
					+ (x->right ? x->right->size : 0) + 1;
				y->size = (y->left ? y->left->size : 0)
					+ (y->right ? y->right->size : 0) + 1;
			}

			bool checkLinks(TreeData *node) const
			{
				if (!node)
					return true;

				if (node->isRed())
				{
					if (node->left && node->left->isRed())
						return false;
					if (node->right && node->right->isRed())
						return false;
				}

				if (node->left && node->left->parent != node) return false;
				if (node->right && node->right->parent != node) return false;
				if (!checkLinks(node->left)) return false;
				if (!checkLinks(node->right)) return false;
				return true;
			}

			void height(TreeData *node, dword currentHeight, dword &maxHeight) const
			{
				if (!node)
					return;

				if (maxHeight < currentHeight)
					maxHeight = currentHeight;
				height(node->left, currentHeight + 1, maxHeight);
				height(node->right, currentHeight + 1, maxHeight);
			}

			bool checkBlackHeight(TreeData *node, int currentHeight, int &blackHeight) const
			{
				if (!node)
				{
					if (blackHeight == -1)
						blackHeight = currentHeight;
					else
						if (blackHeight != currentHeight)
							return false;
					return true;
				}

				if (!checkBlackHeight(node->left, currentHeight + (node->isBlack()), blackHeight))
					return false;
				if (!checkBlackHeight(node->right, currentHeight + (node->isBlack()), blackHeight))
					return false;
				return true;
			}


			dword checkSize(Node *node, bool &fail)
			{
				if (node == 0)
					return 0;
				dword count = checkSize(nodeLeft(node), fail)
					+ checkSize(nodeRight(node), fail) + 1;
				if (count != getTreeData(node)->size)
					fail = true;
				return count;
			}



		public:	
			/*
			 * Initializes tree.
			 *   treeDataOffset - offset of tree data in node.
			 */
			RedNBlackTree(int treeDataOffset)
			{
				this->treeDataOffset = treeDataOffset;
				root = 0;
			}

			~RedNBlackTree()
			{
				clear();
			}
			
			/*
			 * Adds node to R&B tree.
			 * Saves tree properties.
			 */
			void insert(Node *node)
			{
				TreeData *z = getTreeData(node);
				z->initialize();

				TreeData *y = 0, *x = root;
				// drill down until find suitable place.
				while (x != 0)
				{
					y = x;
					if (comparator(*getNode(z), *getNode(x)))
						x = x->left;
					else
						x = x->right;
				}
				
				// add to tree.
				z->parent = y;
				if (y == 0)
					root = z;
				else if (comparator(*getNode(z), *getNode(y)))
					y->left = z;
				else
					y->right = z;

				x = z;
				while (x)
				{
					x->size++;
					x = x->parent;
				}

				// rebalance tree
				x = z;
				while(x != root && x->parent->isRed())
				{
					if (x->parent == x->parent->parent->left)
					{
						//      1.    2.
						// 
						//      B      B
						//     / \    / \
						//    A   y  A   y
						//   /        \
						//  x          x
						//
						y = x->parent->parent->right;
						if (y && y->isRed())
						{
							x->parent->color = TreeData::black; // color[A] = TreeData::black
							y->color = TreeData::black;         // color[y] = TreeData::black
							x->parent->parent->color = TreeData::red; // color[B] = TreeData::red
							x = x->parent->parent;          // move to B
						} else {
							if (x == x->parent->right) // (2)
							{
								x = x->parent; // move to A
								leftRotate(x);
							}
							x->parent->color = TreeData::black;
							x->parent->parent->color = TreeData::red;
							rightRotate(x->parent->parent);
						}
					} else { // symetric case
						y = x->parent->parent->left;
						if (y && y->isRed())
						{
							x->parent->color = TreeData::black;
							y->color = TreeData::black;
							x->parent->parent->color = TreeData::red;
							x = x->parent->parent;
						} else {
							if (x == x->parent->left)
							{
								x = x->parent;
								rightRotate(x);
							}
							x->parent->color = TreeData::black;
							x->parent->parent->color = TreeData::red;
							leftRotate(x->parent->parent);
						}
					}
				}
				root->color = TreeData::black;
			}
			

			/*
			 * Returns tree size.
			 */
			dword size()
			{
				if (root == 0)
					return 0;
				return root->size;
			}

			/*
			 * Removes node from R&B tree.
			 * Saves tree properties.
			 */
			void remove(Node *node)
			{
				TreeData *z = getTreeData(node), *y, *x;

				// find node to remove
				if (z->left == 0 || z->right == 0)
					y = z;
				else
					y = getTreeData(successor(getNode(z)));

				// remove y
				if (y->left)
					x = y->left;
				else
					x = y->right;

				TreeData *xp = y->parent;
				
				if (x) x->parent = xp;
				if (!xp)
					root = x;
				else if (y == xp->left)
					xp->left = x;
				else
					xp->right = x;

				TreeData *w = xp;
				while (w)
				{
					w->size--;
					w = w->parent;
				}

				bool yBlack = y->isBlack();

				if (y != z) // inject y into z position
				{
					// z <- y
					y->parent = z->parent;
					y->left = z->left;
					y->right = z->right;
					y->color = z->color;
					y->size = z->size;

					if (y->left)
						y->left->parent = y;

					if (y->right)
						y->right->parent = y;

					if (!z->parent)
						root = y;
					else
						if (z->parent->left == z)
							z->parent->left = y;
						else
							z->parent->right = y;

					if (xp == z)
						xp = y;
				}

				if (yBlack)
				{ // fixup
					while (x != root && x->isBlack())
					{
						if (x == xp->left)
						{
							TreeData *w = xp->right;
							if (w->isRed())
							{
								w->color = TreeData::black;
								xp->color = TreeData::red;
								w = w->left;
								leftRotate(xp);
							}
							if (w->left->isBlack() && w->right->isBlack())
							{
								w->color = TreeData::red;
								x = xp;
								xp = x->parent;
							} else {
								if (w->right->isBlack()) {
									w->left->color = TreeData::black;
									w->color = TreeData::red;
									rightRotate(w);
									w = xp->right;
								}
								w->color = xp->color;
								xp->color = TreeData::black;
								w->right->color = TreeData::black;
								leftRotate(xp);
								x = root;
								xp = 0;
							}
						} else {
							TreeData *w = xp->left;
							if (w->isRed())
							{
								w->color = TreeData::black;
								xp->color = TreeData::red;
								w = w->right;
								rightRotate(xp);
							}
							if (w->right->isBlack() && w->left->isBlack())
							{
								w->color = TreeData::red;
								x = xp;
								xp = x->parent;
							} else {
								if (w->left->isBlack()) {
									w->right->color = TreeData::black;
									w->color = TreeData::red;
									leftRotate(w);
									w = xp->left;
								}
								w->color = xp->color;
								xp->color = TreeData::black;
								w->left->color = TreeData::black;
								rightRotate(xp);
								x = root;
								xp = 0;
							}
						}
					}
					if (x)
						x->color = TreeData::black;
				}			
				
				z->initialize();
			}

			/*
			 * Returns minimum element.
			 */
			Node *minimum(Node *x)
			{
				while (nodeLeft(x))
					x = nodeLeft(x);
				return x;
			}

			/*
			 * Returns maximum element.
			 */
			Node *maximum(Node *x)
			{
				while (nodeRight(x))
					x = nodeRight(x);
				return x;
			}
			
			/*
			 * Returns successor of node.
			 */
			Node *successor(Node *x)
			{
				if (nodeRight(x))
					return minimum(nodeRight(x));
				Node *y = nodeParent(x);
				while (y && x == nodeRight(y))
				{
					x = y;
					y = nodeParent(y);
				}
				return y;
			}

			/*
			 * Returns predecessor of node.
			 */
			Node *predecessor(Node *x)
			{
				if (nodeLeft(x))
					return maximum(nodeLeft(x));
				Node *y = nodeParent(x);
				while (y && x == nodeLeft(y))
				{
					x = y;
					y = nodeParent(y);
				}
				return y;
			}
			
			/*
			 * Checks all red&black tree properties.
			 * Links integrity. Balanced properties.
			 */
			bool checkIntegrity()
			{
				// check links
				if (!checkLinks(root))
					return false;
				
				// 4 r&b property
				int b = -1;
				if (!checkBlackHeight(root, 0, b))
					return false;
			
				// balanced properties.
				dword h = height(getRoot());
				dword n = nodes(getRoot());
				
				bool fail = false;
				checkSize(getRoot(), fail);
				if (fail)
					return false;

				h >>= 1;
				h = 1 << h;
				dword x = h - 1;
				return n >= x;
			}

			/*
			 * Returns tree height.
       */
			dword height(Node *node) const
			{
				dword h = 0;
				height(getTreeData(node), 0, h);
				return h;
			}

			/*
			 * Return nodes count in tree.
       */
			dword nodes(Node *node) const
			{
				if (!node)
					return 0;
				return nodes(nodeLeft(node)) + 
					nodes(nodeRight(node)) + 1;
			}

			/*
			 * Returns root.
			 */
			Node *getRoot() const
			{
				return getNode(root);
			}

			/*
			 * Clears tree.
			 * Tree don't own nodes, so don't delete items.
			 */
			void clear()
			{
				root = 0;
			}

			/*
			 * Traverse tree in specified order
			 */
			enum order {direct, reverse};
			template <class Functor>
			void traverse(Node *node, Functor &f, order o = direct)
			{
				if (!node) return;
				Node *left = nodeLeft(node); 
				Node *right = nodeRight(node); 
				switch(o)
				{
				case (direct):
					traverse(left, f, o);
					f(*node);
					traverse(right, f, o);
					break;
				case (reverse):
					traverse(right, f, o);
					f(*node);
					traverse(left, f, o);
					break;
				}
			}

			/*
			 * Search tree.
			 */
			template <class Searcher>
			Node *search(Node *node, Searcher &s)
			{
				if (node == 0)
					return 0;
				switch(s(*node))
				{
				case (0): return node;
				case (1): return search(nodeLeft(node) , s);
				case (-1): return search(nodeRight(node), s);
				}
				return 0;
			}

			/*
			 * Returns left child.
			 */
			Node *nodeLeft(Node *node) const
			{
				return getNode(getTreeData(node)->left);
			}

			/*
			 * Returns right child.
			 */
			Node *nodeRight(Node *node) const
			{
				return getNode(getTreeData(node)->right);
			}

			/*
			 * Returns node parent.
			 */
			Node *nodeParent(Node *node) const
			{
				return getNode(getTreeData(node)->parent);
			}

		};
	}
}

#endif