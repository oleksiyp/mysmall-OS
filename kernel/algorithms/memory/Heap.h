#ifndef _HEAP_H_
#define _HEAP_H_


#include <algorithms/memory/fixedpagedheap.h>
#include <structures/trees/rednblacktree.h>


namespace algorithms
{
	namespace memory
	{
		using namespace structures::trees;

		template <int pageSize, class AllocatorType>
		class Heap
		{
		#define H(x) FixedPagedHeap<x, pageSize, AllocatorType> fixedHeap##x
		// 32 fixed heaps.
			H(1);  H(2);  H(3);  H(4);  H(5);  H(6);  H(7);  H(8);
			H(9);  H(10); H(11); H(12); H(13); H(14); H(15); H(16);
			H(17); H(18); H(19); H(20); H(21); H(22); H(23); H(24);
			H(25); H(26); H(27); H(28); H(29); H(30); H(31); H(32);
			H(33); H(34); H(35); H(36); H(37); H(38); H(39); H(40);
			H(41); H(42); H(43); H(44); H(45); H(46); H(47); H(48);
		#undef H

			AllocatorType *allocator;
	public:
		#define I(x) fixedHeap##x(allocator)
			Heap(AllocatorType *allocator) : 
				I(1),  I(2),  I(3),  I(4),  I(5),  I(6),  I(7),  I(8),
				I(9),  I(10), I(11), I(12), I(13), I(14), I(15), I(16),
				I(17), I(18), I(19), I(20), I(21), I(22), I(23), I(24),
				I(25), I(26), I(27), I(28), I(29), I(30), I(31), I(32),
				I(33), I(34), I(35), I(36), I(37), I(38), I(39), I(40),
				I(41), I(42), I(43), I(44), I(45), I(46), I(47), I(48),
				ptrTree(STRUCT_OFFSET(dummyFreeNode, ptrTreeData)),
				sizeTree(STRUCT_OFFSET(dummyFreeNode, sizeTreeData)),
				reservedTree(STRUCT_OFFSET(dummyReservedNode, ptrTreeData))
			{
					this->allocator = allocator;
			}
		#undef I
		private:
			void *allocateFixed(dword size)
			{
		#define A(x) case(x): return fixedHeap##x.allocate();
				switch(size)
				{
					A(1);  A(2);  A(3);  A(4);  A(5);  A(6);  A(7);  A(8);
					A(9);  A(10); A(11); A(12); A(13); A(14); A(15); A(16);
					A(17); A(18); A(19); A(20); A(21); A(22); A(23); A(24);
					A(25); A(26); A(27); A(28); A(29); A(30); A(31); A(32);
					A(33); A(34); A(35); A(36); A(37); A(38); A(39); A(40);
					A(41); A(42); A(43); A(44); A(45); A(46); A(47); A(48);
				}
				return 0;
			}
		#undef A

			bool deallocateFixed(void *ptr)
			{
		#define D(x) if (fixedHeap##x.deallocate(ptr)) return true
				D(1);  D(2);  D(3);  D(4);  D(5);  D(6);  D(7);  D(8);
				D(9);  D(10); D(11); D(12); D(13); D(14); D(15); D(16);
				D(17); D(18); D(19); D(20); D(21); D(22); D(23); D(24);
				D(25); D(26); D(27); D(28); D(29); D(30); D(31); D(32);
				D(33); D(34); D(35); D(36); D(37); D(38); D(39); D(40);
				D(41); D(42); D(43); D(44); D(45); D(46); D(47); D(48);
				return false;
			}
		#undef D

			typedef struct
			{
				dword ptr;
				dword size;
				RNBTreeData ptrTreeData;
				RNBTreeData sizeTreeData;
			} FreeNode;

			typedef struct
			{
				dword ptr;
				dword size;
				RNBTreeData ptrTreeData;
			} ReservedNode;

			FreeNode dummyFreeNode;
			ReservedNode dummyReservedNode;

			template <class T>
				class LessSize
			{
			public:
				bool operator() (const T& x, const T& y) const
				{
					return x.size < y.size;
				}
			};

			template <class T>
				class LessPtr
			{
			public:
				bool operator() (const T& x, const T& y) const
				{
					return x.ptr < y.ptr;
				}
			};

			RedNBlackTree<FreeNode, LessSize<FreeNode> > sizeTree;
			RedNBlackTree<FreeNode, LessPtr<FreeNode> > ptrTree;
			RedNBlackTree<ReservedNode, LessPtr<ReservedNode> > reservedTree;
			
			class SizeSearcher
			{
				dword size;
			public:
				SizeSearcher(dword size)
				{
					this->size = size;
				}
				int operator ()(const FreeNode &n)
				{
					if (n.size >= size)
						return 0;
					return -1;
				}
			};

			class PtrSearcher
			{
				dword ptr;
			public:
				PtrSearcher(dword ptr)
				{
					this->ptr = ptr;
				}
				int operator ()(const ReservedNode &n)
				{
					if (n.ptr > ptr)
						return 1;
					if (n.ptr < ptr)
						return -1;
					return 0;
				}
			};

			FreeNode *joinNodes(FreeNode *node1, FreeNode *node2)
			{
				if ((char *)node1->ptr + node1->size == (char*)node2->ptr)
				{
					ptrTree.remove(node2);
					sizeTree.remove(node2);
					
					sizeTree.remove(node1);
					node1->size += node2->size;
					sizeTree.insert(node1);
					deallocateFixed(node2);
					return node1;
				}
				if ((char *)node2->ptr + node2->size == (char*)node1->ptr)
					return joinNodes(node2, node1);
				return 0;
			}

			FreeNode *addBlock(void *ptr, dword size)
			{
				FreeNode *node = (FreeNode *)allocateFixed(sizeof(FreeNode));
				node->ptr = (dword)ptr;
				node->size = size;

				sizeTree.insert(node);
				ptrTree.insert(node);

				FreeNode *pre;
				do {
					pre = ptrTree.predecessor(node);
					if (pre)
						pre = joinNodes(pre, node);			
					if (pre)
						node = pre;
				} while(pre);

				FreeNode *suc;
				do
				{
					suc = ptrTree.successor(node);
					if (suc)
						suc = joinNodes(suc, node);
					if (suc)
						node = suc;
				} while (suc);
				return node;
			}
		public:

			void *allocate(dword size)
			{
				if (size <= 48)
					return allocateFixed(size);

				FreeNode *node = sizeTree.search(sizeTree.getRoot(), SizeSearcher(size));
				if (node == 0) {			
					dword pages = (size + pageSize - 1) / pageSize;
					void *page = allocator->allocate(pages);
					if (page)
					{
						addBlock(page, pageSize * pages);
					} else {
						FreeNode *node;
						do
						{
							void *page = allocator->allocate();
							if (page == 0)
								return 0;
							node = addBlock(page, pageSize);
						} while (node->size < size);
					}
					return allocate(size);
				} else if (node->size == size) {			
					// return all block
					sizeTree.remove(node);
					ptrTree.remove(node);
					
					ReservedNode *rnode = (ReservedNode *)allocateFixed(sizeof(ReservedNode));
					rnode->ptr = node->ptr;
					rnode->size = size;
					reservedTree.insert(rnode);
					deallocateFixed(node);
					return (void *)rnode->ptr;
				} else if (node->size > size){		
					// cut block
					sizeTree.remove(node);
					node->size -= size;
					sizeTree.insert(node);
					
					void *ptr = (void *)((char*)node->ptr + node->size);
					
					ReservedNode *rnode = (ReservedNode *)allocateFixed(sizeof(ReservedNode));
					rnode->ptr = (dword)ptr;
					rnode->size = size;
					reservedTree.insert(rnode);

					return ptr;
				}
				return 0;
			}

			bool deallocate(void *ptr)
			{
				ReservedNode *rnode = reservedTree.search(reservedTree.getRoot(), PtrSearcher((dword)ptr));
				if (!rnode)
				{
					return deallocateFixed(ptr);
				}
				addBlock((void*)rnode->ptr, rnode->size);
				reservedTree.remove(rnode);
				deallocateFixed(rnode);
				return true;
			}
#ifdef TESTING
			template <class T>
			class PrintBlocks
			{
			public:
				PrintBlocks() {}
				void operator () (const T& block)
				{
					printf("0x%08X - 0x%08X (%d bytes)\n", 
						block.ptr,block.ptr+
						block.size,block.size);
				}
			};

			void memoryStat()
			{
			#define H(x) fixedHeap##x.memoryStat();
			// 32 fixed heaps.
				H(1);  H(2);  H(3);  H(4);  H(5);  H(6);  H(7);  H(8);
				H(9);  H(10); H(11); H(12); H(13); H(14); H(15); H(16);
				H(17); H(18); H(19); H(20); H(21); H(22); H(23); H(24);
				H(25); H(26); H(27); H(28); H(29); H(30); H(31); H(32);
				H(33); H(34); H(35); H(36); H(37); H(38); H(39); H(40);
				H(41); H(42); H(43); H(44); H(45); H(46); H(47); H(48);
			#undef H
				printf("Reserved regions:\n");
				reservedTree.traverse(
					reservedTree.getRoot(),
					PrintBlocks<ReservedNode>()
					);
				printf("Free regions:\n");
				ptrTree.traverse(
					ptrTree.getRoot(),
					PrintBlocks<FreeNode>()
					);
			}
#endif
		};
	}
}

#endif