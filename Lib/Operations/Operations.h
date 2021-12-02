/*

  Operations

  This file is responsible for performing all types of operations based on the user input.

  How it works:

    callent function will provide getFunctionToRun() the option user has chosen,
    getFunctionToRun() will return pointer to the function based on userchoice to
    the callent function. Main function will run that respective function.

*/


#ifndef Operations
#define Operations

#define OP_INSERT_USER_RECT 1
#define OP_INSERT_RD_RECT   2
#define OP_FIND_RECT        3
#define OP_DELETE_RECT      4
#define OP_UNION_RECT       5
#define OP_INTERSECT        6

#define OP_OUTPUT_RECT      7

#define OP_QUIT_PROGRAM     8

#define OP_ADD '+'
#define OP_SUB '-'
#define OP_MUL '*'
#define OP_DIV '/'


// Data Type of the function that will be returned
typedef void function();

/*

  Takes an argument of int that represents user choice,
  and returns the function that will fullfill the task
  the user has requested.

*/

function *getFunctionToRun(int Choice);


void Initialize();



#endif //Operations.h