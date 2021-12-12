/*

    LinkedHashMap.h

    This is a special hybrid data structure that allows us to index
    values by string keys.

    This data structure combines Linked Lists and HashMaps to
    allow users to index values with string keys while also allowing
    them to maintain insertion / sorting order

 */


#ifndef LINKED_HASH_MAP
#define LINKED_HASH_MAP

/*

    LinkedHashMapType

    The variable type for the LinkedHashMap

*/
typedef struct linkedHashMap *__restrict LinkedHashMapType;


/*

    LinkedHashMap structure

    This Structure encapsulates all the functions you might
    need to operate on Linked Hash Maps.

    Example usage:
    LinkedHashMap->new()

 */

typedef struct {

    /*

        LinkedHashMap new(int Capacity,void(*DeletionHandler(void*))

        Creates a new LinkedHashMap amd returns a pointer to it.

        params:
            Capacity, initial capacity to start with.
            DeletionHandler: Function that will be called upon garbage collecting a value

        Usage:
            LinkedHashMap->new()
     */

    LinkedHashMapType (*const new)(const int Capacity, void (*DeletionHandler)(void *));

    /*

        int getLength(LinkedHashMapType)

        Returns the length of the hash map

        params:
            LinkedHashMapType

        Usage:
            LinkedHashMap->getLength()
     */

    int (*const getLength)(LinkedHashMapType);


    /*

        int canStore(LinkedHashMapType)

        Returns true if there is space left.

        params:
            LinkedHashMapType

        Usage:
            LinkedHashMap->getLength()
     */



    int (*const canStore)(LinkedHashMapType);

    void (*const put)(LinkedHashMapType, char *__restrict StringKey, void *__restrict Instance);

    void (*const putAt)(LinkedHashMapType, char *__restrict StringKey, void *__restrict Instance, int Index);

    void *(*const getByKey)(LinkedHashMapType, const char *__restrict StringKey);

    void *(*const getByIndex)(LinkedHashMapType, const int Index);

    void (*const forEach)(LinkedHashMapType,
                          void(*f)(const int Index, const char *__restrict StringKey, const void *__restrict Value));

    void (*const DeleteKey)(LinkedHashMapType, const char *__restrict StringKey);

    void (*const DeleteIndex)(LinkedHashMapType, const int Index);

    void (*const DeleteMap)(LinkedHashMapType);

} linkedHashMapClass;

extern const linkedHashMapClass *__restrict LinkedHashMap;

#endif