/*

    FileWriter.h

    This file is responsible for handling file operations.

    Yeah, that's it.


 */

#ifndef FILE_WRITER
#define FILE_WRITER

/*

    FileWriter

    This structure holds references to the functions that
    can be used for file operations

    Example for Usage:
    FileWriter->Open(); // opens a file for operations


 */

typedef struct {

    /*

        void Open()

        Opens the file for further operations

        Example Usage:
        FileWriter->Open()
     */

    void (*const Open)();


    /*

        void Close()

        Closes the file

        Example Usage:
        FileWriter->Close()
     */

    void (*const Close)();


    /*

        void write(const char *)

        Writes provided string into the file

        Example Usage:
        FileWriter->write("Cats are cool");
     */


    void (*const write)(const char *restrict s);


    /*

        void writeLine()

        Writes the provided string into the file, with luxury of automatically
        adding a new line character at the end.

        Example Usage:
        FileWriter->writeLine("Hello Mars!")
     */

    void (*const writeLine)(const char *restrict s);

} fileWriter;

extern const fileWriter *restrict FileWriter;


#endif