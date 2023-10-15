/*
============================================================================
Name : 15.c
Author : Darshit Jakhaniya
Description : Write a simple program to send some data from parent to the child process.
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
		close(pipe_fd[0]);  //close the read end of the pipe
                char msg[]="hello child how are you!..";
                write(pipe_fd[1],msg,strlen(msg));
		printf("data send to the child: %s\n",msg);
		close(pipe_fd[1]);
	}
	else
	{
		//this is the child process
		close(pipe_fd[1]); //close the read end of the file

		char buf[50];
		int byte_read=read(pipe_fd[0],buf,sizeof(buf));
		if(byte_read>0)
		{
			printf("received data from parent: %s\n",buf);
		}
		else
		{
                        printf("no data received from parent\n");
		}
	        close(pipe_fd[0]);
	}
	return 0;
}
