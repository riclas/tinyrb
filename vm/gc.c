#include "tr.h"

OBJ GC_alloc(void* type){
	OBJ data = calloc(1, sizeof(type));
	if (data == NULL)
		return NULL;

	data->refCount = 1;
	return data;
}

void GC_updateRef(OBJ l, OBJ r){
    if (r != TR_NIL)
        r->refCount++;

    GC_releaseRef(l);
    l = r;
}

void GC_releaseRef(OBJ o){
    if (o == TR_NIL) return;
    
    o->refCount--;
    if (o->refCount == 0)
    {
	//khiter_t k;
	//khash_t(OBJ) *h = o->ivars;
        //for (k = kh_begin(h); k != kh_end(h); ++k){
	//	if (kh_exist(h, k)){
	//		OBJ v = kh_value(h, k);
	//		if(!TR_IMMEDIATE(v))
	//			GC_releaseRef(v);
	//	}
	//}
printf("free pointer\n");
       free(o);
    }
}
