#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t child_pid, my_pid, parent_pid;
    child_pid = fork();

    if (child_pid < 0)
    {
        printf("\nFork failed, exiting...\n");
        exit(1);
    }

    if (child_pid == 0)
    {
        printf("\n[CHILD]This is the child process\n");
        my_pid = getpid();
        parent_pid = getppid();
        printf("\n[CHILD]My pid is %d\n", my_pid);
        printf("\n[CHILD]My parent's pid is %d\n", parent_pid);
        printf("\n[CHILD]Sleeping for 10 seconds\n");
        sleep(10);
        printf("\n[CHILD]My parent has ended, so I am an orphan process adopted by init process\n");
        exit(0);
    }
    else
    {
        printf("\n[PARENT]This is the parent process\n");
        my_pid = getpid();
        parent_pid = getppid();
        printf("\n[PARENT]My pid is %d\n", my_pid);
        printf("\n[PARENT]My parent's pid is %d\n", parent_pid);
        printf("\n[PARENT]Exiting...\n");
        exit(0);
    }

    return 0;
}
