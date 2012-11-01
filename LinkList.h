#ifndef __LinkList__
#define __LinkList__
#include "Node.h"

MCInterface(LinkList)
#include "RC.protocol"
	int count;
	Node* head_p;
	Node* pos_p;
	method(void,delete_node,Node* anode);
	method(void,add_node_next,Node* anode);
	method(void,ins_node_prev,Node* pos, Node* anode);
MCInterfaceEnd(LinkList,Node* head_node_in)

#endif
