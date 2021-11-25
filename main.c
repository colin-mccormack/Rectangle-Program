#include <stdio.h>

#include "LIb/IO/FileWriter.h"

int main() {

    FileWriter->Open();

    FileWriter->write("Writes Text, But doesnt add a new line character at end");
    FileWriter->write(" See?\n");
    FileWriter->writeLine("Writes Text, but also adds a new line character at end");
    FileWriter->writeLine("See?");
    FileWriter->writeLine("Check This Out in Out/Output.txt");

    FileWriter->Close();

    return 0;
}
