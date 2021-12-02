#ifndef RECTANGLE
#define RECTANGLE

#include "../../Configurations.h"

typedef struct {
    int left;
    int right;
    int top;
    int bottom;
    int area;
    int perimeter;
    char name[RECT_NAME_CHARS + 1];
} Rectangle;

typedef struct {
    Rectangle *r1, *r2;
    Rectangle *unionRect;
    Rectangle *sectRect; // Will be set to NULL if no intersection.
} RectangleStatistics;

typedef struct {

    Rectangle *__restrict (*const new)();
    RectangleStatistics *__restrict (*const newRectStats)();

    void (*const Delete)(Rectangle *__restrict);
    void (*const DeleteStats)(RectangleStatistics *__restrict);

    char * (*const SerializeRect) (Rectangle *__restrict);
    char * (*const SerializeRectStats) (Rectangle *__restrict);
}
rectangleClass;

extern const rectangleClass *__restrict RectangleClass;

static char * SerializeRect (Rectangle *__restrict);

#endif
