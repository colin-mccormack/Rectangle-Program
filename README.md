# Rectangle-Program

## Program Structure:

### Main File:
Runs the program using a handler function.
    
### IO.h
Header file containing IO functions, 
Interface between User and Program, 
Globally declared programs include, 
getResponse() => Get choice from user for menu selection,
showMenu() => Clear console then display menu,
ClearConsole() => Use regex code to clear all text from console


### Operations.h
Header file containing all functions created for specific operations,
Including Insert Rectangle, Insert Random Rectangle, Intersection Rectangle, and so on...
All those functions are abstracted away, the only visible functions are getFunctionToRun which returns a function pointer from a switch statement. The function pointer points to the appropriate void function that handles one operation at a time.
These operation functions have no parameters, but will sometimes call functions like area or random rectangle which are locally declared in the operation.c file. Another global function defined in operations.h is initialize() which creates a rectangle or statistic linked hash map list of the size MAX_RECTS.
Interesting : wrap(), pack(), unwrap(), unpack() functions are used to convert the void pointers used to store values in the linked hash map to the correct type (rectangle/statistics) in order for operations.c functions to be able to store/read values.

### Rectangle.h
Define structures for rectangles and rectangle statistics as set out in A04 parameters. 
Creation of structure rectangleClass which contains function pointer memebers that when called will exceute the method defined at the base function in rectangle.c. This structure is then set as a external constant, so the structure itself is restricted to one instance. The members can still be accesed as if structure instances had been initialized in any file that imports this module. In essence, we have created object oriented programming in c. 
The members defined in the rectangleClass structre, are methods to create an empty initallized rectangle/statistic instance using malloc and defulat values. Another method deletes values.

### Configurations.h
Define symbolic constants in accordace with program parameters.

### FileWriter.h
[Disclaimer : Not in use (Depricated from prpject parameters)] : This header defines the external methods for file operations in c using another external constant restriction on a structure for OOP.

### LinkedHashMap.h
Define methods for using the super efficent storage system. 

#### Structure
The rectangles are stored in a hash table by hashing the stringKey using the FNV Hash (non cryptographic algortihm) to determine their array index. Collisions are dealt with as they arise by indexing values at a location into a smaller array as needed. 

As each key is hashed and stored, it is also placed in a linked list. Each node of the hash map that contains the address of a rectangle or statistics, also contains : Last (Pointer to previous node in linked list), Next (Pointer to next node in linked list), and After (to deal with collisons as they arise with the hash map). The doubly linked list that connects these nodes is used to create an effienct sort by name, as well as an efficent search for an insertion point. The search functions take advantage of this by checking if they should start searching from the start, end, or cursor (last searched location).

#### Header
Using linkedHashMapClass restricted as an external constant to allow for OOP there are many methods avaibale for connecting to our 'database'. These include :
getLength => pointer returned by function delaration that takes in a linkedHashMap (structure that contains a linked hash map : it includes information like length, Cursor, MaxCapacity, all the nodes, as well as info on the nodes) value and returns the length of the total list,
canStore => Length < MaxCapacity,
put => Put node at location of hashed key,
putAt => Create new node and put in hash table as well as adding it to the linked list,
getByKey => Search by string key,
getByIndex => Search by numeric index (refrence to location in linked list),
forEach => Parameter includes function pointer so you can run a function over all values in the forEach functions scope (restricted scope based on parameter rectangles/statistics),
DeleteKey => Delete by key,
DeleteIndex => Delete by index,
DeleteMap => Delete an entire map (parameter of map type)

## Authors

- Abdul Mannan Syed, asyed24@ocdsb.ca
- Colin McMcormack, cmcco3@ocdsb.ca

12/05/2021
