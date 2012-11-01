# Mocha 
a set of C macro for OOP programming

![Mou icon](https://secure.gravatar.com/avatar/63f7c4c0a269ebaf049724a024bf01b4?s=420&d=https://a248.e.akamai.net/assets.github.com%2Fimages%2Fgravatars%2Fgravatar-user-420.png)

## Overview

**Mocha**, is a set of C macros for OOP programming use pure C, the aim of Mocha is to add less syntex to support OOP. The reason to make this is as C is a language so beautiful and so powerful. and the OOP is so handful and nature for a programer. i want to mix them with the less modification

## Syntax
**Mocha** use "MC" as the prefix.
#### declear interface - write in .h file

	MCInterface	( Classname )
		int var;
		method(void, name1, arg-list);
		method(void, name2, arg-list);
	MCInterfaceEnd( Classname, argument-list )
	
	
#### implement methods - write in .c file

	MCImplement( Classname )
	
		method_imp(void, name1, arg-list)body(
			this->var++;
		)
		
		method_imp(void, name2, arg-list)body(
			this->var--;
		)
		
	MCImplementEnd( Classname, argument-list )Body(
		Set(var,0);
		Bind(name1);
		Bind(name2);
	)

####keywords

---
1. MCInterface( Classname )
2. MCInterfaceEnd( Classname, arg-list )
3. MCImplement( Classname )
4. MCImplementEnd( Classname, arg-list )
5. Body( lines )
6. Set( var, value )
7. Bind( methodname )
8. method( ret, name, arg-list )
9. method_imp( ret, name, arg-list )
10. body( lines )
11. pull( type, var )
12. push( var )
13. xxx
14. nil
15. id
16. new( obj, Classname, arg-list )
17. call( obj, methodname, arg-list )
18. cast( newobj, Castclass, oldobj )

---
Total **18** keywords.[^1]


####protocol files
	ReferenceCount.protocol
	ReferenceCount.default

######the .protocol file:

	int ref_count;
	method(void,retain,xxx);
	method(void,release,xxx);
	method(void,bye,xxx);

it just list the methods and vars, which is just as decleard in the interface of a class.

the purpose of doing this is: we can use **#include "xx.protocol"** to import them direct in our class interface ! just like this:

	MCInterface	( Classname )
		#include "xx.protocol"
		int var;
		method(void, name1, arg-list);
		method(void, name2, arg-list);
	MCInterfaceEnd( Classname, argument-list )
	
the result of doing this is amazing ! we have already have some feature called: "interface" or "abstract class"
in other OOP language.

######the .default file:

	//for default behavior
	method_imp(void,retain,xxx)body(
		pull(int,ref_count);
			ref_count++;
		push(ref_count);
		printf("retain ref_count is %d\n",ref_count);
	)

	method_imp(void,release,xxx)body(
		pull(int,ref_count);
			ref_count--;
			if (ref_count==0){
				call(this,bye,nil);
			}
		printf("release ref_count is %d\n",ref_count);
	)

it just give implements of the methods in protocol file. as you can guess it also can be **#include "xx.default"**
to our MCImplement parts. we use this to simulate some **inherit** feature. and you also can only use .protocol
file, and let the class to implement its own methods. which we also heard as: **Polymorphism**


[^1]: the syntex is improving, maybe more/less keywords in the feature.

