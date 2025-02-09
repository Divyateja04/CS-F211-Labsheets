#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

void *PrintStars(void *arg)
{
    intptr_t thr = (intptr_t)arg;
    for (int i = 0; i < thr; i++)
    {
        printf("*");
    }
    printf("\n");
    pthread_exit(NULL);
}

int main()
{
    pthread_t thread_id[5] = {0};

    for (int i = 0; i < 5; i++)
    {
        printf("Creating thread %ld...\n", thread_id[i]);
    }

    printf("Equality: %d\n", pthread_equal(thread_id[0], thread_id[1]));

    for (int i = 0; i < 5; i++)
    {
        printf("Creating thread %d...\n", i);
        int status = pthread_create(&thread_id[i], NULL, PrintStars, (void *)((intptr_t)i));
        printf("Thread %d created returning status: %d --> %ld\n", i, status, thread_id[i]);
        if (status)
        {
            printf("Error: Unable to create thread: %d due to %d\n", i, status);
            exit(-1);
        }
    }

    printf("Equality: %d\n", pthread_equal(thread_id[0], thread_id[1]));

    for (int i = 0; i < 5; i++)
    {
        pthread_join(thread_id[i], NULL);
    };

    return 0;
}