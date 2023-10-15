/*
============================================================================
Name : 19.c
Author : Darshit Jakhaniya
Description : Create a FIFO file by
              a. mknod command
              b. mkfifo command
              c. use strace command to find out, which command (mknod or mkfifo) is better.
              c. mknod system call
              d. mkfifo library function
Date:22th sept,2023.
============================================================================
*/
/*a)To create a FIFO file using the mknod command, you can open your terminal and run the following command:
mknod myfifo p
This will create a named pipe (FIFO) called "myfifo" in the current directory.

b)To create a FIFO file using the mkfifo command, you can use the following command:mkfifo myfifo
This will also create a named pipe (FIFO) called "myfifo" in the current directory.

c)To use the strace command to find out which command (mknod or mkfifo) is better in terms of system calls,  you can run both commands with strace and compare the system call activity. For example:
strace mknod myfifo p
strace mkfifo myfifo
->After running both commands, you can analyze the system call traces to see which one involves fewer system calls or has a more efficient system call pattern. Typically, mkfifo is a higher-level command and may involve fewer low-level system calls compared to mknod.

d)The mknod system call is used to create special files, including FIFOs (named pipes), device files, and sockets. To create a FIFO using the mknod system call in C, you can use code like this:
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<stdio.h>

int main() {
    int result = mknod("myfifo", S_IFIFO | 0666, 0);
    if (result == -1) {
        perror("mknod");
        return 1;
    }
    return 0;
}

/*e)
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
	
	int mkfifo_val = mkfifo("mkfifo" , 0666);
	if(mkfifo_val == -1){
		perror("couldn't create FIFO file");
	}
}
*/
