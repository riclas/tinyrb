#include "gc.h"

inline RefCount* GetHeader(void* rc){
    return ((RefCount*)rc)-1;
}

void* GC_alloc(size_t size){
	RefCount* rc = (RefCount*)calloc(1, sizeof(RefCount) + size);
	if (rc == NULL)	return NULL;
	rc->refCount = 1;
	rc+=sizeof(RefCount);printf("%p\n",rc);
	return rc;
//return calloc(1, size);
}

void* GC_realloc(void* ptr, size_t size){
printf("%p realloc%d\n", ptr,size);
	if(ptr == NULL)
		return GC_alloc(size);
	void* aux = realloc(ptr-sizeof(RefCount), sizeof(RefCount) + size);
printf("realocou\n");
	aux+=sizeof(RefCount);
	return aux;
//return realloc(ptr, size);
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
