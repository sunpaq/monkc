#include "ObjectLifeCycle.h"


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