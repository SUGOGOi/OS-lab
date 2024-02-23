#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void sigint_handler(int signal)
{
    if (signal == SIGINT)
    {
        __pid_t child = fork();
        if (child < 0)
        {
            perror("fork");
            exit(1);
        }
        else if (child == 0)
        {
            printf("\nChild Process: PID=%d, PPID=%d\n", getpid(), getppid());
            exit(EXIT_SUCCESS);
        }
        else
        {
            wait(NULL);
            printf("\nParent Process: PID=%d, PPID=%d\n", getpid(), getppid());
        }
    }
}

int main()
{
    if (signal(SIGINT, sigint_handler) == SIG_ERR)
    {
        perror("signal");
        exit(EXIT_FAILURE);
    }
    printf("Press Ctrl+C for SIGINT\n");
    while (1)
    {
    }

    return 0;
}