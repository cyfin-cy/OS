#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t my_pid, child_pid, parent_pid;
    child_pid = fork();
    if (child_pid < 0)
    {
        printf("Fork failed, Exiting...\n");
        exit(1);
    }

    // child process
    if (child_pid == 0)
    {
        printf("\nThis is the child process!\n");
        my_pid = getpid();
        parent_pid = getppid();
        printf("[CHILD] My pid is %d\n", my_pid);
        printf("[CHILD] MY parent's pid is %d\n", parent_pid);
        printf("[CHILD] Exiting...\n");
        exit(1);
    }
    // parent process

    else
    {
        printf("\nThis is the parent process!\n");
        my_pid = getpid();
        parent_pid = getppid();
        printf("[PARENT] My pid is %d\n", my_pid);
        printf("[PARENT] My parent's pid is %d\n", parent_pid);
        printf("[PARENT] Parent sleeping for 10 seconds\n");
        sleep(10);
        printf("[PARENT] Child process with pid = %d has ended, but still has an entry in the process table.\n", child_pid);
        printf("[PARENT] It is therefore, a ZOMBIE process");
    }

    return 0;
}
