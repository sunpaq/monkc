



//apis
unsigned get_tablesize(const unsigned level);
unsigned hash(const char *s);
void package_by_item(mc_hashitem** aitem_p, mc_class** aclass_p);
mc_hashitem* new_item(const char* key, void* value);
mc_hashitem* new_item_h(const char* key, void* value, const unsigned hashval);
mc_hashtable* new_table(const unsigned initlevel);

unsigned set_item(mc_hashtable** const table_p,
	mc_hashitem* const item, 
	int isOverride, int isFreeValue);
mc_hashitem* get_item_bykey(const mc_hashtable** table_p, const char* key);
mc_hashitem* get_item_byhash(const mc_hashtable** table_p, const unsigned hashval, const char* refkey);
mc_hashitem* get_item_byindex(const mc_hashtable** table_p, const unsigned index);











