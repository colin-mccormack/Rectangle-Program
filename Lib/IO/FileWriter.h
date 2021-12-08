#ifndef FILE_WRITER
#define FILE_WRITER

typedef struct {
    void (*const Open)();

    void (*const Close)();

    void (*const write)(const char *restrict s);

    void (*const writeLine)(const char *restrict s);
} fileWriter;

//to use file writer :
//  FileWriter->Open() // Open up the file!!!!!! DONT FORGET!!!!
//  FileWriter->write([String]) , writes the string into file, doesnt add \n at end
//  FileWriter->writeLine([String (no new line)]), wrties the string into file, but adds \n at end making your life easy
//  FileWriter->Close() // C

extern const fileWriter *restrict FileWriter;


#endif