#include <stdio.h>
#include <stdlib.h>

#include "Operations.h"
#include "../Rectangle/Rectangle.h"

#define DISPLAY_INVALID_OPTION_ERROR printf("No working case. Retry.\n");


void InsertUserRect();
void InsertRandomRect();
void FindRect();
void DeleteRect();
void UnionRect();
int IntersectRect();
void DisplayAllEquations();
void ClearConsole();


 void QuitProgram();
 void invalidCase();

 function* getFunctionToRun(int Choice) {

     switch (Choice) {

         // If users wants to generate a random rectangle
         case OP_INSERT_USER_RECT:
             return &InsertUserRect;

             // If users wants the program to store a rectanglge
         case OP_INSERT_RD_RECT:
             return &InsertRandomRect;

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
         case OP_INTERSECT:
             return &IntersectRect;

             // If user wants to display all rectangles
         case OP_OUTPUT_RECT:
             return &DisplayAllEquations;

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

   Insert user rectangle

 */

void InsertUserRect(Rectangle *r) {

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

void FindRect(){}
void DeleteRect(){}

/*

   Find the union of two rectangles

 */

void UnionRect(){

    Rectangle r1, r2, r3Base;
    Rectangle *r3 = &r3Base;

    printf ("\n\nPlease enter rectangle 1.\n");
    InsertUserRect(&r1);
    printf ("\n\nNow enter rectangle 2.\n");
    InsertUserRect(&r2);

    //set the furthest top value (highest) to the union top value
    r3->top = (r1.top < r2.top) ? r2.top : r1.top;
    //printf ("\n\n The union testing rect is : (%i, ", r3->top);

    //set the furthest bottom value (lowest) to the union bottom value
    r3->bottom = (r1.bottom < r2.bottom) ? r1.bottom : r2.bottom;
    //printf ("%i, ", r3->bottom);

    //set the furthest right value (highest) to the union left value
    r3->right = (r1.right < r2.right) ? r2.right : r1.right;
    //printf ("%i, ", r3->right);

    //set the furthest left value (lowest) to the union left value
    r3->left = (r1.left < r2.left) ? r1.left : r2.left;
    //printf ("%i)\n ", r3->left);

}

void UnionRectTesting() {

    Rectangle r1, r2, r3Base;
    Rectangle *r3 = &r3Base;

    r1.top = 6;
    r1.bottom = 4;
    r1.right = 1;
    r1.left = 0;

    r2.top = 2;
    r2.bottom = 0;
    r2.right = 3;
    r2.left = 2;

    //set the furthest top value (highest) to the union top value
    r3->top = (r1.top < r2.top) ? r2.top : r1.top;
    printf ("\n\n The union testing rect is : (%i, ", r3->top);

    //set the furthest bottom value (lowest) to the union bottom value
    r3->bottom = (r1.bottom < r2.bottom) ? r1.bottom : r2.bottom;
    printf ("%i, ", r3->bottom);

    //set the furthest right value (highest) to the union left value
    r3->right = (r1.right < r2.right) ? r2.right : r1.right;
    printf ("%i, ", r3->right);

    //set the furthest left value (lowest) to the union left value
    r3->left = (r1.left < r2.left) ? r1.left : r2.left;
    printf ("%i)\n ", r3->left);

}

int IntersectRect(){

    Rectangle r1, r2, r3Base;
    Rectangle *r3 = &r3Base;
    
    printf ("\n\nPlease enter rectangle 1.\n");
    InsertUserRect(&r1);
    printf ("\n\nNow enter rectangle 2.\n");
    InsertUserRect(&r2);

    //set the answer to the closest top to the origin
    r3->top = (r1.top < r2.top) ? r1.top : r2.top;
    //printf ("%i, ", r3->top);

    //set the answer to the furthest bottom from the origin
    r3->bottom = (r1.bottom < r2.bottom) ? r2.bottom : r1.bottom;
    //printf ("%i)\n", r3->bot);

    //set the answer to the closest right line to the origin
    r3->right = (r1.right < r2.right) ? r1.right : r2.right;
    //printf ("%i, ", r3->rt);

    r3->left = (r1.left < r2.left) ? r2.left : r1.left;
    //printf ("(%i, ", r3->lt);

    if (r3->bottom < r3->top &&  r3->left < r3->right) {
        //valid rectangle
        printf ("The rectangle is valid!\n");
       // printRectangle (r3);
        return 1;
    }

    printf ("The rectangle is invalid.\n");
    return 0;

}

void IntersectRectTesting() {

    Rectangle r1, r2, r3Base;
    Rectangle *r3 = &r3Base;

    r1.top = 6;
    r1.bottom = 3;
    r1.right = 4;
    r1.left = 0;

    r2.top = 2;
    r2.bottom = 0;
    r2.right = 3;
    r2.left = 2;

    //set the answer to the closest top to the origin
    r3->top = (r1.top < r2.top) ? r1.top : r2.top;
    //printf ("%i, ", r3->top);

    //set the answer to the furthest bottom from the origin
    r3->bottom = (r1.bottom < r2.bottom) ? r2.bottom : r1.bottom;
    //printf ("%i)\n", r3->bot);

    //set the answer to the closest right line to the origin
    r3->right = (r1.right < r2.right) ? r1.right : r2.right;
    //printf ("%i, ", r3->rt);

    r3->left = (r1.left < r2.left) ? r2.left : r1.left;
    //printf ("(%i, ", r3->lt);

    if (r3->bottom < r3->top &&  r3->left < r3->right) {
        //valid rectangle
        printf("The rectangle is valid!\n");
        // printRectangle (r3);
    } else {
        printf("The rectangle is invalid!\n");
    }

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

