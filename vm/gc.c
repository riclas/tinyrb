#include "tr.h"

void* GC_alloc(size_t size){
	void* data = calloc(1, size);
	if (data == NULL)
		return NULL;

        //start refCount of a new object
	TR_COBJECT(data)->refCount = 1;
	return data;
}

void GC_updateRef(OBJ *l, OBJ r){
    if(*l == r) return;

    //if it is not an IMMEDIATE it's an object to refCount
    if (!TR_IMMEDIATE(r))
        TR_COBJECT(r)->refCount++;

    //if l was assigned we need to decref it
    GC_releaseRef(*l);
    *l = r;
}

void GC_releaseRef(OBJ o){
    //if the object has not yet been initialized
    //(this check can probably improve, it's hackish right now)
    if (TR_COBJECT(o)->refCount < 0) return;

    TR_COBJECT(o)->refCount--;
    if (TR_COBJECT(o)->refCount == 0)
    {
        //if we are going to free the object we need to
        //decref the instance references
	khiter_t k;
	khash_t(OBJ) *h = TR_COBJECT(o)->ivars;
        for (k = kh_begin(h); k != kh_end(h); ++k){
		if (kh_exist(h, k)){
			OBJ v = kh_value(h, k);
			if(!TR_IMMEDIATE(v))
				GC_releaseRef(v);
		}
	}
        //finally free the object
        free(TR_COBJECT(o));
    }
}
