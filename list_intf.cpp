#include <iostream>
#include "list_intf.h"
#include "includeme.h"

using namespace std;

list_intf::list_intf(){	

	this->head = NULL;
	this->current = this->head;
}

Node* list_intf::get_node(int node_num){
	//this->current = this->head;
	Node *current = this->current;
	for(int i = 0; i < node_num; i++){
		//DEBUG("getnode loop");
		if (current == NULL){
			std::cout << "Exceeding the number of nodes" << std::endl;
			exit(1);
		}
		current = current->next;
	}
	DEBUG(current->data.int_data);
	return current;
}

void list_intf::insert_in_front(Data data){
	//DEBUG("in front");
	Node *new_node = new Node();
	Node *current = this->current;
	new_node->data = data;
	new_node->next = current;
	new_node->prev = NULL;
	if(current != NULL)
		current->prev = new_node;
	current = new_node;
	this->current = current;
	return;
}

void list_intf::insert_in_between(Data data, Node *node){
	//DEBUG("in between");
	Node *new_node = new Node();
	new_node->data = data;
	Node *previous = NULL;
	if(node->prev != NULL){
		previous = node->prev;
	}
	node->prev = new_node;
	new_node->next = node;
	new_node->prev = previous;
	if(previous != NULL)
		previous->next = new_node;
	
	return;
}

void list_intf::display_list(){
	//this->current = this->head;
	Node *current = this->current;
	while(current != NULL){
		//DEBUG("in display");
		std::cout << current->data.int_data << current->data.char_data << std::endl;
		current = current->next;
	}
	return;
}

Data Data::create_datapacket(int int_data, char char_data){
	Data data;
	data.int_data = int_data;
	data.char_data = char_data;
	return data;
}

void list_intf::remove_node(Node *node){
	Node *next_node = node->next;
	Node *prev_node = node->prev;
	if (prev_node != NULL)
		prev_node->next = next_node;
	if (next_node != NULL)
		next_node->prev = prev_node;
	delete node;
	return;
}

list_intf::~list_intf(){
	delete head;
	delete current;
	std::cout << "List deleted" << endl;
}


/*int main(){
	list_intf list;
	list.insert_in_front(list.create_datapacket(45, 'd'));
	list.insert_in_front(list.create_datapacket(92, 'e'));
	list.insert_in_front(list.create_datapacket(10, 'h'));
	list.insert_in_front(list.create_datapacket(48, 'x'));
	list.display_list();
	DEBUG(" ");
	list.insert_in_between(list.create_datapacket(30, 's'), list.get_node(2));
	DEBUG(" ");

	list.display_list();
	DEBUG(" ");
	list.remove_node(list.get_node(1));
	DEBUG(" ");

	list.display_list();
	DEBUG(" ");
	return 0;
}*/


