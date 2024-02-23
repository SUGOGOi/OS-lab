#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg)
{
    printf("Hello World\n");
    pthread_exit(NULL);
}

int main()
{
    pthread_t thread_id; // thread id
    int ret;

    // create a new thread
    ret = pthread_create(&thread_id, NULL, thread_function, NULL);

    if (ret != 0)
    {
        // if thread creation fails
        fprintf(stderr, "Error\n");
        exit(EXIT_FAILURE);
    }

    ret = pthread_join(thread_id, NULL);

    if (ret != 0)
    {
        fprintf(stderr, "Error");
        exit(EXIT_FAILURE);
    }

    return 0;
}