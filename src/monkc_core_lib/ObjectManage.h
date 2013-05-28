
inline mc_block* alloc_mc_block();
mc_block* init_mc_block(mc_block* ablock, void* data);
mc_block* new_mc_block(void* data);
mc_block* new_block_withobject(mc_object* aobject);
mc_blockpool* new_mc_blockpool();
mc_object* new_mc_object(mc_class* const aclass);

void* _alloc(const char* classname, size_t size, loaderFP loader);
void _dealloc(mc_object* aobject);
void _clear(const char* classname, size_t size, loaderFP loader);


