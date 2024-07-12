#include "kernel/types.h"
#include "kernel/riscv.h"
#include "kernel/param.h"
#include "kernel/spinlock.h"
#include "kernel/proc.h"
#include "user/user.h"

int main()
{
    char *ptr;
    struct proc *p = myproc();

    fprintf(1, "Before sbrk(1):\n");
    fprintf(1, "Current break: %p\n", sbrk(0));

    printf("Page table address: %p\n", &(p->pagetable));

    ptr = sbrk(1);
    if (ptr == (char *)-1)
    {
        fprintf(2, "sbrk failed\n");
        exit(1);
    }

    fprintf(1, "After sbrk(1):\n");
    fprintf(1, "New break: %p\n", sbrk(0));

    fprintf(1, "Value at allocated address: %c\n", *ptr);
    printf("Page table address: %p\n", &(p->pagetable));

    exit(0);
}

// int main(int argc, char *argv[])
// {
//     printf("size");

//     struct proc *p = myproc();
//     // pagetable_t pagetable_before, pagetable_after;

//     // _pteprint(p->pagetable, 1);

//     int size = p->sz;

//     printf("%d\n", size);
//     sbrk(1);

//     // _pteprint(p->pagetable, 1);
// }