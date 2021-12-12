/*

    RectangleClass.h

    This file is responsible for encapsulation and abstracting
    rectangle functions.

    This file allows you to easily create rectangle and rectangle statistics
    instances and allocate them on heap to allow you to globally and dynamically
    access them.

    Keep in mind that you will have to manually garbage collect these instances allocated
    on heap once you are done with them.


*/

#ifndef RECTANGLE
#define RECTANGLE

#include "../../Configurations.h"

/*

    Rectangle Structure

    a blueprint of a rectangle instance.
 */

typedef struct {
    int left;
    int right;
    int top;
    int bottom;
    int area;
    int perimeter;
    char name[RECT_NAME_CHARS + 1];
} Rectangle;


/*

    RectangleStatistics structure

    blueprint of a RectangleStatistics instance

 */

typedef struct {
    Rectangle *r1, *r2;
    Rectangle *unionRect;
    Rectangle *sectRect; // Will be set to NULL if no intersection.
} RectangleStatistics;

/*

    RectangleClass

    This structure holds references to the functions that
    can be invoked on Rectangle Instances.

    Example for Usage:
    RectangleClass->new(); // returns a new rectangle instance


 */


typedef struct {

    /*

        Rectangle* new()

        This function enables users to create new rectangle instances

        Once called, this function will return you a pointer to a
        rectangle structure allocated in heap.

        Keep in mind to call delete() to garbage collect this structure.

        Example usage:
        RectangleClass->new()

     */

    Rectangle *__restrict (*const new)();

    /*

        RectangleStatistics* newRectStats()

        This function enables users to create new rectangle statistics instances

        Once called, this function will return you a pointer to a
        rectangle structure allocated in heap.

        Keep in mind to call delete() to garbage collect this structure.

        Example usage:
        RectangleClass->newRectStats()

     */

    RectangleStatistics *__restrict (*const newRectStats)();

    /*

        void Delete(Rectangle*)

        This function enables users to delete  rectangle instances

        This function requires an argument that points to the rectangle
        instance, this function will take care of safely deleting the instance


        Example usage:
        RectangleClass->delete()

     */

    void (*const Delete)(Rectangle *__restrict);


    /*

        void DeleteStats(RectangleStatistics*)

        This function enables users to delete rectangle statistics instances

        This function requires an argument that points to the rectangle
        instance, this function will take care of safely deleting the instance


        Example usage:
        RectangleClass->delete()

     */

    void (*const DeleteStats)(RectangleStatistics *__restrict);

} rectangleClass;

extern const rectangleClass *__restrict RectangleClass;

#endif
