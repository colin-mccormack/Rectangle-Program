#include "LinkedHashMap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Configurations.h"

#define HEAD 1
#define TAIL 2
#define CURSOR 0

/*

    Linked Hash Map

*/

typedef struct node {

    void *__restrict Value;
    char *__restrict StringKey;
    struct node *__restrict Last;
    struct node *__restrict Next;
    struct node *__restrict After;

} Node;

struct linkedHashMap {

    Node *__restrict Head;
    Node *__restrict Tail;
    Node *__restrict NodeAtCursor;

    int Cursor;

    int Length;
    int MaxCapacity;
    Node *Array[];

};


/*

    Hashing Algorithm: FNV Hash


    Returns 64-bit FNV-1a hash for key (NUL-terminated). See description:
    https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function

 */

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

static unsigned long long hash_key(const char *__restrict key) {
    unsigned long long hash = FNV_OFFSET;
    for (const char *p = key; *p; p++) {
        hash ^= (unsigned long long int) (unsigned char) (*p);
        hash *= FNV_PRIME;
    }
    return hash;
}

/*

    Hashes to the following Index between 0 and n
    and returns that hashed index

 */

static unsigned long long getHashIndex(const char *__restrict Key, int n) {
    return (unsigned long long) (hash_key(Key) & (unsigned long long) (n - 1));
}

/*

    LinkedHashMap new()


*/

static LinkedHashMapType new(const int InitialCapacity) {

    LinkedHashMapType newLinkedHashMap = (LinkedHashMapType) malloc(
            sizeof(struct linkedHashMap) +
            sizeof(Node *) * InitialCapacity);

    if (!newLinkedHashMap) MALLOC_ERROR

    for (int i = 0; i < InitialCapacity; i++)
        newLinkedHashMap->Array[i] = NULL;

    newLinkedHashMap->Head = NULL;
    newLinkedHashMap->Tail = NULL;
    newLinkedHashMap->NodeAtCursor = NULL;
    newLinkedHashMap->Cursor = 0;
    newLinkedHashMap->Length = 0;
    newLinkedHashMap->MaxCapacity = InitialCapacity;


    return newLinkedHashMap;
}

/*

    Creating new Node

*/

static Node *newNode() {

    Node *newNode = (Node *) malloc(sizeof(Node));

    if (!newNode) MALLOC_ERROR

    newNode->Value = NULL;
    newNode->StringKey = NULL;
    newNode->Last = NULL;
    newNode->Next = NULL;
    newNode->After = NULL;

    return newNode;
}

/*

    getLength, basically, gets the length of the list


    can store, returns true if we can store more stuff.
 */

static int getLength(LinkedHashMapType Map) {
    return Map->Length;
}

static int canStore(LinkedHashMapType Map) {
    return Map->Length < Map->MaxCapacity;
}

/*

    getNode


 */
static Node *get(LinkedHashMapType list, int Index) {

    if (Index < 0 || Index > list->Length) {
        printf("INDEX OUT OF BOUNDS ERROR!!!! INDEX: %i", Index);
        exit(-1);
    }


    if (Index == 0)
        return list->Head;


    if (Index == list->Length - 1)
        return list->Tail;

    if (Index == list->Cursor)
        return list->NodeAtCursor;

    /*
    Calculating which is the best way to access the values.
    In simple words, we are calculating which way will require
    the least amount of hops to access our node:
     - Will it take less hops if we start from NodeAtCursor?
     - Will it take less hops if we start from Head Node?
     - Will it take less hops if we start from Tail Node?
 */

    int DIRECTION = 0;
    Node *curNode;


    // Calculating The Distance
    int DistanceFromHead = Index;
    int DistanceFromTail = (list->Length - 1) - Index;
    int DistanceFromCursor = abs(list->Cursor - Index);


    // If Closest Path Is From Head
    // <= to handle stalemate situationsWhat if DistanceFromHead == DistanceFromTail?.
    if (DistanceFromHead <= DistanceFromCursor && DistanceFromHead <= DistanceFromTail) {

        curNode = list->Head;

        for (int i = 0; i < DistanceFromHead; i++)
            curNode = curNode->Next;

        list->NodeAtCursor = curNode;
        list->Cursor = DistanceFromHead;

        return curNode;

    }
        // If Closest Path Is From Tail (We have checked If DistanceFromHead is Greater than DistanceFrom Tail,
        // it's not right? It means it bigger from DistanceFromTail so we didn't check DistanceFromTail < DistanceFromCursor)
    else if (DistanceFromTail < DistanceFromCursor) {

        curNode = list->Tail;

        for (int i = 0; i < DistanceFromTail; i++)
            curNode = curNode->Last;

        list->NodeAtCursor = curNode;
        list->Cursor = (list->Length - 1) - DistanceFromTail;

        return curNode;
    }

    //Well then, looks like the closest distance is from Cursor
    curNode = list->NodeAtCursor;

    if (list->Cursor < Index) {

        for (int i = 0; i < DistanceFromCursor; i++)
            curNode = curNode->Next;

        list->Cursor += DistanceFromCursor;
        list->NodeAtCursor = curNode;

        return curNode;
    }


    for (int i = 0; i < DistanceFromCursor; i++)
        curNode = curNode->Last;

    list->Cursor -= DistanceFromCursor;
    list->NodeAtCursor = curNode;

    return curNode;
}


/*

    put


*/

static void putAt(LinkedHashMapType HashMap, char *__restrict StringKey, void *__restrict Instance, int Index) {


    /*

        Creating a Node for storing.

    */

    Node *node = newNode();
    node->StringKey = StringKey;
    node->Value = Instance;

    /*

        Hash Map Part


        Hashing String and getting an index from it.
        Indexing and getting the reference to target node pointer in the array

     */

    Node **targetNode = &HashMap->Array[getHashIndex(StringKey, HashMap->MaxCapacity)];

    if (*targetNode) {

        while ((*targetNode)->After != NULL)
            targetNode = (Node **) (*targetNode)->After;

        (*targetNode)->After = node;

    } else {
        (*targetNode) = node;
    }

    /*

        Linked List Part

     */

    Node *PreviousNode = NULL;
    Node *LastNode = NULL;

    // If the insertion is in head
    if (Index == 0) {


        // If the length is zero, or if there are no nodes
        if (HashMap->Length == 0) {
            HashMap->Head = node;
            HashMap->Tail = node;

        } else {

            PreviousNode = HashMap->Head;

            HashMap->Head = node;
            node->Next = PreviousNode;
            PreviousNode->Last = node;

            HashMap->Cursor++;
        }

    }
        // If insertion is in tail
    else if (Index == HashMap->Length) {


        PreviousNode = HashMap->Tail;
        HashMap->Tail = node;

        PreviousNode->Next = node;
        node->Last = PreviousNode;

        HashMap->Cursor--;
    } else {


        PreviousNode = get(HashMap, Index);
        LastNode = get(HashMap, Index - 1);

        PreviousNode->Last = node;
        LastNode->Next = node;

        node->Next = PreviousNode;
        node->Last = LastNode;

        // Updating Cursor
        if (Index > HashMap->Cursor)
            HashMap->Cursor--;
        else if (Index < HashMap->Cursor)
            HashMap->Cursor++;
        else
            HashMap->NodeAtCursor = node;


    }


    //Incrementing List Size
    HashMap->Length++;

}

static void put(LinkedHashMapType HashMap, char *__restrict StringKey, void *__restrict Instance) {
    putAt(HashMap, StringKey, Instance, HashMap->Length);
}

/*

 getByKey

*/

static void *getByKey(LinkedHashMapType HashMap, const char *__restrict StringKey) {

    const Node *node = HashMap->Array[getHashIndex(StringKey, HashMap->MaxCapacity)];

    if (!node)
        return NULL;

    // If Node->After, then check for all nodes
    if (node->After) {
        while (node->After) {
            if (strcmp(StringKey, node->StringKey) == 0)
                return node->Value;

            node = node->After;
        }
        return NULL;
    }

    // If there is only one node, check for collisions
    if (strcmp(StringKey, node->StringKey) != 0)
        return NULL;

    return node->Value;
}


/*


 getByIndex

*/

void *getByIndex(LinkedHashMapType HashMap, int Index) {
    return get(HashMap, Index)->Value;
}

/*




 */

void forEach(LinkedHashMapType HashMap,
             void(*f)(const int Index, const char *__restrict Key, const void *__restrict Value)) {

    Node *curNode = HashMap->Head;

    for (int i = 0; i < HashMap->Length; i++) {
        f(i, curNode->StringKey, curNode->Value);
        curNode = curNode->Next;
    }

}

/*



 */

static void RemoveNode(LinkedHashMapType HashMap, Node *node) {
    if (node->Last) {
        node->Last->Next = node->Next;
        if (node->Next) {
            node->Next->Last = node->Last;
        } else {
            HashMap->Tail = node;
        }
    } else if (node->Next) {
        node->Next->Last = NULL;
        HashMap->Head = node->Next;
    }
    free(node);
    HashMap->Cursor = 0;
    HashMap->NodeAtCursor = HashMap->Head;
    HashMap->Length--;
}


void DeleteKey(LinkedHashMapType HashMap, const char *__restrict StringKey) {

    int Index = (int) getHashIndex(StringKey, HashMap->MaxCapacity);

    Node *node = HashMap->Array[Index];
    Node *nodeBefore = NULL;
    Node *nodeAfter = NULL;

    if (!node)
        return;

    // If Node->After, then check for all nodes
    if (node->After) {
        while (node->After) {
            if (strcmp(StringKey, node->StringKey) == 0) {
                if (nodeBefore && nodeAfter)
                    nodeBefore->After = nodeAfter;
                RemoveNode(HashMap, node);
                break;
            }

            nodeBefore = node;
            node = node->After;
            if (node) nodeAfter = node->After;

        }
    } else {
        // If there is only one node, check for collisions
        if (strcmp(StringKey, node->StringKey) == 0) {
            if (node->After) HashMap->Array[Index] = node->After;
            RemoveNode(HashMap, node);
        }
    }
}

/*


*/

void DeleteIndex(LinkedHashMapType HashMap, const int Index) {
    DeleteKey(HashMap, get(HashMap, Index)->StringKey);
}


/*



 */

void DeleteMap(LinkedHashMapType HashMap) {

    // Get first node
    Node *curNode = HashMap->Head;

    // To store reference to next node
    Node *NextNode = NULL;

    while (curNode != NULL) {
        NextNode = curNode->Next;

        // GC Data Stored in the Node
        free(curNode->Value);

        // GC Node
        free(curNode);

        // Assign Node
        curNode = NextNode;

    }

    HashMap->Head = NULL;
    HashMap->Tail = NULL;
    HashMap->NodeAtCursor = NULL;

    free(HashMap);
}


/*

    Abstracting and converting functions to methods.

 */

static const linkedHashMapClass LHM = {
        &new,
        &getLength,
        &canStore,
        &put,
        &putAt,
        &getByKey,
        &getByIndex,
        &forEach,
        &DeleteKey,
        &DeleteIndex,
        &DeleteMap,
};

const linkedHashMapClass *__restrict LinkedHashMap = &LHM;
