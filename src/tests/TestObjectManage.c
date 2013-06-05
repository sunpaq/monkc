#include "TestObjectManage.h"

static mc_blockpool* pool;
static mc_block *b1, *b2, *b3, *b4, *b5, *b6, *tb;
static mc_object *o1, *o2, *o3, *o4, *o5, *o6;
void test_bp_init()
{
	pool=new_mc_blockpool();
	b1=new_mc_block(nil);
	b2=new_mc_block(nil);
	b3=new_mc_block(nil);
	b4=new_mc_block(nil);
	b5=new_mc_block(nil);
	b6=new_mc_block(nil);
	tb=nil;
	
	o1=(id)malloc(sizeof(mc_object));
	o2=(id)malloc(sizeof(mc_object));
	o3=(id)malloc(sizeof(mc_object));
	o4=(id)malloc(sizeof(mc_object));
	o5=(id)malloc(sizeof(mc_object));
	o6=(id)malloc(sizeof(mc_object));
	package_by_block(b1, o1);
	package_by_block(b2, o2);
	package_by_block(b3, o3);
	package_by_block(b4, o4);
	package_by_block(b5, o5);
	package_by_block(b6, o6);
}

void test_bp_end()
{
	empty(pool);
	runtime_log("test_bp_end pool count should be 0:%d\n", count(pool));
}

void test_getFromHead()
{
	test_bp_init();
	
	pushToTail(pool, b1);
	pushToTail(pool, b2);
	pushToTail(pool, b3);
	pushToTail(pool, b4);

	runtime_log("pool count should be 4:%d\n", count(pool));
	getFromHead(pool);
	runtime_log("pool count should be 3:%d\n", count(pool));
	getFromHead(pool);
	runtime_log("pool count should be 2:%d\n", count(pool));	
	getFromHead(pool);
	runtime_log("pool count should be 1:%d\n", count(pool));
	getFromHead(pool);
	runtime_log("pool count should be 0:%d\n", count(pool));

	test_bp_end();
}

void test_cut_asc()
{
	test_bp_init();

	pushToTail(pool, b1);
	pushToTail(pool, b2);
	pushToTail(pool, b3);
	pushToTail(pool, b4);
	pushToTail(pool, b5);
	pushToTail(pool, b6);

	runtime_log("pool count should be 6:%d\n", count(pool));
	cut(pool, b1, &tb);
	runtime_log("pool count should be 5:%d\n", count(pool));
	cut(pool, b2, &tb);
	runtime_log("pool count should be 4:%d\n", count(pool));	
	cut(pool, b3, &tb);
	runtime_log("pool count should be 3:%d\n", count(pool));
	cut(pool, b4, &tb);
	runtime_log("pool count should be 2:%d\n", count(pool));
	cut(pool, b5, &tb);
	runtime_log("pool count should be 1:%d\n", count(pool));
	cut(pool, b6, &tb);
	runtime_log("pool count should be 0:%d\n", count(pool));

	test_bp_end();
}

void test_cut_dsc()
{
	test_bp_init();

	pushToTail(pool, b1);
	pushToTail(pool, b2);
	pushToTail(pool, b3);
	pushToTail(pool, b4);

	runtime_log("pool count should be 4:%d\n", count(pool));
	cut(pool, b4, &tb);
	runtime_log("pool count should be 3:%d\n", count(pool));
	cut(pool, b3, &tb);
	runtime_log("pool count should be 2:%d\n", count(pool));	
	cut(pool, b2, &tb);
	runtime_log("pool count should be 1:%d\n", count(pool));
	cut(pool, b1, &tb);
	runtime_log("pool count should be 0:%d\n", count(pool));

	test_bp_end();
}

void test_cut_objasc()
{
	test_bp_init();

	pushToTail(pool, b1);
	pushToTail(pool, b2);
	pushToTail(pool, b3);
	pushToTail(pool, b4);
	pushToTail(pool, b5);
	pushToTail(pool, b6);


	runtime_log("pool count should be 6:%d\n", count(pool));
	cut(pool, deref(o1).block, &tb);
	runtime_log("pool count should be 5:%d\n", count(pool));
	cut(pool, deref(o2).block, &tb);
	runtime_log("pool count should be 4:%d\n", count(pool));	
	cut(pool, deref(o3).block, &tb);
	runtime_log("pool count should be 3:%d\n", count(pool));
	cut(pool, deref(o4).block, &tb);
	runtime_log("pool count should be 2:%d\n", count(pool));
	cut(pool, deref(o5).block, &tb);
	runtime_log("pool count should be 1:%d\n", count(pool));
	cut(pool, deref(o6).block, &tb);
	runtime_log("pool count should be 0:%d\n", count(pool));


	test_bp_end();

}

void test_cut_objdsc()
{
	test_bp_init();

	pushToTail(pool, b1);
	pushToTail(pool, b2);
	pushToTail(pool, b3);
	pushToTail(pool, b4);
	pushToTail(pool, b5);
	pushToTail(pool, b6);


	runtime_log("pool count should be 6:%d\n", count(pool));
	cut(pool, deref(o6).block, &tb);
	runtime_log("pool count should be 5:%d\n", count(pool));
	cut(pool, deref(o5).block, &tb);
	runtime_log("pool count should be 4:%d\n", count(pool));	
	cut(pool, deref(o4).block, &tb);
	runtime_log("pool count should be 3:%d\n", count(pool));
	cut(pool, deref(o3).block, &tb);
	runtime_log("pool count should be 2:%d\n", count(pool));
	cut(pool, deref(o2).block, &tb);
	runtime_log("pool count should be 1:%d\n", count(pool));
	cut(pool, deref(o1).block, &tb);
	runtime_log("pool count should be 0:%d\n", count(pool));


	test_bp_end();

}

void test_blockpool()
{
	test_getFromHead();
	test_cut_asc();//bug
	test_cut_dsc();
	test_cut_objasc();
}