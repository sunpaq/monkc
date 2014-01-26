#include "monkc.h"
#include "Bird.h"
#include "BirdFather.h"
#include "BirdCatA.h"
#include "BirdModeA.h"

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

void test_object_life_cycle()
{
		Bird* bird = new(Bird);
		ff(bird, fly, nil);
		ff(bird, flyhigh, nil);
		ff(bird, singAsong, "a song from child");
		ff(bird, fatherAge, nil);
		ff(bird, cannotResponseThis, nil);
		shift(bird, BirdModeA);
			ff(bird, modemethodC, nil);
		shift_back(bird);
		recycle(bird);
		//one create on delete

		Bird* bird2 = new(Bird);
		debug_log("bird2 pointer %p\n", bird2);
		Bird* bird3 = new(Bird);
		debug_log("bird2 pointer %p\n", bird3);
		Bird* bird31 = new(Bird);
		debug_log("bird2 pointer %p\n", bird31);

		info(Bird);
		info(BirdFather);
		info(BirdGrandFather);

		recycle(bird2);
		recycle(bird3);
		//release(&bird31);

		info(Bird);
		info(BirdFather);
		info(BirdGrandFather);

		Bird* b1=new(Bird);
		Bird* b2=new(Bird);

		info(Bird);
		info(BirdFather);
		info(BirdGrandFather);

		recycle(b1);
		recycle(b2);

		clear(Bird);
		clear(BirdFather);
		clear(BirdGrandFather);

		info(Bird);
		info(BirdFather);
		info(BirdGrandFather);

}

void test_method_jumpping()
{
	debug_log("start\n");
	_push_jump(make_msg(nil, jumpTarget), 100, 200);

}

void monkc_runtime_check()
{
	const char* met1 = "method1";
	const char* met2 = "method2";
	const char* met3 = "method3";

	printf("method1 address: %ld\n", (unsigned long)met1);
	printf("method2 address: %ld\n", (unsigned long)met2);
	printf("method3 address: %ld\n", (unsigned long)met3);
}

int main(int argc, char const *argv[])
{
	mc_init();
		LOG_LEVEL = MC_DEBUG;
		monkc_runtime_check();
//		test_method_jumpping();

		test_object_life_cycle();
	mc_end();
	return 0;
}
