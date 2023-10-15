/*
============================================================================
Name : 16.c
Author : Darshit Jakhaniya
Description : Write a program to send and receive data from parent to child vice versa. Use two way communication.
Date:21th sept,2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pipe_parentToChild[2]; // Parent to Child
    int pipe_childToParent[2]; // Child to Parent
    char message1[] = "message from parent to child process!";
    char message2[] = "messege from child to parent process!";
    char buf1[100];
    char buf2[100];
    pid_t child_pid;

    // Create the pipes
    if (pipe(pipe_parentToChild) == -1 || pipe(pipe_childToParent) == -1) {
        perror("Pipe creation failed");
    }

    // Fork a child process
    child_pid = fork();

    if (child_pid < 0) {
        perror("Fork failed");
    }

    if (child_pid == 0)
     { 
        // Child process
        close(pipe_parentToChild[1]); // Close the write end of pipe_parentToChild (parent to child)
        close(pipe_childToParent[0]); // Close the read end of pipe_childToParent (child to parent)

        // Read data from parent
        read(pipe_parentToChild[0], buf1, sizeof(buf1));
        printf("Child received: %s\n", buf1);

        // Send data to parent
        write(pipe_childToParent[1], message2, sizeof(message2));

        close(pipe_parentToChild[0]);
        close(pipe_childToParent[1]);
    } 
    else 
    { 
        // Parent process
        close(pipe_parentToChild[0]); // Close the read end of pipe_parentToChild (parent to child)
        close(pipe_childToParent[1]); // Close the write end of pipe_childToParent (child to parent)

        // Send data to child
        write(pipe_parentToChild[1], message1, sizeof(message1));

        // Read data from child
        read(pipe_childToParent[0], buf2, sizeof(buf2));
        printf("Parent received: %s\n", buf2);

        close(pipe_parentToChild[1]);
        close(pipe_childToParent[0]);
    }

    return 0;
}
