#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("\nNot passing N in the argument\n");
        exit(1);
    }

    int i = atoi(argv[1]);

    if (i < 1)
    {
        printf("\nInvalid input for N\n");
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        // Child process
        execlp("./fib", "fib", argv[1], NULL);
        perror("execlp failed");
        exit(1);
    }
    else
    {
        // Parent process
        wait(NULL);
        printf("\nChild completed computing Fibonacci\n");

        int shmid = shmget(122, 4096, 0666);
        if (shmid < 0)
        {
            perror("shmget failed");
            exit(1);
        }

        void *smp = shmat(shmid, NULL, 0666);
        if (smp == (void *)-1)
        {
            perror("shmat failed");
            exit(1);
        }

        printf("%s\n", (char *)smp);

        if (shmdt(smp) == -1)
        {
            perror("shmdt failed");
            exit(1);
        }
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <string.h> // For strcat

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("\nNot passing k in the arguments\n");
        exit(1);
    }

    int k = atoi(argv[1]);

    if (k < 1)
    {
        printf("\nError in input\n");
        exit(1);
    }

    int shmid = shmget(122, 4096, 0666 | IPC_CREAT);
    if (shmid < 0)
    {
        perror("shmget failed");
        exit(1);
    }

    void *psm = shmat(shmid, NULL, 0666);
    if (psm == (void *)-1)
    {
        perror("shmat failed");
        exit(1);
    }

    int n1 = 0, n2 = 1, n3;
    char buffer[4096] = {0}; // Buffer to store the Fibonacci sequence

    for (int i = 0; i < k; i++)
    {
        if (i == 0)
        {
            sprintf(buffer, "%d ", n1);
        }
        else if (i == 1)
        {
            sprintf(buffer + strlen(buffer), "%d ", n2);
        }
        else
        {
            n3 = n1 + n2;
            sprintf(buffer + strlen(buffer), "%d ", n3);
            n1 = n2;
            n2 = n3;
        }
    }

    strcpy((char *)psm, buffer); // Copy the buffer content to shared memory

    if (shmdt(psm) == -1)
    {
        perror("shmdt failed");
        exit(1);
    }

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/mman.h>

void append_to_buffer(char *buffer, int *pos, const char *str) {
    while (*str) {
        buffer[*pos] = *str;
        (*pos)++;
        str++;
    }
    buffer[*pos] = '\0'; // Null-terminate the string
}

void int_to_str(int num, char *str) {
    int i = 0, j, temp;
    if (num == 0) {
        str[i++] = '0';
    } else {
        while (num > 0) {
            str[i++] = (num % 10) + '0';
            num /= 10;
        }
        // Reverse the string
        for (j = 0; j < i / 2; j++) {
            temp = str[j];
            str[j] = str[i - j - 1];
            str[i - j - 1] = temp;
        }
    }
    str[i] = ' '; // Add a space after the number
    str[i + 1] = '\0'; // Null-terminate the string
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("\nNot passing k in the arguments\n");
        exit(1);
    }

    int k = atoi(argv[1]);

    if (k < 1)
    {
        printf("\nError in input\n");
        exit(1);
    }

    int shmid = shmget(122, 4096, 0666 | IPC_CREAT);
    if (shmid < 0)
    {
        perror("shmget failed");
        exit(1);
    }

    void *psm = shmat(shmid, NULL, 0666);
    if (psm == (void *)-1)
    {
        perror("shmat failed");
        exit(1);
    }

    int n1 = 0, n2 = 1, n3;
    char buffer[4096] = {0}; // Buffer to store the Fibonacci sequence
    int pos = 0; // Current position in the buffer

    char num_str[12]; // Buffer to convert integers to strings (assuming 32-bit int max length)

    for (int i = 0; i < k; i++)
    {
        if (i == 0)
        {
            int_to_str(n1, num_str);
        }
        else if (i == 1)
        {
            int_to_str(n2, num_str);
        }
        else
        {
            n3 = n1 + n2;
            int_to_str(n3, num_str);
            n1 = n2;
            n2 = n3;
        }
        append_to_buffer(buffer, &pos, num_str);
    }

    // Copy the buffer content to shared memory
    char *dest = (char *)psm;
    for (int i = 0; i <= pos; i++) {
        dest[i] = buffer[i];
    }

    if (shmdt(psm) == -1)
    {
        perror("shmdt failed");
        exit(1);
    }

    return 0;
}

