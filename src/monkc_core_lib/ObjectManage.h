
mc_block* alloc_mc_block();
mc_block* init_mc_block(mc_block* ablock, void* data);
mc_block* new_mc_block(void* data);
void package_by_block(mc_block** ablock_p, mc_object** aobject_p);

mc_blockpool* new_mc_blockpool();

void _info(const char* classname, size_t size, loaderFP loader);
void _clear(const char* classname, size_t size, loaderFP loader);
id _alloc(const char* classname, size_t size, loaderFP loader);
void _dealloc(mc_object* aobject);





