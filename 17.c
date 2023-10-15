/*
============================================================================
Name : 17.c
Author : Darshit Jakhaniya
Description : Write a program to execute ls -l | wc.
              a. use dup
              b. use dup2
              c. use fcntl
Date:21 sept,2023.
============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
        //using fcntl
	int pipe_fd[2];
	int pid = pipe(pipe_fd);

	if(pid == -1){
		perror("pipe creation failed");
	}

	if(!fork())
	{
	        
		close(1);  //STD_OUT is closed
		close(pipe_fd[0]);   //close the read end of the file
		fcntl(pipe_fd[1],F_DUPFD,1);  //copy the file descriptor pipe_fd[1] to standard output for effectively redirecting the standard output to the pipe
		execlp("ls", "ls", "-l", (char*) NULL);
                //The execlp function is called to replace the child process with the ls -l command. This causes the output of ls -l to be sent to the write end of the pipe.
	} 
	else
	{
		close(0);
		close(pipe_fd[1]);
		fcntl(pipe_fd[0],F_DUPFD,0);  ////copy the file descriptor pipe_fd[0] to standard input for effectively redirecting the standard input to the pipe
		execlp("wc", "wc", (char*) NULL);
		/*The execlp function is called to replace the parent process with the wc command. This causes wc to read its input from the read end of the pipe, which connected      to the output of ls -l.*/
	}
	
	//using dup2
	/*
	int pipe_fd[2];
	int pid = pipe(pipe_fd);

	if(pid == -1)
	{
		perror("pipe creation failed");
	}

	if(!fork())
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1],1);
		execlp("ls", "ls", "-l", (char*) NULL);

	} 

	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0],0);
		execlp("wc", "wc", (char*) NULL);
	}
	*/
	
	
	//using dup
	/*
	int pipe_fd[2];
	int pid = pipe(pipe_fd);

	if(pid == -1)
	{
		perror("pipe creation failed");
	}

	if(!fork())
	{
		close(1);
		close(pipe_fd[0]);
		dup(pipe_fd[1]);
		execlp("ls", "ls", "-l", (char*) NULL);

	} 

	else{
		close(0);
		close(pipe_fd[1]);
		dup(pipe_fd[0]);
		execlp("wc", "wc", (char*) NULL);
	}

	*/
} //main completed
