/*

    LinkedHashMap.c

    "This is cool" ~ Colin
    "I'm impressed" ~ Edward Li
    "Nah I just copied python" ~ Abdul
    "This is crazy" ~ Mr. Devlin in future

    in a nutshell, LinkedHashMap is a hybrid data structure of
    LinkedLists and HashMaps.

    The pros:

    HashMaps allow us to index elements within an array with custom indices,
    with constant time complexity, in our case, the indices are Strings.

    Whereas LinkedHashMap's allow us to insert any element within an array with
    constant time complexity.

    The cons:

    HashMaps do not maintain insertion order, impossible to sort.

    Linked Lists are O(n) access, slower for accessing items.

    Solution:

    LinkedHashMaps, hashMaps allow us to index by string indices, and linked lists maintain
    insertion order.

    Solution to O(n) access in linked lists: Fast acces linked lists, a new modified linkedlists
    made by me (Abdul) to access any elements with O(n/2) time, whats even more cool is, its
    O(1) for linear search, and O(log(n)) for binary search.

    Now How it works:

    We are using a non-cryptographic hashing algorithm known as FNV Hash that is fast, simple, and
    most importantly it works. We are using it to generate indexes for indexing or accessing stored
    elements in the array.

    While FNV hash as a security vulnerability linked to it, because of which python migrated to sip hash,
    which is more complicated and slow, in our case, we are sticking with FNV because we are not really
    dealing with real life situation where we are dealing with exploiters.

    So back to the point, FNV hash requires a string and returns an output, we turn that output into
    a numeric index between zero and lenght of the hash map.

    We insert the provided value in that location, we also need to keep in mind that few unique strings
    generate same numeric index, causing collisions, such as "foo" and "x" map to same index.

    To deal with collisions, we create a small linked list that we can use to store values that map to
    same index, this might lead to O(n) time complexity in worst case, but It's pretty rare and hard to
    find strings with same index.

    So that's the hash map part, each value is basically stored in a node, and the hashmap holds pointers
    to the node, empty indexes hold NULL values indicating there are no nodes in that index. Each node
    is also node of a hashmap and a node of a linked list.

    In our case, we are using doubly Linked lists, so each node keeps reference of a node before and after it.

    So each node has fileds of:
        Value : Holds a pointer to a value
        Last  : Holds reference to the node before it (Linked Lists)
        After : Holds a reference to the node that comes after it, meaning, to handle collisions (hash map)
        Next  : Holds a reference to the node that comes next it (Linked Lists)


   A simple diagram

                       Head        LinkedList
                         0   Node 1
      HashMap Array ->   1
                         2   Node 3  ->  Node 4
                         3
                         4   Node 2
                         5

    See how HashMap doesnt maintain order? LinkedList's only job is to maintain that order.
    So linked list nodes will keep pointers to their next and previous nodes to maintain that order.

    Also, see how Node 3 and 4 are causing collisions (Same Index), node's after value is added to
    handle the collisions.


    Read Also:

    documentation for some modified features doesnt exist here, its because it's already
    present, and I dont want to re-state them here. You can find them here:https://github.com/MrMouse2405/Linked-List-C

 */


#include "LinkedHashMap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Configurations.h"

/*

    Node

*/

typedef struct node {

    // Value being stored
    void *__restrict Value;

    // The Key of the node
    char *__restrict StringKey;

    // Node before it (Linked Lists)
    struct node *__restrict Last;

    // Node that comes Next (Linked Lists)
    struct node *__restrict Next;

    // Node that comes after it, to handle collisions (Hash Map)
    struct node *__restrict After;

} Node;

/*

    Linked Hash Mao structure

    This is the structure that holds the references
    to the salient nodes (Head, Tail, Cursor) and
    holds some data about the linked hahs map

 */
struct linkedHashMap {

    // Head Node
    Node *__restrict Head;

    // Tail Node
    Node *__restrict Tail;

    // Cursor Node
    Node *__restrict NodeAtCursor;

    // Cursor Position
    int Cursor;

    // Current length of the map
    int Length;

    // Max length of the mao
    int MaxCapacity;

    // Deletion handler for garbage collection.
    void (*DeletionHandler)(void *__restrict);

    // Array for the hash map
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

    Creates a new LinkedHashMapStructure and assigns default values

*/

static LinkedHashMapType new(const int InitialCapacity, void (*DeletionHandler)(void *)) {

    LinkedHashMapType newLinkedHashMap = (LinkedHashMapType) malloc(
            sizeof(struct linkedHashMap) +
            sizeof(Node *) * InitialCapacity);

    if (!newLinkedHashMap) MALLOC_ERROR

    // Assign all indexes in the array as null
    for (int i = 0; i < InitialCapacity; i++)
        newLinkedHashMap->Array[i] = NULL;

    newLinkedHashMap->Head = NULL;
    newLinkedHashMap->Tail = NULL;
    newLinkedHashMap->NodeAtCursor = NULL;
    newLinkedHashMap->Cursor = 0;
    newLinkedHashMap->Length = 0;
    newLinkedHashMap->DeletionHandler = DeletionHandler;
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

    Documentation for this is here:
    https://github.com/MrMouse2405/Linked-List-C

    In simple words, this just transverses through the
    linked list and get's the node we want.

    Time complexity: O(1) to O(n/2)

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

    putAt

    adds a node at a provided index


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

/*

    Puts the node at the end

 */

static void put(LinkedHashMapType HashMap, char *__restrict StringKey, void *__restrict Instance) {
    putAt(HashMap, StringKey, Instance, HashMap->Length);
}

/*

  getByKey

   Hashes the string to gives us an index, and then returns the node
   that is found at the given index.

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

  Returns the found at the provided index.

*/

void *getByIndex(LinkedHashMapType HashMap, int Index) {
    return get(HashMap, Index)->Value;
}

/*

    Similar to C++ iterator

    calls the provided function on each element
    present in the map in order


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

    Removes the provided node.

 */

static void RemoveNode(LinkedHashMapType HashMap, Node *node) {

    // If there is a node before it
    if (node->Last) {

        // Set Previous node's next as this node's next (NULL if there is no next)
        node->Last->Next = node->Next;

        // if there is a node after this
        if (node->Next)
            // Set next node as this node's Last
            node->Next->Last = node->Last;

        // Else set tail to this node.
        else
            HashMap->Tail = node;

    }

    // If there is a next node and not last node (In case of head node)
    else if (node->Next) {
        node->Next->Last = NULL;
        HashMap->Head = node->Next;
    }

    /*

     Now the deletion part

     */

    // if there is a deletion handler, then use it to delete the value
    if (HashMap->DeletionHandler)
        HashMap->DeletionHandler(node->Value);
    // Else, just free it
    else
        free(node->Value);

    // Delete this node
    free(node);

    // Reset cursor
    HashMap->Cursor = 0;
    HashMap->NodeAtCursor = HashMap->Head;

    // Decrease the length
    HashMap->Length--;
}

/*

    Deletes the node indexed by the provided string.


 */

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

    DeL etes the node present at the index,

*/

void DeleteIndex(LinkedHashMapType HashMap, const int Index) {
    DeleteKey(HashMap, get(HashMap, Index)->StringKey);
}


/*

    Deketes the entire

 */


void DeleteMap(LinkedHashMapType HashMap) {

    // Get first node
    Node *curNode = HashMap->Head;

    void (*Delete)(void *) = (HashMap->DeletionHandler) ? HashMap->DeletionHandler : &free;

    // To store reference to next node
    Node *NextNode = NULL;

    while (curNode != NULL) {
        NextNode = curNode->Next;

        // GC Data Stored in the Node
        Delete(curNode->Value);

        // GC Node
        free(curNode);

        // Assign Node
        curNode = NextNode;

    }

    HashMap->Head = NULL;
    HashMap->Tail = NULL;
    HashMap->NodeAtCursor = NULL;

    free(HashMap->Array);

    free(HashMap);
}


/*

    Abstracting and encapsulating all functions into a class.

    Anyways, this took me 2 days to write.


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
