#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define MAX_MEM 1024

void consume(char *memory) {
    while(1) {
        /* For printing purposes, we need to null the last byte of the memory */
        memory[MAX_MEM - 1] = '\0';

        printf("Memory:\n%s\n", memory);

        /* If we see "end" in the buffer, stop reading */
        if(0 == strncmp(memory, "end", 3)) {
            return;
        }

        /* Flush the buffer just in case and then pause */
        fflush(stdout);
        sleep(1);
    }
}

void produce(char *memory) {
    while(0 != strncmp(memory, "end", 3)) {
        /* Get data from stdin */
        fgets(memory, MAX_MEM, stdin);

        /* Syncs the data into memory */
        msync(memory, MAX_MEM, MS_SYNC);

    }
}

int main(int argc, char **argv) {
    int fd = 0;
    char *memory = NULL;

    if(argc != 3) {
        fprintf(stderr, "Usage: %s <file> [r] | [w]\n", argv[0]);
    }

    /* Open the specified file.
    * No error checking done here for simplicity.
    * Open read/write/create
    */
    fd = open(argv[argc - 2], O_RDWR | O_CREAT);
    if(fd < 0) {
        fprintf(stderr, "[!] Unable to open file: %s\n", argv[1]);
        return -1;
    }

    /* Map at most MAX_MEM bytes from the file into shared memory */
    memory = mmap(NULL, MAX_MEM, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(MAP_FAILED == memory) {
        fprintf(stderr, "[!] Failed to map memory space for file\n");
        return -1;
    }

    /* No longer needs to be open since it's mapped into memory */
    close(fd);

    /* Consumer */
    if(0 == strcmp(argv[argc - 1], "r")) {
       consume(memory);
    }

    /* Producer */
    if(0 == strcmp(argv[argc - 1], "w")) {
        produce(memory);
    }



    return 0;
}