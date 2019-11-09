#include <iostream>
#include <cstdlib>
#include <string.h>
#include <chrono>
#include "../linkedlist_intf/list_intf.h"
#include "../linkedlist_intf/includeme.h"
#include "heap_intf.h"

using namespace std::chrono;

heap_intf::heap_intf(){
	this->root = NULL;
	this->current = this->root;
	//this->leftmost = this->root;
}

heap_intf::~heap_intf(){

}


/*
 * Recursively add nodes to tree
 * That's all you need to know about this...
 */
void heap_intf::insert_into_tree(Heap_node *node, Heap_node *current){	
	if (current == NULL){
		current = node;	//Adding root node
		this->root = node; //Updating root node
		return;
	}
	if(current->left == NULL){
		current->left = node;
		current->left->prev = current;
		if(current->left_sib != NULL){
			current->left_sib->right->right_sib = current->left;
			current->left->left_sib = current->left_sib->right;
		}
		return;
	}
	if(current->right == NULL){
		current->right = node;
		current->right->prev = current;
		current->right->left_sib = current->left;
		current->left->right_sib = current->right;
		return;
	}
	if(current->right_sib != NULL){
		heap_intf::insert_into_tree(node, current->right_sib);
		return;
	}
	while(current->left_sib != NULL){		
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

/*
 *Function for internal swapping of data while heapifying
 *Nodes do not change places due to complexity in structure of tree
 *Data between nodes is exchanged
 *TODO: Could be bettered by actually exchanging nodes by taking care of the complexity of several pointers
 */

void heap_intf::swap_node_data(Heap_node *parent, Heap_node *child){
	Data temp;
	temp = parent->data;
	parent->data = child->data;
	child->data = temp;

	return;
}

/*
 * MOST impottant function : Actually converts tree into min heap
 * Uses recursion
 * Begins from second last leftmost node and works its way up to the root
 */

void heap_intf::heapify(Heap_node *begin, int depth){		//writing for min heap
	Heap_node *temp = NULL;
	Heap_node *node = begin;
	while(node != NULL){ 			//if rightmost node not reached
		if(node->left == NULL){}	//senseless check but nevertheless...
		else if(node->right == NULL){	//if right node is NULL then only compare with left node
			if(node->data.int_data > node->left->data.int_data)
				heap_intf::swap_node_data(node, node->left);
		}		
		//if both nodes present then check with both nodes and swap with smaller of the two if indeed parent is smaller than any of 
		//the nodes
		else if((node->data.int_data > node->left->data.int_data) || (node->data.int_data > node->right->data.int_data)){
			if(node->left->data.int_data > node->right->data.int_data)
				heap_intf::swap_node_data(node, node->right);
			else
				heap_intf::swap_node_data(node, node->left);
		}
		temp = node;		//for right most node case
		node = node->right_sib;
	}
	//print_tree(this->root);
	while(temp->left_sib != NULL){
		temp = temp->left_sib;	//get to leftmost node
	}
	node = temp;
	if(node->prev != NULL){		//if root not reached
		node = node->prev;	//go one level up
		heapify(node, depth - 1);
	}
	return;
}

/*
 *Swaps root node with last node and returns root node
 *One node is reduced from the tree
 */

Heap_node * heap_intf::swap_root(Heap_node *node){
	Heap_node *root = this->root;
	//Heap_node *temp  = NULL;
	while(node->left != NULL)
		node = node->left;
	while(node->right_sib != NULL)
		node = node->right_sib;	//got the last node

	if(node->prev->right != NULL)	//check whether the last node is left or right node and detach it.
		node->prev->right = NULL;
	else if(node->prev->left != NULL)
		node->prev->left = NULL;
	node->prev = root->prev;
	if(node->left_sib != NULL)	//last node's right_sib is obviously NULL
		node->left_sib->right_sib = NULL;
	node->left_sib = root->left_sib;
	node->right_sib = root->right_sib;
	node->left = root->left;
	node->right = root->right;
	if(root->left != NULL)		//take care for root node beingn parent node case
		root->left->prev = node;
	if(root->right != NULL)
		root->right->prev = node;
	this->root = node;

	return root;
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

/*
 *Checks for min heap for entire tree.
 *Returns false if min_heap not found
 *Checks from root node going deeper in each iteration
 * TODO: Can be bettered using recursion of the function
*/

bool heap_intf::check_min_heap(){
	int dep = heap_intf::get_tree_depth();
	Heap_node *node = this->root;
	while(dep != 0){
		if(heap_intf::min_heap(node)){		//if min heap is true for the immediate family of the entered node
			if(node->right_sib != NULL){
				node = node->right_sib;	//change node to right sibling to check for that family 
			}
			else{
				while(node->left_sib != NULL){	//if rightmost node for the level reached, return to leftmost node of level
					node = node->left_sib;	
				}
				node = node->left;	//go one level deeper
			}
		}
		else{
			return FALSE;
		}
		dep--;
	}
	return TRUE;
	
}

//Compare family for min heap. Return TRUE or FALSE
bool heap_intf::min_heap(Heap_node *node){
	if(node->left != NULL){
		if(node->data.int_data > node->left->data.int_data)
			return FALSE;
	}
	if(node->right != NULL){
		if(node->data.int_data > node->right->data.int_data)
			return FALSE;
	}
	else
		return TRUE;
}

void welcome(){
	std::cout << " " << std::endl <<
		"*****************WELCOME TO HEAPSORT*****************" << std::endl <<
		"IF YOU GET A SEGMENTATION FAULT WHEN YOU RUN THIS PIECE OF CODE, YOU PROBABLY DESERVE TO." << std::endl <<
		"THAT'S BECAUSE YOU MOST PROBABLY DID NOT READ THE README FILE. GO READ THAT FIRST." << std::endl << std::endl <<
		"MY CODE SORTS DATA USING HEAPSORT. IF YOU ARE A PROGRAMMER, THEN TAKE A LOOK AT THE NOT SO WELL COMMENTED CODE." << std::endl<<
		"IF YOU AREN'T ONE, THEN YOU MUST TRUST IN ME. ENJOY!" << std::endl << 
		"AND ALSO, IF THE CODE RUNS INTO AN INFINITE LOOP, THAT'S THE RANDOM NUMBER GENERATOR FAULT. SEE THE README." << std::endl << std::endl;

	return;
}
int main(int argc, char *argv[]){
	welcome();
	heap_intf hp;
	std::srand(atoi(argv[1]));	//seed value for the random number generator
	int num = 0;			//int_data	}
	char a = 's';			//char_data	} datatype: Data (see list_intf.cpp)

	std::cout << "Entered list" << std::endl;
	for(int i = 0; i < atoi(argv[2]); i++){		//create input complete binary tree with given number of randomized Data values
		num = std::rand()%100;
		if((num >= 65) && (num <= 90))
			a = num;
		Heap_node *node = new Heap_node();
		Data d = hp.list_intf::create_datapacket(num, a);
		node->data = d;
		hp.list_intf::print_datapacket(d);
		hp.insert_into_tree(node, hp.root);
	}
	
	//hp.print_tree(hp.root);
	Heap_node *temp = NULL;;
	int j = 0;
	auto start = high_resolution_clock::now();	//Timer
	while(hp.root->left != NULL){			//while root node not reached
		temp = hp.root;
		while(temp->left->left != NULL)		//get to leftmost node in the second last level
			temp = temp->left;
		if(!hp.check_min_heap()){		//check if we have min heap

			//heapify if not using the leftmost node on second last node as first input to recursive heapify		
			hp.heapify(temp, hp.get_tree_depth());	
			//hp.print_tree(hp.root); //debug print
		}
		else{					//if min heap is true then swap root node with last node
			hp.list_intf::insert_in_front(hp.swap_root(hp.root)->data);	//insert into 'sorted' list
		}
		//if(j == 20) break;
		j++;
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop-start);
	std::cout << " "<< std::endl;
        std::cout << "Time taken to sort: " << duration.count() << " microseconds" << std::endl;	
	hp.list_intf::insert_in_front(hp.root->data);

	std::cout << "Number of while loop iterations: " << j << std::endl;
	std::cout << "Sorted list:" << std::endl;
	hp.list_intf::display_list();



	return 0;
}
