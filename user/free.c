#include "kernel/types.h"
#include "user/user.h"

// Exercise 2.9 Get free memory

int main(int argc, char *argv[])
{
    printf("Free memory: %d bytes\n", freemem());
    exit(0);
}