#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

void signal_handler(int signal)
{
    if (signal == SIGINT)
    {
        pid_t child_pid = fork();

        if (child_pid < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (child_pid == 0)
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
    else
    {

        printf("\nReceived: %d\n", signo);
    }
}

int main()
{
    for (int i = 1; i <= 64; ++i)
    {
        if (signal(i, signal_handler) == SIG_ERR)
        {
            if (errno == EINVAL)
            {
                continue;
            }
            perror("signal");
            exit(EXIT_FAILURE);
        }
    }

    printf("Press Ctrl+C or send other signals to test\n");
    while (1)
    {
    }

    return 0;
}