#ifndef __STUDENT_H__
#define __STUDENT_H__

#include <stdbool.h>


#define NUM_STUDENTS 10
#define NAME_LENGTH 20
#define NUM_MARKS 3


// Definition of a Date data type
typedef struct  {  
  float marks[NUM_MARKS];
  int numberMarks;
  char name [NAME_LENGTH];
} tStudent;

// Table of Student elements
typedef struct {
   unsigned int size;  
   tStudent* students;
    
} tStudentTable;

// Initialize a user object
int student_init(tStudent* student, const char* name, const float* marks, const int numberMarks);

// Release memory used by user object
void student_free(tStudent* student);

// Compare two student
bool student_equals(tStudent* student1, tStudent* student2);

// Copy the data of a user to another user
int student_cpy(tStudent* dest, tStudent* src);

// **** Functions related to management of tUserTable objects

// Initialize the Table of students
void studentTable_init(tStudentTable* table);

// Release the memory used by userTable structure
void studentTable_free(tStudentTable* table);

// Get the size of the table
unsigned int studentTable_size(tStudentTable* table);

// Add a new user to the table
int studentTable_add(tStudentTable* table, tStudent* student);

// Compare two Table of users
bool studentTable_equals(tStudentTable* studenTable1, tStudentTable* studenTable2);

// Get student by name
tStudent* studentTable_find(tStudentTable* table, const char* name);

// Remove a student from the table
int studentTable_remove(tStudentTable* table, tStudent* user);

void studentTable_print(tStudentTable* table);

void student_print(tStudent* student);

int writeStudentsFile(char * fileName, tStudentTable* table);

int readStudentsFile(char * fileName, tStudentTable* table);

void getMarks(tStudent c[], int num);

void getNames(tStudent c[], int num);

float * calculateAverage(tStudent c[], int num);

void getAverage(float average[], int num);

#endif // __STUDENT_H__