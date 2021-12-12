#include "Rectangle.h"

/*

    To create a new Rectangle

 */

Rectangle *__restrict new() {

    Rectangle *Rect = (Rectangle *) malloc(sizeof(Rectangle));

    if (!Rect) MALLOC_ERROR;

    // Assign all of them to zero lol
    Rect->bottom =
    Rect->top =
    Rect->left =
    Rect->right =
    Rect->area =
    Rect->perimeter = 0;

    // To mark it as an empty string.
    Rect->name[0] = '\0';

    return Rect;
}


/*

    How to cause a function overhead

    LIKE THIS!

 */


void Delete(Rectangle *__restrict rect) {
    free(rect);
}

/*

    To create a new Rectangle Statistics

 */

RectangleStatistics *__restrict newRectStats() {

    RectangleStatistics *RectStats = (RectangleStatistics *) malloc(sizeof(RectangleStatistics));

    if (!RectStats) MALLOC_ERROR;

    // Assign all of them to null lazily
    RectStats->r1 =
    RectStats->r2 =
    RectStats->unionRect =
    RectStats->sectRect = NULL;

    return RectStats;
}

/*

    WHAT WAS THAT DELETE FUNCTION BEFORE FOR, IF YOU CALLED free() DIRECTLY?

    It was there to look cool.

 */

void DeleteStats(RectangleStatistics *__restrict R) {
    free(R->r1);
    free(R->r2);
    free(R->unionRect);
    if (R->sectRect) free(R->sectRect);
}

/*

    What this for then?

    TO CREATE A CLASS OKAY? I KNOW C IS PROCEDURAL, BUT WHY NOT MAKE IT OBJECT ORIENTED?  KEEPS ME SANE OKAY?

    oh okay, go write code in C++

    DAMN NO, C++'s wack syntax makes me go mad srsly why do we have << :: >>

    Yeah, i know Java is your religion

    YES IT IS, NO ONE EVEN CARES OF GARBAGE COLLECTION IN THERE,

    Mr. Devlin says OOP took 6 hours to process a call in Nortel

   Exactly, explains why Nortel's stock is cheaper than a candy


 */

static const rectangleClass rectClass = {
        &new,
        &newRectStats,
        &Delete,
        &DeleteStats
};

const rectangleClass *__restrict RectangleClass = &rectClass;
