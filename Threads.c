#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

int sumres = 0;
int factres = 1;

void *sum(void *arg)
{
    int n = *((int *)arg);
    for (int i = 1; i <= n; i++)
    {
        sumres += i;
    }
    pthread_exit(NULL);
}

void *fact(void *arg)
{
    int n = *((int *)arg);
    for (int i = 1; i <= n; i++)
    {
        factres *= i;
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);
    pthread_t thread_sum, thread_fact;

    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&thread_sum, &attr, sum, &n);
    pthread_create(&thread_fact, &attr, fact, &n);

    pthread_join(thread_sum, NULL);
    pthread_join(thread_fact, NULL);

    printf("SUM = %d\n", sumres);
    printf("FACTORIAL = %d\n", factres);
    return 0;
}
