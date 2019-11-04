#include <iostream>
#include <cstdlib>
#include <string.h>
#include "../linkedlist_intf/list_intf.h"
#include "../linkedlist_intf/includeme.h"
#include "heap_intf.h"

heap_intf::heap_intf(){
	this->root = NULL;
	this->current = this->root;
	//this->leftmost = this->root;
}

heap_intf::~heap_intf(){

}

void heap_intf::insert_into_tree(Heap_node *node, Heap_node *current){	
	if (current == NULL){
		current = node;	//Adding root node
		//DEBUG("first if");
		///DEBUG(node->data.int_data);
		this->root = node; //Updating root node
		return;
	}
	if(current->left == NULL){
		current->left = node;
		//DEBUG("second if");
		//DEBUG(current->left->data.int_data);
		//DEBUG(current->left);
		current->left->prev = current;
		//DEBUG(current);
		if(current->left_sib != NULL){
		//	DEBUG("current->left_sib");
			current->left_sib->right->right_sib = current->left;
			current->left->left_sib = current->left_sib->right;
		}
		return;
	}
	if(current->right == NULL){
		current->right = node;
		//DEBUG("third if");
		//DEBUG(current->right->data.int_data);
		//DEBUG(current->right);
		current->right->prev = current;
		current->right->left_sib = current->left;
		current->left->right_sib = current->right;
		return;
	}
	if(current->right_sib != NULL){
		//DEBUG("current->right_sib");			
		//DEBUG(current->data.int_data);
		//DEBUG(current->right_sib);
		//exit(1);
		//current->right_sib->left_sib = current;
		heap_intf::insert_into_tree(node, current->right_sib);
		return;
	}
	while(current->left_sib != NULL){		
		//DEBUG("while");
		current = current->left_sib;
	}
	heap_intf::insert_into_tree(node, current->left);

	return;
}


void heap_intf::print_tree(Heap_node *node){
	if (node == NULL)
		return;
	std::cout << node->data.int_data << node->data.char_data << " ";

	while(node->right_sib != NULL){
		node = node->right_sib;
		std::cout << node->data.int_data << node->data.char_data << " ";
	}
	while(node->left_sib != NULL)
		node = node->left_sib;
	node = node->left;
	std::cout << " " << std::endl;
	heap_intf::print_tree(node);
	return;
}

Heap_node* heap_intf::swap_parent(Heap_node *parent, Heap_node *child, bool child_branch){
	Heap_node *temp = NULL;
	if(child_branch){
		temp = parent;

		temp->right = child->right;
		temp->left = child->left;
		temp->right_sib = child->right_sib;
		temp->left_sib = child->left_sib;
		temp->prev = child;

		child->right = parent;
		child->right_sib = parent->right;
		child->left_sib = parent->left_sib;
		child->left = parent->left;
		child->prev = parent->prev;

		parent = temp;
	}
	if(!child_branch){
		temp = parent;

		temp->right = child->right;
		temp->left = child->left;
		temp->right_sib = child->right_sib;
		temp->left_sib = child->left_sib;
		temp->prev = child;

		child->left = parent;
		child->right_sib = parent->right;
		child->left_sib = parent->left_sib;
		child->right = parent->right;
		child->prev = parent->prev;

		parent = temp;
	}
	return child;
}

void heap_intf::heapify(Heap_node *begin){		//writing for min heap
	Heap_node *node = begin;	
	while(node->next->next != NULL)
		node = node->next;
	while(node->right_sib == NULL){
		if(node->left->data.int_data > node->right->data.int_data)
			node = heap_intf::swap_parent(node, node->right, 1);
		else
			node = heap_intf::swap_parent(node, node->left, 0);
		node = node->right_sib;
	}
	while(node->left_sib == NULL)
		node = node->left_sib;
	if(node->prev != NULL){		//reached root
		node = node->prev;
		heapify(node);
	}
	return;
	
}

int heap_intf::get_tree_depth(){
	Heap_node *node = this->root;
	int tree_depth = 0;
	while(node->left != NULL){
		node = node->left;
		tree_depth++;
	}
	return tree_depth;
}	

Bool heap_intf::min_heap(Heap_node *node){

}

int main(int argc, char *argv[]){
	heap_intf hp;
	std::srand(240);

	for(int i = 0; i < atoi(argv[1]); i++){
		Heap_node *node = new Heap_node();
		Data d = hp.create_datapacket(std::rand()%200,'s');
		node->data = d;
		hp.insert_into_tree(node, hp.root);
	}

	hp.print_tree(hp.root);

	return 0;
}
