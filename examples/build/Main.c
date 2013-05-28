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

	//
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
		// Bird* bird;
		// bird = (Bird*)_new(_alloc("Bird", sizeof(Bird), Bird_load), Bird_init);
		// debug_log("bird pointer %p\n", bird);
		// _push_jump(make_msg(bird, Bird_fly), nil);
		// debug_log("after new\n");
		//debug_log("%s is child of %s\n", bird->isa->item->key, bird->super->isa->item->key);
		Bird* bird = new(Bird);
		ff(bird, fly, nil);
		ff(bird, flyhigh, nil);
		ff(bird, singAsong, "a song from child");
		ff(bird, fatherAge, nil);
		ff(bird, cannotResponseThis, nil);
		shift(bird, BirdModeA);
			ff(bird, modemethodC, nil);
		shift_back(bird);
		release(&(bird));


		Bird* bird2;
		bird2 = (Bird*)_new(_alloc("Bird", sizeof(Bird), Bird_load), Bird_init);
		debug_log("bird2 pointer %p\n", bird2);

		Bird* bird3;
		bird3 = (Bird*)_new(_alloc("Bird", sizeof(Bird), Bird_load), Bird_init);
		debug_log("bird2 pointer %p\n", bird3);

		Bird* bird31;
		bird31 = (Bird*)_new(_alloc("Bird", sizeof(Bird), Bird_load), Bird_init);
		debug_log("bird2 pointer %p\n", bird31);

		Bird* bird32;
		bird32 = (Bird*)_new(_alloc("Bird", sizeof(Bird), Bird_load), Bird_init);
		debug_log("bird2 pointer %p\n", bird32);

		Bird* bird33;
		bird33 = (Bird*)_new(_alloc("Bird", sizeof(Bird), Bird_load), Bird_init);
		debug_log("bird2 pointer %p\n", bird33);

		Bird* bird34;
		bird34 = (Bird*)_new(_alloc("Bird", sizeof(Bird), Bird_load), Bird_init);
		debug_log("bird2 pointer %p\n", bird34);


		Bird* bird4 = ff(new(Bird), initWithType, 4);
		ff(bird4, fly, nil);
		release(&bird4);


		BirdFather* father = new(BirdFather);
		ff(father, fly, nil);
		release(&father);


		Bird* birdcat = new_category(Bird, BirdCatA);
		ff(birdcat, catmethodA, nil);
		ff(birdcat, fly, nil);
		

		//clear(Bird);
		release(&birdcat);

		release(&bird3);

		release(&bird33);

		release(&bird31);

		release(&bird2);

		release(&bird32);

		release(&bird34);


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
		LOG_LEVEL = VERBOSE;
		monkc_runtime_check();
//		test_method_jumpping();

		test_object_life_cycle();

	mc_end();
	return 0;
}
