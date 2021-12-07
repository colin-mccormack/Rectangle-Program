#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Operations.h"
#include "../Rectangle/Rectangle.h"
#include "../LinkedHashMap/LinkedHashMap.h"

#define DISPLAY_INVALID_OPTION_ERROR printf("No working case. Retry.\n");

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
    RectanglesList = LinkedHashMap->new(MAX_RECTS);
    StatisticsList = LinkedHashMap->new(MAX_RECTS);
}

/*

    Wrapper functions to storing and reading from hash maps.

 */

static inline void *__restrict wrap(const Rectangle*__restrict R) {
    return (void *) R;
}

static inline Rectangle *__restrict unwrap(const void*__restrict R) {
    return (Rectangle *) R;
}

static inline void *__restrict pack(const RectangleStatistics*__restrict RS) {
    return (void*) RS;
}

static inline RectangleStatistics *__restrict unpack(const void*__restrict RS) {
    return (RectangleStatistics*) RS;
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

        printf("Enter the top coordinate :");
        scanf("%d", &r->top);

        printf("Enter the bottom coordinate :");
        scanf("%d", &r->bottom);

        printf("Enter the right coordinate :");
        scanf("%d", &r->right);

        printf("Enter the left coordinate :");
        scanf("%d", &r->left);

        printf("Enter the name :");
        scanf("%s", r->name);

        fflush(stdin);

    //while the entered rectangle is not a valid rectangle, keep asking
    } while (r->top < r->bottom || r->right < r->left);

    //compute area and perimeter
    r->area = area(r->top - r->bottom, r->right - r->left);
    r->perimeter = perimeter(r->top - r->bottom, r->right - r->left);

    fflush(stdin);

}

/*

   Create random name

 */

static void randomName(char fC,char lC,int numC,char *__restrict name) {

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
    randomName(RECT_MIN_NAME_CHAR, RECT_MAX_NAME_CHAR, RECT_NAME_CHARS+1, r->name);

    //compute area and perimeter
    r->area = area(r->top - r->bottom, r->right - r->left);
    r->perimeter = perimeter(r->top - r->bottom, r->right - r->left);

}


/*

   Find the union of two rectangles

 */

static void UnionRect(const RectangleStatistics *__restrict r) {

    //already storing two random rectangles'
    //abstraction to make code easier and less repetitive
    Rectangle *r1 = r->r1;
    Rectangle *r2 = r->r1;
    Rectangle *r3 = r->unionRect;

    //set the furthest top value (highest) to the union top value
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

static void IntersectRect(const RectangleStatistics *__restrict r) {

    //already storing two random rectangle's
    //abstraction to make code easier and less repetitive
    Rectangle *r1 = r->r1;
    Rectangle *r2 = r->r1;
    Rectangle *r3 = r->sectRect;

    //set the answer to the closest top to the origin
    r3->top = (r1->top < r2->top) ? r1->top : r2->top;
    //printf ("%i, ", r3->top);

    //set the answer to the furthest bottom from the origin
    r3->bottom = (r1->bottom < r2->bottom) ? r2->bottom : r1->bottom;
    //printf ("%i)\n", r3->bot);

    //set the answer to the closest right line to the origin
    r3->right = (r1->right < r2->right) ? r1->right : r2->right;
    //printf ("%i, ", r3->rt);

    r3->left = (r1->left < r2->left) ? r2->left : r1->left;
    //printf ("(%i, ", r3->lt);

    if (r3->bottom < r3->top && r3->left < r3->right) {
        //valid rectangle
        printf("The rectangle is valid!\n");
        // printRectangle (r3);
        //compute area and perimeter
        r3->area = area(r3->top - r3->bottom, r3->right - r3->left);
        r3->perimeter = perimeter(r3->top - r3->bottom, r3->right - r3->left);
        return;
    }

    //if the rectangle is invalid then simply set the pointer to null
    r3 = NULL;
    printf("The rectangles do not intersect.\n");

}


void DisplayAllRectangles(const int Index,__attribute__((unused)) const char*__restrict Key,const void *__restrict R) {

    Rectangle *r = unwrap(R);

    printf("%i: %s, (%i, %i), (%i, %i), %i, %i\n",
           Index, r->name, r->top, r->bottom, r->right, r->left, r->area, r->perimeter);


}


void DisplayAllStats(RectangleStatistics *rMath) {

    char *preparedOutput = (char *) malloc(RECT_NAME_CHARS * 2 + 10);

    //output union format :
    /*
        bcaad, (20, 50), (40, 60), 60, 200
        dacdb, (30, 35), (50, 55), 80, 400
        bcaad union dacdb 		= (20,35), (50, 60)
        bcaad intersection dacdb 	= (30,50), (40, 55)
     */

    printf("%s, (%i, %i), (%i, %i), %i, %i\n",
           rMath->r1->name, rMath->r1->top, rMath->r1->bottom, rMath->r1->right, rMath->r1->left, rMath->r1->area,
           rMath->r1->perimeter);
    printf("%s, (%i, %i), (%i, %i), %i, %i\n",
           rMath->r2->name, rMath->r2->top, rMath->r2->bottom, rMath->r2->right, rMath->r2->left, rMath->r2->area,
           rMath->r2->perimeter);

    //preformat input, so it can be properly indented (left align with -30)
    sprintf(preparedOutput, "%s union %s", rMath->r1->name, rMath->r2->name);
    printf("%-30s = (%i,%i), (%i,%i)\n", preparedOutput, rMath->unionRect->top, rMath->unionRect->bottom,
           rMath->unionRect->right, rMath->unionRect->left);
    //print intersect rectangle if it's not NULL
    if (rMath->sectRect != NULL)
        printf("%-30s = (%i,%i), (%i,%i)\n", preparedOutput, rMath->sectRect->top, rMath->sectRect->bottom,
               rMath->sectRect->right, rMath->sectRect->left);
    else
        printf("NONE\n");

    printf("\n");

}

//Begin Operations


/*

    1. Get user rectangle

*/

void UserRect() {

    Rectangle *r = RectangleClass->new();
    InsertUserRect(r);
    //store rectangle\
    LinkedHashMap->put(RectanglesList,r->name, wrap(r));

}

/*

    2. Random rectangle

*/

void RandomRect() {

    Rectangle *r = RectangleClass->new();
    InsertRandomRect(r);
    //store rectangle
    LinkedHashMap->put(RectanglesList, r->name, wrap(r));
}

/*

   3. Find rectangle

*/


void FindRect() {

    char s[100];

    printf("Please Enter Rectangle name:\n>");
    scanf("%s",s);

    void *R = LinkedHashMap->getByKey(RectanglesList,s);

    if(!R) {
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

    char searchKey[RECT_NAME_CHARS+1];
    int choice = 0;
    int indexKey;

    while(1) {

        printf ("\nEnter 1 to search by index or 2 to search by name : \n");
        scanf ("%d", &choice);

        if (choice == 1) {

            printf("Please enter the index of the rectangle you wish to delete : \n");
            scanf("%d", &indexKey);

            //buffer flush in case function gets called again
            fflush(stdin);

            LinkedHashMap->DeleteIndex(RectanglesList, indexKey);

            return;

        }

        if (choice == 2) { 

            printf("Please enter the name of the rectangle you wish to delete : \n");
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

    RectangleStatistics *rMath = RectangleClass->newRectStats();
    Rectangle *temp;

    //get two random rectangles
    InsertRandomRect(rMath->r1);
    InsertRandomRect(rMath->r2);

    //sort them
    //decide which rectangle goes first alphabetically
    if (strcmp(rMath->r1->name, rMath->r2->name) > 0) {
        //if the second one is greater, then swap them by using simple temp swap
        temp = rMath->r1;
        rMath->r1 = rMath->r2;
        rMath->r2 =  temp;
    }

    //find and store union value
    UnionRect(rMath);

    //find and store intersect value
    IntersectRect(rMath);

    DisplayAllStats(rMath);

}

/*

   6. Display all rectangles

*/

void DisplayRectangles() {

    printf("Here are your rectangles ... \n");
    printf("Format : Name, (top, bottom), (right, left), area, perimeter\n");

    //foreachRectangle (&(void) DisplayAllRectanlges(Rectangle *))
    LinkedHashMap->forEach(RectanglesList,&DisplayAllRectangles);

}

/*

   7. Display all statistics

*/

void DisplayStats() {

    printf("Here are your rectangles ... \n");
    printf("Format : Name, (top, bottom), (right, left), area, perimeter\n");

    //foreachstats (&(void) DisplayAllStats(RectangleStatistics *))

}

/*

  8. To Quit Program

*/

void QuitProgram() {

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

