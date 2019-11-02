#ifndef HEAP_INTF_H
#define HEAP_INTF_H
#include <iostream>
#include "../linkedlist_intf/list_intf.h"
#include "../linkedlist_intf/includeme.h"

class Heap_node : public Data
{
	public:
		Data data;
		Heap_node *left = NULL;
	       	Heap_node *right = NULL; 
		Heap_node *left_sib = NULL; 
		Heap_node *right_sib = NULL;
		Heap_node *prev = NULL;

};

class heap_intf : public Heap_node
{
	public:
		Heap_node *root;
		Heap_node *current;
		//Heap_node *leftmost;

		heap_intf();
		~heap_intf();
		void insert_into_heap(Heap_node *node, Heap_node *current);
		void print_heap(Heap_node *node);
};

#endif //HEAP_INTF_H
