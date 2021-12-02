#ifndef RECTANGLE
#define RECTANGLE

#include "../../Configurations.h"

typedef struct {
    int left;
    int right;
    int top;
    int bottom;
    char name[RECT_NAME_CHARS + 1];
} Rectangle;

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
