#include "ClassA.h"

// Interface(ClassA)
// 	int i;
// 	int dcl(open)arg(tail);
// 	void dcl(onnew)arg(tail);
// 	void dcl(onbye)arg(tail);
// Interface(ClassA,tail)

Implement(ClassA)
	method int imp(open)arg(tail)
	body(
		printf("ClassA open\n");
	)

	method void imp(onnew)arg(tail)
	body(
		printf("ClassA hello\n");
	)

	method void imp(onbye)arg(tail)
	body(
		printf("ClassA byebye!\n");
	)
MEnd(ClassA)

Constructor(ClassA)Arg(tail)
Body(
	Bind(ClassA,onnew);
	Bind(ClassA,onbye);
	Bind(ClassA,open);
)CEnd(ClassA)


