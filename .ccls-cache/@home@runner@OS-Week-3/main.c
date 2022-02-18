#include <stdio.h>
#include "week_03.h"
#include "student.h"    
#include <stdlib.h>
#include <string.h>

int testProblem01();
int testProblem02();
int testProblem03();



int main(void) {
  testProblem01();
  testProblem02();
  testProblem03();

  return 0;
}

int testProblem01(){
 int result;

  result = copyFile("test.txt","copy.txt");

  if(result<0){
    printf("Error copyng file %d\n",result);
  
  }
  else {
    printf("File text.txt copy to copy.txt\n");
  }
    return(result);
}

int testProblem02(){
  int result;
   result = readFile("test.txt");
  
  if(result<0){
    printf("Error reading file %d\n",result);
    
  }
  else {
    printf("\nFile test.txt readed\n");
  }
  return(result);
}


// Run all tests for Students
int testProblem03() {

    bool passed = true, failed = false;

    int result;

    tStudentTable students;
    tStudent student1, student2, student3, student4;
    tStudent * studentAux;
    float marks[3];
      printf("Student_1 Initialize the table of students\t");
    // TEST 1: Initialize the table of students
    failed = false;
    studentTable_init(&students);

    if (studentTable_size(&students) != 0) {
        failed = true;
    }

    if (failed) {
        printf("Error  \n ");
        return -1;
    }
   else {
      printf("OK\n ");
    }

    // TEST 2: Initialize a student
    failed = false;
    
    marks[0] = 5;
	marks[1] = 6;
	marks[2] = 7;
    
    result = student_init(&student1, "Alice Smith", marks, 3);

    if (result < 0) {
        failed = true;
	}
	
	marks[0] = 3;
	marks[1] = 6;
	marks[2] = 6;

    printf("Student_2 Initialize a student\t");

    result = student_init(&student2, "Bob Freeman", marks, 3);

     if (result < 0)
        failed = true;      

    if (student_equals(&student1, &student2)) {
        failed = true;
    }

    if (failed) {
        printf("Error  \n ");
        return -1;
       
    }
    else {
      printf("OK\n ");
    }

    // TEST 3: Add a new student
    failed = false;
    printf("Student_3 Add a new student\t");

    result = studentTable_add(&students, &student1);
     if (result < 0){
        failed = true;
    }
	
    if (studentTable_size(&students) != 1) {
        failed = true;
    }
	
    studentAux = studentTable_find(&students, "Alice Smith");
    if (studentAux == NULL) {
        failed = true;
    }	
    else if (!student_equals(studentAux, &student1)) {
        failed = true;
    }

    if (failed) {
         printf("Error \n ");
        return -1;
    }
    else {
      printf("OK\n ");
    }
  

    // TEST 4: Add more students
    failed = false;
    printf("Student_4 Add more students\t");
    
  	marks[0] = 10;
	marks[1] = 9;
	marks[2] = 10;

    result = student_init(&student3, "John Connor", marks, 3);
    
	marks[0] = 10;
	marks[1] = 10;
	marks[2] = 10;
	
    result = student_init(&student4, "Sarah Connor", marks, 3);

    result = studentTable_add(&students, &student3);
    if (result < 0){
        failed = true;
    }
    
    if (studentTable_size(&students) != 2) {
        failed = true;
    }
    
    studentAux = studentTable_find(&students, "John Connor");
    if (studentAux == NULL) {
        failed = true;
    }
    if (!student_equals(studentAux, &student3)) {
        failed = true;
    }
    result = studentTable_add(&students, &student4);
    if (result < 0){
        failed = true;
    }
    
    if (studentTable_size(&students) != 3) {
        failed = true;
    }
    
    studentAux = studentTable_find(&students, "Sarah Connor");
    if (studentAux == NULL) {
        failed = true;
    }
    else if (!student_equals(studentAux, &student4)) {
        failed = true;
    }

    if (failed) {
        printf("Error\n ");
        return -1;
    }
    else {
       printf("OK \n ");
    }
   

    // TEST 5: Remove a student
    failed = false;
     printf("Student_5 Remove a student\t");

    studentAux = studentTable_find(&students, "John Connor");
    if (studentAux == NULL) {
        failed = true;
    }
        
    result = studentTable_remove(&students, &student3);
    if (result < 0){
        failed = true;
    }
    
    if (studentTable_size(&students) != 2) {
        failed = true;
    }    
    
    studentAux = studentTable_find(&students, "John Connor");
    if (studentAux != NULL) {
        failed = true;
    }
    
    studentAux = studentTable_find(&students, "Sarah Connor");
    if (studentAux == NULL) {
        failed = true;
    }

    if (failed) {
         printf("Error \n ");
        return -1;
    }
    else {
      printf(" OK\n ");
    }

    // TEST 6: Remove a non existing student
    failed = false;
    printf("Student_6 Remove a non existing student\t");

    result = studentTable_remove(&students, &student3);
    if (result == 0){
        failed = true;
    }
    
    if (studentTable_size(&students) != 2) {
        failed = true;
    }
    
    studentAux = studentTable_find(&students, "John Connor");
    if (studentAux != NULL) {
        failed = true;
    }
    
    studentAux = studentTable_find(&students, "Sarah Connor");
    if (studentAux == NULL) {
        failed = true;
    }
    
    studentAux = studentTable_find(&students, "Alice Smith");
    if (studentAux == NULL) {
        failed = true;
    }

    if (failed) {
        printf("Error  \n ");
        return -1;
    }
     else {
      printf("OK\n ");
    }

    // Remove used memory
    student_free(&student1);
    student_free(&student2);
    student_free(&student3);
    student_free(&student4);
    
    studentTable_free(&students);
}