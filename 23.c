/*
============================================================================
Name : 23.c
Author : Darshit Jakhaniya
Description : Write a program to print the maximum number of files can be opened within a process and size of a pipe (circular buffer).
Date:1st oct,2023.
============================================================================
*/
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main() {
    
    long number = sysconf(_SC_OPEN_MAX);
    //OPEN_MAX - _SC_OPEN_MAX The maximum number of files that a process can open at any time.

    if (number == -1) 
    {
        perror("error");
    }

    printf("Maximum number of open files for this process: %ld\n", number);

    // Get the size of a pipe (circular buffer)
    int fd[2];
    if (pipe(fd) == -1) 
    {
        perror("error in creating pipe");
    }

    long size = fcntl(fd[0], F_GETPIPE_SZ);
    // Return (as the function result) the capacity of the pipe referred to by fd.
    if (size == -1) 
    {
        perror("error in fcntl");
    }

    printf("Size of a pipe: %ld bytes\n", size);
    close(fd[0]);
    close(fd[1]);

    return 0;
}
