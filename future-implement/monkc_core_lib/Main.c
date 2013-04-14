#include "MCRuntime.h"


int jumpTarget(id const this, void* addr, int arg1, int arg2)
//int Target(id const this, void* addr, int arg1, int arg2)
{
	// unsigned size = _start_stack();
	// printf("stack size is: %d\n", size);

	// printf("jumpTarget addr is: %d\n", addr);
	// printf("jumpTarget this is: %d\n", this);
	// printf("jumpTarget arg1 is: %d\n", arg1);
	// printf("jumpTarget arg2 is: %d\n", arg2);
	static int count = 0;
	printf("count %d\n", count);
	printf("arg2 %d\n", arg2);

	//if(arg2++<400)_jump(nil, addr, 300, arg2++);
	//_clean_stack(size);
	//_clean_stack();
	//_jump(nil, addr, 300, ++count);
	_tail_jump2(nil, addr, 300, ++count);
}

int (*jumpTargetVoid)();
int TargetVoid()
{
	printf("TargetVoid\n");
	printf("TargetVoid haha\n");
	printf("TargetVoid hahaha\n");


}

int main(int argc, char const *argv[])
{
	mc_init();

		// jumpTarget = Target;
		// jumpTargetVoid = TargetVoid;

		debug_log("start\n");
		//(*jumpTarget)(nil, nil, 10, 20);
		//_jump(jumpTargetVoid);
		//for(;;)
		_jump(nil, jumpTarget, 100, 200);
		//_jump(jumpTarget, new(MCObject, nil), 10, 20);

	mc_end();
	return 0;
}