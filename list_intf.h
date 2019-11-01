#ifndef LIST_INTF_H
#define LIST_INTF_H
#include <iostream>

using namespace std;

class Data
{
	public:
	int int_data;
	char char_data;
};

class Node
{
	public:
	Node *next = NULL;
        Node *prev = NULL;
	Data data;
};

class list_intf
{
	public:
		Node *head;
		Node *current;

		list_intf();
		~list_intf();

		Node *get_node(int node_num);
		void insert_in_front(Data data);
		void insert_in_between(Data data, Node *node);
		void display_list();
		Data create_datapacket(int int_data, char char_data);
		void remove_node(Node *node);

	private:
	protected:


};

#endif //LIST_INTF_H
