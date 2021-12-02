#include <string.h>
#include "Rectangle.h"
#include "../../Configurations.h"
#include "../IO/FileWriter.h"

static int TotalRects;

Rectangle *__restrict new() {

    Rectangle *Rect = (Rectangle *) malloc(sizeof(Rectangle));

    if (!Rect) MALLOC_ERROR;

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

void Delete(Rectangle *__restrict rect) {
    free(rect);
}

RectangleStatistics *__restrict newRectStats() {

    RectangleStatistics *RectStats = (RectangleStatistics *) malloc(sizeof(RectangleStatistics));

    if (!RectStats) MALLOC_ERROR;

    RectStats->r1 =
    RectStats->r2 =
    RectStats->unionRect =
    RectStats->sectRect = NULL;

    return RectStats;
}

void DeleteStats(RectangleStatistics *__restrict R) {
    free(R->r1);
    free(R->r2);
    free(R->unionRect);
    if (R->sectRect) free(R->sectRect);
}

void writeRectangles () {

//    FileWriter->Open;
//    FileWriter->writeLine("{");
//
//    change max rects to index!
//
//    for (int i = 0; i < MAX_RECTS; i++) {
//        FileWriter->write(SerializeRect (Rectangle[i]));
//        if (i != MAX_RECTS - 1)
//            FileWriter->writeLine(",");
//     }
//
//     FileWriter->writeLine("}");
//     FileWriter->Close;

}

void writeStats () {

//    FileWriter->Open;
//    FileWriter->writeLine("{");
//
//    change max rects to index!
//
//        FileWriter->write ("\t\"");
//        FileWriter->write (RectangleStatistics->r1->name);
//        FileWriter->write ("\": { \n");
//        FileWriter->write ("\t\t\n\"top\": ");
//        FileWriter->write (itoa(RectangleStatistics->r1->top));
//        FileWriter->write ("\t\t\n\"bottom\": ");
//        FileWriter->write (itoa(RectangleStatistics->r1->bottom));
//        FileWriter->write ("\t\t\n\"right\": ");
//        FileWriter->write (itoa(RectangleStatistics->r1->right));
//        FileWriter->write ("\t\t\n\"left\": ");
//        FileWriter->write (itoa(RectangleStatistics->r1->left));
//        FileWriter->write ("\t\t\n\"area\": ");
//        FileWriter->write (itoa(RectangleStatistics->r1->area));
//        FileWriter->write ("\t\t\n\"perimeter\": ");
//        FileWriter->write (itoa(RectangleStatistics->r1->perimeter));
//        FileWriter->write ("\t}\n");
//
//        FileWriter->write ("\t\"");
//        FileWriter->write (RectangleStatistics->r2->name);
//        FileWriter->write ("\": { \n");
//        FileWriter->write ("\t\t\n\"top\": ");
//        FileWriter->write (itoa(RectangleStatistics->r2->top));
//        FileWriter->write ("\t\t\n\"bottom\": ");
//        FileWriter->write (itoa(RectangleStatistics->r2->bottom));
//        FileWriter->write ("\t\t\n\"right\": ");
//        FileWriter->write (itoa(RectangleStatistics->r2->right));
//        FileWriter->write ("\t\t\n\"left\": ");
//        FileWriter->write (itoa(RectangleStatistics->r2->left));
//        FileWriter->write ("\t\t\n\"area\": ");
//        FileWriter->write (itoa(RectangleStatistics->r2->area));
//        FileWriter->write ("\t\t\n\"perimeter\": ");
//        FileWriter->write (itoa(RectangleStatistics->r2->perimeter));
//        FileWriter->write ("\t}\n");
//        FileWriter->writeLine("}");
//        FileWriter->Close;

}


static char * SerializeRect (Rectangle *__restrict R) {

}

char * SerializeRectStats (Rectangle *__restrict RS) {

}


static const rectangleClass rectClass = {
        &new,
        &newRectStats,
        &Delete,
        &DeleteStats,
        &SerializeRect,
        &SerializeRectStats
};

const rectangleClass *__restrict RectangleClass = &rectClass;
