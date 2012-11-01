#define CLASS LinkList
#include "LinkList.h"
//private functions
static void connect12(Node* node1, Node* node2){
	node1->next = node2;
	node2->prev = node1;
}

static void insert2(Node* node1, Node* node2, Node* node3){
	node1->next = node2;
	node2->prev = node1;
	node2->next = node3;
	node3->prev = node2;
}

static void delete2(Node* node1, Node* node2, Node* node3){
	node1->next = node3;
	node3->prev = node1;
	node2->prev = nil;
	node2->next = nil;
}

MCImplement(LinkList);
#include "RC.default"

method_imp(void, delete_node, Node* anode)body(
	delete2(anode->prev, anode, anode->next);
	if (anode->data!=nil){
		free(anode);
	}
)

method_imp(void, add_node_next, Node* anode)body(
	pull(int,count);pull(Node*,head_p);pull(Node*,pos_p);
	if (count == 0){
		head_p = anode;
		pos_p = anode;
		printf("add first node\n");
	}else{
		connect12(pos_p, anode);
		pos_p = pos_p->next;
		printf("add node next\n");
	}
	count++;
	push(count);push(head_p);push(pos_p);
)

method_imp(void, ins_node_prev, Node* pos, Node* anode)body(
	pull(int,count);pull(Node*,head_p);pull(Node*,pos_p);
	if(count<2){
		printf("node count <2 can not insert!\n");
	}else{
		insert2(pos->prev, anode, pos);
		count++;
		printf("insert a node!\n");
	}
	push(count);push(head_p);push(pos_p);
)

method_imp(void, bye, xxx)body(
	//do clean work here
	printf("LinkList bye\n");
 	free(this);
);

MCImplementEnd(LinkList,Node* head_node_in)Body(
	call(head_node_in, retain, nil);
	//RC protocol support
	Set(ref_count,1);
	Bind(retain);
	Bind(release);
	Bind(bye);

	Set(count,0);
	Set(head_p,head_node_in);
	Set(pos_p,head_node_in);
	Bind(delete_node);
	Bind(add_node_next);
	Bind(ins_node_prev);
)

#undef CLASS
