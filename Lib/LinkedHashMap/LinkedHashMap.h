#ifndef LINKED_HASH_MAP
#define LINKED_HASH_MAP

typedef struct {
    const int *__restrict Index;

} LinkedHashMap;

typedef struct {
    void   (*const Initialize) (const int Capacity);
    int    (*const getLength)  ();
    void   (*const put)        (const char *__restrict StringKey, void *Instance);
    void * (*const getByKey)   (const char *__restrict StringKey);
    void * (*const getByIndex) (const int Index);
    void   (*const forEach)    (void(*f)(const int Index,const char *__restrict StringKey,const void*__restrict Value));
    void   (*const Delete)();
} linkedHashMap;

extern const linkedHashMap *__restrict LinkedHashMapClass;

#endif