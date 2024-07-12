#include "kernel/types.h"
#include "user/user.h"
#include <sys/time.h>

// Excercise 1.6 Ping Pong a byte in two pipes
// Date: 20240711

int main(int argc, char *argv[]) {
    int p1[2], p2[2];
    char byte = '0';
    uint start_time, end_time;
    uint exchanges = 10000;

    argv[0] = "pingpong";
    argv[argc+1] = 0;
    argc--;


    if (argc > 0) {
        exchanges = atoi(argv[argc]);
    }

    printf("Using # of exchanges in pipes: %d\n", exchanges);

    // Create two pipes
    pipe(p1); // Parent to child
    pipe(p2); // Child to parent

    close(0);
    start_time = uptime();

    // Fork child process
    int pid = fork();

    if (pid == 0) {
        // Child process do work
        close(p1[1]);
        close(p2[0]);
        printf("Child PID: %d\n", getpid());
        for (int i = 0; i < exchanges; i++) {
            write(p1[0], &byte, 1); // Send byte to parent
            read(p2[1], &byte, 1); // Read byte back from parent
        }

        close(p1[0]);
        close(p2[1]);
        exit(0);
    } else if (pid > 0) {
        // Parent process
        close(p1[0]);
        close(p2[1]);
        wait(0);
        printf("Parent PID: %d\n", getpid());

        for (int i = 0; i < exchanges; i++) {
            write(p1[1], &byte, 1); // Send byte to child
            read(p2[0], &byte, 1); // Read byte back from child
        }

        close(p1[1]);
        close(p2[0]);
    } else {
        fprintf(2, "Error forking");
        exit(1);
    }
    end_time = uptime();

    uint elapsed_ticks = end_time - start_time;

    printf("Time taken: %d\n", elapsed_ticks);

    if (elapsed_ticks != 0) {
            printf("Exchanges per clock tick: %d\n", (exchanges / elapsed_ticks));
    }
    exit(0);
}