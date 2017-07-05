#include "monkc.h"

class(Monkey, MCObject,
	MCStaticString name;
	MCInt age;
);

method(Monkey, void, info, voida);
method(Monkey, void, showname, voida);
method(Monkey, void, showage, voida);