#include "gc.h"

inline GCrefCount* GetHeader(void* rc){
    return ((GCrefCount*)rc)-1;
}

void* GC_alloc(size_t size){
	void* data = calloc(1, size + sizeof(GCrefCount));
	if (data == NULL)
		return NULL;

	((GCrefCount*) data)->refCount = 1;//printf("%p alloc\n",data + sizeof(GCrefCount));
	return data + sizeof(GCrefCount);
}

void* GC_realloc(void* ptr, size_t size){
	void* data;
	if (ptr == NULL)
		return GC_alloc(size);
		
	ptr -= sizeof(GCrefCount);
	data = realloc(ptr, size + sizeof(GCrefCount));
	return data + sizeof(GCrefCount);
}

void GC_updateRef(void* l, void* r){
    if (r != NULL){
        ++(GetHeader(r)->refCount);
//printf("%d\n",GetHeader(r)->refCount);
}
printf("%p %p\n",l,r);
    GC_releaseRef(l);
    l = r;
}

void GC_releaseRef(void* pMem){
    if (pMem == NULL) return;
    GCrefCount *rc = GetHeader(pMem);
    --(rc->refCount);
    if (rc->refCount == 0)
    {
	//khiter_t k;
	//khash_t(OBJ) *h = pMem->ivars;
        //for (k = kh_begin(h); k != kh_end(h); ++k){
	//	if (kh_exist(h, k)){
	//		OBJ v = kh_value(h, k);
	//		if(!TR_IMMEDIATE(v))
	//			GC_releaseRef(v);
	//	}
	//}
	printf("freeing pointer\n");
        free(rc);
    }
}
