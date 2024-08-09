#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    pid_t child;
    if (argc < 2)
    {
        printf("Not passing n as an argument\n");
        exit(1);
    }
    if (atoi(argv[1]) < 1)
    {
        printf("Invalid argument\n");
        exit(1);
    }

    child = fork();
    if (child < 0)
    {
        printf("Error executing fork\n");
        exit(1);
    }

    if (child == 0)
    {
        execl("./fib", "./fib", argv[1], NULL);
        printf("Error executing execl\n");
        exit(1); // Execl only returns if there's an error
    }
    else
    {
        wait(NULL);
        printf("\nChild finished generating\n");

        int shmid = shm_open("FIB", O_RDONLY, 0666);
        if (shmid == -1)
        {
            perror("shm_open");
            exit(1);
        }

        void *psm = mmap(0, 4096, PROT_READ, MAP_SHARED, shmid, 0);
        if (psm == MAP_FAILED)
        {
            perror("mmap");
            exit(1);
        }

        printf("%s", (char *)psm);

        // Unlink the shared memory
        shm_unlink("FIB");
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Not passing N\n");
        exit(1);
    }

    int n1 = 0, n2 = 1, n3;
    int k = atoi(argv[1]);

    int shmid = shm_open("FIB", O_CREAT | O_RDWR, 0666);
    if (shmid == -1)
    {
        perror("shm_open");
        exit(1);
    }

    ftruncate(shmid, 4096);
    void *psm = mmap(0, 4096, PROT_WRITE, MAP_SHARED, shmid, 0);
    if (psm == MAP_FAILED)
    {
        perror("mmap");
        exit(1);
    }

    char buffer[50];
    for (int i = 0; i < k; i++)
    {
        n3 = n1 + n2;
        sprintf(buffer, "%d ", n1);
        strcpy(psm, buffer);
        psm += strlen(buffer); // Move the pointer to the next memory location
        n1 = n2;
        n2 = n3;
    }

    printf("\nGenerated\n");

    return 0;
}
