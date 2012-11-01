#include "LinkList.h"
#include "Node.h"
#include "String.h"

int main(int argc, char const *argv[])
{
	new(str0, String, "this is head node");
	new(str1, String, "this is node1");
	new(str2, String, "this is node2");
	new(str3, String, "this is node3");
	new(str4, String, "this is node4");
	new(str5, String, "this is node5");
	new(str6, String, "this is node6");

	new(head_node, Node, str0);
	new(node1, Node, str1);
	new(node2, Node, str2);
	new(node3, Node, str3);
	new(node4, Node, str4);
	new(node5, Node, str5);
	new(node6, Node, str6);

	new(ll, LinkList, head_node);

	call(ll,add_node_next,node1);
	call(ll,add_node_next,node2);
	call(ll,add_node_next,node3);
	call(ll,add_node_next,node4);

	call(ll,ins_node_prev,node4,node5);
	call(ll,ins_node_prev,node4,node6);

	//call(ll,delete_node,node3);

	Node* iter;
	iter = ll->head_p;

	while (iter!=nil)
	{
		String* str = (String*)iter->data;
		call(str, show, nil);
		iter = iter->next;
	}

	call(head_node, release, nil);
	call(node1, release, nil);
	call(node2, release, nil);
	call(node3, release, nil);
	call(node4, release, nil);
	call(node5, release, nil);
	call(node6, release, nil);

	call(ll, release, nil);

	call(str0, release, nil);
	call(str1, release, nil);
	call(str2, release, nil);
	call(str3, release, nil);
	call(str4, release, nil);
	call(str5, release, nil);
	call(str6, release, nil);



	// ln->add_node_next(ln,&a1);
	// ln->add_node_next(ln,&a2);
	// ln->add_node_next(ln,&a3);
	// ln->add_node_next(ln,&a4);

	// struct node* iter2;
	// iter2 = ln->head_p;

	// while (iter2!=NULL)
	// {
	// 	char* str = (char*)iter2->data;
	// 	printf("%s\n", str);
	// 	iter2 = iter2->next;
	// }



	// MemAllocator* allocator = MemAllocator_init();
	// ObjectsPool* objp = ObjectsPool_init(allocator);


	// //int index = objp->put(objp,(void*)"this is a object");//segment fault
	// //printf("index is: %d\n", index);
	// //int index = 1;
	// //char* str = (char*)objp->get(objp, index);
	// //printf("str is: %s\n", str);


	// MemAllocator_destory(allocator);

	return 0;
}