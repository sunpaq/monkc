
mc_block* alloc_mc_block();
mc_block* init_mc_block(mc_block* ablock, void* data);
mc_block* new_mc_block(void* data);
void package_by_block(mc_block* ablock, mc_object* aobject);

mc_blockpool* new_mc_blockpool();

void _info(const char* classname, size_t size, loaderFP loader);
void _clear(const char* classname, size_t size, loaderFP loader);
id _alloc(const char* classname, size_t size, loaderFP loader);
void _info_h(const char* classname, size_t size, loaderFP loader, unsigned hashval);
void _clear_h(const char* classname, size_t size, loaderFP loader, unsigned hashval);
id _alloc_h(const char* classname, size_t size, loaderFP loader, unsigned hashval);
void _dealloc(mc_object* aobject, int is_recycle);

#define NO_NODE(bpool) (bpool->tail==nil)
#define ONE_NODE(bpool) (bpool->tail->next==bpool->tail) 
#define TWO_NODE(bpool) (bpool->tail->next->next==bpool->tail)

void pushToTail(mc_blockpool* bpool, mc_block* ablock);
mc_block* getFromHead(mc_blockpool* bpool);
void empty(mc_blockpool* bpool);
int count(mc_blockpool* bpool);
int cut(mc_blockpool* bpool, mc_block* ablock, mc_block** result);






