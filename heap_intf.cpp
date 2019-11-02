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

Data Data::create_datapacket(int int_data, char char_data){
        Data data;
        data.int_data = int_data;
        data.char_data = char_data;
        return data;
}

void heap_intf::insert_into_heap(Heap_node *node, Heap_node *current){	
	if (current == NULL){
		current = node;	//Adding root node
		DEBUG("first if");
		DEBUG(node->data.int_data);
	DEBUG(" ");
		this->root = node; //Updating root node
		return;
	}
	if(current->left == NULL){
		current->left = node;
		DEBUG("second if");
		DEBUG(current->left->data.int_data);
		DEBUG(current->left);
		current->left->prev = current;
		//DEBUG(current);
	DEBUG(" ");
		if(current->left_sib != NULL){
			DEBUG("current->left_sib");
			current->left_sib->right->right_sib = current->left;
			current->left->left_sib = current->left_sib->right;
		}
		return;
	}
	if(current->right == NULL){
		current->right = node;
		DEBUG("third if");
		DEBUG(node->data.int_data);
		DEBUG(current->right);
	DEBUG(" ");
		current->right->prev = current;
		current->right->left_sib = current->left;
		current->left->right_sib = current->right;
		return;
	}
	if(current->right_sib != NULL){
		DEBUG("current->right_sib");			
		//DEBUG(current->data.int_data);
		DEBUG(current->right_sib);
	DEBUG(" ");
		//exit(1);
		//current->right_sib->left_sib = current;
		heap_intf::insert_into_heap(node, current->right_sib);
		return;
	}
	while(current->left_sib != NULL){		
		DEBUG("while");
		current = current->left_sib;
	}
	heap_intf::insert_into_heap(node, current->left);

	return;
}

void heap_intf::print_heap(Heap_node *node){

	DEBUG("in print");
	Heap_node *to_print;
	to_print = node;

	std::cout << to_print->data.int_data << to_print->data.char_data << " ";

	if(to_print->right_sib !=NULL){
		heap_intf::print_heap(to_print->right_sib);		
	}
	while(to_print->left_sib != NULL)
		to_print = to_print->left_sib;
	heap_intf::print_heap(to_print->left);
	return;


}

int main(){
	heap_intf hp;
	std::srand(240);

//	Heap_node *rootnode = NULL;;	

	for(int i = 0; i < 8; i++){
		Heap_node *node = new Heap_node();
		Data d = hp.create_datapacket(i,'s');
		node->data = d;
	/*DEBUG(node->left);
	DEBUG(node->right);
	DEBUG(node->left_sib);
	DEBUG(node->right_sib);
	DEBUG(node->prev);
	DEBUG(" ");*/
		hp.insert_into_heap(node, hp.root);
		//delete node;
	}

	hp.print_heap(hp.root);

	return 0;
}
