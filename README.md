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

[^1]: the syntex is improving, maybe more/less keywords in the feature.