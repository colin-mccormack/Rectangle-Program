#ifndef LINKED_HASH_MAP
#define LINKED_HASH_MAP

typedef struct linkedHashMap *__restrict LinkedHashMapType;

typedef struct {

    LinkedHashMapType (*const new)(const int Capacity);

    int (*const getLength)(LinkedHashMapType);
    int (*const canStore) (LinkedHashMapT                                                                            ype);

    void (*const put)(LinkedHashMapType,char *__restrict StringKey, void *__restrict Instance);
    void (*const putAt)(LinkedHashMapType,char *__restrict StringKey, void *__restrict Instance, int Index);

    void *(*const getByKey)(LinkedHashMapType,const char *__restrict StringKey);
    void *(*const getByIndex)(LinkedHashMapType,const int Index);

    void (*const forEach)(LinkedHashMapType,void(*f)(const int Index, const char *__restrict StringKey, const void *__restrict Value));

    void (*const DeleteKey)(LinkedHashMapType,const char *__restrict StringKey);
    void (*const DeleteIndex)(LinkedHashMapType,const int Index);

    void (*const DeleteMap)(LinkedHashMapType);

} linkedHashMapClass;

extern const linkedHashMapClass *__restrict LinkedHashMap;

#endif