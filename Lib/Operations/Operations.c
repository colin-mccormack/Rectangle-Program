#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Operations.h"
#include "../Rectangle/Rectangle.h"
#include "../LinkedHashMap/LinkedHashMap.h"
#include "../IO/FileWriter.h"

#define DISPLAY_INVALID_OPTION_ERROR printf("No working case. Retry.\n");
#define DISPLAY_INVALID_RECT_ERROR printf("Incorrect rectangle parameters. Retry.\n");

void UserRect();

void RandomRect();

void FindRect();

void DeleteRect();

void AllCalculations();

void DisplayRectangles();

void DisplayStats();

void ClearConsole();

void QuitProgram();

void invalidCase();

function *getFunctionToRun(int Choice) {

    switch (Choice) {

        // If users wants to generate a random rectangle
        case OP_INSERT_USER_RECT:
            return &UserRect;

            // If users wants the program to store a rectangle
        case OP_INSERT_RD_RECT:
            return &RandomRect;

            // If users wants to find rectangle
        case OP_FIND_RECT:
            return &FindRect;

            // If user wants to delete rectangle by name
        case OP_DELETE_RECT:
            return &DeleteRect;

            // If user wants to find union of two rectangles
        case OP_COMPUTE:
            return &AllCalculations;

            // If user wants to find intersection of two rectangles
        case OP_OUTPUT_RECT:
            return &DisplayRectangles;

            // If user wants to display all rectangles
        case OP_OUTPUT_STATS:
            return &DisplayStats;

            // If user wants to close the program
        case OP_QUIT_PROGRAM:
            QuitProgram();
            return NULL;

            // This is an Easter egg hidden, this clears the console,
            // this was added by us to see if you would suffer through this much code reading.
        case 256:
            return &ClearConsole;

            // If users gives us an invalid input.
        default:
            return &invalidCase;

    }
}

/*

    Caching Rectangles and Rectangle Statistics

 */

static LinkedHashMapType RectanglesList = NULL;
static LinkedHashMapType StatisticsList = NULL;

void Initialize() {
    RectanglesList = LinkedHashMap->new(MAX_RECTS, (void (*)(void *)) RectangleClass->Delete);
    StatisticsList = LinkedHashMap->new(MAX_RECTS, (void (*)(void *)) RectangleClass->DeleteStats);
}

/*

    Wrapper functions to storing and reading from hash maps.

 */

static inline void *__restrict wrap(const Rectangle *__restrict R) {
    return (void *) R;
}

static inline Rectangle *__restrict unwrap(const void *__restrict R) {
    return (Rectangle *) R;
}

static inline void *__restrict pack(const RectangleStatistics *__restrict RS) {
    return (void *) RS;
}

static inline RectangleStatistics *__restrict unpack(const void *__restrict RS) {
    return (RectangleStatistics *) RS;
}

/*

    pop()

 */

static void *__restrict pop(LinkedHashMapType HashMap, const int Index) {
    void *__restrict Value = LinkedHashMap->getByIndex(HashMap, Index);
    LinkedHashMap->DeleteIndex(HashMap, Index);
    return Value;
}


/*

    Compute area

*/

int area(int length, int width) {
    return length * width;
}

/*

    Compute perimeter

*/

int perimeter(int length, int width) {
    //added brackets for visual representation
    return (2 * length) + (2 * width);
}

/*

   Insert user rectangle

 */

static void InsertUserRect(Rectangle *r) {

    do {

        printf("Enter the top coordinate : ");
        scanf("%d", &r->top);

        printf("Enter the bottom coordinate : ");
        scanf("%d", &r->bottom);

        printf("Enter the right coordinate : ");
        scanf("%d", &r->right);

        printf("Enter the left coordinate : ");
        scanf("%d", &r->left);

        printf("Enter the name : ");
        scanf("%s", r->name);

        fflush(stdin);

        //if error then display error message
        if (invalidRect)
            DISPLAY_INVALID_RECT_ERROR

        //while the entered rectangle is not a valid rectangle, keep asking
    } while (invalidRect);

    //compute area and perimeter
    r->area = area(r->top - r->bottom, r->right - r->left);
    r->perimeter = perimeter(r->top - r->bottom, r->right - r->left);

    fflush(stdin);

}

/*

   Create random name

 */

static void randomName(char fC, char lC, int numC, char *__restrict name) {

    srand((unsigned int) rand());

    //assign each character to mod of int = rand() based on a base of last char - first char
    for (int i = 0; i < numC; i++)
        name[i] = fC + (rand() % (lC - fC));

    name[numC] = 0;
}

/*

   Insert random rectangle

*/

static void InsertRandomRect(Rectangle *__restrict r) {

    //new random seed
    srand((unsigned int) rand());

    //set top value as any value less than max (top - 1) and then add one to avoid having possibility of 0
    r->top = (rand() % (MPW_TOP - 1)) + 1;
    //set bottom to a value less than top
    r->bottom = rand() % (r->top);

    //set right value as any value less than max (max_right - 1) and then add one to avoid having possibility of 0
    r->right = (rand() % (MPW_RT - 1)) + 1;
    //set left to a value less than right
    r->left = rand() % (r->right);

    //pass all character information including the number of chars plus one for null
    randomName(RECT_MIN_NAME_CHAR, RECT_MAX_NAME_CHAR, RECT_NAME_CHARS + 1, r->name);

    //compute area and perimeter
    r->area = area(r->top - r->bottom, r->right - r->left);
    r->perimeter = perimeter(r->top - r->bottom, r->right - r->left);

}

/*
    
    Sort by Name.

 */

static int stringCompare(char *s1, char *s2) {

    int i = 0;

    while (s1[i] || s2[i]) {
        if (s1[i] < s2[i] || !s1[i]) return -1;
        if (s1[i] > s2[i] || !s2[i]) return 1;
        i++;
    }

    return 0;

}

/*

    Search for the insertion index of a rectangle (compare where in the previously sorted list the rectangle should be stored)

*/

static int indexSearch(LinkedHashMapType HashMap, int *index, int high, char *Key) {

    if (*index > high) return *index;

    else if (stringCompare(unwrap(LinkedHashMap->getByIndex(HashMap, *index))->name, Key) <
             0) {//the string you are inserting is greater than the string being stored
        (*index)++;
        indexSearch(HashMap, index, high, Key);
    } else
        return *index;

}

/*

    Add strings together into a target to allow for statistic string comparison

*/

static void attachStrings(char *s1, char *s2, char *target) {

    int i = 0;

    while (s1[i]) {
        target[i] = s1[i];
        i++;
    }

    int j = 0;

    while (s2[j]) {
        target[i] = s2[j];
        i++;
        j++;
    }

    target[i] = 0;

}

/*

    Search for the insertion index of a computation object (compare where in the previously sorted list the statistics should be stored)

*/

static int indexSearchStats(LinkedHashMapType HashMap, int *index, int high, char *Key) {

    char target[RECT_NAME_CHARS * 2 + 1];

    attachStrings(unpack(LinkedHashMap->getByIndex(HashMap, *index))->r1->name,
                  unpack(LinkedHashMap->getByIndex(HashMap, *index))->r2->name, target);

    if (*index > high) return *index;

    else if (stringCompare(target, Key) < 0) {//the string you are inserting is greater than the string being stored
        (*index)++;
        indexSearch(HashMap, index, high, Key);
    } else
        return *index;

}

/*

    Sort and insert into the appropriate index postition unising unique index search functions

*/

static void sort_and_insert(LinkedHashMapType HashMap, char *__restrict Key, void *__restrict Value) {

    int length = LinkedHashMap->getLength(HashMap);

    if (length == 0) {
        LinkedHashMap->put(HashMap, Key, Value);
        return;
    }

    int count = 0;

    int Index = 0;

    if (HashMap == RectanglesList)
        Index = indexSearch(HashMap, &count, length, Key);

    else
        Index = indexSearchStats(HashMap, &count, length, Key);

    if (Index > length) Index = length;

    LinkedHashMap->putAt(HashMap, Key, Value, Index);
}

/*

   Find the union of two rectangles

 */

static void UnionRect(const RectangleStatistics *__restrict r) {

    //already storing two random rectangles'
    //abstraction to make code easier and less repetitive
    Rectangle *r1 = r->r1;
    Rectangle *r2 = r->r2;
    Rectangle *r3 = r->unionRect;

    //set the furthest top value (highest) to the union top value
    // printf ("Union rect default is : %i\n", r1->top);
    r3->top = (r1->top < r2->top) ? r2->top : r1->top;
    //printf ("\n\n The union testing rect is : (%i, ", r3->top);

    //set the furthest bottom value (lowest) to the union bottom value
    r3->bottom = (r1->bottom < r2->bottom) ? r1->bottom : r2->bottom;
    //printf ("%i, ", r3->bottom);

    //set the furthest right value (highest) to the union right value
    r3->right = (r1->right < r2->right) ? r2->right : r1->right;
    //printf ("%i, ", r3->right);

    //set the furthest left value (lowest) to the union left value
    r3->left = (r1->left < r2->left) ? r1->left : r2->left;
    //printf ("%i)\n ", r3->left);

    //compute area and perimeter
    r3->area = area(r3->top - r3->bottom, r3->right - r3->left);
    r3->perimeter = perimeter(r3->top - r3->bottom, r3->right - r3->left);

}

static void IntersectRect(RectangleStatistics *__restrict r) {

    //already storing two random rectangle's
    //abstraction to make code easier and less repetitive
    Rectangle *r1 = r->r1;
    Rectangle *r2 = r->r2;
    Rectangle *r3 = r->sectRect;

    //set the answer to the closest top to the origin
    r3->top = (r1->top < r2->top) ? r1->top : r2->top;
    //printf ("%i, ", r3->top);

    //set the answer to the furthest bottom from the origin
    r3->bottom = (r1->bottom < r2->bottom) ? r2->bottom : r1->bottom;
    //printf ("%i)\n", r3->bottom);

    //set the answer to the closest right line to the origin
    r3->right = (r1->right < r2->right) ? r1->right : r2->right;
    //printf ("%i, ", r3->right);

    r3->left = (r1->left < r2->left) ? r2->left : r1->left;
    //printf ("(%i, ", r3->left);

    if (r3->bottom < r3->top && r3->left < r3->right) {
        //valid rectangle
        //printf("The rectangle intersection is valid!\n");
        // printRectangle (r3);
        //compute area and perimeter
        r3->area = area(r3->top - r3->bottom, r3->right - r3->left);
        r3->perimeter = perimeter(r3->top - r3->bottom, r3->right - r3->left);
        return;
    }

    //if the rectangle is invalid then simply set the pointer to null
    r->sectRect = NULL;
    //printf ("%p", r->sectRect);
    //printf("The rectangles do not intersect.\n");

}


void
DisplayAllRectangles(const int Index, __attribute__((unused)) const char *__restrict Key, const void *__restrict R) {

    Rectangle *r = unwrap(R);

    printf("%i: %s, (%i, %i), (%i, %i), %i, %i\n",
           Index, r->name, r->top, r->bottom, r->right, r->left, r->area, r->perimeter);

}


void DisplayAllStats(const int Index, __attribute__((unused)) const char *__restrict Key, const void *__restrict R) {

    RectangleStatistics *rMath = unpack(R);
    Rectangle
            *r1 = rMath->r1,
            *r2 = rMath->r2,
            *union_rect = rMath->unionRect,
            *sect_rect = rMath->sectRect;

    printf("Currently printing rectangle : %i\n", Index);

    //if wanted index can show what rectangle to use
    //output union format :
    /*
        bcaad, (20, 50), (40, 60), 60, 200
        dacdb, (30, 35), (50, 55), 80, 400
        bcaad union dacdb 		= (20,35), (50, 60)
        bcaad intersection dacdb 	= (30,50), (40, 55)
     */

    printf("%s, (%i, %i), (%i, %i), %i, %i\n",
           r1->name, r1->top, r1->bottom, r1->right, r1->left, r1->area,
           r1->perimeter);
    printf("%s, (%i, %i), (%i, %i), %i, %i\n",
           r2->name, r2->top, r2->bottom, r2->right, r2->left, r2->area,
           r2->perimeter);

    //preformat input, so it can be properly indented (left align with -30)
    printf("%s union %s = (%i,%i), (%i,%i)\n",
           r1->name, r2->name, union_rect->top,
           union_rect->bottom,
           union_rect->right, union_rect->left);

    //print intersect rectangle if it's not NULL
    if (sect_rect != NULL)
        printf(
                "%s intersection %s = (%i,%i), (%i,%i)\n",
                r1->name, r2->name, sect_rect->top,
                sect_rect->bottom,
                sect_rect->right, sect_rect->left);
    else
        printf("Intersection : NONE\n");

    printf("\n");

}

//Begin Operations


/*

    1. Get user rectangle

*/

void UserRect() {

    Rectangle *r = RectangleClass->new();
    InsertUserRect(r);
    //store rectangle
    sort_and_insert(RectanglesList, r->name, wrap(r));

}

/*

    2. Random rectangle

*/

void RandomRect() {

    Rectangle *r = RectangleClass->new();
    InsertRandomRect(r);
    //store rectangle
    sort_and_insert(RectanglesList, r->name, wrap(r));

}

/*

   3. Find rectangle

*/


void FindRect() {

    char s[100];

    printf("Please Enter Rectangle name:\n>");
    scanf("%s", s);

    void *R = LinkedHashMap->getByKey(RectanglesList, s);

    if (!R) {
        printf("Rectangle Doesn't Exist\n");
        return;
    }

    Rectangle *r = unwrap(R);

    printf("Here's your rectangle...\n"
           "%s, (%i, %i), (%i, %i), %i, %i\n",
           r->name, r->top, r->bottom, r->right, r->left, r->area, r->perimeter);


}

/*

    4. Delete Rectangle

*/

void DeleteRect() {

    char searchKey[RECT_NAME_CHARS + 1];
    int choice = 0;
    int lenght = LinkedHashMap->getLength(RectanglesList) - 1;
    int indexKey;

    while (1) {

        printf("\nEnter 1 to search by index or 2 to search by name : \n>");
        scanf("%d", &choice);

        if (choice == 1) {

            // Using Goto here isnt bad, it's a bad practice
            // if its abused and is used to make a spaghetti code

            printf("Please enter the index of the rectangle you wish to delete : \n>");
            scanf("%d", &indexKey);

            //buffer flush in case function gets called again
            fflush(stdin);

            LinkedHashMap->DeleteIndex(RectanglesList, indexKey);

            return;

        }

        if (choice == 2) {

            // lol, I am seriously bored at this moment after speed running
            // an essay and submitting in 10 mins ago

            printf("Please enter the name of the rectangle you wish to delete : \n>");
            scanf("%s", searchKey);

            //buffer flush in case function gets called again
            fflush(stdin);


            LinkedHashMap->DeleteKey(RectanglesList, searchKey);

            return;

        }

    }

}

/*

    5. Run and manage all computations and calculations

*/

void AllCalculations() {

    RectangleStatistics *rMath = unpack(RectangleClass->newRectStats());
    Rectangle *temp, *r1, *r2;

    int length = LinkedHashMap->getLength(RectanglesList);

    //if length is zero, no check possible
    if (length == 0) {
        invalidCase();
        return;
    }

    void *r1p, *r2p;

    //get two random rectangles
    //while the rectangles are teh same keep getting new ones


    srand((unsigned int) rand());

    r1p = LinkedHashMap->getByIndex(RectanglesList, (rand() % length));
    do
        r2p = LinkedHashMap->getByIndex(RectanglesList, (rand() % length));
    while (r1p == r2p);

    r1 = unwrap(r1p);
    r2 = unwrap(r2p);

    //sort them
    //decide which rectangle goes first alphabetically
    if (strcmp(r1->name, r2->name) > 0) {
        //if the second one is greater, then swap them by using simple temp swap
        temp = r1;
        r1 = r2;
        r2 = temp;
    }

    //set the two members from the rectangle statistics to the random rectangles
    rMath->r1 = RectangleClass->new();
    rMath->r2 = RectangleClass->new();
    rMath->unionRect = RectangleClass->new();
    rMath->sectRect = RectangleClass->new();

    memcpy(rMath->r1, r1, sizeof(Rectangle));
    memcpy(rMath->r2, r2, sizeof(Rectangle));


    //find and store union value
    UnionRect(rMath);

    //printf ("This far\n");
    //find and store intersect value
    IntersectRect(rMath);

    //store values for this statistic math
    //sort_and_insert(StatisticsList, strcat(rMath->r1->name, rMath->r2->name), pack(rMath));
    sort_and_insert(StatisticsList, rMath->r1->name, pack(rMath));


    //printf("Where you should now put!\n");
    DisplayAllStats(0, "\0", pack(rMath));

}

/*

   6. Display all rectangles

*/

void DisplayRectangles() {

    printf("Here are your rectangles ... \n");
    printf("Format : Name, (top, bottom), (right, left), area, perimeter\n");

    //foreachRectangle (&(void) DisplayAllRectanlges(Rectangle *))
    LinkedHashMap->forEach(RectanglesList, &DisplayAllRectangles);

}

/*

   7. Display all statistics

*/

void DisplayStats() {

    printf("Here are your statistics ... \n");
    //printf("Format : Name, (top, bottom), (right, left), area, perimeter\n");

    LinkedHashMap->forEach(StatisticsList, &DisplayAllStats);

}

/*

  8. To Quit Program

*/

#define SINGLE_INDENT "  "
#define DOUBLE_INDENT SINGLE_INDENT""SINGLE_INDENT
#define TRIPLE_INDENT DOUBLE_INDENT""SINGLE_INDENT
#define QUADRIPLE_INDENT DOUBLE_INDENT""DOUBLE_INDENT
#define QUINTIPLE_INDENT QUADRIPLE_INDENT""SINGLE_INDENT
#define BUFFER_SIZE 1000

static void serializeRect(const int Index, const char *__restrict Key, const void *__restrict Value) {


    char Buffer[BUFFER_SIZE];

    Rectangle *r = unwrap(Value);

    snprintf(

            /*

                Stream : Buffer

             */

            Buffer,
            BUFFER_SIZE,

            /*

                Printing format

             */


            //Name & Open Bracket
            DOUBLE_INDENT"\"%s\": {\n"
            //Top
            TRIPLE_INDENT"\"Top\": %i,\n"
            //Bottom
            TRIPLE_INDENT"\"Bottom\": %i,\n"
            //Right
            TRIPLE_INDENT"\"Right\": %i,\n"
            //Left
            TRIPLE_INDENT"\"Left\": %i,\n"
            //Area
            TRIPLE_INDENT"\"Area\": %i,\n"
            //Perimeter
            TRIPLE_INDENT"\"Perimeter\": %i\n"
            // Close Bracket
            DOUBLE_INDENT"}%c",

            /*

               Passing the parameters

             */

            Key, r->top, r->bottom, r->right, r->left, r->area, r->perimeter,

            // We are only adding a comma if there is another
            (Index != LinkedHashMap->getLength(RectanglesList) - 1) ? ',' : '\0'
    );


    FileWriter->writeLine(Buffer);

}

static void serializeToFile(const int Comma, const char *__restrict Key, const Rectangle *__restrict r) {

    char stream[BUFFER_SIZE];

    sprintf(

            /*

                Stream : Buffer

             */

            stream,

            /*

                Printing format

             */


            //Name & Open Bracket
            QUADRIPLE_INDENT"\"%s\": {\n"
            //Top
            QUINTIPLE_INDENT"\"Top\": %i,\n"
            //Bottom
            QUINTIPLE_INDENT"\"Bottom\": %i,\n"
            //Right
            QUINTIPLE_INDENT"\"Right\": %i,\n"
            //Left
            QUINTIPLE_INDENT"\"Left\": %i,\n"
            //Area
            QUINTIPLE_INDENT"\"Area\": %i,\n"
            //Perimeter
            QUINTIPLE_INDENT"\"Perimeter\": %i\n"
            // Close Bracket
            QUADRIPLE_INDENT"}%c",

            /*

               Passing the parameters

             */

            Key, r->top, r->bottom, r->right, r->left, r->area, r->perimeter,

            // We are only adding a comma if there is another
            (Comma) ? ',' : '\0'
    );

    FileWriter->writeLine(stream);

}

#define YES_COMMA 1
#define NO_COMMA  0

static void serializeStats(const int Index, const char *__restrict Key, const void *__restrict Value) {

    char Buffer[BUFFER_SIZE];

    RectangleStatistics *RS = unpack(Value);

    Rectangle
            *r1 = RS->r1,
            *r2 = RS->r2,
            *unionRect = RS->unionRect,
            *sectRect = RS->sectRect;

    // Statistics Number
    sprintf(Buffer,
            DOUBLE_INDENT"\"%i\": {\n"
            TRIPLE_INDENT"\"Rectangles\": {\n",
            Index);

    FileWriter->writeLine(Buffer);

    serializeToFile(YES_COMMA, r1->name, r1);
    serializeToFile(NO_COMMA, r2->name, r2);

    sprintf(Buffer,
            TRIPLE_INDENT"},\n"
            TRIPLE_INDENT"\"Statistics\": {\n");

    FileWriter->writeLine(Buffer);

    serializeToFile(YES_COMMA, "union-rect", unionRect);
    if (sectRect) serializeToFile(NO_COMMA, "sect-rect", sectRect);
    else FileWriter->writeLine(QUADRIPLE_INDENT"\"sect-rect\":  null\n");

    sprintf(Buffer,
            TRIPLE_INDENT"}\n"
            DOUBLE_INDENT"}%c",
            (Index != LinkedHashMap->getLength(StatisticsList) - 1) ? ',' : '\0');

    FileWriter->writeLine(Buffer);
}

void QuitProgram() {

    printf("Saving,,,, Hold on...\n");

    /*

        Writing into Files using JSON Format

     */

    // Opening File
    FileWriter->Open();

    printf("Saving Rectangles....\n");


    // Open Bracket
    FileWriter->writeLine("{");
    // First Dictionary
    FileWriter->writeLine(SINGLE_INDENT"\"Rectangles\": {");
    // Serializing all elements and printing it inside this dictionary
    LinkedHashMap->forEach(RectanglesList, &serializeRect);
    // Closing First Dictionary
    FileWriter->writeLine(SINGLE_INDENT"},");


    printf("Saved Rectangles...\n");

    printf("Saving Statistics....\n");


    // Second Dictionary
    FileWriter->writeLine(SINGLE_INDENT"\"Rectangle Statistics\": {");
    // Serializing all stats and printing in inside this dictionary
    LinkedHashMap->forEach(StatisticsList, &serializeStats);
    // Closing all dictionaries
    FileWriter->writeLine(SINGLE_INDENT"}\n}");
    // Closing File
    FileWriter->Close();


    printf("Saved Statistics...\n");

    printf("Exiting...\n");

    /*

        Performing Garbage Collection

     */

    LinkedHashMap->DeleteMap(RectanglesList);
    LinkedHashMap->DeleteMap(StatisticsList);


    printf("\nGood bye!\n");

}

/*

  Invalid Option

*/

void invalidCase() {

    /*

      Ask them to retry with error prompt

    */

    DISPLAY_INVALID_OPTION_ERROR
}

