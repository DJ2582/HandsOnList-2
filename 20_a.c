/*
============================================================================
Name : 20a.c
Author : Darshit Jakhaniya
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date:23th sept,2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {

    const char* message = "Hello, FIFO!";

    // Create the FIFO (if it doesn't exist)
    mkfifo("myfifo", 0666);

    // Open the FIFO for writing
    int fd = open("myfifo", O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // Write the message into the FIFO
    write(fd, message, strlen(message));
    close(fd);

    printf("Writer wrote: %s\n", message);

    return 0;
}
