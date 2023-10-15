/*
============================================================================
Name : 14.c
Author : Darshit Jakhaniya
Description : Write a simple program to create a pipe, write to the pipe, read from pipe and display on the monitor.
Date:20th sept,2023.
============================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main()
{
	int pipe_fd[2];
	pid_t pid;

	if(pipe(pipe_fd)==-1)
	{
		perror("pipe creation failed");
	}
	pid=fork();
	if(pid==-1)
	{
                perror("fork failed");
	}

	if(pid>0)
	{
		//this is the parent process
		close(pipe_fd[1]);  //close the write end of the pipe
		char buf[50];
		int byte_read=read(pipe_fd[0],buf,sizeof(buf));

		if(byte_read>0)
		{
			printf("parent process:i am reading from the pipe: %s\n",buf);
		}
		else
		{
			printf("parent process: nothing to read from pipe.\n");
		}
		close(pipe_fd[0]);
	}
	else
	{
		//this is the child process
		close(pipe_fd[0]); //close the read end of the file
                //child is writing to the parent
		char msg[]="hello how are you parent!..";
		write(pipe_fd[1],msg,strlen(msg));

		printf("child process: i am writing to the pipe: %s\n",msg);

		close(pipe_fd[1]);
	}
	return 0;
}
