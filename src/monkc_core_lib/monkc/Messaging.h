
typedef struct mc_message_struct
{
	id object;
	void* addr;
}mc_message;

//write by asm
void* _push_jump(mc_message msg, ...);
void* _clean_jump1(mc_message msg, ...);
void* _clean_jump2(mc_message msg, ...);
void* _clean_jump3(mc_message msg, ...);
void* _clean_jump4(mc_message msg, ...);

//write by c
mc_message make_msg(id const this, const void* entry);
mc_message _self_response_to(const id obj, const char* methodname);
mc_message _self_response_to_h(const id obj, const char* methodname, unsigned hashval);
mc_message _response_to(id const obj, const char* methodname);
mc_message _response_to_h(id const obj, const char* methodname, unsigned hashval);

