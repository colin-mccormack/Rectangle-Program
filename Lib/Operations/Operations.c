#include <stdio.h>
#include <stdlib.h>

#include "Operations.h"
#include "../Rectangle/Rectangle.h"
#include "../LinkedHashMap/LinkedHashMap.h"

#define DISPLAY_INVALID_OPTION_ERROR printf("No working case. Retry.\n");

void UserRect();

void RandomRect();

void FindRect();

void DeleteRect();
void UnionRect();
int IntersectRect();
void DisplayAllEquations();
void ClearConsole();


 void QuitProgram();
 void invalidCase();

function *getFunctionToRun(int Choice) {

    switch (Choice) {

        // If users wants to generate a random rectangle
        case OP_INSERT_USER_RECT:
            return &UserRect;

            // If users wants the program to store a rectanglge
        case OP_INSERT_RD_RECT:
            return &RandomRect;

            // If users wants to find rectangle
        case OP_FIND_RECT:
            return &FindRect;

            // If user wants to delete rectangle by name
        case OP_DELETE_RECT:
            return &DeleteRect;

             // If user wants to find union of two rectangles
         case OP_UNION_RECT:
             return &UnionRect;

            // If user wants to find intersection of two rectangles
        case OP_OUTPUT_RECT:
            return &DisplayRectangles;

             // If user wants to close the program
         case OP_QUIT_PROGRAM:
             QuitProgram();
             return NULL;

            // This is an easter egg hidden, this clears the console,
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

static void *__restrict wrap(const Rectangle*__restrict R) {
    return (void *) R;
}

static Rectangle *__restrict unwrap(const void*__restrict R) {
    return (Rectangle *) R;
}

static void *__restrict pack(const RectangleStatistics*__restrict RS) {
    return (void*) RS;
}

static RectangleStatistics *__restrict unpack(const void*__restrict RS) {
    return (RectangleStatistics*) RS;
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

    } while (r->top < r->bottom || r->right < r->left);

    fflush(stdin);

}

/*

   Insert random rectangle

*/

void InsertRandomRect(Rectangle r) {

    //new random seed
    srand((unsigned int) rand());

    //set top value as any value less than max (top - 1) and then add one to avoid having possibility of 0
    r.top = (rand() % (MPW_TOP-1)) + 1;
    //set bottom to a value less than top
    r.bottom = rand() % (r.top);

    //set right value as any value less than max (max_right - 1) and then add one to avoid having possibility of 0
    r.right = (rand() % (MPW_RT-1)) + 1;
    //set left to a value less than right
    r.left = rand() % (r.right);


}

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

void DeleteRect() {}

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

void DisplayAllEquations(){}


/*

  To Quit Program

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

