#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct p
{
    int n, data[30];
} pack;

void main()
{
    int shmid;
    shmid = shmget(112, 4096, 0666);
    printf("The key is %d", shmid);
    pack *psm = (pack *)shmat(shmid, NULL, 0666);
    if (psm == (pack *)-1)
    {
        perror("shmat failed");
        exit(1);
    }
    printf("The attachment address is: %p\n", (void *)psm);

    printf("Enter a number");
    scanf("%d", &psm->n);
    pid_t child = fork();
    if (child < 0)
    {
        printf("Error");
        exit(1);
    }
    else if (child == 0)
        execlp("./odd", "./odd", NULL);
    else
    {
        wait(NULL);
        printf("Child process has finished its execution");
        printf("\nThe first n odd no.s are");
        for (int i = 0; i < psm->n; i++)
            printf("%d", psm->data[i]);
        shmdt((void *)psm);
        shmctl(shmid, IPC_RMID, NULL);
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct p
{
    int n, data[30];
} pack;

int main()
{
    int shmid;

    shmid = shmget(112, 4096, 0666 | IPC_CREAT);
    if (shmid < 0)
    {
        perror("shmget failed");
        exit(1);
    }

    pack *psm = (pack *)shmat(shmid, NULL, 0666);
    if (psm == (pack *)-1)
    {
        perror("shmat failed");
        exit(1);
    }

    for (int i = 0; i < psm->n; i++)
    {
        psm->data[i] = 2 * i + 1;
    }
    if (shmdt((void *)psm) == -1)
    {
        perror("shmdt failed");
        exit(1);
    }

    return 0;
}
