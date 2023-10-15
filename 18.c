/*
===============================================================================================================================
Name : 18.c
Author : Darshit Jakhaniya
Description : Write a program to find out total number of directories on the pwd.execute ls -l | grep ^d | wc ? Use only dup2.
Date:22th sept,2023.
===============================================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int ls_fd[2];

    // Create a pipe
    if (pipe(ls_fd) == -1) 
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        // Child process
        close(ls_fd[0]); // Close the read end of the pipe
        dup2(ls_fd[1], 1); // Redirect stdout to the pipe, we can write STDOUT_FILENO also as second argument
        close(ls_fd[1]); // Close the write end of the pipe

        // Execute "ls -l"
        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls");
        exit(EXIT_FAILURE);
    } 
    else 
    {
        // Parent process
        close(ls_fd[1]); // Close the write end of the pipe
        dup2(ls_fd[0], STDIN_FILENO); // Redirect stdin to the pipe
        close(ls_fd[0]); // Close the read end of the pipe

        // Create a pipe for grep
        int grep_ls_fd[2];
        if (pipe(grep_ls_fd) == -1) 
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pid_t grep_pid = fork();
        if (grep_pid == -1) 
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (grep_pid == 0) 
        {
            // Child process (grep ^d)
            close(grep_ls_fd[0]); // Close the read end of the pipe
            dup2(grep_ls_fd[1], STDOUT_FILENO); // Redirect stdout to the pipe
            close(grep_ls_fd[1]); // Close the write end of the pipe

            // Execute "grep ^d"
            execlp("grep", "grep", "^d", NULL);
            perror("execlp grep");
            exit(EXIT_FAILURE);
        } 
        else 
        {
            // Parent process
            close(grep_ls_fd[1]); // Close the write end of the pipe
            dup2(grep_ls_fd[0], STDIN_FILENO); // Redirect stdin to the pipe
            close(grep_ls_fd[0]); // Close the read end of the pipe

            // Execute "wc -l" to count lines (directories)
            execlp("wc", "wc", "-l", NULL);
            perror("execlp wc");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
