#include "gc.h"

inline RefCount* GetHeader(void* rc){
    return ((RefCount*)rc)-1;
}

void* GC_alloc(size_t size){
	void* data = calloc(1, size + sizeof(RefCount));
	if (data == NULL)
		return NULL;

	RefCount* rc = (RefCount*) data;
	rc->refCount = 1;
	return data+sizeof(RefCount);
}

void* GC_realloc(void* ptr, size_t size){
	void* data;
	if (ptr == NULL)
		return GC_alloc(size);
		
	ptr -= sizeof(RefCount);
	data = realloc(ptr, size+sizeof(RefCount));
	// RefCount* rc = (RefCount*) data;
	// Do something with RefCount?
	return data+sizeof(RefCount);
}

void GC_updateRef(void** l, void* r){
    if (r != NULL)
        ++(GetHeader(r)->refCount);
//printf("%d\n",GetHeader(l)->refCount);
    GC_releaseRef(*l);
    *l = r;
}

void GC_releaseRef(void* pMem)
{
    if (pMem == NULL) return;
    RefCount *rc = GetHeader(pMem);
    --(rc->refCount);
    if (rc->refCount == 0)
    {
        //foreach(PVOID pChild in Get_Child(pHdr)) 
          //  GC_ReleaseRef(pChild);
	printf("freeing pointer\n");
        free(rc);
    }
}
