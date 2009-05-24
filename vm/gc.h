#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int refCount;
} GCrefCount;

void* GC_alloc(size_t size);
void* GC_realloc(void* ptr, size_t size);
void GC_updateRef(void* l, void* r);
void GC_releaseRef(void* pMem);
