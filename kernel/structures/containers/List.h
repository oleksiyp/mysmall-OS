#ifndef _LIST_H_
#define _LIST_H_

#include <basic/types.h>

namespace structures
{
	namespace containers
	{
		template <class Value>
		class List
		{
			typedef struct _Node
			{
				struct _Node *next, *prev;
				Value val;
			} Node;
			dword size;
		public:
			typedef void *Iterator;
		private:
			void insert(Iterator it, Node *node, bool after)
			{
				if (it == 0)
				{
					if (head == 0)
					{
						head = node;
						node->next = node;
						node->prev = node;
					} else if (after){
						node->prev = head->prev;
						node->next = head;
						
						head->prev = node;
						node->prev->next = node;

						head = node;
					} else {
						node->prev = head->prev;
						node->next = head;
						
						head->prev = node;
						node->prev->next = node;
					}
				} else {
					Node *n = (Node *)it;
					if (after)
					{
						n->next->prev = node;
						node->next = n->next;
						n->next = node;
						node->prev = n;
					} else {
						n->prev->next = node;
						node->prev = n->prev;
						n->prev = node;
						node->next = n;
					}
				}
				size++;
			}

		public:
			Node *head;
			List()
			{
				head = 0;
				size = 0;
			}
			List(const List<Value> &list)
			{
				head = 0;
				size = 0;
				insertTail(list);
			}
			~List()
			{
				clear();
			}

		public:

			Iterator insertTail(const Value &val)
			{
				Node *n = new Node;
				n->val = val;
				insert(0, n, false);
				return (Iterator)n;
			}

			Iterator insertHead(const Value &val)
			{
				Node *n = new Node;
				n->val = val;
				insert(0, n, true);
				return (Iterator)n;
			}

			Iterator insertAfter(Iterator it, const Value &val)
			{
				Node *n = new Node;
				n->val = val;
				insert(it, n, true);
				return (Iterator)n;
			}

			Iterator insertBefore(Iterator it, const Value &val)
			{
				Node *n = new Node;
				n->val = val;
				insert(it, n, false);
				return (Iterator)n;
			}


			Iterator insertTail(const List<Value> &list)
			{
				Iterator r = 0;
				for (Iterator it = list.head; it; it = list.next(it))
				{
					Iterator x = insertTail(list[it]);
					if (r == 0)
						r = x;
				}
				return (Iterator)r;
			}

			Iterator insertHead(const List<Value> &list)
			{
				Iterator r = 0;
				for (Iterator it = list; it; it = list.next(it))
				{
					Iterator x = insertHead(list[it]);
					if (r == 0)
						r = x;
				}
				return (Iterator)r;
			}

			Iterator insertAfter(Iterator x, const List<Value> &list)
			{
				Iterator r = 0;
				for (Iterator it = list; it; it = list.next(it))
				{
					x = insertAfter(x, list[it]);
					if (r == 0)
						r = x;
				}
				return (Iterator)r;
			}

			Iterator insertBefore(Iterator it, const List<Value> &list)
			{
				return insertAfter(prev(it), list);
			}

			void remove(Iterator it)
			{
				Node *node = (Node *)it;
				if (node->next == node)
				{
					head = 0;
				} else {
					node->next->prev = node->prev;
					node->prev->next = node->next;
				}
				size--;
				delete node;
			}

			Iterator getHead() const
			{
				return (Iterator)head;
			}

			Iterator getTail() const
			{
				if (head == 0)
					return 0;
				return (Iterator)head->prev;
			}

			void clear()
			{
				Node *next;
				for (Node *node = head; node; node = next) {
					next = node->next;
					delete node;
					if (next == head)
						break;
				}
				head = 0;
				size = 0;
			}

			Iterator next(Iterator it) const
			{
				Node *node = (Node *)it;
				if (node->next == head)
					return 0;
				return (Iterator)node->next;
			}

			Iterator prev(Iterator it) const
			{
				Node *node = (Node *)it;
				if (node == head)
					return 0;
				return (Iterator)node->prev;
			}

			const Value &operator [](Iterator it) const
			{
				Node *node = (Node *)it;
				return node->val;
			}
			Value &operator [](Iterator it)
			{
				Node *node = (Node *)it;
				return node->val;
			}

			dword getSize() const
			{
				return size;
			}
			
			List<Value> copy() const
			{
				List<Value> r;
				for(Iterator it = head; it; it = next(it))
					r.insertTail(((Node *)it)->val);
				return r;
			}
		};
	}
}

#endif