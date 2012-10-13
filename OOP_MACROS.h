//something strange with _ in connect the para
//so we use ## to connect
//usually ## is used to connect the two para

//class define
#define Class(name) typedef struct _##name{
#define Implement(name) }name;name name##_obj;
#define Constructor(name) name* name##_new(
#define Arg() 
#define End() )
#define Body(body) {body}
#define Finish(name) 
//Global Macros
#define New(name) name##_new( 
#define Bind(class,name) class##_obj.name=name;
#define Var(class,name) class##_obj.name
#define ReturnInstance(name) \
	name* instance = (name*)malloc(sizeof(name##_obj));\
	memcpy(instance, &name##_obj, sizeof(name##_obj));\
	return instance;
//methods
#define dcl(name) (*name)(void* self
#define	imp(name) name(void* self
#define arg() ,
#define end() )
#define body(body) {CLASS* this = (CLASS*)self;body}
#define call(obj,name) obj->name(obj
//main loop
#define Main(body) int main(int argc, char* argv[]){body}