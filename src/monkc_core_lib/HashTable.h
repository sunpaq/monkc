



//apis
inline unsigned get_tablesize(const unsigned level);
unsigned hash(const char *s);
mc_hashitem* new_item_withclass(const char* key, mc_class* aclass);
mc_hashitem* new_item_withclass_h(const char* key, mc_class* aclass, unsigned hashval);
mc_hashitem* new_item(const char* key, void* value);
mc_hashitem* new_item_h(const char* key, void* value, const unsigned hashval);
mc_hashtable* new_table(const unsigned initlevel);

unsigned set_item(mc_hashtable** const table_p,
	mc_hashitem* const item, 
	BOOL isOverride, BOOL isFreeValue);
mc_hashitem* get_item_bykey(const mc_hashtable** table_p, const char* key);
mc_hashitem* get_item_byhash(const mc_hashtable** table_p, const unsigned hashval, const char* refkey);
mc_hashitem* get_item_byindex(const mc_hashtable** table_p, const unsigned index);











