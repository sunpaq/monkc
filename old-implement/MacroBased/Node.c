#define CLASS Node
#include "Node.h"

MCImplement(Node)
#include "RC.default"

method_imp(void, bye, xxx)body(
	//clear data if it is clearable
	pull(id,data);
	cast(rco,RCObject,data);
	printf("node release string\n");
	call(rco,release,nil);
	printf("node bye\n");
	free(this);
);

MCImplementEnd(Node,id data_in)Body(
	//reference counting(RC) protocol support
	//new(str,String,"i am node");
	//Set(info,str);
	Set(ref_count,1);
	Bind(retain);
	Bind(release);
	Bind(bye);

	Set(data,data_in);
	Set(next,nil);
	Set(prev,nil);

	cast(rco,RCObject,data_in);
	printf("node retain string\n");
	call(rco, retain, nil);
)

#undef CLASS