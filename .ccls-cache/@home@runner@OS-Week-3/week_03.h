#ifndef WEEK_03_H    /* This is an "include guard" */
#define WEEK_03_H    /* prevents the file from being included twice. */
                     /* Including a header file twice causes all kinds */
                     /* of interesting problems.*/




/*Problem 1:
Write a C function or POSIX that copies one file to another. The original name and the destination are parameters of the function. The destination file must have protections that allow it to be read by any user, but only to be modified by the owner. Error conditions to be controlled: Source file cannot be open. Destination file cannot be created. Copy process did not finish well.*/
int copyFile(char * srcFileName, char * outFileName);

/*
Problem 2:
Write a C program that opens a file, which name the student can give, checks that it exists and reads all its content and displays it on the screen.*/
int readFile(char * fileName);

/*Problem 3:
Write a program to use sizeof and strlen.

Write a program that displays the size in bytes of a 10-element integer vector. And declare a string of 12, copy a text of 8 and show its length.*/
void problem_03();

/*Problem 4:
Write a C program that allows you to create a dynamic array of integer type whose size is requested by input, as well as its elements.

Once created, the array should be printed in reverse order.*/
void problem_04 ();

/*Problem 5:
Write a program that calls a function that increments the value of an integer that it receives by reference. The function must be of type void.*/
void problem_05 ();

/*Problem 6:
Write a program in C that for a number of students, which is requested by keyboard, asks for each one of them: name and 3 notes (which can have decimals). Once the list of students has been entered, it calculates the average of the three grades for each student and displays the name and average grade of the student on the screen.*/
void problem_06() ;


#endif /* WEEK_01_H */