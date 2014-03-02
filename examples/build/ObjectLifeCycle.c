#include "ObjectLifeCycle.h"


void test_object_life_cycle()
{
		Bird* bird = hew(Bird, 2070745);
		fh(bird,fly, 101491, nil);
		fh(bird,flyhigh, 3537959061, nil);
		ff(bird, singAsong, "a song from child");
		fh(bird,fatherAge, 522530307, nil);
		//fh(bird,cannotResponseThis, 2144997154, nil);
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