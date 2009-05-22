#include "gc.h"

void* GC_alloc(size_t nelem, size_t size){
//printf("%d %d\n", nelem, size);

return calloc(nelem, size);
}
