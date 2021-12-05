# Rectangle-Program

## Program Structure:

### Main File:
Runs the program using a handler function.
    
### IO.h
Header file containing IO functions, 
Interface between User and Program.

### Operations.h
Header file containing all functions created for specific operations,
Including Insert Rectangle, Insert Random Rectangle, Intersection Rectangle, and so on...
All those functions are abstracted away.
The only visible function visible is getFunctionToRun()
decideWhatToDo will return a function pointer that can be ran.

## Authors

- Abdul Mannan Syed, asyed24@ocdsb.ca
- Colin McMcormack, cmcco3@ocdsb.ca

12/05/2021
