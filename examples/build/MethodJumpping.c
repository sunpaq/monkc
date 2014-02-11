#include "MethodJumpping.h"

int jumpTarget(mo const this, const void* entry, int arg1, int arg2)
{
	static int count = 0;
	printf("count %d\n", count);
	printf("arg2 %d\n", arg2);

	if(count==100)return;
	_clean_jump2(make_msg(this, entry), 300, ++count);
}

int TargetVoid()
{
	printf("TargetVoid\n");
	printf("TargetVoid haha\n");
	printf("TargetVoid hahaha\n");
}

void test_method_jumpping()
{
	debug_log("start\n");
	_push_jump(nil, make_msg(nil, jumpTarget), 100, 200);

}