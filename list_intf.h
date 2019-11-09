#ifndef LIST_INTF_H
#define LIST_INTF_H
#include <iostream>

using namespace std;

class Data
{
	public:
	int int_data;
	char char_data;
	Data create_datapacket(int i_data, char c_data);
	void print_datapacket(Data data);
};

class Node : public Data
{
	public:
	Node *next = NULL;
        Node *prev = NULL;
	Data data;
};

class list_intf : public Node
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
		void remove_node(Node *node);

	private:
	protected:


};

#endif //LIST_INTF_H
