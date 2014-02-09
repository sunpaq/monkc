#include "Bird.h"

initer(Bird)
{
	obj->super = hew(BirdFather, 875971477);
	obj->type = 3;
	debug_logt("Bird", "[%p] init called\n", obj);
	return obj;
}

method(Bird, void, bye, xxx)
{
	recycle(obj->super);
	debug_logt(nameof(obj), "[%p] bye called\n", obj);
}

void funcA(Bird* obj, int arg1)
{
	debug_log("i am local function A\n");
}

protocol(Flyable, void, duckFly, xxx)
{
	debug_log("%s:Duck GuaGuaGua fly\n", nameof(cast(Bird*, obj)));
}

protocol(Flyable, void, chickenFly, xxx)
{
	debug_log("%s:Chicken JiJiJi fly\n", nameof(cast(Bird*, obj)));
}

method(Bird, Bird*, initWithType, int type)
{
	obj->type = type;
	return obj;
}

method(Bird, int, fatherAge, xxx)
{
	int fage = cast(BirdFather*, obj->super)->age;
	debug_logt(nameof(obj), "my father age is: %d\n", fage);
	return fage;
}

method(Bird, void, fly, xxx)
{
	debug_log("Bird[%p->%p]: default fly type %d\n", obj, obj->super, obj->type);
	funcA(obj, 100);
}

//
/*
method(Bird, fly1, xxx){}
method(Bird, fly2, xxx){}
method(Bird, fly3, xxx){}
method(Bird, fly4, xxx){}
method(Bird, fly5, xxx){}
method(Bird, fly6, xxx){}
method(Bird, fly7, xxx){}
method(Bird, fly8, xxx){}
method(Bird, fly9, xxx){}
method(Bird, fly10, xxx){}
method(Bird, fly11, xxx){}
method(Bird, fly12, xxx){}
method(Bird, fly13, xxx){}
method(Bird, fly14, xxx){}
method(Bird, fly15, xxx){}
method(Bird, fly16, xxx){}
method(Bird, fly17, xxx){}
method(Bird, fly18, xxx){}
method(Bird, fly19, xxx){}
method(Bird, fly20, xxx){}
method(Bird, fly21, xxx){}
method(Bird, fly22, xxx){}
method(Bird, fly23, xxx){}
method(Bird, fly24, xxx){}
method(Bird, fly25, xxx){}
method(Bird, fly26, xxx){}
method(Bird, fly27, xxx){}
method(Bird, fly28, xxx){}
method(Bird, fly29, xxx){}
method(Bird, fly30, xxx){}
method(Bird, fly31, xxx){}
method(Bird, fly32, xxx){}
method(Bird, fly33, xxx){}
method(Bird, fly34, xxx){}
method(Bird, fly35, xxx){}
method(Bird, fly36, xxx){}
method(Bird, fly37, xxx){}
method(Bird, fly38, xxx){}
method(Bird, fly39, xxx){}
method(Bird, fly40, xxx){}
method(Bird, fly41, xxx){}
method(Bird, fly42, xxx){}
method(Bird, fly43, xxx){}
method(Bird, fly44, xxx){}
method(Bird, fly45, xxx){}
method(Bird, fly46, xxx){}
method(Bird, fly47, xxx){}
method(Bird, fly48, xxx){}
method(Bird, fly49, xxx){}
method(Bird, fly50, xxx){}
*/


loader(Bird)
{
	//debug_logt(class->item->key, "load called\n");
	#include "Flyable.p"
	//just copy the declears in .h file and change 'method'->'binding'
	/*new() binding()*/
hinding(Bird, void, bye, 98030, xxx);
hinding(Bird, Bird*, initWithType, 1326160464, int type);
hinding(Bird, void, fly, 101491, xxx);
hinding(Bird, int, fatherAge, 522530307, xxx);

	/*
	hinding(Bird, fly1, xxx), 3694001;
	hinding(Bird, fly2, xxx), 3694001;
	hinding(Bird, fly3, xxx), 3694001;
	hinding(Bird, fly4, xxx), 3694001;
	hinding(Bird, fly5, xxx), 3694001;
	hinding(Bird, fly6, xxx), 3694001;
	hinding(Bird, fly7, xxx), 3694001;
	hinding(Bird, fly8, xxx), 3694001;
	hinding(Bird, fly9, xxx), 3694001;
	hinding(Bird, fly10, xxx), 3694001;
	hinding(Bird, fly11, xxx), 3694001;
	hinding(Bird, fly12, xxx), 3694001;
	hinding(Bird, fly13, xxx), 3694001;
	hinding(Bird, fly14, xxx), 3694001;
	hinding(Bird, fly15, xxx), 3694001;
	hinding(Bird, fly16, xxx), 3694001;
	hinding(Bird, fly17, xxx), 3694001;
	hinding(Bird, fly18, xxx), 3694001;
	hinding(Bird, fly19, xxx), 3694001;
	hinding(Bird, fly20, xxx), 3694001;
	hinding(Bird, fly21, xxx), 3694001;
	hinding(Bird, fly22, xxx), 3694001;
	hinding(Bird, fly23, xxx), 3694001;
	hinding(Bird, fly24, xxx), 3694001;
	hinding(Bird, fly25, xxx), 3694001;
	hinding(Bird, fly26, xxx), 3694001;
	hinding(Bird, fly27, xxx), 3694001;
	hinding(Bird, fly28, xxx), 3694001;
	hinding(Bird, fly29, xxx), 3694001;
	hinding(Bird, fly30, xxx), 3694001;
	hinding(Bird, fly31, xxx), 3694001;
	hinding(Bird, fly32, xxx), 3694001;
	hinding(Bird, fly33, xxx), 3694001;
	hinding(Bird, fly34, xxx), 3694001;
	hinding(Bird, fly35, xxx), 3694001;
	hinding(Bird, fly36, xxx), 3694001;
	hinding(Bird, fly37, xxx), 3694001;
	hinding(Bird, fly38, xxx), 3694001;
	hinding(Bird, fly39, xxx), 3694001;
	hinding(Bird, fly40, xxx), 3694001;
	hinding(Bird, fly41, xxx), 3694001;
	hinding(Bird, fly42, xxx), 3694001;
	hinding(Bird, fly43, xxx), 3694001;
	hinding(Bird, fly44, xxx), 3694001;
	hinding(Bird, fly45, xxx), 3694001;
	hinding(Bird, fly46, xxx), 3694001;
	hinding(Bird, fly47, xxx), 3694001;
	hinding(Bird, fly48, xxx), 3694001;
	hinding(Bird, fly49, xxx), 3694001;
	hinding(Bird, fly50, xxx), 3694001;
	*/
	debug_logt(nameofc(claz), "load called\n");
	return claz;
}


