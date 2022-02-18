#include "week_03.h"
#include "stdio.h"
#include "string.h"
#include <sys/types.h> // open
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> // read
#include <stdlib.h> // realloc
#include <dirent.h> // DIR

#define PERM 0644
#define BUFSIZE 512
#define LINES 75

int readFile(char * fileName) {
    int file, nread;
    char buffer[BUFSIZE];

    if (!fileExists(fileName)) {
        printf("%s file does not exist", fileName);
        return (-1); // file does not exist
    }

    if ((file = open(fileName, O_RDONLY)) < 0) {
        perror("cannot open file");
        return (-2);

    }

    //read file BUFSIZE characters at once 512    
    while ((nread = read(file, buffer, BUFSIZE)) > 0) {
        if (nread == BUFSIZE) {
            printf("%s",buffer);
        } else {
            for (int i = 0; i < nread; i++) {
                printf("%c",buffer[i]);
            }
        }
    }
    if (nread == -1) {
        perror("Error reading");
        close(file);
        return (-4); // error
    }

    close(file);

    return 0;

}

// check if a file exists
int fileExists(const char * file) {
    struct stat buf;
    return (stat(file, & buf) == 0);
}

int copyFile(char * srcFileName, char * outFileName) {
    int infile, outfile, nread;
    char buffer[BUFSIZE];

    if (!fileExists(srcFileName)) {
        printf("%s file does not exist", srcFileName);
        return (-1); // file does not exist
    }

    if ((infile = open(srcFileName, O_RDONLY)) < 0)
        return (-1); // cannot open file
    if ((outfile = creat(outFileName, PERM)) < 0) {
        close(infile);
        return (-2); //cannot create file
    }
    //read file BUFSIZE characters at once
    while ((nread = read(infile, buffer, BUFSIZE)) > 0) {
        //write the buffer to the outfile 
        if (write(outfile, buffer, nread) < nread) {
            close(infile);
            close(outfile);
            return (-3); // error writting 
        }
    }
    if (nread == -1) {
        close(infile);
        close(outfile);
        return (-4); // error reading 

        close(infile);
        close(outfile);
        return (0);

    }
}