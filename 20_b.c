/*
============================================================================
Name : 20b.c
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
    char buffer[256];

    // Open the FIFO for reading
    int fd = open("myfifo", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // Read data from the FIFO
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer));
    if (bytesRead == -1) {
        perror("read");
        exit(1);
    }

    // Null-terminate the received data to print it as a string
    buffer[bytesRead] = '\0';

    printf("Reader received: %s\n", buffer);

    close(fd);

    return 0;
}
