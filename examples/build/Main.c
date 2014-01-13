#include "monkc.h"
#include "Bird.h"
#include "BirdFather.h"
#include "BirdCatA.h"
#include "BirdModeA.h"

int jumpTarget(id const this, const void* entry, int arg1, int arg2)
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
		Bird* bird = hew(Bird, 2070745);
		fh(bird,fly, 101491, nil);
		fh(bird,flyhigh, 3537959061, nil);
		ff(bird, singAsong, "a song from child");
		fh(bird,fatherAge, 522530307, nil);
		fh(bird,cannotResponseThis, 2144997154, nil);
		shift(bird, BirdModeA);
			fh(bird,modemethodC, 1891533951, nil);
		shift_back(bird);
		recycle(bird);
		//one create on delete

		Bird* bird2 = hew(Bird, 2070745);
		debug_log("bird2 pointer %p\n", bird2);
		Bird* bird3 = hew(Bird, 2070745);
		debug_log("bird2 pointer %p\n", bird3);
		Bird* bird31 = hew(Bird, 2070745);
		debug_log("bird2 pointer %p\n", bird31);

		hnfo(Bird, 2070745);
		hnfo(BirdFather, 875971477);
		hnfo(BirdGrandFather, 302479087);

		recycle(bird2);
		recycle(bird3);
		//release(&bird31);

		hnfo(Bird, 2070745);
		hnfo(BirdFather, 875971477);
		hnfo(BirdGrandFather, 302479087);

		Bird* b1=hew(Bird, 2070745);
		Bird* b2=hew(Bird, 2070745);

		hnfo(Bird, 2070745);
		hnfo(BirdFather, 875971477);
		hnfo(BirdGrandFather, 302479087);

		recycle(b1);
		recycle(b2);

		hlear(Bird, 2070745);
		hlear(BirdFather, 875971477);
		hlear(BirdGrandFather, 302479087);

		hnfo(Bird, 2070745);
		hnfo(BirdFather, 875971477);
		hnfo(BirdGrandFather, 302479087);

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
		LOG_LEVEL = DEBUG;
		monkc_runtime_check();
//		test_method_jumpping();

		test_object_life_cycle();
	mc_end();
	return 0;
}
