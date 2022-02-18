#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h> // open
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> // read
#include "student.h"

// Initialize a user object
int student_init(tStudent* student, const char* name, const float* marks, const int numberMarks){
	
 // Verify pre conditions
    assert(student != NULL);
    assert(name != NULL);
   
	
     // Allocate the memory for all the fields, using the length of the provided 
    // text plus 1 space for the "end of string" char '\0'. 
    // To allocate memory we use the malloc command.
    //student->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
	//student->marks = (float*)malloc(numberMarks * sizeof(float));

	
    // Check that memory has been allocated for all fields. 
    // Pointer must be different from NULL.
    if (student->name == NULL ) {
        // Some of the fields have a NULL value, what means that we found 
        // some problem allocating the memory
        return -1;
    }

    strcpy(student->name, name);	
	
	for(int i=0;i <numberMarks; i++){
		student->marks [i] = marks[i];
	}
	
	student->numberMarks = numberMarks;
		
    return 0;

}

// Release memory used by student 
void student_free(tStudent* student){
	 // Verify pre conditions
    assert(student != NULL);

    // All memory allocated with malloc and realloc needs to be freed using the free command. 
    // In this case, as we use malloc to allocate the fields, we have to free them

    /*if (student->name != NULL) {
        free(student->name);
        student->name = NULL;
    }

    if (student->marks != NULL) {
        free(student->marks);
        student->marks = NULL;
    }
	*/
	

	}

// Compare two student
bool student_equals(tStudent* student1, tStudent* student2){
	 // Verify pre conditions
    assert(student1 != NULL);
    assert(student2 != NULL);

    // To see if two users are equals, we need to see ALL the values for their fields are equals.    
    // Strings are pointers to a table of chars, therefore, cannot be compared  as  
    // " user1->username == user2->username ". We need to use a string comparison function    

    if (strcmp(student1->name, student2->name) != 0) {
        // names are different
        return false;
    }  

    // All fields have the same value
    return true;
}

// Copy the data of a user to another user
int student_cpy(tStudent* dst, tStudent* src){
	// Verify pre conditions
    assert(dst != NULL);
    assert(src != NULL);

    // Just in case, free space used by destination object.
    student_free(dst);

    // Initialize the element with the new data
    student_init(dst,  src->name, src->marks, src->numberMarks );

    return 0;
	
	}

// **** Functions related to management of tStudentsTable objects

// Initialize the Table of students
void studentTable_init(tStudentTable* table){
// Verify pre conditions
    assert(table != NULL);

    // The initialization of a table is to set it to the empty state. 
    // That is, with 0 elements. 
    table->size = 0;
    // Using dynamic memory, the pointer to the elements 
    // must be set to NULL (no memory allocated). 
    // This is the main difference with respect to the user of static memory, 
    // where data was always initialized (tStudent students[MAX_ELEMENTS])
    table->students = NULL;
	
	}

// Release the memory used by studentTable structure
void studentTable_free(tStudentTable* table){
	// Verify pre conditions
    assert(table != NULL);

    // All memory allocated with malloc and realloc needs to be freed using the free command. In this case, as we use malloc/realloc to allocate the elements, and need to free them.
    if (table->students != NULL) {
        for (int i = 0; i < table->size; i++) {
            student_free(&table->students[i]);
        }
        free(table->students);
        table->students = NULL;
        // As the table is now empty, assign the size to 0.
        table->size = 0;
	}

	}

// Get the size of the table
unsigned int studentTable_size(tStudentTable* table){
	 // Verify pre conditions
    assert(table != NULL);

    // The size of the table is the number of elements. This value is stored in the "size" field.
    return table->size;
}

// Add a new students to the table
int studentTable_add(tStudentTable* table, tStudent* student){
	// Verify pre conditions
    assert(table != NULL);
    assert(student != NULL);

    // Check if users already is on the table
    if (studentTable_find(table, student->name))
        return -1;

    // The first step is to allocate the required space. 
    // There are two methods to manage the 
    // memory (malloc and realloc). Malloc allows 
    // to allocate a new memory block, while realloc 
    // allows to modify an existing memory block.    
    if (table->size == 0) {
        // Empty table

        // Increase the number of elements of the table
        table->size = 1;

        // Since the table is empty, and we do not have any previous memory block, 
        // we have to use malloc. The amount of memory we need is the number of 
        // students (will be 1) times the size of one element, which is computed 
        // by sizeof(type). In this case the type is tUser.
        table->students = (tStudent*)malloc(table->size * sizeof(tStudent));
    }
    else {
        // table with students

        // Increase the number of students of the table
        table->size = table->size + 1;

        // Since the table is not empty, we already have a memory block. 
        // We need to modify the size of this block, using the realloc command. 
        // The amount of memory we need is the number of students times 
        // the size of one element, which is computed by sizeof(type). 
        // In this case the type is tUser. We provide the previous block of memory.
        table->students = (tStudent*)realloc(table->students, table->size * sizeof(tStudent));
    }

    // Check that the memory has been allocated
    if (table->students == NULL) {
        // Error allocating or reallocating the memory
        return -1;
    }

    // Once we have the block of memory, which is an array of tUser students, 
    // we initialize the new element (which is the last one). The last element 
    // is " table->students[table->size - 1] " (we start counting at 0)
    student_init(&(table->students[table->size - 1]), student->name, student->marks, student->numberMarks);

    return 0;

	}

// Compare two Table of students
bool studentTable_equals(tStudentTable* studenTable1, tStudentTable* studenTable2){
	    // Verify pre conditions
    assert(studenTable1 != NULL);
    assert(studenTable2 != NULL);

    int i;
    if (studenTable1->size != studenTable2->size) {
        return false;
    }

    for (i = 0; i< studenTable1->size; i++)
    {
        // Uses "find" because the order of users could be different
        if (!studentTable_find(studenTable1, studenTable2->students[i].name)) {
            // Usernames are different
            return false;
        }
    }

    return true;

	}

// Get student by name
tStudent* studentTable_find(tStudentTable* table, const char* name){
	int i;

    // Verify pre conditions
    assert(table != NULL);
    assert(name != NULL);

    // Search over the table and return once we found the student.
    for (i = 0; i<table->size; i++) {
        if (strcmp(table->students[i].name, name) == 0) {
            // We return the ADDRESS (&) of the student, which is a pointer to the student
            return &(table->students[i]);
        }
    }

    // The student has not been found. Return NULL (empty pointer).
    return NULL;

	}

// Remove a student from the table
int studentTable_remove(tStudentTable* table, tStudent* student){
	bool found;

    // Verify pre conditions
    assert(table != NULL);
    assert(student != NULL);

    // To remove an element of a table, we will move all elements after this element one position, 
    // to fill the space of the removed element.
    found = false;
    for (int i = 0; i<table->size; i++) {
        // If the element has been found. Displace this element to the previous element 
        // (will never happend for the first one). We use the ADDRESS of the previous element &(table->elements[i-1]) 
        // as destination, and ADDRESS of the current element &(table->elements[i]) as source.
        if (found) {
            // Check the return code to detect memory allocation errors
            if (student_cpy(&(table->students[i - 1]), &(table->students[i])) < 0) {
                // Error allocating memory. Just stop the process and return memory error.
                return -1;
            }

        }
        else if (strcmp(table->students[i].name, student->name) == 0) {
            // The current element is the element we want to remove. Set found flag to true to start element movement.
            found = true;
        }
    }

    // Once removed the element, we need to modify the memory used by the table.
    if (found) {
        // If we are removing the last element, we will free 
        // the last/remaining element in table / assign pointer 
        // to NULL
        if (table->size <= 1) {
            studentTable_free(table);
        }
        else {
            student_free(&table->students[table->size - 1]);
            // Modify the used memory. As we are modifying a previously 
            // allocated block, we need to use the realloc command.
            table->students = (tStudent*)realloc(table->students, table->size * sizeof(tStudent));

            // Check that the memory has been allocated
            if (table->students == NULL) {
                // Error allocating or reallocating the memory
                return -1;
            }
            else {
                // Succesfully allocated, set new table size
                table->size = table->size - 1;
            }
        }
    }
    else {
        // If the element was not in the table, return an error.
        return -1;
    }

    return 0;


	}

void studentTable_print(tStudentTable* table){
    
    for(int i=0; i< table->size; i++){
        
        student_print(&table->students[i]);
    
    }	
    
}

void student_print(tStudent* student){        
        
        printf("Student: %s \n",student->name);
        printf("Marks: \n");
        for(int i=0; i< student->numberMarks;i++){
            printf("%f\t",student->marks[i]);
            }
        printf("\n");        
    
}

int writeStudentsFile(char * fileName, tStudentTable* table) {
    int file, sz;
    file = open(fileName, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file < 0){
		printf("Error creating file %s",fileName);
        return (-1); /* cannot create file */
	}
	

    for (int i = 0; i < table->size ; i++) {
        //student_print(&table->students[i]);
        sz = write(file, &table->students[i], sizeof(tStudent));
        if (sz < 0) {
            printf("Error writing file %s",fileName);
            close(file);
            return (-1);
        }
    }

    close(file);

    return 0;
}

int readStudentsFile(char * fileName, tStudentTable* table) {
    int file, nread;
    
    tStudent student;
    
    file = open(fileName, O_RDONLY);
    if (file < 0){
		printf("Error opening file %s",fileName);
        return (-1); /* cannot create file */
	}
	

   
    while ((nread = read(file, &student, sizeof(tStudent))) > 0) {
        //student_print(student);
        studentTable_add(table, &student);

    }
    
    if (nread == -1) {
		printf("Error reading file %s",fileName);
        close(file);
        return (-1); /* error reading*/
    }
    
     

    close(file);

    return 0;
}

void getNames(tStudent c[], int num){
  int i,j;

  printf("\n");
  
  for (i=0;i<num; i++) {
      printf ("Give the student's name %d:",i);
      fgets (c[i].name,20,stdin);
      c[i].name[strlen(c[i].name)-1]='\0';  //I remove the new line
    }
}

void getMarks(tStudent c[], int num){
  int i,j;
  
  printf("\n");
  for (i=0;i<num; i++)
    for (j=0; j<NUM_MARKS;j++) {
      printf ("Give the mark %d of the student %s(decimals with .):",j,c[i].name );
      scanf ("%f", &(c[i].marks[j]) );
    }
}
float * calculateAverage(tStudent c[], int num){
  int i,j;
  float add,*average;
  
  average=(float *)malloc(NUM_STUDENTS*sizeof(float));
  for (i=0;i<num; i++) {
    add=0;
    for (j=0; j<NUM_MARKS;j++) {
      add=add+c[i].marks[j];
	  
	}
    average[i]=add/NUM_MARKS;
  }  
  return average;
}

void getAverage(float average[], int num){
    
  printf("\n");
  for (int i=0;i<num; i++){
    printf ("Average student grade %d=%f\n",i,average[i]);
    }
}
