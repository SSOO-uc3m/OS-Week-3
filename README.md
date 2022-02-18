# Lab C Strings and Files

### Problem 1

Write a C function or POSIX that copies one file to another. The original name and the destination are parameters of the function. The destination file must have protections that allow it to be read by any user, but only to be modified by the owner.
Error conditions to be controlled:
Source file cannot be open.
Destination file cannot be created. 
Copy process did not finish well.

### Problem 2

Write a C program that opens a file, which name the student can give, checks that it exists and reads all its content and displays it on the screen.


### Problem 3: 

Write a program in C that for a number of students, which is requested by keyboard, asks for each one of them: name and 3 notes (which can have decimals). 
The program must create a file and write the data of each student in the file as they are read. 
Once the list of students has been entered, it calculates the average of the three grades for each student and displays the name and average grade of the student on the screen.



## Test

### Question 1

Which are the main functions of an operating system?

````
The operating system is a program that is responsible for covering the hardware to facilitate the use of the computer,
which it carries out by performing three main functions:

- Management of system resources.

- Execution of services for programs.

- Execution of programs by users.

````

### Question 2

Which of the following hardware mechanisms is not a requirement to build a multiprogrammed operating system with protection between users? Give reasons for your answer.

a.- Virtual memory.

b.- Memory protection.

c.- I / O instructions that can only be executed in kernel mode.

d.- 2 modes of operation: core and user.

````

The correct answer is a: Virtual Memory

Although it is necessary to have a large amount of main memory, this does not require the use of said service.

On the other hand, the remaining options are necessary.
````

