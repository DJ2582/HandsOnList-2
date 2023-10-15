/*
============================================================================
Name : 24.c
Author : Darshit Jakhaniya
Description : Write a program to create a message queue and print the key and message queue id.
Date:1st oct,2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

int main() {
    key_t key;
    int msqid;

    // Generate a unique key using ftok
    if ((key = ftok(".", 'A')) == -1)
     {
        perror("ftok");
    }

    // Create a message queue with the generated key
    if ((msqid = msgget(key, IPC_CREAT | 0764)) == -1) {
        perror("error in creating Message Queue");
    }

    printf("Message Queue Key: 0x%x\n", key);
    printf("Message Queue ID: %d\n", msqid);

    return 0;
}
